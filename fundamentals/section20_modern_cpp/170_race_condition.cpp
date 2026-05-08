// Section 19 - 19.3 ~ 19.5
// Focus: race_condition
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

std::mutex mtx;

int main() 
{
    // std::atomic<int> shared_memory(0);
    int shared_memory(0);
    auto count_fuc = [&](){
        for(int i = 0; i < 1000; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            // shared_memory.fetch_add(1);
            // mtx.lock();
            // std::lock_guard lock(mtx);
            std::scoped_lock lock(mtx);
            shared_memory++;
            // mtx.unlock();
        }
    };

    std::thread t1 = std::thread(count_fuc);
    std::thread t2 = std::thread(count_fuc);

    t1.join();
    t2.join();

    std::cout << "After" << "\n" << shared_memory << "\n";
    return 0;
}