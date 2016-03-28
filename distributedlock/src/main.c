#include "dlock.h"
#include "stdio.h"

int main(int argc, char* argv[]){
	int ret;

	ret = getLock("lock1");

	if (ret != 0) {
		printf("not get lock.\n");
	}else{
		printf("get lock.\n");
	}

	ret = testLock("lock1");	

	if (ret != 0) {
		printf("no lock.\n");
	}else{
		printf("lock exist.\n");
	}

	ret = releaseLock("lock1");	

	if (ret != 0) {
		printf("fail to release lock.\n");
	}else{
		printf("release lock.\n");
	}

	return 0;
}