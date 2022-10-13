#include <iostream>
#include "string"
#include <stdio.h>
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

#define ADTS_HEADER__LEN 7

const int sampling_frequencies[] = {
        96000,  // 0x0
        88200,  // 0x1
        64000,  // 0x2
        48000,  // 0x3
        44100,  // 0x4
        32000,  // 0x5
        24000,  // 0x6
        22050,  // 0x7
        16000,  // 0x8
        12000,  // 0x9
        11025,  // 0xa
        8000   // 0xb
        // 0xc d e f是保留的
};

int adts_header(char * const p_adts_header, const int data_length,
                const int profile, const int samplerate,
                const int channels)
{

    int sampling_frequency_index = 3; // 默认使用48000hz
    int adtsLen = data_length + 7;

    int frequencies_size = sizeof(sampling_frequencies) / sizeof(sampling_frequencies[0]);
    int i = 0;
    for(i = 0; i < frequencies_size; i++)
    {
        if(sampling_frequencies[i] == samplerate)
        {
            sampling_frequency_index = i;
            break;
        }
    }
    if(i >= frequencies_size)
    {
        printf("unsupport samplerate:%d\n", samplerate);
        return -1;
    }

    p_adts_header[0] = 0xff;         //syncword:0xfff                          高8bits
    p_adts_header[1] = 0xf0;         //syncword:0xfff                          低4bits
    p_adts_header[1] |= (0 << 3);    //MPEG Version:0 for MPEG-4,1 for MPEG-2  1bit
    p_adts_header[1] |= (0 << 1);    //Layer:0                                 2bits
    p_adts_header[1] |= 1;           //protection absent:1                     1bit

    p_adts_header[2] = (profile) << 6;            //profile:profile               2bits
    p_adts_header[2] |= (sampling_frequency_index & 0x0f) << 2; //sampling frequency index:sampling_frequency_index  4bits
    p_adts_header[2] |= (0 << 1);             //private bit:0                   1bit
    p_adts_header[2] |= (channels & 0x04) >> 2; //channel configuration:channels  高1bit

    p_adts_header[3] = (channels & 0x03) << 6; //channel configuration:channels 低2bits
    p_adts_header[3] |= (0 << 5);               //original：0                1bit
    p_adts_header[3] |= (0 << 4);               //home：0                    1bit
    p_adts_header[3] |= (0 << 3);               //copyright id bit：0        1bit
    p_adts_header[3] |= (0 << 2);               //copyright id start：0      1bit
    p_adts_header[3] |= ((adtsLen & 0x1800) >> 11);           //frame length：value   高2bits

    p_adts_header[4] = (uint8_t)((adtsLen & 0x7f8) >> 3);     //frame length:value    中间8bits
    p_adts_header[5] = (uint8_t)((adtsLen & 0x7) << 5);       //frame length:value    低3bits
    p_adts_header[5] |= 0x1f;                                 //buffer fullness:0x7ff 高5bits
    p_adts_header[6] = 0xfc;      //11111100      //buffer fullness:0x7ff 低6bits
    // number_of_raw_data_blocks_in_frame：
    //    表示ADTS帧中有number_of_raw_data_blocks_in_frame + 1个AAC原始帧。

    return 0;
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
    if (!file){
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
            char adts_header_buf[7];
            adts_header(adts_header_buf,pkt.size,
                            formatContext->streams[audioIndex]->codecpar->profile,
                            formatContext->streams[audioIndex]->codecpar->sample_rate,
                            formatContext->streams[audioIndex]->codecpar->channels
                            );
            fwrite(adts_header_buf,1,7,file);
            int len = fwrite(pkt.data,1,pkt.size,file);
            if (len != pkt.size){
                av_log(nullptr,AV_LOG_WARNING,"包长度与data不符");
            }
        }
        av_packet_unref(&pkt);
    }
    error:
    if (file){
        fclose(file);
    }
    avformat_close_input(&formatContext);
    return 0;
}