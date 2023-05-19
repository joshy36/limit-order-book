/*
 * Order.h
 * 
 * Purpose: Interface for the Order class.
 */

#ifndef __ORDER__
#define __ORDER__

#include "Limit.h"

class Order {
    public:
        enum  OrderType { BUY, SELL };

        Order(int _idNumber, OrderType buyOrSell, double _shares, 
              double _limit, int _entryTime, int _eventTime);
        ~Order();

        bool operator==(const Order& other) const;

        int       getIdNumber()  const;
        OrderType getBuyOrSell() const;
        double    getShares()    const;
        double    getLimit()     const;
        int       getEntryTime() const;
        int       getEventTime() const;
        
    private:
        int       idNumber;
        OrderType buyOrSell;
        double    shares;
        double    limit;
        int       entryTime;
        int       eventTime;
    //  Limit *parentLimit;
};

#endif /* __ORDER__ */