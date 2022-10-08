#include <iostream>
#include "string"
extern "C"{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/time.h"
#include "libswscale/swscale.h"
#include <libavutil/avutil.h>
}
using namespace std;
#define Max(a,b)(a > b?a :b)
#define sum(a,b) a+b
#define tul  1 + 2
inline int min(int a ,int b){
    return a + b;
}
int main() {
    char errStr[256] = { 0 };
//    int version =avformat_version();
//    cout<<"version:"<<version<<endl;


//    av_log_set_level(AV_LOG_INFO);
//    int ret;
//    ret = avpriv_io_move("111.txt","222.txt");
//    if (ret <= 0){
//        av_log(nullptr,AV_LOG_ERROR,"Failed to update error 111.txt\n");
//        return -1;
//    }
//    av_log(nullptr,AV_LOG_INFO,"Success to update 111.txt\n");
//
//    ret = avpriv_io_delete("./mytest.txt");
//    if (ret <= 0){
//        av_log(nullptr,AV_LOG_ERROR,"Failed to delete file mytest.txt\n");
//        return -1;
//    }
//    av_log(nullptr,AV_LOG_INFO,"Success to delete mytest.txt\n");

//    int ret;
//    string *dir = (string *) "./";
//    AVIODirContext *ctx = nullptr;
//    AVIODirEntry *entry = nullptr;
//    av_log_set_level(AV_LOG_INFO);
//    ret = avio_open_dir(&ctx,"/Users",nullptr);
//    char errStr[256] = { 0 };
//    if (ret < 0){
//        av_log(nullptr,AV_LOG_ERROR,"Cant open dir:%d\n",av_strerror(ret, errStr, sizeof(errStr)));
//        return -1;
//    }
//    while (1){
//        ret = avio_read_dir(ctx,&entry);
//        if (ret < 0){
//            av_log(nullptr,AV_LOG_ERROR,"Cant readdir:%d\n", av_strerror(ret, errStr, sizeof(errStr)));
//            goto _fail;
//        }
//        if(!entry){
//            break;
//        }
//        av_log(nullptr,AV_LOG_INFO,"%12%s\n",entry->size,entry->name);
//        avio_free_directory_entry(&entry);
//    }
//    _fail:
//    avio_close_dir(&ctx);
//
//    cout<< max(11,12) << endl;
//    cout<< sum(11,21) << endl;
//    cout<< min(1,1) << endl;
//    int a = 4 * tul;
/**
 * 打印多媒体文件信息
 * */
//    int ret;
//    AVFormatContext *formatContext = nullptr;
//    av_log_set_level(AV_LOG_INFO);
//    av_register_all();
//    ret = avformat_open_input(&formatContext,"./test.mp4", nullptr, nullptr);
//    if (ret < 0){
//        av_log(nullptr,AV_LOG_ERROR,"Cont open file:%d\n", av_strerror(ret,errStr,sizeof(errStr)));
//        return -1;
//    }
//    av_dump_format(formatContext,0,"./test.mp4",0);
//    avformat_close_input(&formatContext);

/**
 * 抽取音频数据
 **/
    string src,dst;
    int ret,audioIndex;
    av_log(nullptr,AV_LOG_INFO,"请输入源路径:\n");
    cin>>src;
    av_log(nullptr,AV_LOG_INFO,"请输入目标路径:\n");
    cin>>dst;
    if (src.empty()||dst.empty()){
        av_log(nullptr,AV_LOG_INFO,"源地址或目标地址为空\n");
    }


    AVFormatContext *formatContext = nullptr;
    AVPacket pkt;
    av_log_set_level(AV_LOG_INFO);
    av_register_all();
    ret = avformat_open_input(&formatContext,src.data(),nullptr, nullptr);
    if (ret < 0){
        av_log(nullptr,AV_LOG_ERROR,"Cont open file:%d\n", av_strerror(ret,errStr,sizeof(errStr)));
        return -1;
    }
    FILE  *file = fopen(dst.data(),"wb");
    if (file){
        av_log(nullptr,AV_LOG_ERROR,"不能打开输出文件\n");
        goto error;
    }
    av_dump_format(formatContext,0,"./test.mp4",0);
    ret = av_find_best_stream(formatContext,AVMEDIA_TYPE_AUDIO,-1,-1, nullptr,0);
    if (ret < 0){
        av_log(nullptr,AV_LOG_ERROR,"打开流失败!");
        fclose(file);
        goto error;
    }
    audioIndex = ret;
    av_init_packet(&pkt);
    while (av_read_frame(formatContext,&pkt) >=0){
        if (pkt.stream_index == audioIndex){
            int len = fwrite(pkt.data,1,pkt.size,file);
            if (len != pkt.size){
                av_log(nullptr,AV_LOG_WARNING,"包长度与data不符");
            }
        }
    }
    av_packet_unref(&pkt);
    error:
    avformat_close_input(&formatContext);
    if (file){
        fclose(file);
    }
    return 0;
}