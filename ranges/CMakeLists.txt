cmake_minimum_required (VERSION 2.6)
project (Presentation)

include(CheckCXXCompilerFlag)
enable_language(CXX)

if(CMAKE_HOST_APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(ENABLE_CXXFLAGS_TO_CHECK 
    -std=gnu++1y 
    -std=c++1y
    -std=gnu++11 
    -std=c++11
    -std=gnu++0x 
    -std=c++0x)

foreach(flag ${ENABLE_CXXFLAGS_TO_CHECK})
    string(REPLACE "-std=" "_" flag_var ${flag})
    string(REPLACE "+" "x" flag_var ${flag_var})
    check_cxx_compiler_flag("${flag}" COMPILER_HAS_CXX_FLAG${flag_var})
    if(COMPILER_HAS_CXX_FLAG${flag_var})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}")
        break()
    endif()
endforeach()

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(sampler)

file(GLOB filenames ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

foreach (filename ${filenames})
    get_filename_component(basename ${filename} NAME_WE)
    add_executable(code_sample_${basename} ${filename})
endforeach ()

macro(process_presentation FILENAME)
    add_custom_command(
        OUTPUT
            ${FILENAME}
        COMMAND
            sampler
            ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.in
            ${CMAKE_SOURCE_DIR}/${FILENAME}
            ${filenames}
        DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}.in
            ${filenames}
        COMMENT
            "Generating ${FILENAME} from ${FILENAME}.in and source code samples."
    )
    string(REPLACE "." "_" TARGETNAME ${FILENAME})
    string(REPLACE "/" "_" TARGETNAME ${TARGETNAME})
    add_custom_target(gen_${TARGETNAME} ALL DEPENDS ${FILENAME})
endmacro(process_presentation)

process_presentation(presentation.md)
