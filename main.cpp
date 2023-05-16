
#include <iostream>

#include "OrderBook.h"
#include "Order.h"
#include "Limit.h"

int idNumber  = 0;
int entryTime = 0;
int eventTime = 0;

Order orderGenerator(bool buyOrSell, int shares, int limit) {
    Order o = Order(idNumber, buyOrSell, shares, limit, entryTime, eventTime);
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
    book.addOrder(orderGenerator(false, 2, 7));
    book.addOrder(orderGenerator(true, 5, 4));
    book.addOrder(orderGenerator(true, 6, 6));
    book.addOrder(orderGenerator(true, 7, 6));
    book.addOrder(orderGenerator(false, 2, 9));
    book.addOrder(orderGenerator(false, 2, 5));
    book.print();
    book.printLimit();
    resetOrders();
}

int main()
{
    testAdd();
    return 0;
}