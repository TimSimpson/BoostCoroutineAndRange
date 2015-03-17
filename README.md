# BoostCoroutineAndRange

This repo contains the March 11 Austin C/C++ Presentation Double Feature for Boost Range and Coroutine material.

The Boost.Range material was created by Paul Fultz, while Boost.Coroutine's material was created by Tim Simpson (who mostly copied the Boost examples as stated by the comments).

If you want more information on these libraries, below are instructions on how to build all the examples for the curious.

## PreReqs

This repo has a few submodules it needs, such as Fit or the Reveal.JS framework. Initialize them with "git submodule update --init" before proceeding.

Next, you'll need to build the "sampler" utility, written by Zach Laine. This is used to embed example snippets later.

Enter the directory ./sampler/CMake and execute the following:

$ cmake CMakeLists.txt -b ./
$ cmake --build ./


[Ranges](https://timsimpson.github.io/BoostCoroutineAndRange/ranges/)


## CMake

Enter the directory ./ranges/CMake and execute the following:

$ cmake CMakeLists.txt -b ./
$ cmake --build ./

Note: these examples feature C++11 features not yet implemented by Visual Studio, so you may need to install MinGW or TDM GCC and run 'cmake -G "MinGW Makefiles"' as step 1.5 above.

[Coroutine](https://timsimpson.github.io/BoostCoroutineAndRange/ranges/coroutine.html)

Build instructions:

## Boost Build

Enter the Boost Build directory and execute the following:

$ b2

(You may need to use link=static)

## CMake

Enter the directory ./Coroutine/CMake and execute the following:

$ cmake CMakeLists.txt -b ./
$ cmake --build ./

## Slides

The slides need NodeJS, NPM, and Grunt.

Enter the directory ./slides and execute the following:

$ npm install
$ grunt serve
