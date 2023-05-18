#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "OrderBook.h"
#include "Order.h"
#include "Limit.h"

int idNumber  = 0;
int entryTime = 0;
int eventTime = 0;

Order* orderGenerator(Order::OrderType type, double shares, double limit) 
{
    Order *o = new Order(idNumber, type, shares, limit, entryTime, eventTime);
    idNumber  += 1;
    entryTime += 1;
    eventTime += 1;
    return o;
}

void resetOrders() 
{
    idNumber  = 0;
    entryTime = 0;
    eventTime = 0;
}

void testAddClear() 
{
    OrderBook book;
    book.addOrder(orderGenerator(Order::SELL, 2, 7.9));
    book.addOrder(orderGenerator(Order::BUY,  5, 4.3));
    book.addOrder(orderGenerator(Order::BUY,  6, 6.11));
    book.addOrder(orderGenerator(Order::BUY,  7, 6));
    book.addOrder(orderGenerator(Order::SELL, 2, 6.2));
    book.addOrder(orderGenerator(Order::SELL, 2, 6.2));
    book.print();
    book.printLimit();
    // testing clear
    book.clearBook();
    book.print();
    book.printLimit();
    resetOrders();
}

void stressTestAdd(int num, bool oneLimit) 
{
    OrderBook book;

    std::ofstream outputFile;
    if (oneLimit)
        outputFile.open("oneLimit.txt");
    else
        outputFile.open("multipleLimits.txt");

    if (!outputFile.is_open()) {
        std::cout << "Failed to open the output file." << std::endl;
        exit(0);
    }

    outputFile << "Orders Time(s)" << std::endl;
    for (int i = 1; i <= num; i *= 10) {
        auto start = std::chrono::system_clock::now();

        for (int j = 1; j <= i; j++) {
            if (oneLimit)
                book.addOrder(orderGenerator(Order::BUY, 1, 1));
            else
                book.addOrder(orderGenerator(Order::BUY, 1, j));
        }

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        outputFile << i << " " << std::fixed << elapsed.count() << std::defaultfloat << std::endl;
    }

    outputFile.close();
    // book.printLimit();

    resetOrders();
}

int main()
{
    // testAddClear();
    stressTestAdd(std::pow(10,8), true);
    stressTestAdd(std::pow(10,8), false);
    return 0;
}