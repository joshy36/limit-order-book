/*
 * Order.h
 * 
 * Purpose: 
 */

#ifndef __ORDER__
#define __ORDER__

#include "Limit.h"

struct Order {
    int   idNumber;
    // true for buy, false for sell
    bool  buyOrSell;
    int   shares;
    int   limit;
    int   entryTime;
    int   eventTime;
    Order *nextOrder;
    Order *prevOrder;
    Limit *parentLimit;

    Order(int        _idNumber,
          bool       _buyOrSell,
          int        _shares,
          int        _limit,
          int        _entryTime,
          int        _eventTime,
          Order      *_nextOrder,
          Order      *_prevOrder,
          Limit      *_parentLimit) : 
          idNumber   (_idNumber),
          buyOrSell  (_buyOrSell),
          shares     (_shares),
          limit      (_limit),
          entryTime  (_entryTime),
          eventTime  (_eventTime),
          nextOrder  (_nextOrder),
          prevOrder  (_prevOrder),
          parentLimit(_parentLimit) {}
};

#endif /* __ORDER__ */