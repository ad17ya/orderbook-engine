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

            uint64_t tradePriceTicks = resting->m_priceTicks;
            uint64_t buyId  = (incoming->m_side == Side::Buy)
                                ? incoming->m_orderId
                                : resting->m_orderId;
            uint64_t sellId = (incoming->m_side == Side::Sell)
                                ? incoming->m_orderId
                                : resting->m_orderId;

            std::cout << "TRADE "
                << "price=" << tradePriceTicks
                << " qty=" << tradedQty
                << " buyID=" << buyId
                << " sellID=" << sellId
                << "\n";

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

    // For debugging
    void printOrderBook() const
    {
        std::cout << "---------------------\n";
        std::cout << "Order Book:\n";
        std::cout << "Bids:\n";
        for (const auto& [price, level] : m_book.Bids)
        {
            std::cout << " Price: " << price << " Qty: ";
            uint64_t totalQty = 0;
            for (Order* o = level.headOrder; o != nullptr; o = o->next)
                totalQty += o->m_qty;
            std::cout << totalQty << "\n";
        }

        std::cout << "Asks:\n";
        for (const auto& [price, level] : m_book.Asks)
        {
            std::cout << " Price: " << price << " Qty: ";
            uint64_t totalQty = 0;
            for (Order* o = level.headOrder; o != nullptr; o = o->next)
                totalQty += o->m_qty;
            std::cout << totalQty << "\n";
        }
        std::cout << "---------------------\n";
    }
};

} // namespace OrderBookEngine
