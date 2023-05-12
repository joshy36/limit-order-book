/*
 * OrderBook.cpp
 * 
 * Purpose: 
 */
#include <iostream>

#include "OrderBook.h"
#include "Order.h"
#include "Limit.h"

/*
 * Default constructor.
 */
OrderBook::OrderBook()
{
    buySide    = new std::map<int, Limit>;
    sellSide   = new std::map<int, Limit, std::greater<int>>;
    orders     = new std::unordered_map<int, Order>;
    limits     = new std::unordered_map<int, Limit>;
    lowestSell = nullptr;
    highestBuy = nullptr;
}

/*
 * Destructor to free allocated memory.
 */
OrderBook::~OrderBook()
{
    delete buySide;
    delete sellSide;
    delete orders;
    delete limits;
    delete lowestSell;
    delete highestBuy;
}

/*
 * addOrder
 * Purpose: Add an order to the book, either buy or sell side.
 * If order matches an existing order on the book, execute.
 * Parameters: Order to add to book.
 * Returns: Nothing.
 */
void OrderBook::addOrder(Order &o)
{
    try {
        limits->at(o.limit);
        std::cout << "Limit in book, add to linked list instead" << limits->at(o.limit).size << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Add limit to book" << std::endl;
        std::list<Order> orderList;
        orderList.push_back(o);
        Limit l = Limit(o.limit, o.shares, 0, orderList);
        if (o.buyOrSell)
            buySide->insert(std::make_pair(l.limitPrice, l));
        else
            sellSide->insert(std::make_pair(l.limitPrice, l));
    }
}

/*
 * printBook
 * Purpose: Print the order book, used for testing and debugging.
 * Parameters: None.
 * Returns: Nothing.
 */
void OrderBook::print() const
{
    std::cout << "Sell Side\n" << "--------" << std::endl;
    for (const auto& pair : *sellSide) {
        for (auto i : pair.second.orders) {
            std::cout << "Price: "       << i.limit 
                      << ", Id: "        << i.idNumber 
                      << ", Shares: "    << i.shares 
                      << ", Timestamp: " << i.entryTime 
                      << std::endl;
        }
    }
    std::cout << "~~~Spread~~~" << std::endl;
    for (const auto& pair : *buySide) {
        for (auto i : pair.second.orders) {
            std::cout << "Price: "       << i.limit 
                      << ", Id: "        << i.idNumber 
                      << ", Shares: "    << i.shares 
                      << ", Timestamp: " << i.entryTime 
                      << std::endl;
        }
    }
    std::cout << "--------" << "Buy Side\n\n" << std::endl;
}