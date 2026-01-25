#pragma once
#include "MatchingEngine.h"

namespace OrderBookEngine
{

MatchingEngine::MatchingEngine()
{
    m_OrderBook = std::make_shared<OrderBook>();
}

bool MatchingEngine::isPriceMatch(enSIDE side, double marketPrice, double orderPrice)
{
    if (side == enSIDE::Buy)
        return orderPrice >= marketPrice;
    else
        return orderPrice <= marketPrice;
};

void MatchingEngine::matchOrder(HOrder order)
{
    auto book = order->getSide() == enSIDE::Buy ? m_OrderBook->ASKS : m_OrderBook->BIDS;
    while(order->getLeftOverQty() > 0 && !book.empty())
    {
        auto it = book.begin();

        if (!isPriceMatch(order->getSide(), it->first, order->getPrice()))
        {
            break;
        }

        matchLevel(order, it->second, book, it);
    }
}

void MatchingEngine::matchLevel(HOrder incoming, PriceLevel& level, BookType& book, IteratorType it)
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

void MatchingEngine::storeOrderToDealBook(HOrder order)
{

}

void MatchingEngine::onNewOrder(HOrder order)
{
    // Invalid order
    if (!order || !order->isValid()) 
        return;

    // Already received order with same ID
    auto itr = m_OrderBook->lookup.find(order->getOrderId());
    if (itr != m_OrderBook->lookup.end())
        return;

    if (order->getSide() == Buy)
        matchBuyOrder(order);
    else
        matchSellOrder(order);

    if (!order->isFullyFilled())
    {
        // Add remaining order to order book
        storeOrderToDealBook(order);
    }
}

}