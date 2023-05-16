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
        int getVolumeAtLimit(int limitPrice) const;
        int getBestBid() const;
        int getBestOffer() const;

        void print() const;
        void printList(const std::list<Order>* listPtr) const;
    private:
        std::map<int, Limit, std::greater<int>> *sellSide;
        std::map<int, Limit, std::greater<int>> *buySide;
        std::unordered_map<int, Order> *orders;
        std::unordered_map<int, Limit> *limits;

        Limit *lowestSell;
        Limit *highestBuy;
};

#endif /* __ORDERBOOK__ */