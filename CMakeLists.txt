cmake_minimum_required(VERSION 3.16)

project(N-Pendulum-2D)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)
find_package(Eigen3 REQUIRED)

add_executable(N-Pendulum-2D
    src/main.cpp
    src/State.cpp
    src/MathUtils.cpp
)

target_include_directories(N-Pendulum-2D
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(N-Pendulum-2D
    PRIVATE
        raylib
        Eigen3::Eigen
)