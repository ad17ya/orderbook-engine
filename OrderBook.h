#pragma once

#include <iostream>
#include <map>
#include <memory>
#include "PriceLevel.h"

namespace OrderBookEngine
{

typedef std::shared_ptr<OrderBook> HOrderBook;

struct OrderBook
{
    std::map<double, HPriceLevel, std::greater<double>> buy_levels;
    std::map<double, HPriceLevel> sell_levels;
};

}