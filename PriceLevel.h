#pragma once

#include "Order.h"

namespace OrderBookEngine
{

struct PriceLevel
{
    Order* headOrder = nullptr;
    Order* tailOrder = nullptr;

    bool empty() const noexcept
    {
        return headOrder == nullptr;
    }

    void addOrder(Order* order) noexcept
    {
        order->next = nullptr;
        order->prev = tailOrder;

        // Price level is empty
        if (tailOrder) 
            tailOrder->next = order;
        else
            headOrder = order;

        tailOrder = order;
    }

    void removeOrder(Order* order) noexcept
    {
        if (order->prev)
            order->prev->next = order->next;
        else
            headOrder = order->next;

        if (order->next)
            order->next->prev = order->prev;
        else
            tailOrder = order->prev;

        order->prev = order->next = nullptr;
    }

};

}