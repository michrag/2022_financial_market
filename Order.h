#ifndef ORDER_H_
#define ORDER_H_

#include <string>

#include "OrderVerb.h"


/**
 An Order represents the intention to buy or sell a given quantity of a certain product at a specified price.
 */
class Order
{
private:
    std::string _orderId;
    double _quantity;
    double _price;
    std::string _productId;
    OrderVerb _verb;
    bool _active;


public:
    //NOTE: feel free to implement one or more additional constructors, if you need them

    Order(): _orderId(""),
        _quantity(-1.0),
        _price(-1.0),
        _productId(""),
        _verb(OrderVerb::BUY),
        _active(false)
    {

    }

    Order(const std::string& orderId,
          double quantity,
          double price,
          const std::string& productId,
          OrderVerb verb,
          bool active) : _orderId(orderId),
        _quantity(quantity),
        _price(price),
        _productId(productId),
        _verb(verb),
        _active(active) {}

    bool operator < (const Order& order) const
    {
        return (_price < order._price);
    }

    bool operator > (const Order& order) const
    {
        return (_price > order._price);
    }

    /**
     @return the Unique identifier of the Order
     */
    std::string getId() const;

    /**
     @return the current quantity of the Order
     */
    double getQty() const;

    void setQty(double quantity);

    /**
     @return the current price of the Order
     */
    double getPrice() const;

    void setPrice(double price);

    /**
     @return the product which the Order was placed on
     */
    std::string getProductId() const;

    /**
     @return the Verb of the Order
     */
    OrderVerb getVerb() const;

    /**
     @return
     - true: if the Order is currently active on the Financial Market
     - false: if the Order is currently suspended on the Financial Market
     */
    bool isActive() const;

    void setActive(bool active);
};

#endif //ORDER_H_
