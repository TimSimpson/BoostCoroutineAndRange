#include <boost/range/algorithm/set_algorithm.hpp>
#include <boost/function_output_iterator.hpp>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <iostream>


void intersection_to_array()
{
    // sample(intersection_to_array)
    std::set<int> s1 = {1, 2, 3, 4};
    std::set<int> s2 = {3, 4, 5, 6};
    int values[3];
    boost::range::set_intersection(s1, s2, values);
    // end-sample
}

void intersection_copy()
{
    // sample(intersection_copy)
    std::set<int> s1 = {1, 2, 3, 4};
    std::set<int> s2 = {3, 4, 5, 6};
    std::vector<int> result;
    boost::range::set_intersection(s1, s2, std::back_inserter(result));
    // end-sample
}

void intersection_print()
{
    // sample(intersection_print)
    std::set<int> s1 = {1, 2, 3, 4};
    std::set<int> s2 = {3, 4, 5, 6};
    std::vector<int> result;
    boost::range::set_intersection(s1, s2, 
        boost::make_function_output_iterator(+[](int i)
    {
        std::cout << i << std::endl;
    }));
    // end-sample
}

int main()
{
    intersection_to_array();
    intersection_copy();
    intersection_print();
}

