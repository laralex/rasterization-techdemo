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
# TODO(laralex): need to tidy up artifacts from external libraries and CMake itself
string(TOUPPER "CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CMAKE_BUILD_TYPE}" OUTPUT_DIRECTORY) # debug to DEBUG
set(${OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
message(STATUS "> BUILD TYPE = ${CMAKE_BUILD_TYPE}")

# ==== install external libs ====
# TODO(laralex): check if Debug project build builds Release externals
set(EXTERN_BUILD_DIR ${CMAKE_BINARY_DIR}/extern)
set(EXTERN_SOURCE_DIR ${CMAKE_SOURCE_DIR}/extern)

# TODO(laralex): check if I can disable building of tests and examples
add_subdirectory(${EXTERN_SOURCE_DIR}/spdlog ${EXTERN_BUILD_DIR}/spdlog)
list(APPEND EXTERN_INCLUDE_DIRS ${EXTERN_SOURCE_DIR}/spdlog/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${EXTERN_SOURCE_DIR}/glfw ${EXTERN_BUILD_DIR}/glfw)
list(APPEND EXTERN_INCLUDE_DIRS ${EXTERN_SOURCE_DIR}/glfw/include)

add_library(glad STATIC ${EXTERN_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(glad PRIVATE ${EXTERN_SOURCE_DIR}/glad/include)
list(APPEND EXTERN_INCLUDE_DIRS ${EXTERN_SOURCE_DIR}/glad/include)

add_subdirectory(${EXTERN_SOURCE_DIR}/glm ${EXTERN_BUILD_DIR}/glm)
list(APPEND EXTERN_INCLUDE_DIRS ${EXTERN_SOURCE_DIR}/glm/include)

# ==== project libraries and executables ====
# TODO(laralex): need to install libraries in some way (put files in e.g. /include and /lib)
add_subdirectory(src/engine ${${OUTPUT_DIRECTORY}}/obj/engine)
add_subdirectory(src/techdemo ${${OUTPUT_DIRECTORY}}/obj/techdemo)

# ==== tests ====
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()