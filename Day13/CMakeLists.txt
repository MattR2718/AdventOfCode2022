cmake_minimum_required (VERSION 3.18)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(day13 day13.cpp)

target_link_libraries(
    day13
    nlohmann_json::nlohmann_json
)