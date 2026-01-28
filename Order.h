#pragma once
#include <cstdint>
#include <memory>

namespace OrderBookEngine
{
enum enSIDE { Buy, Sell };

class Order
{
private:
    uint64_t m_orderId;
    uint64_t m_qty;
    uint64_t m_price;
    enSIDE m_side;

public:
    Order* next;
    Order* prev;

    Order(uint16_t orderId, uint64_t qty, uint64_t price, enSIDE side)
    : m_orderId(orderId), 
    m_qty(qty), 
    m_price(price), 
    m_side(side) {};

    ~Order() {};

    // write getters for all private members
    uint64_t getOrderId() const { return m_orderId; }
    uint64_t getQty() const { return m_qty; }
    uint64_t getPrice() const { return m_price; }
    enSIDE getSide() const { return m_side; }

    void setPrice(uint64_t price) { m_price = price; }

    bool isValid() const 
    { 
        return m_qty > 0 && m_price > 0; 
    }

    bool isFullyFilled() const
    {
        return m_filledQty == m_qty;
    }
};

}