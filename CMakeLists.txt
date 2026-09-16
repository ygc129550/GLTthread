cmake_minimum_required(VERSION 3.26)
project(glueds VERSION 1.0.0 LANGUAGES C)

# ============================================================
# 选项：允许外部项目通过 add_subdirectory 集成时关闭测试构建
# ============================================================
option(GLT_BUILD_TESTS "Build test programs" ON)
option(GLT_BUILD_SHARED "Build shared library" ON)
option(GLT_BUILD_STATIC "Build static library" ON)

# ============================================================
# 收集库源文件 & 公共头文件
# ============================================================
file(GLOB GLT_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/utils/*.c")

# ============================================================
# 静态库
# ============================================================
if(GLT_BUILD_STATIC)
    add_library(glueds_static STATIC ${GLT_SOURCES})
    target_include_directories(glueds_static
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>

    )
    set_target_properties(glueds_static PROPERTIES
        OUTPUT_NAME glueds
        POSITION_INDEPENDENT_CODE ON
    )
endif()

# ============================================================
# 共享库
# ============================================================
if(GLT_BUILD_SHARED)
    add_library(glueds_shared SHARED ${GLT_SOURCES})
    target_include_directories(glueds_shared
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>

    )
    set_target_properties(glueds_shared PROPERTIES
        OUTPUT_NAME glueds
    )
endif()

# ============================================================
# 提供一个统一的别名目标，方便外部项目使用
# add_subdirectory 集成时可直接 link glueds::glueds
# ============================================================
if(GLT_BUILD_STATIC)
    add_library(glueds::glueds ALIAS glueds_static)
elseif(GLT_BUILD_SHARED)
    add_library(glueds::glueds ALIAS glueds_shared)
endif()

# ============================================================
# 测试程序（可选）
# ============================================================
if(GLT_BUILD_TESTS)
    # 选择链接的库目标（优先静态）
    if(GLT_BUILD_STATIC)
        set(_GLUEDS_LINK_TARGET glueds_static)
    else()
        set(_GLUEDS_LINK_TARGET glueds_shared)
    endif()

    foreach(_test gllist_test glqueue_test glstack_test)
        add_executable(${_test} src/${_test}.c)
        target_link_libraries(${_test} PRIVATE ${_GLUEDS_LINK_TARGET})
    endforeach()
endif()

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
