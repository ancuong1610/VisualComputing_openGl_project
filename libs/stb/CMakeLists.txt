cmake_minimum_required(VERSION 3.0)

project(stb_lib)

add_library(stb STATIC "${CMAKE_CURRENT_SOURCE_DIR}/stb_image.h" "${CMAKE_CURRENT_SOURCE_DIR}/stb_image.c" "${CMAKE_CURRENT_SOURCE_DIR}/stb_image_write.h" "${CMAKE_CURRENT_SOURCE_DIR}/stb_image_write.c")

target_include_directories(stb INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")