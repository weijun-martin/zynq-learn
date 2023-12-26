# 设置CMake的最小版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(MyProject)
enable_testing()
# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# 添加可执行文件
add_executable(MyExecutable src/main.cpp)

target_include_directories(MyExecutable PUBLIC include)

target_link_libraries(MyExecutable websockets)