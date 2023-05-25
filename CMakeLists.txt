cmake_minimum_required(VERSION 3.24)
project(blockKiller)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
#find_package(Boost 1.82 COMPONENTS REQUIRED system CONFIG)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED CONFIG)
#find_package(Box2d COMPONENTS REQUIRED CONFIG)

add_subdirectory(src)
