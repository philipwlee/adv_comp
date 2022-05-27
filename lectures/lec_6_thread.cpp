#include <iostream>
#include <thread>
#include <mutex>

long BALANCE{0};
std::mutex MUT;

void inc_balance()
{
    for (long i{0}; i<10000000; ++i) {std::lock_guard<std::mutex> guard{MUT}; ++BALANCE;}
}

void dec_balance()
{
    for (long i{0}; i<10000000; ++i) {std::lock_guard<std::mutex> guard{MUT}; --BALANCE;}
}

void thread_func()
{
    std::cout << BALANCE << '\n';

    std::thread t_inc{inc_balance};
    std::thread t_dec{dec_balance};

    t_inc.join();
    t_dec.join();

    std::cout << BALANCE << '\n';
}

void thread_lambda()
{
    std::cout << BALANCE << '\n';

    std::thread t_inc_{ []()->void {for(long i{0}; i<10000000; ++i) {MUT.lock(); ++BALANCE; MUT.unlock();} }};
    std::thread t_dec_{ []()->void {for(long i{0}; i<10000000; ++i) {MUT.lock(); --BALANCE; MUT.unlock();} }};

    t_inc_.join();
    t_dec_.join();

    std::cout << BALANCE << '\n';
}

/*
 * HFT cannot tolerate context switching (switching between multiple tasks)
 * extra Order(microsecond) latency - destroys profitability
 *
 * deque employed to be thread-core safe
 * lock free datastructure
 * reading and writing must be at different places
 *
 */

int lec_6_thread_main()
{
    std::cout << "Lecture 6 Thread\n\n";
    thread_func();

    BALANCE=0;
    thread_lambda();

    std::cout << "0 equals nullptr: " << (0==nullptr) << '\n';

    return 0;
}