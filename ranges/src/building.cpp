#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/fusion/functional/adapter/fused.hpp>
#include <boost/fusion/functional/generation/make_fused.hpp>
#include <boost/fusion/functional/adapter/fused_procedure.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/join.hpp>
#include <iostream>
#include <vector>


// sample(single)
template<class T>
auto single(T& x)
{
    return boost::make_iterator_range(
        std::addressof(x), 
        std::addressof(x) + 1
    );
}

void single_example()
{
    int n = 5;
    auto range = single(n);
    for(int i:range) std::cout << i << std::endl;
}
// end-sample

// sample(drop_while)
template<class Range, class Predicate>
auto drop_while(Range&& r, Predicate p)
{
    return boost::make_iterator_range(
        boost::range::find_if(r, [&](auto&& x) { return not p(x); }),
        boost::end(r)
    );
}

void drop_while_example()
{
    std::vector<int> vec = {1, 3, 5, 7, 10, 11, 12, 13, 14, 15};
    auto r = drop_while(vec, [](int i) { return i % 2 != 0; });
    for(int i:r) std::cout << i << std::endl;
}
// end-sample

// sample(trim1)
template<class Range, class Predicate>
auto trim(Range&& r, Predicate p)
{
    auto not_p = [&](auto&& x) { return not p(x); };
    return boost::make_iterator_range(
        boost::range::find_if(r, not_p),
        boost::range::find_if(r | boost::adaptors::reversed, not_p)
            .base()
    );
}

template<class Range>
auto trim(Range&& r)
{
    return trim(r, [](auto c){ return isspace(c); });
}
// end-sample

// sample(trim2)
template<class Range>
std::string as_string(Range&& r)
{
    return std::string(boost::begin(r), boost::end(r));
}

void trim_example()
{
    std::string s = "   hello world!   ";
    auto trimmed = trim(s);
    std::cout << boost::distance(trimmed) <<  " vs " 
              << boost::distance(s) << std::endl;
    std::cout << as_string(trimmed) << std::endl;
}
// end-sample

int main()
{
    single_example();
    drop_while_example();
    trim_example();
}