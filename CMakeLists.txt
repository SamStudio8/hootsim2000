cmake_minimum_required(VERSION 2.8)

project(hootsim2000)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -Wextra -Werror -pedantic")

FILE(GLOB_RECURSE HOOTSIM_SOURCES "src/*.cpp")
FILE(GLOB_RECURSE HOOTSIM_HEADERS "include/*.hpp")

source_group("Header Files" FILES ${HOOTSIM_HEADERS})
source_group("Source Files" FILES ${HOOTSIM_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(hootsim2000 ${HOOTSIM_SOURCES} ${HOOTSIM_HEADERS})

# TODO remove main.cpp from hootsim library
add_library(hootsim ${HOOTSIM_SOURCES} ${HOOTSIM_HEADERS})

install(TARGETS hootsim2000 RUNTIME DESTINATION bin)
