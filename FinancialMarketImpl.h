#ifndef FINANCIALMARKET_IMPL_H_
#define FINANCIALMARKET_IMPL_H_


#include <cstdint>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "FinancialMarket.h"
#include "Order.h"


class FinancialMarketImpl : public FinancialMarket
{
private:
    uint64_t m_orderUniqueId;
    std::map<std::string, Order> m_placedOrders;

    bool setOrderActiveStatus(const std::string& orderId, bool active);


public:
    /**
     * Instantiates a new Financial Market
     */
    FinancialMarketImpl();

    virtual std::optional<std::string> createOrder(const std::string& productId, OrderVerb verb, double price, double quantity);

    virtual bool modifyOrder(const std::string& orderId, double newPrice, double newQty);

    virtual bool deleteOrder(const std::string& orderId);

    virtual std::optional<Order> getOrder(const std::string& orderId) const;

    virtual bool suspendOrder(const std::string& orderId);

    virtual bool reactivateOrder(const std::string& orderId);

    virtual std::vector<Order> getAllOrdersSortedByPrice(const std::string& productId, OrderVerb verb) const;

    virtual std::vector<Order> getOrdersAtBestLevel(const std::string& productId, OrderVerb verb) const;

    virtual double getCumulativeQuantityAtBestLevel(const std::string& productId, OrderVerb verb) const;
};

#endif //FINANCIALMARKET_IMPL_H_
