/*
 * Order.cpp
 * 
 * Purpose: Implementation of the Order class.
 */

#include "Order.h"

/*
 * Default constructor.
 */
Order::Order(int _idNumber, OrderType _buyOrSell, double _shares, 
             double _limit, int _entryTime, int _eventTime)
{
    idNumber  = _idNumber;
    buyOrSell = _buyOrSell;
    shares    = _shares;
    limit     = _limit;
    entryTime = _entryTime;
    eventTime = _eventTime;
}

/*
 * Destructor to free allocated memory.
 */
Order::~Order()
{
    // Nothing to free.
}

/*
 * equal to operator overload
 * Purpose: Determine whether two orders are equal.
 * Parameters: A const Order reference.
 * Returns: A boolean value that is true iff the Order instances are the same.
 */
bool Order::operator==(const Order& other) const {
    return idNumber == other.idNumber;
}

/*
 * getter functions
 * Purpose: Provides access to get private data members.
 * Parameters: None.
 * Returns: Desired data member.
 */
int Order::getIdNumber() const {
    return idNumber;
}

Order::OrderType Order::getBuyOrSell() const {
    return buyOrSell;
}

double Order::getShares() const {
    return shares;
}

double Order::getLimit() const {
    return limit;
}

int Order::getEntryTime() const {
    return entryTime;
}

int Order::getEventTime() const {
    return eventTime;
}