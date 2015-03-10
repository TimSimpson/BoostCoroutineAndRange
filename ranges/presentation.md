# Boost.Range

---------

## Introduction

- Are like an STL container except don't necessarily own elements
- A range is a pair of iterators.
    - begin iterator - an iterator to the first element
    - end iterator - an iterator to one past the last element

---

## Types of ranges

- Single pass range
- Forward range
- Bidirectional range
- Random access range

---

## Using a Range

- Functions:
    - `boost::begin`
    - `boost::end`
- Metafunctions:
    - `range_iterator`
    - `range_value`
    - `range_category`
    - `has_range_iterator`

---

## What is a Range?

- Retrieve iterators using either:
    - Member functions
        - `begin`
        - `end`
    - Free functions:
        - `range_begin`(`begin` in C++11)
        - `range_end`(`end` in C++11)

---

## What is a Range?

- Retrieve the iterator type either using:
    - Nested type:
        - `iterator`
        - `const_iterator`
    - Metafunction:
        - `boost::range_mutable_iterator`
        - `boost::range_const_iterator`

---

## Range core operations

- empty
- distance
- size

---


## Range core operations

```cpp
std::vector<int> vec = {1, 2, 3, 4};
if (boost::empty(vec)) std::cout << "Not empty" << std::endl;
std::cout << "Number of elements: " << boost::distance(vec) << std::endl;
std::cout << "Number of elements: " << boost::size(vec) << std::endl;
```

---

## What classes are ranges?

- STL Containers
- std::pair
- and range adaptors




---------

## Algorithms

- Boost.Range provides range-based algorithms

---

## STL Algorithms

```cpp
std::vector<int> v = {2, 4, 1, 3};
std::sort(v.begin(), v.end());
```

---

## Range Algorithms

```cpp
std::vector<int> v = {2, 4, 1, 3};
boost::range::sort(v);
```

---

## Intersection

```cpp
set_intersection(range1, range2, output_iterator)
```

---

## Output iterator

- Is only writable and not readable

```cpp
*iterator = value;
```

---

## Intersection

```cpp
std::set<int> s1 = {1, 2, 3, 4};
std::set<int> s2 = {3, 4, 5, 6};
int values[3];
boost::range::set_intersection(s1, s2, values);
```

---

## Intersection

```cpp
std::set<int> s1 = {1, 2, 3, 4};
std::set<int> s2 = {3, 4, 5, 6};
std::vector<int> result;
boost::range::set_intersection(s1, s2, std::back_inserter(result));
```

---

## Intersection

```cpp
std::set<int> s1 = {1, 2, 3, 4};
std::set<int> s2 = {3, 4, 5, 6};
std::vector<int> result;
boost::range::set_intersection(s1, s2, 
    boost::make_function_output_iterator(+[](int i)
{
    std::cout << i << std::endl;
}));
```

---------

## Adaptors

- Adaptors provide a view of another range

---

## Adaptors

- filtered
- map_keys
- map_values
- reveresed
- sliced
- strided
- transformed

---

## Adaptors

- reversed

```cpp
std::vector<int> vec = { 1, 2, 3, 4 };
for(int i:vec | boost::adaptors::reversed)
{
    std::cout << i << std::endl;
}
```

---

## Adaptors

- map_values

```cpp
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
```

---

## Adaptors

- We can find all employee names who make over 100,000

```cpp
auto rich_employee_names = employees
    | boost::adaptors::filtered([](const employee& e) 
        { return e.salary > 100000; })
    | boost::adaptors::transformed([](const employee& e) 
        { return e.name; });
for(std::string name:rich_employee_names)
{
    std::cout << name << std::endl;
}
```

---

## Zip ranges

```cpp
auto differences = boost::combine(v1, v2) 
    | boost::adaptors::transformed(boost::fusion::make_fused(
        +[](float x, float y)
        {
            return x - y;
        })
    );
auto max_diff = boost::range::max_element(differences);
```

---

## Join ranges

```cpp
std::vector<int> v1 = { 1, 2, 3, 4};
std::vector<int> v2 = { 5, 6, 7, 8};
auto numbers = boost::range::join(v1, v2);
for(int i:numbers)
{
    std::cout << i << std::endl;
}
```

---

## Integer ranges

```cpp
auto numbers = boost::irange(1, 9);
for(int i:numbers)
{
    std::cout << i << std::endl;
}
```

---------

## Building ranges

- `iterator_range` class holds two iterators in order to make them a range

---

## Single

```cpp
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
```

---

## Drop while

```cpp
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
```

---

## Trim

```cpp
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
```

---

## Trim

```cpp
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
```

---








