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
#include <fit/indirect.h>
#include <boost/optional.hpp>

struct employee
{
    std::string name;
    long salary;
};

std::vector<employee> employees = 
{
    {"Tom Hanks", 50000},
    {"Billybob Thomas", 500000},
    {"Steve Wozniack", 800000},
    {"Scott Meyers", 80000}
};

// sample(regular)
template<class F>
auto regular(F f)
{
    return fit::indirect(boost::optional<F>(std::move(f)));
}
// end-sample

// sample(rich_employees_regular)
void find_rich_employees(int salary)
{
    auto rich_employee_names = employees
        | boost::adaptors::filtered(regular([&](const employee& e) 
            { return e.salary > salary; }))
        | boost::adaptors::transformed(+[](const employee& e) 
            { return e.name; });
    for(std::string name:rich_employee_names)
    {
        std::cout << name << std::endl;
    }
    auto pred = regular([&](const employee& e) 
            { return e.salary > salary; });
    using predicate = decltype(pred);
    static_assert(std::is_default_constructible<predicate>() and std::is_copy_assignable<predicate>(), "Not regular");
}
// end-sample

void find_rich_employees_check(int salary)
{
    auto rich_employee_names = employees
        | boost::adaptors::filtered(regular([&](const employee& e) 
            { return e.salary > salary; }))
        | boost::adaptors::transformed(+[](const employee& e) 
            { return e.name; });
    for(std::string name:rich_employee_names)
    {
        std::cout << name << std::endl;
    }
    auto pred = regular([&](const employee& e) 
            { return e.salary > salary; });
    using predicate = decltype(pred);
    static_assert(std::is_default_constructible<predicate>() and std::is_copy_assignable<predicate>(), "Not regular");
}



int main()
{
    find_rich_employees(100000);
}