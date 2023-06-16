# CMakeList.txt: lua-test-cmake 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("lua-test-cmake")


if(APPLE)
	list(APPEND SYS_LIBS -lm -lpthread)
    ADD_DEFINITIONS(
        -DMACOS -g -Wunused-variable -Wunused-parameter -Wunused-function -Wunused
        -Wno-deprecated -Wwrite-strings
    )
elseif(UNIX)
	list(APPEND SYS_LIBS -lm -lpthread)
    ADD_DEFINITIONS(
        -DUNIX -g -fPIC -Wunused-variable -Wunused-parameter -Wunused-function -Wunused
        -Wno-deprecated -Wwrite-strings 
    )
else()
	list(APPEND SYS_LIBS wsock32 ws2_32)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -DHAVE_STRUCT_TIMESPEC)
endif()

SET(CMAKE_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(CMAKE_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")

SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
find_library(LUA_LIB_A lua54 "./lib")
if (${LUA_LIB_A} STREQUAL "LUA_LIB_A-NOTFOUND")
    message (FATAL_ERROR "required lua54 library but not found!")
else()
    message (STATUS "lua54 library found in ${LUA_LIB_A}")
endif()

message("LUA_LIB_A = ${LUA_LIB_A}")

SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
find_library(LUA_LIB_SO lua54 "./lib")
if (${LUA_LIB_SO} STREQUAL "LUA_LIB_SO-NOTFOUND")
    message (FATAL_ERROR "required lua54 library but not found!")
else()
    message (STATUS "lua54 library found in ${LUA_LIB_SO}")
endif()

message("LUA_LIB_SO = ${LUA_LIB_SO}")

add_executable (lua-test-cmake "lua-test-cmake.cpp" "lua-test-cmake.h")

include_directories(${CMAKE_INCLUDE_PATH})
link_directories(${CMAKE_LIBRARY_PATH})
target_link_libraries(lua-test-cmake ${LUA_LIB_A} ${LUA_LIB_SO} dl)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lua-test-cmake PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
