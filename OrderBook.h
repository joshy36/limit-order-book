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

        void addOrder(Order &o);
        void cancelOrder(int idNumber);
        // execute or market order?

        // Getters
        int getVolumeAtLimit(int limitPrice) const;
        int getBestBid() const;
        int getBestOffer() const;

    private:
        std::map<int, Limit> *buySide;
        std::map<int, Limit, std::greater<int>> *sellSide;
        std::unordered_map<int, Order> *orders;
        std::unordered_map<int, Limit> *limits;

        Limit *lowestSell;
        Limit *highestBuy;
};

#endif /* __ORDERBOOK__ */