cmake_minimum_required(VERSION 3.24.0)
project(Roguelike-Engine VERSION 1.0 LANGUAGES C CXX)

# Set CMake output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Include Dependency List
include(lib/CMakeLists.txt)

# Link Libraries
link_libraries(
    SDL2::SDL2main
    SDL2::SDL2
    gl3w
    imgui
    glm::glm
)

# Define main sources
set(SOURCES src/main.cpp)

set(ENGINE_NAME engine)
set(ENGINE_DIR ${CMAKE_CURRENT_LIST_DIR}/src/engine)
set(ENGINE_SOURCES)
include(src/CMakeLists.txt)
add_library(${ENGINE_NAME} SHARED ${ENGINE_SOURCES})

# Add the main sources
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${ENGINE_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE include)