# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 3.19)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")

# Set the name and the supported language of the project
project(6 C)

#Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtkmm-3.0)


# Add other flags to the compiler
ADD_DEFINITIONS(${GTK_CFLAGS_OTHER})
add_executable(6 src/gtk3.c)
TARGET_LINK_LIBRARIES(6 ${GTK_LIBRARIES})


# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK_LIBRARY_DIRS})
