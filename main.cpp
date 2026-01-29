#include "MatchingEngine.h"

using namespace OrderBookEngine;

int main()
{
    MatchingEngine engine;

    // Order ID, Qty, Price, Side
    Order* o1 = new Order(1, 50, 103.30, Side::Buy);
    Order* o2 = new Order(2, 58, 103.33, Side::Buy);
    Order* o3 = new Order(3, 43, 103.29, Side::Sell);

    engine.onNewOrder(o1);
    engine.onNewOrder(o2);
    engine.onNewOrder(o3);

    return 0;
}