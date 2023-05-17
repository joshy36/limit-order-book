/*
 * Limit.cpp
 * 
 * Purpose: Implementation of the Limit class.
 */

#include "Limit.h"

/*
 * Default constructor.
 */
Limit::Limit(double _limitPrice, double _totalVolume)
{
    limitPrice  = _limitPrice;
    totalVolume = _totalVolume;
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
}

/*
 * setVol
 * Purpose: Set the volume when an order is added or removed.
 * Parameters: A double to change the vol by.
 * Returns: Nothing.
 */
void Limit::setVol(double volDiff)
{
    totalVolume += volDiff;
}
