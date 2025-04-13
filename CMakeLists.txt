cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 23)

project(8080 LANGUAGES CXX)

include(src/CMakeLists.txt)

add_executable(8080 ${SRC})
target_include_directories(8080 PUBLIC include)
target_compile_options(8080 PRIVATE -Werror -Wall -Wextra)