cmake_minimum_required(VERSION 3.24.0)
project(Roguelike-Engine VERSION 1.0 LANGUAGES C CXX)

# Include Dependency List
include(lib/CMakeLists.txt)

# Include SDL2 as a Dependency
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Compile the main project
add_executable(${PROJECT_NAME} main.cpp)

# Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES} # SDL2
    libglew_static
    glm::glm # GL Math
)
target_include_directories(${PROJECT_NAME} PRIVATE include)