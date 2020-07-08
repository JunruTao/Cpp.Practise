#ifndef __TIMER_H__
#define __TIMER_H__

#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <stdexcept>
#include <future>
#include <chrono>

class Timer
{
public:

    Timer() {};
    void CheckIn()
    {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        times.push_back(now);

        if (times.size() > 1)
        {
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(times[times.size() - 1] - times[times.size() - 2]);
            int dur = (int)duration.count();
            std::cout << "\033[34m"
                      << "_____________________________________________\n" 
                      << "|  [Check Point \033[33m" << times.size() << "\033[34m] :\033[32m" << dur << "\033[34m ms\n" 
                      << "---------------------------------------------\n"
                      << "\033[0m";
            durList.push_back(dur);
        }
        else
        {
            std::cout << "\033[34m"
                      << "_____________________________________________\n" 
                      << "|  [Ckeck Point \033[33m1\033[34m] :\033[32m" << 0 << "\033[34m ms\n" 
                      << "---------------------------------------------\n"
                      << "\033[0m";
            durList.push_back(0);
        }
    }
    void PrintAllCheckPoints()
    {
        std::cout
                  << "\033[33m\n\n\n - End of Session - \n\033[36m"
                  << "\n  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  "
                  << "\n______________________________________________ "
                  << "\n---------------TIME USAGE SUM---------------\n";

        for (size_t i = 0; i < durList.size();i++)
        {

            std::cout << " ## Check Point[" << i << "]: " << durList[i] << " ms\n" << " -----------\n";
        }
        std::cout << "______________________________________________ "
                  << "\n----------------SUMMARY ENDS----------------\n"
                  << "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  \n"
            << "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  \n"
            << "  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  \n\033[0m";
        times.clear();
        durList.clear();
    }

private:
    std::vector<std::chrono::high_resolution_clock::time_point> times;
    std::vector<int> durList;
};


inline void ThreadSleepMilliseconds(unsigned int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    std::cout << "this thread #\033[35m" << std::this_thread::get_id()
        << "\033[0m slept for " << milliseconds << std::endl;
}



#endif