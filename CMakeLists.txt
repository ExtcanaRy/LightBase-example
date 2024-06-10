cmake_minimum_required(VERSION 3.6)

project(lightbase_example)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# ------------------------------------------------
# ------------------------------------------------
# ------------------------------------------------
# ------------------------------------------------
# ------------------------------------------------

# lightbase linux
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(include)

set(LIGHTBASE_SOURCE src/main.c)

add_library(lightbase_example SHARED ${LIGHTBASE_SOURCE})

target_link_libraries(lightbase_example)

ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

# ------------------------------------------------
# ------------------------------------------------
# ------------------------------------------------
# ------------------------------------------------
# ------------------------------------------------

# lightbase windows
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

add_definitions(
    -D"_CRT_SECURE_NO_WARNINGS"
    -DWIN32_LEAN_AND_MEAN
    -D"LIGHTBASE_EXPORTS"
)

add_compile_options(
    /diagnostics:column
    /FC
    /GL
    /nologo
    /permissive-
    /sdl
    /utf-8
    /Zi
)

add_link_options(
    /LTCG
    /INCREMENTAL:NO
)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /NODEFAULTLIB:MSVCRTD")

# lightbase_example main
file(GLOB_RECURSE SRC_FILES_DIR
    ${PROJECT_SOURCE_DIR}/src/main.c
)

add_library(lightbase_example SHARED ${SRC_FILES_DIR})
target_link_libraries(lightbase_example win/lightbase
    debug "MSVCRTD.lib"
    optimized "MSVCRT.lib"
    "win/lightbase"
)
set_target_properties(lightbase_example PROPERTIES OUTPUT_NAME "lightbase_example")


ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows")