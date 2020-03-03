cmake_minimum_required(VERSION 3.0.0)

project(dynalo-test)

set(CMAKE_CXX_STANDARD          11 )
set(CMAKE_CXX_STANDARD_REQUIRED ON )
set(CMAKE_CXX_EXTENSIONS        OFF)

add_executable(loader loader.cpp)
target_link_libraries(loader PRIVATE dynalo)

add_library(shared SHARED shared.cpp)
target_link_libraries(shared PRIVATE dynalo)


target_sources(shared PUBLIC shared.hpp)

add_dependencies(loader shared)

enable_testing()

add_test(NAME function_test 
    COMMAND loader "$<TARGET_FILE_DIR:shared>" "function"
)

add_test(NAME function_pointer_test 
    COMMAND loader "$<TARGET_FILE_DIR:shared>" "function_ptr"
)
