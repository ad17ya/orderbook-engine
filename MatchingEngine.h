#pragma once
#include "OrderBook.h"

namespace OrderBookEngine
{

template <typename BookType = std::map<double, PriceLevel>, typename IteratorType = typename BookType::iterator>

class MatchingEngine
{
private:
    HOrderBook m_OrderBook;
    std::unordered_map<uint64_t, HOrder> lookup; // order id to order map

    template<typename T, typename Iter>
    void matchLevel(HOrder incoming, PriceLevel& level, T& book, Iter it)
    {
        while (incoming->getLeftOverQty() > 0 && !level.empty())
        {
            HOrder resting = level.headOrder;
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

    template<typename T>
    void matchOrder(HOrder order, T& book)
    {
        while(order->getLeftOverQty() > 0 && !book.empty())
        {
            auto it = book.begin();
            if (!isPriceMatch(order->getSide(), it->first, order->getPrice()))
                break;

            matchLevel(order, it->second, book, it);
        }
    }

    void storeOrderToDealBook(HOrder) {};

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

    void onNewOrder(HOrder order)
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
            matchOrder(order, m_OrderBook->ASKS);
        else
            matchOrder(order, m_OrderBook->BIDS);

        if (!order->isFullyFilled())
        {
            // Add remaining order to order book
            storeOrderToDealBook(order);
        }
    }
};

} // namespace OrderBookEngine
