cmake_minimum_required (VERSION 3.2)
project (BoostCoroutineExamples)

include(CheckCXXCompilerFlag)
enable_language(CXX)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


# Disable autolinking - comes from this Stack Overflow question:
# http://stackoverflow.com/questions/6646405/how-do-you-add-boost-libraries-in-cmakelists-txt
# Without this Boost Context / Coroutine would not work on good 'ole Windows.
add_definitions( -DBOOST_ALL_NO_LIB )

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)


find_package(Boost 1.57 COMPONENTS context coroutine system REQUIRED )

include_directories(${Boost_INCLUDE_DIRS})

macro(add_exe FILENAME)
    add_executable(${FILENAME}
                   ${CMAKE_CURRENT_SOURCE_DIR}/../src/${FILENAME}.cpp)
    target_link_libraries(${FILENAME} ${Boost_LIBRARIES} )
endmacro(add_exe)

add_exe(asio_example1)
add_exe(asio_example2)
add_exe(exceptions)
add_exe(fibonacci)
add_exe(fibonacci2)
add_exe(push_type_range)
add_exe(reverse_fibonacci)
add_exe(symmetric_coro)
