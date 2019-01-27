include_directories(include)
add_library(utils STATIC src/util.cpp)
target_include_directories(utils PUBLIC include)
