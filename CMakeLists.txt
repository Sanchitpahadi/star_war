cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)

project(Game)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(
    /usr/dev/GL
    /usr/dev/GLFW
    /usr/dev/glm
)

# Add library directories (Optional, CMake usually finds these automatically)
link_directories(
    /usr/lib/x86_64-linux-gnu
    /usr/local/lib
)

# Manually set GLFW path if find_package fails
set(GLFW_DIR /usr/include/GLFW)

# Add executable
add_executable(game_executable 
    glad.c
    main.cpp 
    main.h
    
)

# Link OpenGL and GLFW manually
target_link_libraries(game_executable 
/usr/lib/x86_64-linux-gnu/libGL.so
/usr/lib/x86_64-linux-gnu/libglfw.so
/usr/lib/x86_64-linux-gnu/libGLEW.so

)
