#pragma once
#include "OrderBook.h"

namespace OrderBookEngine
{

class MatchingEngine
{
private:
    OrderBook m_book;
    std::unordered_map<uint64_t, Order*> lookup; // order id to order map

    void matchLevel(Order* incoming, PriceLevel& level)
    {
        Order* resting = level.headOrder;
        while(incoming->m_qty > 0 && resting != nullptr)
        {
            uint64_t tradedQty = std::min(incoming->m_qty, resting->m_qty);
            incoming->m_qty -= tradedQty;
            resting->m_qty -= tradedQty;

            if (resting->m_qty == 0)
            {
                Order* toRemove = resting;
                resting = resting->next;
                level.removeOrder(toRemove);
                lookup.erase(toRemove->getOrderId());
            }
        }
    }

    void matchBuyOrder(Order* order)
    {
        auto& asks = m_book.Asks;
        while (order->m_qty > 0 && !asks.empty())
        {
            auto itr = asks.begin();
            if (order->m_price < itr->first) break;
            matchLevel(order, itr->second);
            if (itr->second.empty())
                asks.erase(itr);
        }
    }

    void matchSellOrder(Order* order)
    {
        auto& bids = m_book.Bids;
        while (order->m_qty > 0 && !bids.empty())
        {
            auto itr = bids.begin();
            if (order->m_price > itr->first) break;
            matchLevel(order, itr->second);
            if (itr->second.empty())
                bids.erase(itr);
        }
    }

    void insertOrder(Order* order)
    {
        auto& book = Side::Buy == order->m_side ? m_book.Bids : m_book.Asks;
        book[order->m_price].addOrder(order);
        lookup[order->m_orderId] = order;
    }

public:
    MatchingEngine() {};

    void onNewOrder(Order* order)
    {
        // No validations here, invalid orders should not enter the system
        if (order->m_side == Side::Buy)
            matchBuyOrder(order);
        else
            matchSellOrder(order);

        if (order->m_qty > 0)
            insertOrder(order); 
    }
};

} // namespace OrderBookEngine
