#include <cstdint>
#include <memory>

namespace OrderBookEngine
{

enum enSIDE { Buy, SELL };
typedef std::shared_ptr<Order> HOrder;

class Order
{
private:
    uint64_t m_orderId;
    uint64_t m_qty;
    uint64_t m_filledQty;
    uint64_t m_leftOverQty;
    double m_price;
    enSIDE m_side;

    HOrder next;
    HOrder prev;

public:
    Order(uint16_t orderId, uint64_t qty, double price, enSIDE side)
    : m_orderId(orderId), 
    m_qty(qty), 
    m_filledQty(0),
    m_leftOverQty(qty),
    m_price(price), 
    m_side(side) {};

    ~Order() {};

    // write getters for all private members
    uint64_t getOrderId() const { return m_orderId; }
    uint64_t getQty() const { return m_qty; }
    uint64_t getFilledQty() const { return m_filledQty; }
    uint64_t getLeftOverQty() const { return m_leftOverQty; }
    double getPrice() const { return m_price; }
    enSIDE getSide() const { return m_side; }

    void setPrice(double price) { m_price = price; }
    void setFilledQty(uint64_t qty) { m_filledQty = qty; }
    void setLeftOverQty(uint64_t qty) { m_leftOverQty = qty; }

    bool isValid() const 
    { 
        return m_qty > 0 && m_price > 0; 
    }

    bool isFullyFilled() const
    {
        return m_filledQty == m_qty;
    }
};

}