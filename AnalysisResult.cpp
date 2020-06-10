#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
//#include "queue.h"
#include "AnalysisResult.h"
#define LISTENQ 2
#define BUFF_SIZE 1500


// pthread_t g_thread;
// AnalysisResult* g_pthis;
// int End=0;//主线程结束标志位

// typedef struct stuReDataaAndThis
// {
// 	AnalysisResult* pThis;
// 	char* pData;
// }*pstuReDataaAndThis;
AnalysisResult::AnalysisResult()
{
	// g_pthis = this;
}
AnalysisResult::~AnalysisResult()
{
	std::cout << "close is OK!" << std::endl;
	close(m_nSocketfd);
}
void AnalysisResult::callbackdata(callbackFun* fcallback, char *data)
{
	m_callback = fcallback;
}

// //子线程执行函数
// void *thread_func(void *data)
// {
	
//     int i=0; 
//     sem_wait(&g_pthis->btn_sem);//子线程等待开始
//     while(1)
//     {    
//         Queue *tmp=Pop(g_pthis->m_head);
//         if(tmp==NULL)//队列已经空了
//         {
// 			sleep(1);
//         }
//         else
//         {
//             printf("Chlid Thread! ");
// 			// char* strRebuff = g_pthis->AnalysisData((char*)data);
// 			g_pthis->m_callback((char*)data);
// 			// delete[]data;
// 			// data = NULL;
// 			// delete[] strRebuff;
// 			// strRebuff = NULL;
// 			// //pthis->callbackdata((void*)(ptrFun((void*)pthis)),NULL);
//             // printf("\n");//子线程输出
//             free(tmp);
//         }
//         if(End==1)
//         {
//             if(g_pthis->m_head->next==NULL)
//                 return NULL;
//         }
//     }    
// }


IF_AnalysisResult* create(){
	return new AnalysisResult;
}

void destroy(IF_AnalysisResult* p) {
	delete p;
}

// void AnalysisResult::test()
// {
// 	int i = 0;
// 	while(1)
// 	{
// 		g_pthis->m_callback("test!");
// 		std::cout << "test!" << std::endl;
// 	}
// }
bool AnalysisResult::InitAnalysisResult(unsigned short port)
{

	if (port <= 0)
	{
		return false;
	}
	m_snport = port;
	std::cout << "set port:" << m_snport << std::endl;
	return true;
}

bool AnalysisResult::UnInitAnalysisResult()
{
	close(m_nSocketfd);
	return true;
}
int AnalysisResult::run()
{
	
	int nRet = InitNetWork();
	if (nRet < 0)
	{
		/* code */
		std::cout << "Init NetWork Failed!!!"<< std::endl;
		std::cout << nRet << std::endl;
		return false;
	}
}
int AnalysisResult::InitQueueAndThread()
{
	// m_head=CreateQueue();
    // int res;
    // res=sem_init(&btn_sem,0,0);
    // if(res!=0)
    // {
    //     printf("Signal initials failed!\n");
    //     return -1;
    // }
    // res=sem_init(&flag_sem,0,0);
    // if(res!=0)
    // {
    //     printf("Signal initials failed!\n");
    //     return -2;
    // }
    // res=pthread_create(&g_thread,NULL,thread_func,this);
    // if(res!=0)
    // {
    //     printf("Create thread failed!\n");
    //     return -3;
    // }
	// return 0;
}
int AnalysisResult::InitNetWork()
{
	// create socket
	int nRet= socket(AF_INET, SOCK_DGRAM, 0);

	if(nRet < 0){

		std::cout << "create socketfd failed" <<std::endl;
		return -1;
	}
	m_nSocketfd = nRet;
	//bing socket
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;

	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	servaddr.sin_port = htons(m_snport);

	nRet = bind(m_nSocketfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	if(nRet < 0)
	{
		return -2;
	}

	// sem_post(&btn_sem);	//第一次进入主循环时发信号，告知子线程可以开始
	int nconnfd = 0;
	int nlen = 0;
	std::cout << "Init Success!" << std::endl;
	std::cout << "Start Recv Data" << std::endl;
	while(1)
	{
		char buff[BUFF_SIZE] = {0};
		// char * pbuff =  new char[BUFF_SIZE];
		nlen = recv(m_nSocketfd,buff,BUFF_SIZE,0);
		if (nlen < 0)
		{
			/* code */
			printf("RECV FAILED!");

			break;
		}
		// std::cout << buff << std::endl;
		char* strRebuff = AnalysisData((char*)buff);
		m_callback(strRebuff);
		

		// // g_pthis->m_callback(pbuff);
		// std::cout << pbuff << std::endl;
		// // continue;
		// // // recv success!
		// nRet=Push(m_head,pbuff);//数据直接进入队列
        // if(nRet==-1)//如果队列满了，需要等待
        // {
        //     while(Push(m_head,pbuff)==-1);//放到队列有空间为止
        //     //Push(head,i); //子线程发信号，表示队列有空间了，此时把等待的信息push进队列
        // }
	}
	// End=1;
    // void *thread_res;
    // pthread_join(g_thread,&thread_res);//等待子线程结束后，结束主线程
    // sem_destroy(&btn_sem);
    // sem_destroy(&flag_sem);
    // DestroyQueue(m_head);
	return 0;
}
char* AnalysisResult::AnalysisData(char* data)
{
	int nlen = strlen(data);
	std::cout << nlen << std::endl;
	std::vector<uint8_t> arrBinary;
	for(int i = 0;i < BUFF_SIZE;i++)
	{
		arrBinary.push_back(data[i]);
	}
	SPointcloudResultInfo *pData = new SPointcloudResultInfo;
	AnalysisResultBinary(arrBinary,pData);
	return (char* )(pData);
}
bool AnalysisResult::AnalysisResultBinary(const std::vector<uint8_t>& arrBinary, SPointcloudResultInfo* pData)																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																															
{
	return true;
}


