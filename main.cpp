
#include <iostream>

#include "OrderBook.h"
#include "Order.h"
#include "Limit.h"

int idNumber  = 0;
int entryTime = 0;
int eventTime = 0;

Order orderGenerator(Order::OrderType type, int shares, double limit) {
    Order o = Order(idNumber, type, shares, limit, entryTime, eventTime);
    idNumber  += 1;
    entryTime += 1;
    eventTime += 1;
    return o;
}

void resetOrders() {
    idNumber  = 0;
    entryTime = 0;
    eventTime = 0;
}

void testAdd() {
    OrderBook book;
    book.addOrder(orderGenerator(Order::SELL, 2, 7.9));
    book.addOrder(orderGenerator(Order::BUY, 5, 4.3));
    book.addOrder(orderGenerator(Order::BUY, 6, 6.11));
    book.addOrder(orderGenerator(Order::BUY, 7, 6));
    book.addOrder(orderGenerator(Order::SELL, 2, 5.2));
    book.addOrder(orderGenerator(Order::SELL, 2, 5.2));
    book.print();
    book.printLimit();
    resetOrders();
}

int main()
{
    testAdd();
    return 0;
}