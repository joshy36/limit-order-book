/*
 * OrderBook.cpp
 * 
 * Purpose: Implementation of the OrderBook class.
 */
#include <iostream>
#include <iomanip>

#include "OrderBook.h"

/*
 * Default constructor.
 */
OrderBook::OrderBook()
{
    sellSide   = new std::map<double, Limit*, std::greater<double>>;
    buySide    = new std::map<double, Limit*, std::greater<double>>;
    orders     = new std::unordered_map<int, Order*>;
    limits     = new std::unordered_map<double, Limit*>;
    bestBid    = nullptr;
    bestOffer  = nullptr;
}

/*
 * Destructor to free allocated memory.
 */
OrderBook::~OrderBook()
{
    clearBook();

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
void OrderBook::addOrder(Order *o)
{
    try {
        limits->at(o->getLimit());
        orders->emplace(o->getIdNumber(), o);
    } catch (const std::out_of_range& e) {
        Limit *l = new Limit(o->getLimit());
        limits->emplace(l->getPrice(), l);
        orders->emplace(o->getIdNumber(), o);
        if (o->getBuyOrSell() == Order::BUY) {
            buySide->emplace(l->getPrice(), l);
            if (bestBid == nullptr)
                bestBid = l;
            else if (o->getLimit() > bestBid->getPrice())
                bestBid = l;
        }
        else {
            sellSide->emplace(l->getPrice(), l);
            if (bestOffer == nullptr)
                bestOffer = l;
            else if (o->getLimit() < bestOffer->getPrice())
                bestOffer = l;
        }
    }
    limits->at(o->getLimit())->addOrder(*o);
}

/*
 * cancelOrder
 * Purpose: Remove an order from the book.
 * Parameters: idNumber of order to remove.
 * Returns: Nothing.
 */
void OrderBook::cancelOrder(int idNumber) 
{
    try {
        Order *o = orders->at(idNumber);
        limits->at(o->getLimit())->removeOrder(*o);
        Limit *l = limits->at(o->getLimit());
        if (l->getOrders()->size() == 0) {
            if (l == bestBid)
                bestBid = nullptr;
            else if (l == bestOffer)
                bestOffer = nullptr;
            // remove limit from correct tree
            if (o->getBuyOrSell() == Order::BUY)
                buySide->erase(l->getPrice());
            else
                sellSide->erase(l->getPrice());
            // remove limit from map
            limits->erase(l->getPrice());
            delete l;
            if (bestBid == nullptr)
                bestBid = buySide->begin()->second;
            else if (bestOffer == nullptr)
                bestOffer = sellSide->rbegin()->second;
        }
        orders->erase(idNumber);
        delete o;
    } catch (const std::out_of_range& e) {
        std::cerr << "Not in book" << std::endl;
    }
}

/*
 * clearBook
 * Purpose: Clears all the orders out of the book, effectively 
 * reseting to an empty book.
 * Parameters: None.
 * Returns: Nothing.
 */
void OrderBook::clearBook()
{
    for (auto& entry : *orders) {
        delete entry.second;
        entry.second = nullptr;
    }

    for (auto& entry : *limits) {
        delete entry.second;
        entry.second = nullptr;
    }

    sellSide->clear();
    buySide->clear();
    orders->clear();
    limits->clear();
    
    bestBid   = nullptr;
    bestOffer = nullptr;
}

/*
 * getVolumeAtLimit
 * Purpose: Get the volume of shares at a limit price.
 * Parameters: Limit price to check.
 * Returns: A double with the volume at that limit.
 */
double OrderBook::getVolumeAtLimit(double limitPrice) const
{
    try {
        return limits->at(limitPrice)->getVol();
    } catch (const std::out_of_range& e) {
        return 0;
    }
}

Limit* OrderBook::getBestBid() const
{
    if (bestBid == nullptr)
        std::cerr << "No bids in book" << std::endl;
    return bestBid;
}
        
Limit* OrderBook::getBestOffer() const
{
    if (bestOffer == nullptr)
        std::cerr << "No offers in book" << std::endl;
    return bestOffer;
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
    std::cout << std::setw(columnWidth) << std::left << "Price" << "| " 
              << std::setw(columnWidth) << "Shares" << "| " 
              << std::setw(columnWidth) << "Timestamp" << "| " 
              << std::setw(columnWidth) << "Id" 
              << std::endl;
    std::cout << std::setfill('-') << std::setw(columnWidth * 4 + 2) << "" 
              << std::setfill(' ') << std::endl;
    for (const auto& pair : *sellSide)
        printOrderHelper(pair.second->getOrders(), columnWidth);
    std::cout << std::setfill('-') << std::setw(columnWidth * 4 + 2) << "" 
              << std::setfill(' ') << " Print Spread here" << std::endl;
    for (const auto& pair : *buySide)
        printOrderHelper(pair.second->getOrders(), columnWidth);
    std::cout << std::setfill('-') << std::setw(columnWidth * 4 + 2) << "" 
              << std::setfill(' ') << std::endl << std::endl;
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
    std::cout << std::setw(columnWidth) << std::left << "Price" << "| " 
              << std::setw(columnWidth) << "Total Vol" << std::endl;
    std::cout << std::setfill('-') << std::setw(columnWidth * 2 + 2) << "" 
              << std::setfill(' ') << std::endl;
    for (const auto& pair : *sellSide) 
        printLimitHelper(pair.second, columnWidth);
    std::cout << std::setfill('-') << std::setw(columnWidth * 2 + 2) << "" 
              << std::setfill(' ') << " Print Spread here" << std::endl;
    for (const auto& pair : *buySide) 
        printLimitHelper(pair.second, columnWidth);
    std::cout << std::setfill('-') << std::setw(columnWidth * 2 + 2) 
              << "" << std::setfill(' ') << std::endl << std::endl;
}

void OrderBook::printOrderHelper(const std::list<Order>* list, int columnWidth) const
{
    for (const Order& i : *list) {
        std::cout << std::setw(columnWidth) << i.getLimit()     << "| "
                  << std::setw(columnWidth) << i.getShares()    << "| "
                  << std::setw(columnWidth) << i.getEntryTime() << "| "
                  << std::setw(columnWidth) << i.getIdNumber() 
                  << std::endl;
    }
}

void OrderBook::printLimitHelper(const Limit* limit, int columnWidth) const
{
    std::string red = "\033[31m";
    std::string green = "\033[32m";
    std::string reset = "\033[0m";
    std::cout << std::setw(columnWidth) << limit->getPrice() << "| "
              << std::setw(columnWidth) << limit->getVol()   << "| "
              << std::endl;
}
