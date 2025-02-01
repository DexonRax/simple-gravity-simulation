cmake_minimum_required(VERSION 3.10)

# Project name and version
project(GravitySim VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable target with source files
add_executable(${PROJECT_NAME}
    main.cpp
)
#     src/Label.cpp
#     src/Player.cpp
#     src/Tilemap.cpp
# )

# Include directories for header files
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Find and link SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

# Find and link noise library
find_library(NOISE_LIB noise REQUIRED)
if(NOISE_LIB)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${NOISE_LIB})
else()
    message(FATAL_ERROR "Noise library not found")
endif()

# Copy 'assets' and 'libs' directories to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/libs DESTINATION ${CMAKE_BINARY_DIR})

