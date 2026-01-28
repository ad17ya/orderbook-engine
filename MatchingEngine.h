#pragma once
#include "OrderBook.h"

namespace OrderBookEngine
{

class MatchingEngine
{
private:
    OrderBook* m_OrderBook;
    std::unordered_map<uint64_t, Order*> lookup; // order id to order map

    void matchLevel(Order* incoming, PriceLevel& level, T& book, Iter it)
    {
        while (incoming->getLeftOverQty() > 0 && !level.empty())
        {
            Order* resting = level.headOrder;
            uint64_t execs = std::min(incoming->getLeftOverQty(), resting->getLeftOverQty());

            incoming->addExecs(execs);
            resting->addExecs(execs);

            if (resting->getLeftOverQty() == 0)
            {
                level.removeOrder(resting);
                lookup.erase(resting->getOrderId());
            }
        }

        if (level.empty())
        {
            book.erase(it);
        }
    }

    void matchOrder(Order* order, T& book)
    {
        while(order->getLeftOverQty() > 0 && !book.empty())
        {
            auto it = book.begin();
            if (!isPriceMatch(order->getSide(), it->first, order->getPrice()))
                break;

            matchLevel(order, it->second, book, it);
        }
    }

    void storeOrderToDealBook(Order*) {};

    bool isPriceMatch(enSIDE side, double marketPrice, double orderPrice)
    {
        if (side == enSIDE::Buy)
            return orderPrice >= marketPrice;
        else
            return orderPrice <= marketPrice;
    }

public:
    MatchingEngine() 
    {
        m_OrderBook = std::make_shared<OrderBook>();
    };

    void onNewOrder(Order* order)
    {
        // Invalid order
        if (!order || !order->isValid()) 
            return;

        // Already received order with same ID
        auto itr = lookup.find(order->getOrderId());
        if (itr != lookup.end())
            return;

        lookup.insert({order->getOrderId(), order});
        
        if (order->getSide() == enSIDE::Buy)
            matchOrder(order, m_OrderBook->Asks);
        else
            matchOrder(order, m_OrderBook->Bids);

        if (!order->isFullyFilled())
        {
            // Add remaining order to order book
            storeOrderToDealBook(order);
        }
    }
};

} // namespace OrderBookEngine
