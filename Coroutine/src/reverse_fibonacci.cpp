#include "precompiled_headers.hpp"

// Taken from Boost Coroutine docs:
// http://www.boost.org/doc/libs/1_57_0/libs/coroutine/doc/html/coroutine/coroutine/asymmetric.html

#include <boost/coroutine/all.hpp>
#include <boost/bind.hpp>
#include <iostream>

template<typename T>
using a_coro = boost::coroutines::asymmetric_coroutine<T>;


void print_fib(a_coro<int>::pull_type & source) {
    std::cout << "fib1\n";
    for (auto i : source) {
        std::cout << i << " ";
    }
    // Note: this is never called!
    std::cout << "\nThe end!\n";
}



int main() {
    a_coro<int>::push_type yield(print_fib);
    // Unlike when we create a pull_type, creating a push_type won't instantly
    // call the function. So at this point print_fib has not started executing
    // yet.

    int first = 1;
    int second = 1;
    // Now begin execution of print_fib. It won't return until it tries to
    // get more data from us which happens in the loop.
    yield(first);
    yield(second);
    for(int i = 0; i < 8; ++i){
        int third = first + second;
        first = second;
        second = third;
        yield(third);
    }
    // Note that with the push_type, we can send data to the print_fib
    // coroutine but we can't receive. So we can only tell it what to do.
    // That's the opposite of before were we could get data but couldn't
    // give it new data after we'd first invoked it.
}
