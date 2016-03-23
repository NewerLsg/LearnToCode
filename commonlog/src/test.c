#include "glog.h"
#include<unistd.h>

void testGlog(){
	GLogDbg("glog in test");
}

void testGlog2(){
	GLogDbg("glog in test[%d]",getpid());
}