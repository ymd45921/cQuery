cmake_minimum_required(VERSION 3.17)
project(cQuery)
include(CheckCXXCompilerFlag)

set(CMAKE_CXX_STANDARD 20)

check_cxx_compiler_flag("-std=c++17" COMPILER_SUPPORTS_CXX17)
check_cxx_compiler_flag("-std=c++2a" COMPILER_SUPPORTS_CXX20)

message(STATUS "[INFO] Detected C/C++ Compiler: ${CMAKE_CXX_COMPILER}")
if(COMPILER_SUPPORTS_CXX20)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++2a")
    message(STATUS "[INFO] Your compiler is supported C++2a")
else()
    message(ERROR "[ERR!] Detected compiler has no C++20 or newer support.")
endif()

aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCE_DIRS)
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
file(GLOB HEADER_DIRS "${INCLUDE_PATH}/*.h")

include_directories(${INCLUDE_PATH})
get_property(dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_library(cQuery main.cpp ${SOURCE_DIRS} ${HEADER_DIRS})