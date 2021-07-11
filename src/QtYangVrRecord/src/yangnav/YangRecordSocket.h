#ifndef __________YangRecUDP___
#define __________YangRecUDP___
#include <sys/socket.h>
#include <netinet/in.h>

#include "YangRecordI.h"
#include "yangutil/sys/YangThread.h"
class YangRecUDP :public YangThread
{
public:
    YangRecUDP(void);
    ~YangRecUDP(void);
	void tcpListen();
	void udpListen();
	
	//void send();
	void proc(char *b,int plen);
    int m_isStart;
    YangRecordI *p1;

    void stop();
protected:
    void run();
    int m_isConvert;
};
class YangUdpUtil{
public:
    YangUdpUtil(void);
    ~YangUdpUtil(void);
	sockaddr_in addrClient1;
	void init(const char *ip,int port);
	int sendUdp(char* data,int len);
	int sockSrv;
};
#endif
