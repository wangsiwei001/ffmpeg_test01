cmake_minimum_required(VERSION 3.19)
project(ffmpeg_test01)

set(CMAKE_CXX_STANDARD 11)


include_directories(D:\\ffmpeg-n4.4.2-95-ga8f16d4eb4-win64-gpl-shared-4.4\\include)
link_directories(D:\\ffmpeg-n4.4.2-95-ga8f16d4eb4-win64-gpl-shared-4.4\\lib)

add_executable(ffmpeg_test01 main.cpp)
add_executable(test main2.cpp)
add_executable(test2 main3.cpp)
add_executable(test3 main4.cpp)
add_executable(test4 main5.cpp)

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
target_link_libraries(
        test
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swresample
        swscale
)
target_link_libraries(
        test2
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swresample
        swscale
)
target_link_libraries(
        test3
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swresample
        swscale
)
target_link_libraries(
        test4
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swresample
        swscale
)