cmake_minimum_required(VERSION 3.14)
project(boost_graph_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск Boost (требуется компонент graph)
find_package(Boost 1.70 REQUIRED COMPONENTS graph)

add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE Boost::graph)
