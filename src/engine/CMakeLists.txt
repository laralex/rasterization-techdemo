# ==== prelude ====
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(engine)
set(CMAKE_CXX_STANDARD 17)

# ==== targets ====
add_subdirectory(core)
add_subdirectory(render)