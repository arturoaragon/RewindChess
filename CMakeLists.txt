cmake_minimum_required(VERSION 3.20)
project(RewindChess LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Get the graphics library if it is not already installed.
find_package(raylib 5.5 QUIET)
if(NOT raylib_FOUND)
    include(FetchContent)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        URL_HASH SHA256=aea98ecf5bc5c5e0b789a76de0083a21a70457050ea4cc2aec7566935f5e258e
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
    FetchContent_MakeAvailable(raylib)
endif()

# main.cpp includes the other game files, so compile only this entry point.
add_executable(RewindChess src/main.cpp)
target_link_libraries(RewindChess PRIVATE raylib)
