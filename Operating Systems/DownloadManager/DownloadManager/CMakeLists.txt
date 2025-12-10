cmake_minimum_required(VERSION 3.10)
project(DownloadManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Browser Browser.cpp)

add_executable(Downloader Downloader.cpp)

if(WIN32)
    target_compile_definitions(Browser PRIVATE _MBCS)
    target_compile_definitions(Downloader PRIVATE _MBCS)
endif()