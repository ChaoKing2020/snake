cmake_minimum_required(VERSION 3.27)

project(chess)

# 赋值所有源程序文件名
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# 将整个目录下的静态资源文件复制到构建目录
file(COPY ${CMAKE_SOURCE_DIR}/static DESTINATION ${CMAKE_BINARY_DIR})
# 头文件的路径
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/easyx)
# 库文件的路径
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
# 设置可执行文件的输出目录
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
# 生成可执行文件
add_executable(app ${SRC})
target_link_libraries(app easyx ole32 gdi32 winmm)
