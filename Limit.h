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
        Limit(double price, double volume);
        // ~Limit();

        double            getPrice()  const;
        double            getVol()    const;
        std::list<Order>* getOrders() const;

        void              addOrder(const Order &o);
        void              setVol(double volDiff);
        void printVol() const;
    
    private:
        double           limitPrice;
        double           totalVolume;
        std::list<Order> *orders;
};

#endif /* __LIMIT__ */