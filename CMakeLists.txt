cmake_minimum_required(VERSION 3.19)
project(ffmpeg_test01)

set(CMAKE_CXX_STANDARD 11)


include_directories(D:\\ffmpeg-n4.4.2-95-ga8f16d4eb4-win64-gpl-shared-4.4\\include)
link_directories(D:\\ffmpeg-n4.4.2-95-ga8f16d4eb4-win64-gpl-shared-4.4\\lib)

add_executable(ffmpeg_test01 main.cpp)
target_link_libraries(
        ffmpeg_test01
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swresample
        swscale
)
