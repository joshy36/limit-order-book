/*
 * Order.h
 * 
 * Purpose: 
 */

#ifndef __ORDER__
#define __ORDER__

#include "Limit.h"

struct Order {
    int       idNumber;
    enum      OrderType { BUY, SELL };
    OrderType buyOrSell;
    double    shares;
    double    limit;
    int       entryTime;
    int       eventTime;
    // Limit *parentLimit;

    Order(int       _idNumber,
          OrderType _type,
          double    _shares,
          double    _limit,
          int       _entryTime,
          int       _eventTime) :
        //   Limit      *_parentLimit) : 
          idNumber  (_idNumber),
          buyOrSell (_type),
          shares    (_shares),
          limit     (_limit),
          entryTime (_entryTime),
          eventTime (_eventTime) {}
        //   parentLimit(_parentLimit) {}
};

#endif /* __ORDER__ */