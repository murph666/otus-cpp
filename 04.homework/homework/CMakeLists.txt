cmake_minimum_required(VERSION 3.5)

project(calc)
# Установка переменной со списком исходников для исполняемого файла
set(SOURCE_EXE
    src/astnode.cpp
    src/lexer.cpp
    src/parser.cpp
    src/main.cpp)
# Тоже самое, но для библиотеки
set(SOURCE_LIB
    include/astnode.hpp
    include/lexer.hpp
    include/parser.hpp
    include/number.hpp)

add_library(lib ${SOURCE_LIB})
add_executable(main ${SOURCE_EXE})

target_link_libraries(main lib)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(main PRIVATE
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(main PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()
