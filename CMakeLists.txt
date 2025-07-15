cmake_minimum_required(VERSION 3.10)

project(kr2-obj-parser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Option to build with graphics
option(BUILD_GRAPHICS "Build with graphics support" ON)

# Add googletest first
add_subdirectory(vendor/googletest)

# Include Google Test CMake module
include(GoogleTest)

# Add graphics dependencies only if enabled
if(BUILD_GRAPHICS)
    add_subdirectory(vendor/glfw)
    add_subdirectory(vendor/glad)
    # add_subdirectory(vendor/spdlog)
    add_subdirectory(vendor/glm)
    add_subdirectory(vendor/fmt)
    add_subdirectory(vendor/stb)
endif()

# Create test executable (minimal dependencies)
add_executable(test_parser
        test/test_parser.cpp
        obj_parser.cpp
        vertex_parser.cpp
        face_parser.cpp)

target_include_directories(test_parser
        PUBLIC .)

target_link_libraries(test_parser
        gtest
        gtest_main
        pthread)

# Enable testing
enable_testing()

# Use Google Test's automatic test discovery
gtest_discover_tests(test_parser
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Also keep the simple test for backward compatibility
add_test(NAME all_tests COMMAND test_parser WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Create main executable only if graphics are enabled
if(BUILD_GRAPHICS)
    add_executable(${PROJECT_NAME}
            main.cpp
            obj_parser.cpp
            vertex_parser.cpp
            face_parser.cpp

            # Application
            Core/Application.cpp
            Core/OpenGLApplication.cpp
            Core/Log.cpp

            Graphics/VertexBuffer.cpp
            Graphics/IndexBuffer.cpp
            Graphics/Shader.cpp
            Graphics/VertexArray.cpp
            Graphics/Texture.cpp)

    target_include_directories(${PROJECT_NAME}
            PUBLIC .
            PUBLIC Core
            PUBLIC Graphics)

    target_link_libraries(${PROJECT_NAME} PUBLIC
            glfw
            glad::glad
            glm::glm
            fmt::fmt
            stb::stb)
endif()
