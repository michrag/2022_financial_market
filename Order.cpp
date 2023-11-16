#include "Order.h"


std::string Order::getId() const
{
    return _orderId;
}


double Order::getQty() const
{
    return _quantity;
}


void Order::setQty(double quantity)
{
    _quantity = quantity;
}


double Order::getPrice() const
{
    return _price;
}


void Order::setPrice(double price)
{
    _price = price;
}


std::string Order::getProductId() const
{
    return _productId;
}


OrderVerb Order::getVerb() const
{
    return _verb;
}


bool Order::isActive() const
{
    return _active;
}


void Order::setActive(bool active)
{
    _active = active;
}
