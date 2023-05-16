/*
 * OrderBook.h
 * 
 * Purpose: 
 */

#ifndef __ORDERBOOK__
#define __ORDERBOOK__

#include <map>
#include <unordered_map>
#include "Order.h"
#include "Limit.h"

class OrderBook {
    public:
        OrderBook();
        ~OrderBook();

        void addOrder(const Order &o);
        void cancelOrder(int idNumber);
        // execute or market order?

        // Getters
        int  getVolumeAtLimit(double limitPrice) const;
        int  getBestBid()                     const;
        int  getBestOffer()                   const;

        void print()                          const;
        void printLimit()                     const;

    private:
        void printOrderHelper(const std::list<Order>* listPtr, int columnWidth) const;
        void printLimitHelper(const Limit& limit, int columnWidth)              const;

        std::map<double, Limit, std::greater<double>> *sellSide;
        std::map<double, Limit, std::greater<double>> *buySide;
        std::unordered_map<double, Order> *orders;
        std::unordered_map<double, Limit> *limits;

        Limit *lowestSell;
        Limit *highestBuy;
};

#endif /* __ORDERBOOK__ */