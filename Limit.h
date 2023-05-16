/*
 * Limit.h
 * 
 * Purpose: 
 */

#ifndef __LIMIT__
#define __LIMIT__

#include <list>
#include "Order.h"

struct Order;

struct Limit {
    double           limitPrice;
    double           totalVolume;
    std::list<Order> *orders;

    Limit(double _limitPrice) :
        limitPrice (_limitPrice),
        totalVolume(0),
        orders(new std::list<Order>) {}

    // ~Limit()
    // {
    //   delete orders;
    // }

};

#endif /* __LIMIT__ */