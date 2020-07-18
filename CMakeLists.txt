cmake_minimum_required(VERSION 3.5)

project(expt)

set(CXX_FLAGS -std=c++17 -g -Wall -Werror -Wextra)
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bst)