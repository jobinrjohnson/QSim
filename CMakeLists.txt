cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (QSim)

add_subdirectory(implementation)
add_subdirectory(utils)

find_package(GSL REQUIRED)

add_executable(QSim QSim.cpp)
target_link_libraries(QSim LINK_PUBLIC utils implementation -lgsl -lgslcblas -lm)
