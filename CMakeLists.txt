cmake_minimum_required(VERSION 3.24)

project("p5-async_primitives" LANGUAGES "CXX")

add_subdirectory("library")

if (CMAKE_CURRENT_SOURCE_DIR PATH_EQUAL CMAKE_SOURCE_DIR)
    add_subdirectory("examples")
endif (CMAKE_CURRENT_SOURCE_DIR PATH_EQUAL CMAKE_SOURCE_DIR)
