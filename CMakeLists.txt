cmake_minimum_required(VERSION 3.16)
project(NPendulum2D)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib REQUIRED)
find_package(Eigen3 REQUIRED)

add_executable(NPendulum2D
    main.cpp
    State.cpp
    MathUtils.cpp
)

target_link_libraries(NPendulum2D
    raylib
    Eigen3::Eigen
)