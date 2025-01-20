#include "OrderBook.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

class ProgressBar {
  private:
    int total;
    int barWidth;
    std::chrono::steady_clock::time_point startTime;

  public:
    ProgressBar(int total, int width = 50) : total(total), barWidth(width) {
        startTime = std::chrono::steady_clock::now();
    }

    void update(int current) {
        float progress = static_cast<float>(current) / total;
        int pos = static_cast<int>(barWidth * progress);

        std::cout << "\r[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos)
                std::cout << "=";
            else if (i == pos)
                std::cout << ">";
            else
                std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << "%" << std::flush;
    }

    void finish() {
        std::cout << "\r[";
        for (int i = 0; i < barWidth; ++i) {
            std::cout << "=";
        }
        std::cout << "] 100%" << std::endl;
    }
};

class OrderBookBenchmark {
  private:
    OrderBook book;
    std::mt19937 rng;
    std::uniform_real_distribution<> price_dist;
    std::uniform_real_distribution<> size_dist;
    std::uniform_int_distribution<> side_dist;
    int current_time;

  public:
    OrderBookBenchmark()
        : rng(std::random_device{}()), price_dist(90.0, 110.0),
          size_dist(1.0, 100.0), side_dist(0, 1), current_time(0) {}

    void runThroughputTest(int numOrders) {
        std::cout << "\n=== Add Order Throughput Test (" << numOrders
                  << " orders) ===\n";
        ProgressBar progress(numOrders);

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numOrders; i++) {
            double price = price_dist(rng);
            double size = size_dist(rng);
            Order::OrderType side =
                side_dist(rng) == 1 ? Order::BUY : Order::SELL;

            int entry_time = current_time++;
            int event_time = current_time;

            Order *order =
                new Order(i, side, size, price, entry_time, event_time);
            book.addOrder(order);

            if (i % 1000 == 0) {
                progress.update(i);
            }
        }
        progress.finish();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        double seconds = duration.count() / 1000000.0;
        double ordersPerSecond = numOrders / seconds;

        std::cout << "Stats:\n";
        std::cout << "- Time: " << std::fixed << std::setprecision(3) << seconds
                  << " seconds\n";
        std::cout << "- Throughput: " << std::fixed << std::setprecision(0)
                  << ordersPerSecond << " orders/second\n";

        std::cout << "\n=== Cancel Order Test (" << numOrders
                  << " orders) ===\n";
        ProgressBar cancelProgress(numOrders);

        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numOrders; i++) {
            book.cancelOrder(i);
            if (i % 1000 == 0) {
                cancelProgress.update(i);
            }
        }
        cancelProgress.finish();

        end = std::chrono::high_resolution_clock::now();
        duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        seconds = duration.count() / 1000000.0;
        ordersPerSecond = numOrders / seconds;

        std::cout << "Stats:\n";
        std::cout << "- Time: " << std::fixed << std::setprecision(3) << seconds
                  << " seconds\n";
        std::cout << "- Throughput: " << std::fixed << std::setprecision(0)
                  << ordersPerSecond << " cancels/second\n";

        book.clearBook();
    }

    void runDenseBookTest(int numOrders) {
        std::cout << "\n=== Dense Book Test (" << numOrders << " orders) ===\n";

        std::uniform_real_distribution<> tight_price_dist(99.90, 100.10);
        ProgressBar progress(numOrders);

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numOrders; i++) {
            double price = tight_price_dist(rng);
            double size = size_dist(rng);
            Order::OrderType side =
                side_dist(rng) == 1 ? Order::BUY : Order::SELL;

            int entry_time = current_time++;
            int event_time = current_time;

            Order *order =
                new Order(i, side, size, price, entry_time, event_time);
            book.addOrder(order);

            if (i % 1000 == 0) {
                progress.update(i);
            }
        }
        progress.finish();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        double seconds = duration.count() / 1000000.0;
        double ordersPerSecond = numOrders / seconds;

        std::cout << "Stats:\n";
        std::cout << "- Time: " << std::fixed << std::setprecision(3) << seconds
                  << " seconds\n";
        std::cout << "- Throughput: " << std::fixed << std::setprecision(0)
                  << ordersPerSecond << " orders/second\n";

        book.clearBook();
    }

    void runBestPriceUpdateTest(int numUpdates) {
        std::cout << "\n=== Best Price Update Test (" << numUpdates
                  << " updates) ===\n";
        ProgressBar progress(numUpdates *
                             2); // *2 because we add both bid and offer

        auto start = std::chrono::high_resolution_clock::now();

        int entry_time = current_time++;
        int event_time = current_time;

        Order *bid =
            new Order(0, Order::BUY, 1.0, 100.00, entry_time, event_time);
        entry_time = current_time++;
        event_time = current_time;
        Order *offer =
            new Order(1, Order::SELL, 1.0, 100.10, entry_time, event_time);

        book.addOrder(bid);
        book.addOrder(offer);
        progress.update(2);

        for (int i = 2; i < numUpdates * 2; i += 2) {
            entry_time = current_time++;
            event_time = current_time;

            Order *newBid = new Order(i, Order::BUY, 1.0, 100.00 + (i * 0.01),
                                      entry_time, event_time);

            entry_time = current_time++;
            event_time = current_time;

            Order *newOffer =
                new Order(i + 1, Order::SELL, 1.0, 100.10 + (i * 0.01),
                          entry_time, event_time);

            book.addOrder(newBid);
            book.addOrder(newOffer);

            if (i % 1000 == 0) {
                progress.update(i);
            }
        }
        progress.finish();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        double seconds = duration.count() / 1000000.0;
        double updatesPerSecond = numUpdates / seconds;

        std::cout << "Stats:\n";
        std::cout << "- Time: " << std::fixed << std::setprecision(3) << seconds
                  << " seconds\n";
        std::cout << "- Throughput: " << std::fixed << std::setprecision(0)
                  << updatesPerSecond << " updates/second\n";

        book.clearBook();
    }
};

int main() {
    OrderBookBenchmark benchmark;

    benchmark.runThroughputTest(100000);
    benchmark.runDenseBookTest(50000);
    benchmark.runBestPriceUpdateTest(10000);

    return 0;
}