cmake_minimum_required(VERSION 3.5)


project(06.homework)

# Установка переменной со списком исходников для исполняемого файла
set(SOURCE_EXE
    main.cpp)
set(SOURCE_LIB
    serial_container.hpp
)

add_executable(main ${SOURCE_EXE} ${SOURCE_LIB})


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
