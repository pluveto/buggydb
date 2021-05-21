cmake_minimum_required(VERSION 3.0.0)
project(buggydb VERSION 0.1.0)

include_directories("include")

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(buggydb src/buggydb.cpp ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# FOR TESTING
add_executable(primary_test test/primary_test.cpp)
TARGET_LINK_LIBRARIES(primary_test buggydb)
