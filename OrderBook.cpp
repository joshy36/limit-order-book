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
        Limit l = Limit(o.limit, o.shares, 0, &o, &o);
        if (o.buyOrSell)
            buySide->insert(std::make_pair(l.limitPrice, l));
        else
            sellSide->insert(std::make_pair(l.limitPrice, l));
            
    }
    
}