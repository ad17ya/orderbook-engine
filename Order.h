#pragma once
#include <cstdint>

namespace OrderBookEngine
{

enum Side { Buy, Sell };

struct Order
{
    uint64_t m_orderId;
    uint64_t m_priceTicks;
    uint64_t m_qty;
    Side m_side;
    Order* next;
    Order* prev;

    Order(uint64_t orderId, uint64_t priceTicks, uint64_t qty, Side side)
        : m_orderId(orderId), m_priceTicks(priceTicks), m_qty(qty), m_side(side), next(nullptr), prev(nullptr)
    {}
};

}