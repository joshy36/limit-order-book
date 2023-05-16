
#include <iostream>

#include "OrderBook.h"
#include "Order.h"
#include "Limit.h"

int idNumber  = 0;
int entryTime = 0;
int eventTime = 0;

Order orderGenerator(bool buyOrSell, int shares, int limit) {
    Order o = Order(idNumber, buyOrSell, shares, limit, entryTime, eventTime, nullptr);
    idNumber  += 1;
    entryTime += 1;
    eventTime += 1;
    return o;
}

void testAdd() {
    OrderBook book;
    book.print();
    book.addOrder(orderGenerator(false, 2, 7));
    book.addOrder(orderGenerator(true, 5, 4));
    book.addOrder(orderGenerator(true, 5, 6));
    book.addOrder(orderGenerator(true, 5, 6));
    book.addOrder(orderGenerator(false, 2, 9));
    book.addOrder(orderGenerator(false, 2, 5));
    book.print();
}

int main()
{
    testAdd();
    return 0;
}