file(GLOB HEADER_FILES *.hpp)
file(GLOB SRC_FILES *.cpp)

add_library(engine_render SHARED ${SRC_FILES})