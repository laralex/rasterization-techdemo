file(GLOB HEADER_FILES *.hpp)
file(GLOB SRC_FILES *.cpp)

add_library(engine_render SHARED ${SRC_FILES})

# TODO(laralex): maybe libraries should be installed in a certain path 
# to then be included/linked against
target_include_directories(engine_render PRIVATE ../..) 

target_link_libraries(engine_render engine_core) 