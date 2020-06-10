#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset
#include <string>
#include <assert.h>
#include <sys/types.h> // AF_INET , SOCK_STREAM
#include <sys/socket.h> // socket , bind , connect , accept
#include <netinet/in.h> // sockaddr_in
#include <unistd.h>
#include <iostream>

#include "IF_AnalysisResult.h"

class AnalysisResult:public IF_AnalysisResult{
public:
	AnalysisResult();
	~AnalysisResult();
private:
	int 	m_nSocketfd;	// 
	short 	m_snport;
	char	m_SrvIp[16];
public:
	// Queue *m_head;//队列头部
	// sem_t btn_sem;//二进制信号量
	// sem_t flag_sem;
	callbackFun* m_callback;
public:
	char* AnalysisData(char* data);
private:
	int InitNetWork();
	int InitQueueAndThread();

public:
	virtual void test();
	virtual bool InitAnalysisResult(const unsigned short port);
	virtual int run();
	virtual bool UnInitAnalysisResult();
	virtual bool AnalysisResultBinary(const std::vector<uint8_t>& arrBinary, SPointcloudResultInfo* pData);
	virtual void callbackdata(callbackFun* fcallback, char *data);
};


