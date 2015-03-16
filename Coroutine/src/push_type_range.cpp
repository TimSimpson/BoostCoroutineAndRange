#include "precompiled_headers.hpp"

// Taken from Boost Coroutine docs:
// http://www.boost.org/doc/libs/1_57_0/libs/coroutine/doc/html/coroutine/coroutine/asymmetric.html

#include <boost/coroutine/all.hpp>
#include <boost/bind.hpp>
#include <iostream>

template<typename T>
using a_coro = boost::coroutines::asymmetric_coroutine<T>;


void printer(a_coro<char>::pull_type & source) {
    while(source && source.get() != '\0') {
        std::cout << source.get() << " ";
        source();
    }
}


int main() {
    a_coro<char>::push_type print(printer);

    print('a');
    print('b');


    const char text[] = R"TEXT(
In Egypt's sandy silence, all alone
stands a gigantic leg which far off throws
the only shadow that the desert knows.
    )TEXT";
    // Treat the push_type coroutine as an output iterator.
    std::copy(boost::begin(text), boost::end(text), boost::begin(print));
}
