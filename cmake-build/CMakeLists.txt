cmake_minimum_required(VERSION 3.10.0)
project(hospital_simulator C CXX)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()
find_package(PkgConfig REQUIRED) # To check for the GTK Module
pkg_check_modules(GTK REQUIRED "gtk+-3.0")
find_package(Threads REQUIRED)

include(${CMAKE_CURRENT_SOURCE_DIR}/modules/GTest_ExternalProject.cmake)
include(GoogleTest)
include(${CMAKE_CURRENT_SOURCE_DIR}/modules/CodeCoverage.cmake)
append_coverage_compiler_flags()

include_directories(../inc ${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ../src/*.c)
list(FILTER SRC_FILES EXCLUDE REGEX "quick_save.c")
add_executable(${PROJECT_NAME} ${SRC_FILES})
add_library(${PROJECT_NAME}_library SHARED ${SRC_FILES})

add_dependencies(${PROJECT_NAME}
    ${PROJECT_NAME}
    libgtest
    libgtest_main
)

file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS ../tests/*.cxx)
add_executable(${PROJECT_NAME}_unit_tests ${TEST_FILES})
add_dependencies(${PROJECT_NAME}_unit_tests
    ${PROJECT_NAME}_library
    libgtest
    libgtest_main
)

set(WARNING_LEVELS_GCC
    -Werror
)
set(WARNING_LEVELS_GCC_DEBUG
	-Wall
	-Wextra
	-Wno-unused-parameter
	# -pedantic
	-Wno-write-strings
	-g
)

target_link_libraries(${PROJECT_NAME} ${GTK_LDFLAGS})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTK_CFLAGS} ${WARNING_LEVELS_GCC_DEBUG})

target_link_libraries(${PROJECT_NAME}_unit_tests ${GTK_LDFLAGS} ${GTEST_LDFLAGS} libgtest libgtest_main ${PROJECT_NAME}_library)
target_compile_options(${PROJECT_NAME}_unit_tests PRIVATE ${GTK_CFLAGS} ${GTEST_CFLAGS} ${WARNING_LEVELS_GCC_DEBUG})

gtest_discover_tests(${PROJECT_NAME}_unit_tests)
setup_target_for_coverage_gcovr_html(
    NAME ${PROJECT_NAME}_coverage
    EXECUTABLE ctest -j ${PROCESSOR_COUNT}
    DEPENDENCIES ${PROJECT_NAME}_unit_tests
    EXCLUDE "${CMAKE_CURRENT_BINARY_DIR}/gtest/*")