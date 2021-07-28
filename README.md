# yangrecord
基于yangrtc开发的高清录播直播系统  
1、支持多机位，支持支持支持电影模式、画中画模式和资源模式等录制模式  
2、支持电影模式直播和多路直播  
3、支持录制h264和h265等mp4、flv  
4、支持10bit录制  
5、直播支持Rtmp、Srt，二期支持Webrtc  

参数配置在yang_config_record.ini文件里
 
[audio]//音频  
sample=44100  //采样率
channel=2     //声道  
bitrate=128  //码率  
usingMono=0 //是否单声道（视频会议建议单声道）1:单声道 0：双声道  
hasAec=0    //回声消除 1:启用 0:不启用  
echoPath=10 //aec   
aecBufferFrames=8   
audioPlayType=0  
audioEncoderType=0 //音频编码 0:AAc 1:Mp3 2:Speex 3:Opus    
audioDecoderType=0 //音频解码 0:AAc 1:Mp3 2:Speex 3:Opus  
audioCacheNum=100  
audioCacheSize=100  
audioPlayCacheNum=10  
aIndex=1  //声卡声音采集编号  
aSubIndex=0 //linux下，子设备编号  


[video]//视频  
width=640  //摄像头采集width  
height=480  //摄像头采集height  
outWidth=640 //编码输出width  
outHeight=480 //编码输出height  
rate=4096  //码率  
frame=25  //帧数  
videoEncoderType=0 //0:h264 1:h265  
videoDecoderType=0 //0:h264 1:h265   
videoEncHwType=0   //0:软编 1:硬编  
videoDecHwType=0  //0:软解 1:硬解  
vIndex=0        //摄像头编号  

[sys]  
transType=1 //1:Srt 0:Rtmp 2:webrtc(二期实现)  
hasVr=1 //启动Vr 1:启动 0:不启动  
isMultCamera=1 //1:多个摄像头 0:单个摄像头  
cameraIndexs=0,1,2 //支持多个摄像头，摄像头编号以逗号分割  
cameraCount=3 //摄像头个数,yangrtc理论上支持的摄像头个数没有上限  
bgFilename=/home/jpg/02.jpeg //背景文件，目前支持jpeg  
rtmpPort=1935   //rtmp端口  
httpPort=8090   //http端口  
srtPort=8080    //srt端口  
dataPort=9999   //信令和数据端口  
rtmpServerIP=10.42.0.1  //rtmp服务地址  
srtServerIP=10.42.0.1   //srt服务器地址  
httpServerIP=10.42.0.1   //http服务器地址  
dataServerIP=10.42.0.1    //数据和信令服务器地址  
logLevel=5  //日志级别 fatal/error/debug/info/trace  
hasLogFile=0  //开启日志文件 1:输出到文件 0:输出到console  

[record]  
fileTimeLen=60  //录制视频文件单个文件分钟数，60为录制视文件1小时（60分钟）后生成第二个视频文件  
filePath=/home/recordfile  //保存文件路径  
roomId=1  //教室编号
app=live //直播app名称
  
[hd]//互动参数  
meetingId=1001 //会议编号  
classroomId=1 //教室编号  
app=yangmeeting //服务端app名称   

[enc]  
preset=7  //预设编码参数，参考x264和x265  
enc_threads=4 //编码线程数  
