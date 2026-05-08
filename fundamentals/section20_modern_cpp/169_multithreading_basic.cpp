// Section 19 - 19.3 ~ 19.5
// Focus: multithreading
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

std::mutex mtx;

int main() 
{
    /*
    const int num_pro = std::thread::hardware_concurrency();
    std::cout << std::this_thread::get_id() << "\n";

    std::vector<std::thread> my_threads;
    my_threads.resize(num_pro);

    for(auto & e : my_threads)
        e = std::thread([](){
            std::cout << std::this_thread::get_id() << "\n";
            while(true) {}
        });
    
    for (auto & e : my_threads)
        e.join();
    */
   auto work_func = [](const std::string & name)
   {
    for (int i=0; i<5; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::scoped_lock<std::mutex> lock(mtx);
        std::cout << name << " " << std::this_thread::get_id() << " is working " << i << "\n";
    }
   };

   // work_func("JackJack");
   // work_func("Kkandull");

   std::thread t1 = std::thread(work_func, "JAckJAck");
   std::thread t2 = std::thread(work_func, "kkandull");

   t1.join();
   t2.join();
   return 0;
}