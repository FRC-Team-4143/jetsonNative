#include <stdio.h>
#include <string.h>

#define __USE_GNU
#include <dlfcn.h>

int HAL_CreateSimDevice(const char* name) {
	printf("HAL_CreateSimDevice: %s\n", name);
	if(!strncmp(name, "SPARK", 5) || !strncmp(name, "navX", 4)) {  // pretend we are not in a simulation for REV
		printf("skipping orig HAL_CreateSimDevice\n");
		return 0;
	} else {  			// otherwise act normal
		int (*origFunc)(const char*) = dlsym(RTLD_NEXT,"HAL_CreateSimDevice");
		if(origFunc) {
			//printf("calling orig HAL_CreateSimDevice\n");
			return origFunc(name);
		} else {
			void* handle = dlopen("libwpiHal.so",RTLD_LAZY);
			if(!handle) {
				printf("dlopen failed\n");
				return 0;
			}
			origFunc = dlsym(handle,"HAL_CreateSimDevice");
			if(!origFunc) {
				printf("can't find orig HAL_CreateSimDevice\n");
				return 0;
			}
			return origFunc(name);
		}
	}
}
