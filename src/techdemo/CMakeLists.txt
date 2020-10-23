file(GLOB SRC_FILES *.cpp)

add_executable(techdemo ${SRC_FILES})

# TODO(laralex): maybe libraries should be installed in a certain path 
# to then be included/linked against
target_include_directories(techdemo PRIVATE ..) 

target_link_libraries(techdemo engine_core engine_render) 