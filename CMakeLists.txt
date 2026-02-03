cmake_minimum_required(VERSION 3.10)
project(Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------
# Include paths
# -------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}/dev
    ${CMAKE_SOURCE_DIR}/src/include
)

# -------------------------
# Source files
# -------------------------
set(SOURCES
    src/glad.c
    src/main.cpp
    src/Texture.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
    src/VertexBufferLayout.cpp
)

add_executable(cpp ${SOURCES})

# -------------------------
# Libraries
# -------------------------
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(cpp
    OpenGL::GL
    glfw
    dl
)

# -------------------------
# Copy shaders next to exe
# -------------------------
file(GLOB SHADER_FILES
    "${CMAKE_SOURCE_DIR}/src/shader/*.vs"
    "${CMAKE_SOURCE_DIR}/src/shader/*.fs"
)

foreach(SHADER ${SHADER_FILES})
    add_custom_command(TARGET cpp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${SHADER}
        $<TARGET_FILE_DIR:cpp>
    )
endforeach()

# -------------------------
# Copy texture directory
# -------------------------
add_custom_command(TARGET cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/texture
    $<TARGET_FILE_DIR:cpp>/texture
)
