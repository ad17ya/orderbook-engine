#pragma once
#include <map>
#include <unordered_map>

#include "PriceLevel.h"

namespace OrderBookEngine
{

struct OrderBook
{
    // Price -> PriceLevel
    std::map<uint64_t, PriceLevel, std::greater<uint64_t>> Bids;
    std::map<uint64_t, PriceLevel, std::less<uint64_t>> Asks;
};
    
}