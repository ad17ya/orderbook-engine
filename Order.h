#include <cstdint>
#include <memory>

namespace OrderBookEngine
{

enum Side { BUY, SELL };
typedef std::shared_ptr<Order> HOrder;

class Order
{
private:
    uint64_t m_orderId;
    uint64_t m_qty;
    double m_price;
    Side m_side;

    HOrder m_next;
    HOrder prev;

public:
    Order(uint16_t orderId, uint64_t qty, double price, Side side);
    ~Order() {};
};

Order::Order(uint16_t orderId, uint64_t qty, double price, Side side) 
    : m_orderId(orderId), 
    m_qty(qty), 
    m_price(price), 
    m_side(side) {}

}