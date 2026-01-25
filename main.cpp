#include "MatchingEngine.h"

using namespace OrderBookEngine;

int main()
{
    MatchingEngine engine;

    // Order ID, Qty, Price, Side
    HOrder o1.reset(new HOrder(1, 90, 103.14, enSIDE::Buy));
    HOrder o2.reset(new HOrder(2, 58, 103.33, enSIDE::Buy));
    HOrder o3.reset(new HOrder(3, 43, 103.29, enSIDE::Buy));

    engine.onNewOrder(o1);
    engine.onNewOrder(o2);
    engine.onNewOrder(o3);

    return 0;
}