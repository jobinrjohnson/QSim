cmake_minimum_required (VERSION 2.6)
project (QSim)

add_subdirectory(implementation)
add_subdirectory(utils)

add_executable(QSim QSim.cpp)
target_link_libraries(QSim LINK_PUBLIC utils implementation)
