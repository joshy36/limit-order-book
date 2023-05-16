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
    int              limitPrice;
    int              size;
    int              totalVolume;
    std::list<Order> *orders;

    Limit(int _limitPrice, int _size, int _totalVolume) :
      limitPrice (_limitPrice),
      size       (_size),
      totalVolume(_totalVolume),
      orders(new std::list<Order>()) {}

    // ~Limit()
    // {
    //   delete orders;
    // }

};

#endif /* __LIMIT__ */