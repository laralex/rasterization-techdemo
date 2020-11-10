include(GoogleTest)

# ==== build Google Test ====
# NOTE: not a git submodule so that it's not downloaded unless you build with tests
set(GTEST_PATH ${EXTERN_BUILD_DIR}/googletest)
configure_file(${CMAKE_SOURCE_DIR}/extern/googletest/CMakeLists.txt.in ${GTEST_PATH}/CMakeLists.txt)

# cmake step
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${GTEST_PATH})
if(result)
    message(FATAL_ERROR "Googletest CMAKE step failed: ${result}")
endif()

# build step
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${GTEST_PATH})
if(result)
    message(FATAL_ERROR "Googletest BUILD step failed: ${result}")
endif()

# prevent overriding compiler/linker settings (on Windows)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
#set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
#set(CMAKE_CTEST_COMMAND "${CMAKE_CTEST_COMMAND} --output-log ${CMAKE_BINARY_DIR}/test/ctestlog" CACHE STRING "" FORCE)
# define the gtest and gtest_main targets.
add_subdirectory(${GTEST_PATH}/src ${GTEST_PATH}/build EXCLUDE_FROM_ALL)
set_target_properties(gtest_main gmock_main gtest gmock PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${GTEST_PATH}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${GTEST_PATH}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${GTEST_PATH}/lib"
    PDB_OUTPUT_DIRECTORY     "${GTEST_PATH}/bin")
    
# ==== to shrink repetitive code ====
macro(assemble_test TESTNAME FILES)
    add_executable(${TESTNAME} ${FILES})
    target_include_directories(${TESTNAME} PRIVATE ${EXTERN_INCLUDE_DIRS} ../src)
    target_link_libraries(${TESTNAME} gtest gtest_main ${ARGN})
    gtest_discover_tests(${TESTNAME}
        SOURCES ${FILES}
        WORKING_DIRECTORY "${${OUTPUT_DIRECTORY}}"
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${${OUTPUT_DIRECTORY}}"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER mygtest)
endmacro()

# ==== tests ====
assemble_test(unit_tests example_test.cpp engine_render)

# ==== keep cache cleaner ====
# https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html
mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)
set_target_properties(gtest PROPERTIES FOLDER myglib)
set_target_properties(gtest_main PROPERTIES FOLDER myglib)
set_target_properties(gmock PROPERTIES FOLDER myglib)
set_target_properties(gmock_main PROPERTIES FOLDER myglib)