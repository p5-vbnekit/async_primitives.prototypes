cmake_minimum_required(VERSION 3.20)

cmake_path(
    RELATIVE_PATH CMAKE_CURRENT_SOURCE_DIR
    BASE_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE "_target_prefix"
)
string(REGEX REPLACE "[^A-z]" "." "_target_prefix" "${_target_prefix}")
string(PREPEND "_target_prefix" "${PROJECT_NAME}.")

find_package(QT NAMES "Qt5" "Qt6" REQUIRED COMPONENTS "Core")
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS "Core")

add_library("${_target_prefix}.common" INTERFACE)
target_compile_features("${_target_prefix}.common" INTERFACE "cxx_std_17")
target_link_libraries("${_target_prefix}.common" INTERFACE "Qt${QT_VERSION_MAJOR}::Core")
target_link_libraries("${_target_prefix}.common" INTERFACE "${PROJECT_NAME}")

add_executable("${_target_prefix}.easy" "src/easy.cxx")
add_executable("${_target_prefix}.hard" "src/hard.cxx")
add_executable("${_target_prefix}.nightmare" "src/nightmare.cxx")

target_link_libraries("${_target_prefix}.easy" PRIVATE "${_target_prefix}.common")
target_link_libraries("${_target_prefix}.hard" PRIVATE "${_target_prefix}.common")
target_link_libraries("${_target_prefix}.nightmare" PRIVATE "${_target_prefix}.common")
