cmake_minimum_required(VERSION 3.20)

cmake_path(
    RELATIVE_PATH CMAKE_CURRENT_SOURCE_DIR
    BASE_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE "_target_prefix"
)
string(REGEX REPLACE "[^A-z]" "." "_target_prefix" "${_target_prefix}")
string(PREPEND "_target_prefix" "${PROJECT_NAME}.")

add_library("${_target_prefix}.common" INTERFACE)
target_compile_features("${_target_prefix}.common" INTERFACE "cxx_std_20")
target_link_libraries("${_target_prefix}.common" INTERFACE "${PROJECT_NAME}")

add_executable("${_target_prefix}.main" "src/main.cxx")
target_link_libraries("${_target_prefix}.main" PRIVATE "${_target_prefix}.common")
