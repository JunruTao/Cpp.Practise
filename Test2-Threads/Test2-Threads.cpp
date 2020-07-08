#include <thread>
#include <iostream>
#include <chrono>
#include <vector>

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
            std::cout << ".....\n" << "@@[Check Point "<<times.size()<<"]-[Time Cost From last check point] :" << dur << " ms\n" << ".....\n";
            durList.push_back(dur);
        }
        else 
        {
            std::cout << ".....\n" << "@@[Ckeck Point 1] :" << 0 << " ms\n" << ".....\n";
            durList.push_back(0);
        }
    }
    void PrintAllCheckPoints()
    {
        std::cout << "\n....\n---------------TIME USAGE SUM---------------\n";
        for (size_t i = 0; i<durList.size();i++)
        {
            
            std::cout << "Check Point[" << i << "]: " << durList[i] << " ms\n"<<".....\n";
        }
    }

private:
    std::vector<std::chrono::high_resolution_clock::time_point> times;
    std::vector<int> durList;
};



void ThreadSleepMilliseconds(unsigned int milliseconds) 
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    std::cout << "this thread#" << std::this_thread::get_id()
        << " slept for " << milliseconds << std::endl;
}



class Object 
{
public:
    Object() : _x(0) {}
   
    
    void GetInfo() 
    {
        ThreadSleepMilliseconds(100);
        std::cout << "[My Object] Thread #" << std::this_thread::get_id() << "\n" << "Info: " << _x << std::endl;
    }
    

private:
    int _x;
};



int main()
{
    Timer myTimer;
    myTimer.CheckIn();


    int number = 10;
    auto fun = [&number]()mutable
    {
        ThreadSleepMilliseconds(200);
        std::cout <<"This Thread #"<<std::this_thread::get_id()<<" with number"<< number<<"+1"<< std::endl;
        ++number;
    };

    Object myObject;
    std::thread t1(ThreadSleepMilliseconds,100);
    std::thread t2(&Object::GetInfo, myObject);
    std::thread t3(fun);

    myTimer.CheckIn();

    t1.join();
    t2.join();
    t3.join();

    myTimer.CheckIn();

    std::cout << "\n\n ... \n --------[All Threads Joined]-------\n";
    
    ThreadSleepMilliseconds(1000);
    std::cout << "Main Thread id: " << std::this_thread::get_id()<<std::endl;
    std::cout << "variable number = " << number << std::endl;

    myTimer.CheckIn();

    myTimer.PrintAllCheckPoints();
}
