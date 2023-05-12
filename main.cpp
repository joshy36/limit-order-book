
#include <iostream>

#include "OrderBook.h"
#include "Order.h"
#include "Limit.h"

void testAdd() {
    OrderBook book;
    Order o = Order(0, false, 10, 9, 0, 0, nullptr);
    book.print();
    book.addOrder(o);
    // book.addOrder(o); FIX WHATEVERS GOING ON HERE
    book.print();
    // std::cout << "Hello World" << std::endl;
}

int main()
{
    testAdd();
    return 0;
}