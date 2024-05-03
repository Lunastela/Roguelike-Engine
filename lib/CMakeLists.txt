
# Add the SDL2 Library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/SDL2)
find_package(SDL2 QUIET)
include_directories(${SDL2_INCLUDE_DIRS})

# Add the GL Math Library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/GLM)

# Generate GL3W files
set(GLM_ENABLE_CXX_11 ON)
execute_process(COMMAND python gl3w_gen.py --root ${CMAKE_CURRENT_LIST_DIR}/GL3W WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/GL3W)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/GL3W)
include_directories(${GL3W_INCLUDE})

# Add the imgui library
set(IMGUI_DIR ${CMAKE_CURRENT_LIST_DIR}/imgui)
file(GLOB IMGUI_SOURCES 
    ${IMGUI_DIR}/*.cpp 
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp 
)
add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_SOURCES}/backends/)
target_link_libraries(imgui PRIVATE 
    SDL2::SDL2main
    SDL2::SDL2
)
target_include_directories(imgui PRIVATE ${SDL2_INCLUDE_DIRS})
include_directories(${IMGUI_DIR})