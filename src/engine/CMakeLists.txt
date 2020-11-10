# ==== prelude ====
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(engine)
set(CMAKE_CXX_STANDARD 17)

# ==== targets ====
file(GLOB HEADER_FILES core/*.hpp)
file(GLOB SRC_FILES core/*.cpp)
add_library(engine_core SHARED ${SRC_FILES})

file(GLOB HEADER_FILES render/*.hpp)
file(GLOB SRC_FILES render/*.cpp)
add_library(engine_render SHARED ${SRC_FILES})
target_include_directories(engine_render PRIVATE ${EXTERN_INCLUDE_DIRS} ..) 
target_link_libraries(engine_render engine_core glad glfw glm imgui) 

# TODO(laralex): maybe libraries should be installed in a certain path 
# to then be included/linked against
# TODO(laralex): maybe only necessary libraries should be included, not all 
# (e.g. logging library isn't needed there)
# TODO(laralex): maybe some cmake variables for common libraries names and include paths