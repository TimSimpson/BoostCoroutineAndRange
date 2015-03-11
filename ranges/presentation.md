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

%%operations%%

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

%%sort_iterators%%

---

## Range Algorithms

%%sort_range%%

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

%%intersection_to_array%%

---

## Intersection

%%intersection_copy%%

---

## Intersection

%%intersection_print%%

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

%%reverse_adaptors%%

---

## Adaptors

- map_values

%%map_values_adaptors%%

---

## Adaptors

- We can find all employee names who make over 100,000

%%rich_employees%%

---

## Zip ranges

%%zip_ranges%%

---

## Join ranges

%%join_ranges%%

---

## Integer ranges

%%integer_ranges%%

---------

## Building ranges

- `iterator_range` class holds two iterators in order to make them a range

---

## Single

%%single%%

---

## Drop while

%%drop_while%%

---

## Trim

%%trim1%%

---

## Trim

%%trim2%%


---------

## Caveats

- Calling adaptors on temporaries, will crash

%%map_caveat%%

---

## Caveats

- Passing lambdas to adaptors or iterators may not compile
    - Iterators need to be default constructible
    - Lambas are not default constructible
    - Lambas are stored in the iterators

---

## Caveats

- For non-generic lambdas that don't capture add a `+` in front of it to convert it to a plain function

%%rich_employees%%

---

## Caveats

- For other lambdas use a regular adaptor

%%rich_employees_regular%%

---

## Caveats

%%regular%%

---------

## Other libraries

- Pstade.Oven
    - http://p-stade.sourceforge.net/oven/doc/html/index.html

- ranges-v3
    - http://p-stade.sourceforge.net/oven/doc/html/index.html

