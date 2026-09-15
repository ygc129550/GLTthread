cmake_minimum_required(VERSION 3.26)
project(GLTthread)

# 自动收集 utils 目录下所有 .c 文件（支持增量检测）
file(GLOB UTILS_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/utils/*.c")

# glthread 测试
add_executable(glthread_test ${UTILS_SOURCES} src/glthread_test.c)
target_include_directories(glthread_test PRIVATE ${CMAKE_SOURCE_DIR}/include)

# glqueue 测试
add_executable(glqueue_test ${UTILS_SOURCES} src/glqueue_test.c)
target_include_directories(glqueue_test PRIVATE ${CMAKE_SOURCE_DIR}/include)

# glstack 测试
add_executable(glstack_test ${UTILS_SOURCES} src/glstack_test.c)
target_include_directories(glstack_test PRIVATE ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_BUILD_TYPE Debug)
