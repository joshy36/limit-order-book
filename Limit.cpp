/*
 * Limit.cpp
 * 
 * Purpose: 
 */

#include "Limit.h"

/*
 * Default constructor.
 */
Limit::Limit(double _limitPrice)
{
    limitPrice  = _limitPrice;
    totalVolume = 0;
    orders      = new std::list<Order>;
}

/*
 * getPrice
 * Purpose: Get the limit price.
 * Parameters: None.
 * Returns: The limit price.
 */
double Limit::getPrice() const
{
    return limitPrice;
}

/*
 * getVol
 * Purpose: Get the limit volume.
 * Parameters: None.
 * Returns: The limit volume.
 */
double Limit::getVol() const
{
    return totalVolume;
}

/*
 * getOrders
 * Purpose: Get the orders at a limit.
 * Parameters: None.
 * Returns: A list of the orders at a limit.
 */
std::list<Order>* Limit::getOrders() const
{
    return orders;
}

/*
 * addOrder
 * Purpose: Add an order to a limit.
 * Parameters: A const reference to the order to add.
 * Returns: Nothing.
 */
void Limit::addOrder(const Order &o)
{
    orders->push_back(o);
}

/*
 * Destructor to free allocated memory.
 */
// Limit::~Limit()
// {
//     delete orders;
// }