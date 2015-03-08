#include "precompiled_headers.hpp"

// Taken from Boost Coroutine docs:
// http://www.boost.org/doc/libs/1_57_0/libs/coroutine/doc/html/coroutine/coroutine/asymmetric.html
// Modificatied for presentation.

#include <boost/coroutine/all.hpp>


void fib(boost::coroutines::asymmetric_coroutine<int>::push_type& yield) {
    int first = 1;
    int second = 1;
    yield(first);    // Returns for the first time.
    // Entrance #2
    yield(second);   // Returns for the second time.
    // Entrance #3
    for(int i = 0; i < 8; ++i){
        int third = first + second;
        first = second;
        second = third;
        yield(third);
    }
}


int main() {
    // Instantiates a pull_type, which creates the coroutine and begins running
    // the function above until "yield(first);" is called.
    boost::coroutines::asymmetric_coroutine<int>::pull_type source(fib);
    int answer1 = source.get();  // Retrieves the first result of yield.
    std::cout << answer1;
    source();                    // Execution goes to "Entrance #2" above.
    int answer2 = source.get();  // Retrieves the second result of yield.
    std::cout << answer2;
    source();                    // Execution goes to "Entrance #3..."
    int answer3 = source.get();  // Gets the third answer...
    std::cout << answer3;
    source();                    // Runs one more time.

    // Continously gets the last result of yield and assigns it to i in the
    // loop, then runs the coroutine again.
    for (auto i : source) {
        std::cout << i << " ";
    }
}
