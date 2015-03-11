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

// sample(map_caveat)
std::map<std::string, int> get_map()
{
    std::map<std::string, int> m = 
    { 
        {"One", 1},
        {"Two", 2},
        {"Three", 3},
        {"Four", 4}
    };
    return m;
}

int main()
{
    for(int i:get_map() | boost::adaptors::map_values)
    {
        std::cout << i << std::endl;
    }
}
// end-sample