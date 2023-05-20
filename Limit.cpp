/*
 * Limit.cpp
 * 
 * Purpose: Implementation of the Limit class.
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
 * Destructor to free allocated memory.
 */
Limit::~Limit()
{
    delete orders;
}

/*
 * equal to operator overload
 * Purpose: Determine whether two limits are equal.
 * Parameters: A const Limit reference.
 * Returns: A boolean value that is true iff the Limit instances are the same.
 */
bool Limit::operator==(const Limit& other) const {
    return limitPrice == other.limitPrice;
}

/*
 * getter functions
 * Purpose: Provides access to get private data members.
 * Parameters: None.
 * Returns: Desired data member.
 */
double Limit::getPrice() const
{
    return limitPrice;
}

double Limit::getVol() const
{
    return totalVolume;
}

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
    totalVolume += o.getShares();
}

/*
 * removeOrder
 * Purpose: Remove an order from a limit.
 * Parameters: A const reference to the order to remove.
 * Returns: Nothing.
 */
void Limit::removeOrder(const Order &o)
{
    orders->remove(o);
    totalVolume -= o.getShares();
}