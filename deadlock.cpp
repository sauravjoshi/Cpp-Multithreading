// deadlock.cpp
// This file contains functions showcasing deadlock conditions and preventions using unique_lock
// With C++17, the resolution of the deadlock becomes quite easy. We get the std::scoped_lock that can lock an arbitrary number of mutexes atomically - so long as you only have to use a std::lock_guard instead of the std::lock call. That’s all. Here is the modified function deadlock.

#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

struct CriticalData
{
    std::mutex mut;
};

void deadLock(CriticalData &a, CriticalData &b)
{

    a.mut.lock();
    std::cout << "get the first mutex" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    b.mut.lock();
    std::cout << "get the second mutex" << std::endl;
    // do something with a and b
    a.mut.unlock();
    b.mut.unlock();

    std::mutex m;
    std::lock_guard<std::mutex> lockGuard(m);
}

void deadLockPrevention(CriticalData &a, CriticalData &b)
{

    std::unique_lock<std::mutex> guard1(a.mut, std::defer_lock);
    std::cout << "Thread: " << std::this_thread::get_id() << " first mutex" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    std::unique_lock<std::mutex> guard2(b.mut, std::defer_lock);
    std::cout << "  Thread: " << std::this_thread::get_id() << " second mutex" << std::endl;
    std::cout << "    Thread: " << std::this_thread::get_id() << " get both mutex" << std::endl;

    // variadic template
    std::lock(guard1, guard2);
}

int main()
{

    CriticalData c1;
    CriticalData c2;

    std::thread t1([&]
                   { deadLockPrevention(c1, c2); });
    std::thread t2([&]
                   { deadLockPrevention(c2, c1); });

    t1.join();
    t2.join();
}