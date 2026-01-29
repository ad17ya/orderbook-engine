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
                lookup.erase(toRemove->m_orderId);
            }
        }
    }

    void matchBuyOrder(Order* order)
    {
        auto& asks = m_book.Asks;
        while (order->m_qty > 0 && !asks.empty())
        {
            auto itr = asks.begin();
            if (order->m_priceTicks < itr->first) break;
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
            if (order->m_priceTicks > itr->first) break;
            matchLevel(order, itr->second);
            if (itr->second.empty())
                bids.erase(itr);
        }
    }

    void insertOrder(Order* order)
    {
        if (order->m_side == Side::Buy)
            m_book.Bids[order->m_priceTicks].addOrder(order);
        else
            m_book.Asks[order->m_priceTicks].addOrder(order);

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
