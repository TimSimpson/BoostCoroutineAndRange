#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/fusion/functional/adapter/fused.hpp>
#include <boost/fusion/functional/generation/make_fused.hpp>
#include <boost/fusion/functional/adapter/fused_procedure.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <iostream>
#include <vector>

void operations()
{
    // sample(operations)
    std::vector<int> vec = {1, 2, 3, 4};
    if (boost::empty(vec)) std::cout << "Not empty" << std::endl;
    std::cout << "Number of elements: " << boost::distance(vec) << std::endl;
    std::cout << "Number of elements: " << boost::size(vec) << std::endl;
    // end-sample
}

int main()
{
    operations();
}