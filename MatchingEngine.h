#pragma once
#include "OrderBook.h"

namespace OrderBookEngine
{
template<typename BookType, typename IteratorType>;

class MatchingEngine
{
private:
    HOrderBook m_OrderBook;
    std::unordered_map<uint64_t, HOrder> lookup; // order id to order map

    MatchingEngine();

    void matchOrder(HOrder order);
    void storeOrderToDealBook(HOrder order);

    bool isPriceMatch(enSIDE side, double marketPrice, double orderPrice);
    void matchLevel(HOrder order, PriceLevel& level, BookType& book, IteratorType it);

public:

    void onNewOrder(HOrder order)
};

};