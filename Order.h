#pragma once
#include <cstdint>
#include <memory>

namespace OrderBookEngine
{

enum Side { Buy, Sell };

struct Order
{
private:
    uint64_t m_orderId;
    uint64_t m_qty;
    uint64_t m_price;
    Side m_side;
    Order* next;
    Order* prev;

    Order(uint64_t id, Side side, int64_t priceTicks, uint64_t qty) : 
        m_orderId(id), m_side(side), m_price(priceTicks), m_qty(qty), next(nullptr), prev(nullptr) 
    {}
};

}