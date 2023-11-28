#include "FinancialMarketImpl.h"

#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>


FinancialMarketImpl::FinancialMarketImpl()
{
    m_orderUniqueId = 0;
}


std::optional<std::string> FinancialMarketImpl::createOrder(const std::string& productId, OrderVerb verb, double price, double quantity)
{
    if(quantity < 0) // quantity cannot be negative
    {
        return std::nullopt;
    }

    if((m_placedOrders.size() == m_placedOrders.max_size()) || (m_orderUniqueId == std::numeric_limits<uint64_t>::max()))
    {
        return std::nullopt;
    }

    std::string orderIdAsString = std::to_string(m_orderUniqueId);
    bool orderIsActive = true;

    Order order(orderIdAsString, quantity, price, productId, verb, orderIsActive);

    m_placedOrders[orderIdAsString] = order;

    m_orderUniqueId++;

    return orderIdAsString;
}


bool FinancialMarketImpl::modifyOrder(const std::string& orderId, double newPrice, double newQty)
{
    if(m_placedOrders.find(orderId) == m_placedOrders.end())
    {
        return false;
    }

    m_placedOrders.at(orderId).setPrice(newPrice);
    m_placedOrders.at(orderId).setQty(newQty);

    return true;
}


bool FinancialMarketImpl::deleteOrder(const std::string& orderId)
{
    const auto& it = m_placedOrders.find(orderId);

    if(it == m_placedOrders.end())
    {
        return false;
    }

    m_placedOrders.erase(it);

    return true;
}


std::optional<Order> FinancialMarketImpl::getOrder(const std::string& orderId) const
{
    if(m_placedOrders.find(orderId) == m_placedOrders.end())
    {
        return std::nullopt;
    }

    return m_placedOrders.at(orderId);
}


bool FinancialMarketImpl::suspendOrder(const std::string& orderId)
{
    return setOrderActiveStatus(orderId, false);
}


bool FinancialMarketImpl::reactivateOrder(const std::string& orderId)
{
    return setOrderActiveStatus(orderId, true);
}


bool FinancialMarketImpl::setOrderActiveStatus(const std::string& orderId, bool active)
{
    const auto& it = m_placedOrders.find(orderId);

    if(it == m_placedOrders.end())
    {
        return false;
    }

    it->second.setActive(active);

    return true;
}


std::vector<Order> FinancialMarketImpl::getAllOrdersSortedByPrice(const std::string& productId, OrderVerb verb) const
{
    std::vector<Order> result;

    for(const auto& order : m_placedOrders)
    {
        if((order.second.getProductId() == productId) && (order.second.getVerb() == verb))
        {
            result.push_back(order.second);
        }
    }

    if(verb == OrderVerb::BUY)
    {
        // descending order
        std::sort(result.begin(), result.end(), std::greater<Order>());
    }

    if(verb == OrderVerb::SELL)
    {
        // ascending order
        std::sort(result.begin(), result.end());
    }

    return result;
}


std::vector<Order> FinancialMarketImpl::getOrdersAtBestLevel(const std::string& productId, OrderVerb verb) const
{
    std::vector<Order> orderedOrders = getAllOrdersSortedByPrice(productId, verb);

    std::size_t i = 0;

    while((i < orderedOrders.size()) && !(orderedOrders.at(i).isActive()))
    {
        i++;
    }

    std::vector<Order> result;

    if(i == orderedOrders.size())
    {
        // no active orders
        return result;
    }

    double bestPrice = orderedOrders.at(i).getPrice();

    while(i < orderedOrders.size() && (orderedOrders.at(i).getPrice() == bestPrice))
    {
        if(orderedOrders.at(i).isActive())
        {
            result.push_back(orderedOrders.at(i));
        }

        i++;
    }

    return result;
}


double FinancialMarketImpl::getCumulativeQuantityAtBestLevel(const std::string& productId, OrderVerb verb) const
{
    std::vector<Order> ordersAtBestLevel = getOrdersAtBestLevel(productId, verb);

    double result = 0.0;

    for(const auto& order : ordersAtBestLevel)
    {
        result += order.getQty();
    }

    return result;
}
