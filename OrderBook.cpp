/*
 * OrderBook.cpp
 * 
 * Purpose: 
 */
#include <iostream>

#include "OrderBook.h"

/*
 * Default constructor.
 */
OrderBook::OrderBook()
{
    sellSide   = new std::map<int, Limit, std::greater<int>>;
    buySide    = new std::map<int, Limit, std::greater<int>>;
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
    delete sellSide;
    delete buySide;
    delete orders;
    delete limits;
}

/*
 * addOrder
 * Purpose: Add an order to the book, either buy or sell side.
 * If order matches an existing order on the book, execute.
 * Parameters: Order to add to book.
 * Returns: Nothing.
 */
void OrderBook::addOrder(const Order &o)
{
    try {
        // check to see if a limit exists at order limit
        limits->at(o.limit);
        std::cout << "Limit in book, add to linked list" << std::endl;
        // insert order into map
        orders->insert(std::make_pair(o.limit, o));
        // update size
        limits->at(o.limit).size += o.shares;
    } catch (const std::out_of_range& e) {
        std::cout << "Add limit to book" << std::endl;
        // create the new limit
        Limit l = Limit(o.limit, o.shares, 0);
        // insert the limit into map, and order into map
        limits->insert(std::make_pair(l.limitPrice, l));
        orders->insert(std::make_pair(o.limit, o));
        if (o.buyOrSell)
            buySide->insert(std::make_pair(l.limitPrice, l));
        else
            sellSide->insert(std::make_pair(l.limitPrice, l));
    }
    // insert order into linked list at corresponding limit
    limits->at(o.limit).orders->push_back(o);
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
        printList(pair.second.orders);
    }
    std::cout << "~~~Spread~~~" << std::endl;
    for (const auto& pair : *buySide) {
        printList(pair.second.orders);
    }
    std::cout << "--------\n" << "Buy Side\n\n" << std::endl;
}

void OrderBook::printList(const std::list<Order>* listPtr) const
{
    for (const Order& i : *listPtr) {
        std::cout << "Price: "       << i.limit 
                  << ", Id: "        << i.idNumber 
                  << ", Shares: "    << i.shares 
                  << ", Timestamp: " << i.entryTime 
                  << std::endl;
    }
}