# Boost.Coroutine

---------

## Introduction

A coroutine is a routine that can be interrupted and resumed at multiple points.

---
## Introduction


<img src="pics/24h.jpg" width=120 height=280/>

In contrast, threads are like 24 where multiple events are always happening at the same time.

---
## Introduction

<img src="pics/ql.png"/>

Think of the show Quantum Leap. The function is going somewhere, but in between it meets crazy characters and embarks on other adventures before returning to what it was doing before. In that sense, the coroutine is the main story but it always takes breaks so Scott Bakula can look in a mirror and be in a wig.


---------
## State Machines

Often programs that involve parallel actions without using threads may need to write state machines to solve the problems. A good example is entity AI in games.

---------

## Generators

Python fans (who are all several miles south at the Capital Factory right now) know all about generators. Boost.Coroutine can allow for the same kind of functionality in C++.

Note that complex iteration semantics are supported.

See fibonacci.cpp, fibonacci2.cpp

---

## Push Type vs Pull Type

Generators get invoked as "pull" type, which means the thing using them "pulls" data, while the earlier game example would have been a "push" type as data (the elapsed time) was passed into it.

Note that the push types can be used as output iterators.

---
## Symmetric Coroutines

In some cases it can be useful to have a coroutine not return to its caller when suspending but instead call any other coroutine. Symmetric coroutines allow this.

See symmetric_coro.cpp


---------


## Boost.ASIO Support

Boost ASIO is a great communication library, but much of the code ends up being difficult to parse as it has to use generous amounts of call back functions.

However some of this can be alleviated thanks to its relatively recent Boost.Coroutine support.

See asio_example1.cpp, asio_example2.cpp


---------

## Portability

Boost.Coroutine depends on Boost.Context which requires some assembly code. Currently supported on x86_64, arm, i386, mips1, ppc3, ppc64:

http://www.boost.org/doc/libs/1_57_0/libs/context/doc/html/context/architectures.html


---------

## Alternative- Duff's Device

If you really need to use coroutines but have to write portable code, one solution may be to utilize case-label fall through to create "stackless" coroutines. These coroutines can't have local variables that retain their value between being interrupted and resumed and can only work within a single function (just like Python generators).

---

## Alternative- Duff's Device

Simon Tatham has a good write up on this solution, but the gist is to use macros to simulate a yield statement which actually create case statements and set a variable for the switch statement inside a state machine.

http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html

---

## Alternatives - Boost ASIO Coroutines

This is actually such a handy tool that Boost ASIO includes a version of it as part of it's library.

http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html

However I recommend everyone build their own. Its fun, like those science kits they sell for children that use potatos to make a race car.

---
