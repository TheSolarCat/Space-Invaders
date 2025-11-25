cmake_minimum_required(VERSION 3.10)
project(SpaceInvaders CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force MSVC if on Windows
if(WIN32)
    set(CMAKE_C_COMPILER "cl.exe")
    set(CMAKE_CXX_COMPILER "cl.exe")
endif()

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Bullet.cpp
    src/GameConfig.cpp
)

# Create executable
add_executable(SpaceInvaders ${SOURCES})

# Link libraries
target_link_libraries(SpaceInvaders PRIVATE sfml-graphics sfml-window sfml-system)

# Copy resources to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.ini 
               ${CMAKE_CURRENT_BINARY_DIR}/config.ini COPYONLY)
