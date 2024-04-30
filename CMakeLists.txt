cmake_minimum_required(VERSION 3.24.0)
project(Roguelike-Engine VERSION 1.0 LANGUAGES C CXX)

# Set CMake output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Include Dependency List
include(lib/CMakeLists.txt)

# Include SDL2 as a Dependency
find_package(SDL2 QUIET)
include_directories(${SDL2_INCLUDE_DIRS})

# Compile the main project
add_executable(${PROJECT_NAME} main.cpp)

# Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
    libglew_static
    glm::glm # GL Math
)
target_include_directories(${PROJECT_NAME} PRIVATE include)