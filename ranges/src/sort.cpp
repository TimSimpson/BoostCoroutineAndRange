#include <boost/range/algorithm/sort.hpp>
#include <vector>
#include <algorithm>
#include <string>


void sort_iterators()
{
    // sample(sort_iterators)
    std::vector<int> v = {2, 4, 1, 3};
    std::sort(v.begin(), v.end());
    // end-sample
}

void sort_range()
{
    // sample(sort_range)
    std::vector<int> v = {2, 4, 1, 3};
    boost::range::sort(v);
    // end-sample
}

int main()
{
    sort_iterators();
    sort_range();
}