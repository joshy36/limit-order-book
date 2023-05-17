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

class Limit {
    public:
        Limit(double _limitPrice);
        // ~Limit();

        double            getPrice()  const;
        double            getVol()    const;
        std::list<Order>* getOrders() const;

        void              addOrder(const Order &o);
        void              setVol()    const;
    
    private:
        double           limitPrice;
        double           totalVolume;
        std::list<Order> *orders;
};

#endif /* __LIMIT__ */