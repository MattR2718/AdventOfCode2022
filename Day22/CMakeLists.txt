cmake_minimum_required (VERSION 3.18)

find_package(Boost REQUIRED)

add_executable(day22 day22.cpp)

target_link_libraries(day22 Boost::boost)