cmake_minimum_required(VERSION 3.26)   # 指定 CMake 最低版本
project(test)                      # 项目名称

add_executable(test
    utils/glthread.c
    src/test.c
)            # 生成可执行程序

target_include_directories(test PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

set(CMAKE_BUILD_TYPE Debug)