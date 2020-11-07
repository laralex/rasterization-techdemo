file(GLOB HEADER_FILES *.hpp)
file(GLOB SRC_FILES *.cpp)

add_library(engine_render SHARED ${SRC_FILES})

# TODO(laralex): maybe libraries should be installed in a certain path 
# to then be included/linked against
# TODO(laralex): maybe only necessary libraries should be included, not all 
# (e.g. logging library isn't needed there)
target_include_directories(engine_render PRIVATE ${EXTERN_INCLUDE_DIRS} ../..) 

target_link_libraries(engine_render engine_core) 