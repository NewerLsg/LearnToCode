#include<stdio.h>
#include<dlfcn.h>

typedef int (*fn)();

int main(){
	void *handle;
	fn cal;

	handle = dlopen("./libtestlib.so", RTLD_LAZY);

	if(handle == NULL) {
		printf("fail to get so.");
		return 0;
	}	

	dlerror();

	*(void **) &cal = dlsym(handle, "test1");

	if(dlerror() != NULL) {
		printf("fail to get func.");
		return 1;
	}

	cal();

	dlclose(handle);

	return 0;
}
