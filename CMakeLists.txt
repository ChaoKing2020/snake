cmake_minimum_required(VERSION 3.27)

project(chess)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/easyx)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(app ${SRC})
target_link_libraries(app easyx ole32 gdi32)
