cmake_minimum_required(VERSION 3.27)

project(chess)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/easyx)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# 将整个目录下的静态资源文件复制到构建目录
file(COPY ${CMAKE_SOURCE_DIR}/static DESTINATION ${CMAKE_BINARY_DIR})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(app ${SRC})
target_link_libraries(app easyx ole32 gdi32)
