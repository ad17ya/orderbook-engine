#include <iostream>

#include "MatchingEngine.h"

using namespace OrderBookEngine;

int main()
{
    MatchingEngine engine;

    // Order ID, Price, Qty, Side
    Order* o1 = new Order(1, 103, 70, Side::Buy);
    Order* o2 = new Order(2, 103, 30, Side::Sell);
    Order* o3 = new Order(3, 104, 200, Side::Buy);
    Order* o4 = new Order(4, 105, 800, Side::Sell);
    Order* o5 = new Order(5, 104, 150, Side::Sell);

    engine.onNewOrder(o1);
    engine.printOrderBook();

    engine.onNewOrder(o2);
    engine.printOrderBook();

    engine.onNewOrder(o3);
    engine.printOrderBook();

    engine.onNewOrder(o4);
    engine.printOrderBook();

    engine.onNewOrder(o5);
    engine.printOrderBook();

    return 0;
}