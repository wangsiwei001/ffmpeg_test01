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
int main(){
    AVFormatContext* srcFmtCtx = nullptr, * dstFmtCtx = nullptr;
    AVPacket *avPacket = av_packet_alloc();
    string src,drc;
}