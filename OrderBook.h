/*
 * OrderBook.h
 * 
 * Purpose: Interface for the OrderBook class.
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

        void addOrder(Order *o);
        void cancelOrder(int idNumber);
        // execute or market order?
        void clearBook();

        double getVolumeAtLimit(double limitPrice) const;
        Limit* getBestBid()                        const;
        Limit* getBestOffer()                      const;

        void print()                               const;
        void printLimit()                          const;

    private:
        void printOrderHelper(const std::list<Order>* list, int columnWidth) const;
        void printLimitHelper(const Limit* limit, int columnWidth)           const;

        std::map<double, Limit*, std::greater<double>> *sellSide;
        std::map<double, Limit*, std::greater<double>> *buySide;
        // map from idNumber to order
        std::unordered_map<int, Order*> *orders;
        // map from limitPrice to limit
        std::unordered_map<double, Limit*> *limits;

        Limit *bestBid;
        Limit *bestOffer;
};

#endif /* __ORDERBOOK__ */