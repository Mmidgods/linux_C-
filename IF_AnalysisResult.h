#ifndef IF_ANALYSISRESULT_H
#define IF_ANALYSISRESULT_H

#include <sys/types.h>
#include <iostream>
#include <vector>
#include <stdint.h>


typedef void(callbackFun)(char* rebuff);
class IF_AnalysisResult {
public:
	virtual bool InitAnalysisResult(unsigned short port) = 0;
	virtual int run() = 0;
	virtual bool UnInitAnalysisResult() = 0;
	
	virtual void callbackdata(callbackFun* fcallback, char *data) = 0;
};

// the types of the class factories
extern "C" IF_AnalysisResult *create();

extern "C" void destroy_t(IF_AnalysisResult* p);

#endif
