/*
 * OrderBook.cpp
 * 
 * Purpose: 
 */
#include <iostream>
#include <iomanip>

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
        std::cout << limits->at(o.limit).size << std::endl;
        std::cout << o.shares << std::endl;
        limits->at(o.limit).size += o.shares;
        std::cout << limits->at(o.limit).size << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Add limit to book" << std::endl;
        // create the new limit
        Limit l = Limit(o.limit, o.shares);
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
 * print
 * Purpose: Print the order book orders, used for testing and debugging.
 * Parameters: None.
 * Returns: Nothing.
 */
void OrderBook::print() const
{
    int columnWidth = 10;
    std::cout << std::setw(columnWidth) << std::left << "Price" << "|" << std::setw(columnWidth) << "Id" << "|" << std::setw(columnWidth) << "Shares" << "|" << std::setw(columnWidth) << "Timestamp" << std::endl;
    std::cout << std::setfill('-') << std::setw(columnWidth * 4 + 2) << "" << std::setfill(' ') << std::endl;
    for (const auto& pair : *sellSide)
        printOrderHelper(pair.second.orders, columnWidth);
    std::cout << std::setfill('-') << std::setw(columnWidth * 4 + 2) << "" << std::setfill(' ') << std::endl;
    for (const auto& pair : *buySide)
        printOrderHelper(pair.second.orders, columnWidth);
    std::cout << std::setfill('-') << std::setw(columnWidth * 4 + 2) << "" << std::setfill(' ') << std::endl;
}

/*
 * printLimit
 * Purpose: Print the order book limits, used for testing and debugging.
 * Parameters: None.
 * Returns: Nothing.
 */
void OrderBook::printLimit() const
{
    int columnWidth = 10;
    std::cout << std::setw(columnWidth) << std::left << "Price" << "|" << std::setw(columnWidth) << "Size" << "|" << std::setw(columnWidth) << "Total Vol" << std::endl;
    std::cout << std::setfill('-') << std::setw(columnWidth * 3 + 2) << "" << std::setfill(' ') << std::endl;
    for (const auto& pair : *sellSide) 
        printLimitHelper(pair.second, columnWidth);
    std::cout << std::setfill('-') << std::setw(columnWidth * 3 + 2) << "" << std::setfill(' ') << " Print Spread here" << std::endl;
    for (const auto& pair : *buySide) 
        printLimitHelper(pair.second, columnWidth);
    std::cout << std::setfill('-') << std::setw(columnWidth * 3 + 2) << "" << std::setfill(' ') << std::endl;
}

void OrderBook::printLimitHelper(const Limit& limit, int columnWidth) const
{
    std::string red = "\033[31m";
    std::string green = "\033[32m";
    std::string reset = "\033[0m";
    std::cout << std::setw(columnWidth)
              << limit.limitPrice <<  "|"
              << std::setw(columnWidth) 
              << std::fixed 
              << limit.size << "|"
              << std::setw(columnWidth) 
              << limit.totalVolume
              << std::endl;
}

void OrderBook::printOrderHelper(const std::list<Order>* listPtr, int columnWidth) const
{
    for (const Order& i : *listPtr) {
        std::cout << std::setw(columnWidth)
                  << i.limit <<  "|"
                  << std::setw(columnWidth) 
                  << std::fixed 
                  << i.idNumber << "|"
                  << std::setw(columnWidth) 
                  << i.shares << "|"
                  << std::setw(columnWidth) 
                  << i.entryTime
                  << std::endl;
    }
}