#pragma once
#include <map>
#include <unordered_map>

#include "PriceLevel.h"
#include "OrderBook.h"

namespace OrderBookEngine
{

struct OrderBook
{
    // Price -> PriceLevel
    std::map<double, PriceLevel, std::greater<double>> BIDS;
    std::map<double, PriceLevel, std::less<double>> ASKS;
};

typedef std::shared_ptr<OrderBook> HOrderBook;
    
}