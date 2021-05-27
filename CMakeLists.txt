# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")

# Set the name and the supported language of the project
project(6 C)

#Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
#pkg_check_modules(GTK REQUIRED gtkmm-3.0)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")




# Add other flags to the compiler
ADD_DEFINITIONS(${GTK_CFLAGS_OTHER})
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.c)
add_executable(${PROJECT_NAME} ${SRC_FILES})
add_library(${PROJECT_NAME}_library SHARED ${SRC_FILES})

#add_executable(6 src/gtk3.c src/persons.c src/seat_rows.c src/main.c)
TARGET_LINK_LIBRARIES(6 ${GTK_LIBRARIES})


# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(inc ${GTK_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK_LIBRARY_DIRS})
