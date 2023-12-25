cmake_minimum_required(VERSION 3.14)

include("GNUInstallDirs")

add_library("${PROJECT_NAME}" STATIC "src/main.cxx")
file(GLOB_RECURSE "_include" "${CMAKE_CURRENT_SOURCE_DIR}/include" "*.hxx")
target_sources("${PROJECT_NAME}" PUBLIC ${_include})

target_compile_features("${PROJECT_NAME}" PUBLIC "cxx_std_17")
target_include_directories("${PROJECT_NAME}" PUBLIC "include")
