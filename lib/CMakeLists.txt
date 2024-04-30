# Add the SDL2 Library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/SDL2)

# Add the GL Math Library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/GLM)

# Add GLEW 
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/GLEW)
set(ONLY_LIBS ON) # Set to only build libraries