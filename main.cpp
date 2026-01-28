#include "MatchingEngine.h"

using namespace OrderBookEngine;

int main()
{
    MatchingEngine engine;

    // Order ID, Qty, Price, Side
    Order* o1 = std::make_unique<Order>(1, 90, 103.14, enSIDE::Buy);
    Order* o2 = std::make_unique<Order>(2, 58, 103.33, enSIDE::Buy);
    Order* o3 = std::make_unique<Order>(3, 43, 103.29, enSIDE::Sell);

    engine.onNewOrder(o1);
    engine.onNewOrder(o2);
    engine.onNewOrder(o3);

    return 0;
}