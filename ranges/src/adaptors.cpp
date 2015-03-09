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


void reverse_adaptors()
{
    // sample(reverse_adaptors)
    std::vector<int> vec = { 1, 2, 3, 4 };
    for(int i:vec | boost::adaptors::reversed)
    {
        std::cout << i << std::endl;
    }
    // end-sample
}

void map_values_adaptors()
{
    // sample(map_values_adaptors)
    std::map<std::string, int> m = 
    { 
        {"One", 1},
        {"Two", 2},
        {"Three", 3},
        {"Four", 4}
    };
    for(int i:m | boost::adaptors::map_values)
    {
        std::cout << i << std::endl;
    }
    // end-sample
}

struct employee
{
    std::string name;
    long salary;
};

void find_rich_employees()
{
    std::vector<employee> employees = 
    {
        {"Tom Hanks", 50000},
        {"Billybob Thomas", 500000},
        {"Steve Wozniack", 800000},
        {"Scott Meyers", 80000}
    };
    // sample(rich_employees)
    auto rich_employee_names = employees
        | boost::adaptors::filtered([](const employee& e) { return e.salary > 100000; })
        | boost::adaptors::transformed([](const employee& e) { return e.name; });
    for(std::string name:rich_employee_names)
    {
        std::cout << name << std::endl;
    }
    // end-sample
}

void zip_ranges()
{
    std::vector<float> v1 = { 1.0, 2.0, 3.0, 4.0};
    std::vector<float> v2 = { 1.01, 2.03, 3.4, 4.6};
    // sample(zip_ranges)
    auto differences = boost::combine(v1, v2) 
        | boost::adaptors::transformed(boost::fusion::make_fused(+[](float x, float y)
        {
            return x - y;
        }));
    auto max_diff = boost::range::max_element(differences);
    // end-sample
}

int main() 
{
    reverse_adaptors();
    map_values_adaptors();
    find_rich_employees();
    zip_ranges();
}