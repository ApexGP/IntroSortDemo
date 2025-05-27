cmake_minimum_required(VERSION 3.10)

project(IntroSortDemo VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# 设置二进制文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 添加头文件路径
include_directories(${CMAKE_SOURCE_DIR}/include)

# 添加源代码子目录
add_subdirectory(src)

# 添加测试子目录
add_subdirectory(test)
