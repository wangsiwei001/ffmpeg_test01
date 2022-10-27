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
//    av_dump_format(inContext, 0, in_filename.data(), 0);
    avformat_alloc_output_context2(&outContext, nullptr, nullptr,out_filename.data());
    if (!outContext){
        av_log(nullptr,AV_LOG_ERROR,"输出文件创建失败！\n");
        goto end;
    }
    avOutputFormat = inContext->oformat;
    for(i = 0;i < inContext->nb_streams;i++){
        AVStream *inStream = inContext->streams[i];
        AVStream *outStream = avformat_new_stream(inContext, inStream->codec->codec);
        if (!outStream){
            av_log(nullptr,AV_LOG_ERROR,"Failed allocating output stream\n");
            goto end;
        }
        ret = avcodec_copy_context(outStream->codec, inStream->codec);
        if (ret < 0){
            av_log(nullptr,AV_LOG_ERROR,"Failed to copy context from input to output stream codec context\n");
            goto end;
        }
        outStream->codec->codec_tag = 0;
        if (outContext->oformat->flags & AVFMT_GLOBALHEADER)
            outStream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }
    av_dump_format(outContext, 0, out_filename.data(), 1);
    if (!(outContext->flags & AVFMT_NOFILE)){
        int ret = avio_open(&outContext->pb, out_filename.data(), AVIO_FLAG_WRITE);
        if (ret < 0){
            av_log(nullptr,AV_LOG_ERROR,"Could not open output file %s",out_filename.data());
            goto end;
        }
        ret = avformat_write_header(outContext, NULL);
        if (ret < 0) {
            fprintf(stderr, "Error occurred when opening output file\n");
            goto end;
        }
    }
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
    cut_video(20, 30,"test.mp4","test02.mp4");
}
