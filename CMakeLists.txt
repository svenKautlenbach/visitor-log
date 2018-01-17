cmake_minimum_required(VERSION 3.7)
project(visitor-log)

add_compile_options(-std=c++1z -Wall -Werror -Wextra -fsanitize=address)
link_libraries(-fsanitize=address)

include_directories( src/ )

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(visitor-log main.cpp ${SOURCE_FILES})
