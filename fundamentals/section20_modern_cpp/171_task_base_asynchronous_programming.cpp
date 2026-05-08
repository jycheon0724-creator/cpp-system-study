// Section 19 - 19.3 ~ 19.5
// Focus: task_base_asynchronous_programming
#include <iostream>
#include <future>
#include <thread>

int main() 
{
    // multi_threading
    {
        int result;
        std::thread t([&]{ result = 1 + 2; });
        t.join();
        std::cout << result << '\n';
    }

    // task-based parallelism
    {   
        // std::future<int> fut = ...
        auto fut = std::async([] { return 1 + 2; });
        std::cout << fut.get() << "\n"; // 미래를 기다리는 형태
    }

    // future and promise
    {
        std::promise<int> prom;
        auto fut = prom.get_future();

        auto t = std::thread([](std::promise<int>&& prom)
        {
            prom.set_value(1+2);
        }, std::move(prom));

        std::cout << fut.get() << "\n";
        t.join();
    }

    {
        auto f1 = std::async([] {
            std::cout << "async1 start" << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            std::cout << "async1 end" << "\n";
        });

        auto f2 = std::async([] {
            std::cout << "async2 start" << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            std::cout << "async2 end" << "\n";
        });

        std::cout << "Main function" << "\n";
    }
    /*
    {
        std::async([] {
            std::cout << "async1 start" << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            std::cout << "async1 end" << "\n";
        });

        std::async([] {
            std::cout << "async2 start" << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            std::cout << "async2 end" << "\n";
        });

        std::cout << "Main function" << "\n";
    }
    */
    return 0;
}