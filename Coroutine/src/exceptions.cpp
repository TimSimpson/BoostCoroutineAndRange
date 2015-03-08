#include "precompiled_headers.hpp"

// Taken from Boost Coroutine docs:
// http://www.boost.org/doc/libs/1_57_0/libs/coroutine/doc/html/coroutine/coroutine/asymmetric.html

#include <boost/coroutine/all.hpp>
#include <boost/bind.hpp>

template<typename T>
using a_coro = boost::coroutines::asymmetric_coroutine<T>;


struct simple {
    const char * name_;

    simple(const char * name)
    :   name_(name) {
        std::cout << name_ << " ctor" << std::endl;
    }
    ~simple() {
        std::cout << name_ << " ~dtor" << std::endl;
    }
};


void coro_except(a_coro<int>::push_type & yield) {
    simple a("a");
    yield(1);
    simple b("b");
    yield(2);
    simple c("c");
    throw std::exception();
}



int main() {
    try {
        a_coro<int>::pull_type source(coro_except);

        std::cout << "coroutine yields result : " << source.get() << std::endl;
        source();
        std::cout << "coroutine yields result : " << source.get() << std::endl;
        source();
        std::cout << "coroutine yields result : " << source.get() << std::endl;
    } catch(...) {
        std::cerr << "Oh no, an exception occured! Drat." << std::endl;
    }
}
