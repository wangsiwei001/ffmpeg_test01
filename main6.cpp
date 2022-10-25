//
// Created by Administrator on 2022/10/25.
//
#include "string"
#include <stdio.h>
#include "iostream"
extern "C"{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/time.h"
#include "libswscale/swscale.h"
#include <libavutil/avutil.h>
}
using namespace std;
int cut_video(double from_seconds, double end_seconds, const string in_filename, const string out_filename)
{
    AVOutputFormat *avOutputFormat = nullptr;
    AVFormatContext *inContext = nullptr,*outContext = nullptr;
    AVPacket avPacket;
    int ret,i;
    av_register_all();
    av_log_set_level(AV_LOG_INFO);
    if ((ret = avformat_open_input(&inContext,in_filename.data(),0,0)) < 0)
    {
        av_log(nullptr,AV_LOG_ERROR,"打开文件失败,请检查文件,错误码:%d\n",ret);
        goto end;
    }
    if ((ret = avformat_find_stream_info(inContext, 0)) < 0)
    {
        av_log(nullptr,AV_LOG_ERROR,"打开流失败,请检查文件,错误码:%d\n",ret);
        goto end;
    }
    av_dump_format(inContext, 0, in_filename.data(), 0);
    avformat_alloc_output_context2(&inContext, nullptr, nullptr,out_filename.data());
    if (!outContext){
        av_log(nullptr,AV_LOG_ERROR,"输出文件创建失败！\n");
        goto end;
    }
    avOutputFormat = inContext->oformat;
    
    end:
    avformat_close_input(&inContext);
    if (inContext && !(avOutputFormat->flags & AVFMT_NOFILE))
        avio_closep(&inContext->pb);
    avformat_free_context(outContext);

    if (ret < 0 && ret != AVERROR_EOF) {
        fprintf(stderr, "Error occurred: %d\n", ret);
        return 1;
    }
    return 0;
}
int main()
{
    cut_video(20, 30,"test01.mp4","test02.mp4");
}
