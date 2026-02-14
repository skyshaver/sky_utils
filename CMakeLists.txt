cmake_minimum_required(VERSION 3.25)

project("sky_utils")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(sky_utils_HEADERS
    sky_utils.hpp
)

set(sky_utils_TESTS
    tests/sky_utils_test.cpp
)

# Download the dependencies to the same folder as the project.
# To install them system-wide, set CPM_SOURCE_CACHE with a path to the dependencies
# either as an environment variable or pass it with -DCPM_SOURCE_CACHE=<path> when invoking cmake.
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

include(cmake/cpm.cmake)

# Adds googletest.
cpmaddpackage(
    NAME
    GOOGLETEST
    GITHUB_REPOSITORY
    google/googletest
    VERSION
    1.16.0
    SOURCE_DIR
    ${LIB_DIR}/googletest
    OPTIONS
    "INSTALL_GTEST OFF"
    "gtest_force_shared_crt ON"
)

enable_testing()

add_executable(sky_utils_tests ${sky_utils_TESTS})

target_link_libraries(
    sky_utils_tests
    PRIVATE
    GTest::gtest_main
)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin/)