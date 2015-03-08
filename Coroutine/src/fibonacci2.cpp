#include "precompiled_headers.hpp"

// Taken from Boost Coroutine docs:
// http://www.boost.org/doc/libs/1_57_0/libs/coroutine/doc/html/coroutine/coroutine/asymmetric.html

#include <boost/coroutine/all.hpp>
#include <boost/bind.hpp>

template<typename T>
using a_coro = boost::coroutines::asymmetric_coroutine<T>;


void fib(a_coro<int>::push_type & yield) {
    int first = 1;
    int second = 1;
    yield(first);
    yield(second);
    for(int i = 0; i < 8; ++i){
        int third = first + second;
        first = second;
        second = third;
        yield(third);
    }
}


void fib2(int max, a_coro<int>::push_type & yield) {
    int first = 1;
    int second = 1;
    yield(first);
    yield(second);
    for(int i = 0; i < max; ++i){
        int third = first + second;
        first = second;
        second = third;
        yield(third);
    }
}


a_coro<int>::pull_type fib3(int max) {
    return a_coro<int>::pull_type([max](a_coro<int>::push_type& yield) {
        int first = 1;
        int second = 1;
        yield(first);
        yield(second);
        for(int i = 0; i < max; ++i){
            int third = first + second;
            first = second;
            second = third;
            yield(third);
        }
    });
}


int main() {
    std::cout << "fib1\n";
    a_coro<int>::pull_type source(fib);
    for (auto i : source) {
        std::cout << i << " ";
    }

    std::cout << "\nfib2\n";
    a_coro<int>::pull_type source2(boost::bind(fib2, 20, _1));
    for (auto i : source2) {
        std::cout << i << " ";
    }

    std::cout << "\nfib3\n";
    for (auto i : fib3(20)) {
        std::cout << i << " ";
    }
}
