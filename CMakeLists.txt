# ==== prelude ====
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(rasterization_techdemo)
set(CMAKE_CXX_STANDARD 17)

option(PACKAGE_TESTS "Build the tests" ON)

# ==== build types ====
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE release)
endif(NOT CMAKE_BUILD_TYPE)

string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)

set(BUILD_TYPES debug release)
if (CMAKE_BUILD_TYPE MATCHES debug)
    add_definitions(-DDEBUG)
elseif(NOT ${CMAKE_BUILD_TYPE} IN_LIST ${BUILD_TYPES})
    message(FATAL_ERROR "> UKNOWN BUILD TYPE: neither of ${BUILD_TYPES}")
endif()

# ==== artifacts folders ====
string(TOUPPER "CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CMAKE_BUILD_TYPE}" OUTPUT_DIRECTORY) # debug to DEBUG
set(${OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
message(STATUS "> BUILD TYPE = ${CMAKE_BUILD_TYPE}")

# ==== libraries and executables ====
add_subdirectory(src/engine ${${OUTPUT_DIRECTORY}}/obj/engine)
add_subdirectory(src/techdemo ${${OUTPUT_DIRECTORY}}/obj/techdemo)

# ==== tests ====
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()