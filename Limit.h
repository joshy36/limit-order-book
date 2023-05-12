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
    int   limitPrice;
    int   size;
    int   totalVolume;
    // Limit *parent;
    // Limit *leftChild;
    // Limit *rightChild;
    std::list<Order> orders;
    // Order *headOrder;
    // Order *tailOrder;

    Limit(int        _limitPrice,
          int        _size,
          int        _totalVolume,
          std::list<Order>  _orders) :
        //   Limit      *_parent,
        //   Limit      *_leftChild,
        //   Limit      *_rightChild,
          // Order      *_headOrder,
          // Order      *_tailOrder) : 
          limitPrice (_limitPrice),
          size       (_size),
          totalVolume(_totalVolume),
        //   parent     (_parent),
        //   leftChild  (_leftChild),
        //   rightChild (_rightChild),
          orders(_orders) {}
          // headOrder  (_headOrder),
          // tailOrder  (_tailOrder) {}
};

#endif /* __LIMIT__ */