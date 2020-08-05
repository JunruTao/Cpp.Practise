#include <iostream>
#include <pthread.h>
#include <chrono>
#include <pthread.h>
#include <thread>


void Foo()
{
    std::cout<<"Hi from worker thread!"<<std::endl;
}

int main()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<"Hello World\n";
    return 0;
}