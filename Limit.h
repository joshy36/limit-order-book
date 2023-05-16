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

    Limit(int _limitPrice, int _size) :
      limitPrice (_limitPrice),
      size       (_size),
      totalVolume(0),
      orders(new std::list<Order>) {}

    // ~Limit()
    // {
    //   delete orders;
    // }

};

#endif /* __LIMIT__ */