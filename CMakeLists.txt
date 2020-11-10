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
elseif(NOT ${CMAKE_BUILD_TYPE} IN_LIST BUILD_TYPES)
    message(FATAL_ERROR "> UKNOWN BUILD TYPE: neither of ${BUILD_TYPES}")
endif()

# ==== artifacts folders ====
# TODO(laralex): need to tidy up artifacts from external libraries and CMake itself
# set(CMAKE_INSTALL_LIBDIR "extern" CACHE INTERNAL STRING FORCE)
string(TOUPPER "CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CMAKE_BUILD_TYPE}" OUTPUT_DIRECTORY) # debug to DEBUG
set(${OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
message(STATUS "> BUILD TYPE = ${CMAKE_BUILD_TYPE}")

# ==== install external libs ====
# MAYBE(laralex): check if Debug project build builds Release externals,
# actually for debugging purposes it's better to have more detailed crashes, so forget it
set(EXTERN_BUILD_DIR  ${CMAKE_BINARY_DIR}/extern/${CMAKE_BUILD_TYPE})
set(EXTERN_SOURCE_DIR ${CMAKE_SOURCE_DIR}/extern)

# > spdlog -- logging
add_subdirectory(${EXTERN_SOURCE_DIR}/spdlog ${EXTERN_BUILD_DIR}/spdlog)
list(APPEND EXTERN_INCLUDE_DIRS ${EXTERN_SOURCE_DIR}/spdlog/include)

# > glfw -- everything for openGL, vulkan and cross-platform windows
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${EXTERN_SOURCE_DIR}/glfw ${EXTERN_BUILD_DIR}/glfw)
set_target_properties(glfw PROPERTIES COMPILE_FLAGS "-w") # no warnings
list(APPEND EXTERN_INCLUDE_DIRS ${EXTERN_SOURCE_DIR}/glfw/include)

# > glad -- load openGL for the target machine
# TODO(laralex): glad2
set(GLAD_API "gl=4.5")
set(GLAD_PROFILE "compatibility") 
set(GLAD_EXTENSIONS "GL_ARB_vertex_shader,GL_ARB_fragment_shader")
add_subdirectory(${EXTERN_SOURCE_DIR}/glad ${EXTERN_BUILD_DIR}/glad)
list(APPEND EXTERN_INCLUDE_DIRS ${EXTERN_SOURCE_DIR}/glad/include)

# > glm -- math for graphics
add_subdirectory(${EXTERN_SOURCE_DIR}/glm ${EXTERN_BUILD_DIR}/glm)
list(APPEND EXTERN_INCLUDE_DIRS ${EXTERN_SOURCE_DIR}/glm/include)

# > imgui -- GUI extensions
# TODO(laralex): set artifact path
# TODO(laralex): maybe not PRIVATE includes
set(IMGUI_INCLUDE_DIR ${EXTERN_SOURCE_DIR}/imgui_)
file(GLOB   IMGUI_SRC_FILES ${IMGUI_INCLUDE_DIR}/imgui/*.cpp)
list(APPEND IMGUI_SRC_FILES ${IMGUI_INCLUDE_DIR}/imgui/backends/imgui_impl_glfw.cpp 
                            ${IMGUI_INCLUDE_DIR}/imgui/backends/imgui_impl_opengl3.cpp)
add_library(imgui STATIC ${IMGUI_SRC_FILES})
target_include_directories(imgui PRIVATE ${IMGUI_INCLUDE_DIR}/imgui ${EXTERN_SOURCE_DIR}/glfw/include)
target_compile_definitions(imgui PRIVATE 
    -DIMGUI_IMPL_OPENGL_LOADER_GLAD 
    -DIMGUI_USER_CONFIG="${CMAKE_SOURCE_DIR}/src/engine/gui/custom_imgui_config.h")
target_link_libraries(imgui glfw glad)
set_target_properties(imgui PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${EXTERN_BUILD_DIR}/imgui")
# NOTE(laralex): I like including via <imgui/imgui.h>, but imgui internals sadly use just "imgui.h", 
# so I have to expose them like that
list(APPEND EXTERN_INCLUDE_DIRS ${IMGUI_INCLUDE_DIR} ${IMGUI_INCLUDE_DIR}/imgui) 

# ==== project libraries and executables ====
# TODO(laralex): need to install libraries in some way (put files in e.g. /include and /lib)
add_subdirectory(src/engine   ${${OUTPUT_DIRECTORY}}/obj/engine)
add_subdirectory(src/techdemo ${${OUTPUT_DIRECTORY}}/obj/techdemo)

# ==== tests ====
if(PACKAGE_TESTS)
    message(STATUS "> BUILDING TESTS")
    enable_testing()
    add_subdirectory(test)
endif()