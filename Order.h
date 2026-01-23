#pragma once
#include <cstdint>
#include <memory>

namespace OrderBookEngine
{

enum class Side
{
    SIDE_BUY,
    SIDE_SELL
};

typedef std::shared_ptr<Order> HOrder;

class Order
{
public:
    Order(uint64_t order_id, Side side, double price, uint32_t qty)
        : order_id(order_id), side(side), price(price), qty(qty), prev(nullptr), next(nullptr)
    {
    }

    uint64_t getOrderId() const { return order_id; }
    Side getSide() const { return side; }
    double getPrice() const { return price; }
    uint32_t getQty() const { return qty; }

    void setPrev(HOrder p) { prev = p; }
    HOrder getPrev() const { return prev; }

    void setNext(HOrder n) { next = n; }
    HOrder getNext() const { return next; }

private:
    uint64_t order_id;
    Side side;
    double price;
    uint32_t qty;

    HOrder prev;
    HOrder next;
}

}