
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <stdexcept>
#include <future>
#include <chrono>
#include "timer.h"



void Fun1()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::cout << "Hello From Thread #\033[35m" << std::this_thread::get_id() <<"\033[0m"<< std::endl;
}


int main()
{
	std::cout 
		<< "\033[1m\033[31m\n\n*****************[ PART 1]*******************\n"
		<<"#############################################\n"<<"\033[0m";
	Timer timer;

	/*◙▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚◙*/
	//▶ 🆃🅴🆂🆃🆂 - 3.1 MainThread-workerThread-ship
	timer.CheckIn();/*--------------------------------------------------⌚[𝘾𝙝𝙚𝙘𝙠 𝙞𝙣 𝙥𝙤𝙞𝙣𝙩] 1*/
	
	std::vector<std::thread> threads;
	for (size_t i = 0; i < 10; i++)
	{
		threads.emplace_back(std::thread(Fun1));
	}

	//timer.CheckIn();/*--------------------------------------------------⌚[𝘾𝙝𝙚𝙘𝙠 𝙞𝙣 𝙥𝙤𝙞𝙣𝙩] 2*/
	//beause is rvalue inside, so t must us a reference: &t
	for (auto &t : threads)t.join();

	timer.CheckIn();/*--------------------------------------------------⌚[𝘾𝙝𝙚𝙘𝙠 𝙞𝙣 𝙥𝙤𝙞𝙣𝙩] 3*/

	timer.PrintAllCheckPoints();//--------------------------------------⌚◙◙◙ Clear Timer ◙◙◙

	/*_______________________________________
	 | As you can see, Everytime Executing  |
	 | this code, the result is different,  |
	 | and the order is purely random and   |
	 | dangling around like printing on the |
	 | same line.                           |
	 ----------------------------------------*/





	/*◙▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚◙*/
	//▶ 🆃🅴🆂🆃🆂 - 3.2 Promises and Futures
	std::cout <<"\033[1m\033[31m\n\n\n\n\n\*****************[ PART 2]*******************\n"<< "#############################################\n" << "\033[0m";
	timer.CheckIn();/*--------------------------------------------------⌚[𝘾𝙝𝙚𝙘𝙠 𝙞𝙣 𝙥𝙤𝙞𝙣𝙩] 1*/

	//● ⑴ Making Promise: 
	std::promise<std::string> pms;

	//● ⑵ Set correlated future link:
	std::future<std::string> ftr = pms.get_future();

	//----Creating a message to pass 
	//    in the fun2 function( λ-function )
	std::string MyMessage = "My Message from the past";

	//● ⑶ The Function: 
	//     Must be taking a a promise as Rvalue, and use `set_value`
	//     To pass the message to the future. Because R value, the 
	//     promise-future channel is a one-way comm-channel and 
	//     ought to be used once only.
	auto func2 = [](std::promise<std::string>&& prm, std::string message)
	{
		ThreadSleepMilliseconds(100);
		std::string newmessage = message + " is modified in the thread";
		prm.set_value(newmessage);
	};

	timer.CheckIn();/*--------------------------------------------------⌚[𝘾𝙝𝙚𝙘𝙠 𝙞𝙣 𝙥𝙤𝙞𝙣𝙩] 2*/

	//● ⑷ Creating a new thread, passing promise
	//    ▼and message the through the function.
	std::thread t2(func2, std::move(pms), MyMessage);


	//● ⑸ Let the thread to finish, 
	//    ▼so pausing this thread(main thread)
	ftr.wait();

	timer.CheckIn();/*--------------------------------------------------⌚[𝘾𝙝𝙚𝙘𝙠 𝙞𝙣 𝙥𝙤𝙞𝙣𝙩] 3*/


	//● ⑹                                 ▼ ▼ ▼ ▼ using .get the get the result;
	std::cout << "Message recieved = " << ftr.get() << std::endl;

	//● ⑺ Don't forget to join the thread back.
	t2.join();
	timer.CheckIn();/*--------------------------------------------------⌚[𝘾𝙝𝙚𝙘𝙠 𝙞𝙣 𝙥𝙤𝙞𝙣𝙩] 4*/

	timer.PrintAllCheckPoints();//--------------------------------------⌚◙◙◙ Clear Timer ◙◙◙

	/*_______________________________________
	 | As you can see, the Code block is very|
	 | messy and futures and promises needed |
	 | to be managed very carefully, so that |
	 | you can pass information across the   |
	 | threads, which is not very convinient |
	 ----------------------------------------*/




	ThreadSleepMilliseconds(1000);

	/*◙▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚▚◙*/
	//▶ 🆃🅴🆂🆃🆂 - 3.3 Async : Threads & Tasks

	//● With std::async, there is no need to join back 
	// the theads and it can be asynchronous or sync.
	// it will be decided by the thread manager of OS


	std::cout
		<< "\033[1m\033[31m\n\n\n\n\n\*****************[ PART 3]*******************\n"
		<< "#############################################\n" << "\033[0m";
	double x = 0.1;

	timer.CheckIn();/*--------------------------------------------------⌚[𝘾𝙝𝙚𝙘𝙠 𝙞𝙣 𝙥𝙤𝙞𝙣𝙩] 1*/

	//Good practice: NO promise needed.
	std::future<double> ftr2 = std::async([&x]()mutable  //Here[!]
		{        /*NOTE: Async takes no type<> here, it depends 
				 on the function return type, if lambdas, must 
				 return the same type*/
			ThreadSleepMilliseconds(200);
			x += 1;
			return x;
		});
	timer.CheckIn();/*--------------------------------------------------⌚[𝘾𝙝𝙚𝙘𝙠 𝙞𝙣 𝙥𝙤𝙞𝙣𝙩] 2*/


	double xget = ftr2.get();
	timer.CheckIn();/*--------------------------------------------------⌚[𝘾𝙝𝙚𝙘𝙠 𝙞𝙣 𝙥𝙤𝙞𝙣𝙩] 3*/

	std::cout << "The original varible after mutable lambda funtion is:" << x << std::endl;
	std::cout << "result from thread using future.get is: " << xget <<std::endl;

	//No join needed, async automatic join the threads

	timer.PrintAllCheckPoints();//--------------------------------------⌚◙◙◙ Clear Timer ◙◙◙



	//Now test the async lauch modes:
	timer.CheckIn();
	//[1] any, let OS decide
	std::vector<std::future<void>> furs1;
	for (size_t i = 0; i < 10; i++) 
	{
		furs1.emplace_back(std::async(Fun1));
	}
	for (auto& f : furs1) 
	{
		f.get();
	}
	timer.CheckIn();


	//[2] std::launch::async
	std::vector<std::future<void>> furs2;
	for (size_t i = 0; i < 10; i++)
	{
		furs2.emplace_back(std::async(std::launch::async,Fun1));
	}
	for (auto& f : furs2)
	{
		f.get();
	}
	timer.CheckIn();



	//[3] std::launch::deferred
	std::vector<std::future<void>> furs3;
	for (size_t i = 0; i < 10; i++)
	{
		furs3.emplace_back(std::async(std::launch::deferred, Fun1));
	}
	for (auto& f : furs3)
	{
		f.get();
	}
	timer.CheckIn();
	timer.PrintAllCheckPoints();
}