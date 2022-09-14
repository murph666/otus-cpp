cmake_minimum_required(VERSION 3.5)

project(calc)

# Установка переменной со списком исходников для исполняемого файла
set(SOURCE_EXE
    src/astnode.cpp
    src/lexer.cpp
    src/parser.cpp
    src/main.cpp)
set(SOURCE_LIB
    include/astnode.hpp
    include/lexer.hpp
    include/parser.hpp
    include/Add.hpp
    include/Sub.hpp
    include/Mul.hpp
    include/Div.hpp
    include/Variable.hpp
    include/number.hpp)

add_executable(calc ${SOURCE_EXE} ${SOURCE_LIB})
target_include_directories(calc PRIVATE include)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(calc PRIVATE
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(calc PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()
