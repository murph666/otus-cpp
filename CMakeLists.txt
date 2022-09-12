cmake_minimum_required(VERSION 3.5)
set(file "4homework")

project(${file}CXX)

add_executable(${file} 
    ${file}.cpp

)

target_compile_features(${file} PUBLIC cxx_std_17)

if (MSVC)
    target_compile_options(${file} PUBLIC /W4 /WX)
else()
    target_compile_options(${file} PUBLIC -Wall -Wextra -pedantic -Werror)
endif()
