cmake_minimum_required(VERSION 3.10)
project(MyOpenCVProject)

# 查找 OpenCV 库
find_package(OpenCV REQUIRED)

# 指定源文件
add_executable(main main.cpp)

# 链接 OpenCV 库
target_link_libraries(main ${OpenCV_LIBS})
