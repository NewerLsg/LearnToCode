#include "glog.h"
#include<stdio.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
	int i = 0;
	GLogInit("test.txt",GLOG_MSG);

	for(i = 0; i < 10 ;i++){
		pid_t pid = fork();
		if(pid == 0){
			break;
		}
	}


	GLogMsg("test[%d]",123);

	testGlog();
	testGlog2();
		
	return 0;
}
