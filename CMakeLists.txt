cmake_minimum_required(VERSION 2.6)

project(PIRATES)

set(EXECUTABLE_OUTPUT_PATH "bin/")
include_directories("${CMAKE_SOURCE_DIR}/header")

add_definitions(-Wall -std=c++11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1 sfml-network>=2.1)
pkg_check_modules(BOX2D REQUIRED box2d>=2.3)
pkg_check_modules(LIBTMX   REQUIRED libtmx>=0.1)
pkg_check_modules(THOR REQUIRED thor>=2.0)

add_subdirectory(lib)

file(GLOB SRC_SRV "src/server/*")
file(GLOB SRC_CLT "src/client/*")
file(GLOB SRC_CMN "src/common/*")
file(GLOB_RECURSE HEADERS "header/*")

add_executable(server ${SRC_SRV} ${SRC_CMN} ${HEADERS})
add_executable(client ${SRC_CLT} ${SRC_CMN} ${HEADERS})

target_link_libraries(server libWorldBox libServer libCommon)
target_link_libraries(client libClient libCommon)


