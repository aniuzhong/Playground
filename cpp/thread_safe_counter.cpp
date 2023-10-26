#include <cstdlib>
#include <cassert>

#include <mutex>
#include <thread>
#include <iostream>

class ThreadsafeCounter {
    mutable std::mutex m;  // The "M&M rule": mutable and mutex go together
    int data = 0;

public:
    int get() const {
        std::lock_guard<std::mutex> lk(m);
        return data;
    }

    void inc() {
        std::lock_guard<std::mutex> lk(m);
        ++data;
    }
};

int main() {
    ThreadsafeCounter counter;
    std::thread t1([&]() {
        for (int i = 0; i < 10; ++i)
            counter.inc();
    });
    std::thread t2([&]() {
        for (int i = 0; i < 5; ++i)
            counter.inc();
    });
    t1.join();
    t2.join();
    assert(counter.get() == 15);
    std::cout << counter.get() << '\n';
}