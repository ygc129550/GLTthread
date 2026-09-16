cmake_minimum_required(VERSION 3.26)
project(GLTthread VERSION 1.0.0 LANGUAGES C)

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
set(GLT_PUBLIC_HEADERS
    ${CMAKE_SOURCE_DIR}/include/glthread.h
    ${CMAKE_SOURCE_DIR}/include/glqueue.h
    ${CMAKE_SOURCE_DIR}/include/glstack.h
)

# ============================================================
# 静态库
# ============================================================
if(GLT_BUILD_STATIC)
    add_library(glt_static STATIC ${GLT_SOURCES})
    target_include_directories(glt_static
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
    set_target_properties(glt_static PROPERTIES
        OUTPUT_NAME glt
        POSITION_INDEPENDENT_CODE ON
        PUBLIC_HEADER "${GLT_PUBLIC_HEADERS}"
    )
endif()

# ============================================================
# 共享库
# ============================================================
if(GLT_BUILD_SHARED)
    add_library(glt_shared SHARED ${GLT_SOURCES})
    target_include_directories(glt_shared
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
    set_target_properties(glt_shared PROPERTIES
        OUTPUT_NAME glt
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER "${GLT_PUBLIC_HEADERS}"
    )
endif()

# ============================================================
# 提供一个统一的别名目标，方便外部项目使用
# add_subdirectory 集成时可直接 link GLTthread::glt
# ============================================================
if(GLT_BUILD_STATIC)
    add_library(GLTthread::glt ALIAS glt_static)
elseif(GLT_BUILD_SHARED)
    add_library(GLTthread::glt ALIAS glt_shared)
endif()

# ============================================================
# 测试程序（可选）
# ============================================================
if(GLT_BUILD_TESTS)
    # 选择链接的库目标（优先静态）
    if(GLT_BUILD_STATIC)
        set(_GLT_LINK_TARGET glt_static)
    else()
        set(_GLT_LINK_TARGET glt_shared)
    endif()

    foreach(_test glthread_test glqueue_test glstack_test)
        add_executable(${_test} src/${_test}.c)
        target_link_libraries(${_test} PRIVATE ${_GLT_LINK_TARGET})
    endforeach()
endif()

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
