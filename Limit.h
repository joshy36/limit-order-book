/*
 * Limit.h
 * 
 * Purpose: Interface for the Limit class.
 */

#ifndef __LIMIT__
#define __LIMIT__

#include <list>
#include "Order.h"

class Order;

class Limit {
    public:
        Limit(double _limitPrice);
        ~Limit();

        bool operator==(const Limit& other) const;

        double            getPrice()  const;
        double            getVol()    const;
        std::list<Order>* getOrders() const;

        void              addOrder(const Order &o);
        void              removeOrder(const Order &o);
    
    private:
        double           limitPrice;
        double           totalVolume;
        std::list<Order> *orders;
};

#endif /* __LIMIT__ */