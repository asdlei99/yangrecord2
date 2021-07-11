#include "yangrecordthread.h"
#include <QDebug>
#include <QMapIterator>
//#include "../yangutil/yangmeetingtype.h"
YangRecordThread::YangRecordThread()
{
    // m_ys=nullptr;
    m_isLoop=0;
  //  delState=0;
    m_bgColor={0,0,0};
    m_textColor={0,0,255};
    m_captureFormat=YangI420;
    m_is16bit=1;
    m_videoPlayNum=5;
    m_sid=1;
    m_vb=NULL;
    m_isStart=0;
}

YangRecordThread::~YangRecordThread(){
    // m_ys=nullptr;
    // m_vb=NULL;
    m_vb=NULL;

   stopAll();
}
void YangRecordThread::stopAll(){
    if(m_isLoop){
        m_isLoop=0;
        while (m_isStart) {
            QThread::msleep(1);
        }
    }
     closeAll();
}
void YangRecordThread::initPara(YangRecordContext *pini){
   // m_ini=pini;
    m_para=pini;
    for(int i=0;i<Yang_Record_VideoCount+1;i++){
        memset(&m_videos[i],0,sizeof(YangRecordThreadWin));
    }
    if(pini->video.videoCaptureFormat==YangYv12){
        m_captureFormat=YangYv12;
        m_is16bit=0;
    }
    if(pini->video.videoDecoderType==1) {
        m_captureFormat=YangI420;
       // qDebug()<<"*****************YangYv12*************add video uid==";
    }
    m_videoPlayNum=pini->video.videoPlayCacheNum;
}
void YangRecordThread::closeAll(){
    clearRender();
}

void YangRecordThread::clearRender(){
    int i=0;
    for(i=0;i<Yang_Record_VideoCount+1;i++){
        YangRecordThreadWin *ys=&m_videos[i];
        if(ys&&ys->videoWindow){
            ys->videoBuffer=NULL;
            ys->winId=NULL;
            YANG_DELETE(m_videos[i].videoWindow);
            //ys->widget=NULL;

        }
        ys=NULL;

    }

}


/**
void YangRecordThread::initPlaySdl(YangRecordThreadWin *ys){
    if(ys->videoWindow->m_width==0){
        ys->videoWindow->initVideo(ys->videoBuffer->m_width,ys->videoBuffer->m_height,m_captureFormat);
        ys->videoWindow->initText(ys->videoName,&m_textColor);
    }else {
        if(ys->videoWindow->m_width!=ys->videoBuffer->m_width||ys->videoWindow->m_height!=ys->videoBuffer->m_height)
            ys->videoWindow->reInitVideo(ys->videoBuffer->m_width,ys->videoBuffer->m_height,m_captureFormat);//YangNv12 YangYv12);
          ys->videoWindow->reInitText(ys->videoName,&m_textColor);
    }
}**/
void YangRecordThread::render(){
    for(int i=0;i<Yang_Record_VideoCount+1;i++){
        YangRecordThreadWin *ys=&m_videos[i];
          if(ys&&!ys->videoWindow){
            // qDebug()<<"....has videobuffer sdl=="<<(ys->videoWindow==NULL?"NULL":"not null")<<"..winid=="<<(ys->winId==NULL?"NULL":"not null");
                    YangWinPlayFactroy pf;
                    ys->videoWindow=pf.createWinPlay();
                   ys->videoWindow->init(ys->winId);
                    ys->videoWindow->initBg(ys->width,ys->height);
                 //   if(i==1){
                  //      ys->videoWindow->initVideo(m_para->video.width,m_para->video.height,YangNv12);
                 //        printf("\n%d captureformat=================%d",i,YangNv12);
                  //  }
                  //      else{
                    ys->videoWindow->initVideo(m_para->video.width,m_para->video.height,m_captureFormat);
                    printf("\n%d captureformat=================%d",i,m_captureFormat);
                 //   }
                  //  ys->videoWindow->initText(ys->videoName,&m_textColor);
        }

        if(ys->videoBuffer){
            if(ys->videoBuffer->m_size>0)  {
               unsigned char* vdata=ys->videoBuffer->getVideoIn(&ys->timestamp);
                ys->videoWindow->render(vdata);
                if(m_sid==i) m_videos[0].videoWindow->render(vdata);
                if(ys->videoBuffer&&ys->videoBuffer->m_size>m_videoPlayNum) ys->videoBuffer->resetIndex();
                vdata=NULL;
            }
        }
        //else{
         //   if(ys->videoWindow) ys->videoWindow->renderBg(&m_bgColor);

        //}
        ys=NULL;
    }//end for
}

void YangRecordThread::run(){
    // init();

    m_isLoop=1;
    m_isStart=1;
    // int interval=1000*1000/50;
    while(m_isLoop){
      //  if(delState>1){
         //   msleep(1);
         //   if(delState==3) delState=2;
            //  qDebug()<<"-----------------------thread is running delState==--"<<delState;
          //  continue;
       // }
        QThread::msleep(20);
        // qDebug()<<"----------------------------------------thread is running==--";
        render();
    }
    m_isStart=0;
   // closeAll();
}
