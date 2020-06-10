
//----------
//main.cpp:
//----------
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include "IF_AnalysisResult.h"
using namespace std;


void FunTEST(char *rebuff)
{
	cout << rebuff << endl;
}
 
typedef IF_AnalysisResult* (*pTestDLObj)();  //定义一个函数指针
int main(){
	using std::cout;
	using std::cerr;
	char* error ;

	void* triangle = dlopen("libAnalysisResult.so", RTLD_LAZY);
	if (!triangle) {
		cerr << "Cannot load library: " << dlerror() << '\n';
		return -1;
	}
	dlerror();
	pTestDLObj create_class = (pTestDLObj)dlsym(triangle,"create");
    const char *dlmsg = dlerror();
    if(NULL != dlmsg)
    {
        printf("get class testdl error\nErrmsg:%s\n",dlmsg);
        dlclose(triangle);
        return -1;
    }
	IF_AnalysisResult* tmp = create_class();
	tmp->InitAnalysisResult(8888);
	char* Pdata = NULL;
	tmp->callbackdata(FunTEST,Pdata);
	
	
	tmp->run();


	tmp->UnInitAnalysisResult();

	dlclose(triangle);
	return 0;
}
