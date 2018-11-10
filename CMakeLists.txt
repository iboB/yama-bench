cmake_minimum_required(VERSION 3.2.2)

project(yama-bench)

include_directories(
    yama/include
    glm
    picobench/include
)

add_executable(yama-bench
    main.cpp
    inv-matrix.cpp
)
