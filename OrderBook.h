#pragma once
#include <map>
#include <unordered_map>

#include "PriceLevel.h"
namespace OrderBookEngine
{

struct OrderBook
{
    // Price -> PriceLevel
    std::map<double, PriceLevel> BIDS;
    std::map<double, PriceLevel> ASKS;

    std::unordered_map<uint64_t, HOrder> orderIdtoOrderMap;
};
    
}