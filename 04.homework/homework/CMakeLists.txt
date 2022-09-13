cmake_minimum_required(VERSION 3.5)

project(homework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(homework main.cpp)

install(TARGETS homework
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
