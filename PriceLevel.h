#pragma once

#include "Order.h"

namespace OrderBookEngine
{

struct PriceLevel
{
    HOrder headOrder = nullptr;
    HOrder tailOrder = nullptr;

    bool empty()
    {
        return headOrder == nullptr;
    }

    void addOrder(HOrder order)
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

    void removeOrder(HOrder order)
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