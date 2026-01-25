#pragma once
#include <map>
#include <unordered_map>

#include "PriceLevel.h"
namespace OrderBookEngine
{

typedef std::shared_ptr<OrderBook> HOrderBook;
struct OrderBook
{
    // Price -> PriceLevel
    std::map<double, PriceLevel, std::greater<double>> BIDS;
    std::map<double, PriceLevel, std::less<double>> ASKS;
};
    
}