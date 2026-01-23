#pragma once

#include <cstdint>
#include <memory>
#include "Order.h"

namespace OrderBookEngine
{

typedef std::shared_ptr<class PriceLevel> HPriceLevel;

class PriceLevel
{
public:
    bool empty() const
    {
        return head_order == nullptr;
    }

    void push_back(HOrder order)
    {
        if (empty())
        {
            head_order = order;
            tail_order = order;
        }
        else
        {
            tail_order->setNext(order);
            order->setPrev(tail_order);
            tail_order = order;
        }
    }

    void remove(HOrder order)
    {
        HOrder prev = order->getPrev();
        HOrder next = order->getNext();

        if (prev)
            prev->setNext(next);
        else
            head_order = next;

        if (next)
            next->setPrev(prev);
        else
            tail_order = prev;

        order->setPrev(nullptr);
        order->setNext(nullptr);
    }


private:
    HOrder head_order;
    HOrder tail_order;
};


}