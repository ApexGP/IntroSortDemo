# 添加库文件
add_library(sort STATIC
    Sort.cpp
    ExSort.cpp
)

# 添加可执行文件
add_executable(introsort main.cpp)

# 链接库
target_link_libraries(introsort sort)