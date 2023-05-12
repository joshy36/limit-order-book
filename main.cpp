
#include <iostream>

#include "OrderBook.h"
#include "Order.h"
#include "Limit.h"

void testAdd() {
    OrderBook book;
    Order o = Order(0, false, 10, 9, 0, 0, nullptr, nullptr, nullptr);
    book.addOrder(o);
    // std::cout << "Hello World" << std::endl;
}

int main()
{
    testAdd();
    return 0;
}