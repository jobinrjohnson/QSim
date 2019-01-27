include_directories(include)
FILE(GLOB src_files *.cpp)
add_library(implementation STATIC ${src_files})
target_include_directories(implementation PUBLIC include)
