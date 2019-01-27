include_directories(include)
FILE(GLOB src_files *.cpp)
add_library(utils STATIC ${src_files})
target_include_directories(utils PUBLIC include)
