#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#define __USE_GNU
#include <dlfcn.h>

int32_t HAL_CreateSimDevice(const char* name) {
	printf("HAL_CreateSimDevice: %s\n", name);
	if(!strncmp(name, "SPARK", 5) || !strncmp(name, "navX", 4)) {  
		// pretend we are not in a simulation 
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


/*
HAL_ENUM(HAL_SerialPort) {
  HAL_SerialPort_Onboard = 0,
  HAL_SerialPort_MXP = 1,
  HAL_SerialPort_USB = 2,
  HAL_SerialPort_USB1 = 2,
  HAL_SerialPort_USB2 = 3
};
*/

int serial_port = 0;

int32_t HAL_InitializeSerialPort(int32_t port,
                                              int32_t* status) {
	printf("HAL_InitializeSerialPort: %d\n", port);
	serial_port = open("/dev/ttyACM0", O_RDWR);

	return 0;
}

int32_t HAL_InitializeSerialPortDirect(int32_t port,
                                                    const char* portName,
                                                    int32_t* status) {
	printf("HAL_InitializeSerialPortDirect: %s %d\n", portName, port);
	serial_port = open("/dev/ttyACM0", O_RDWR);

	return 0;
}

int32_t HAL_ReadSerial(int32_t handle, char* buffer, int32_t count,
                       int32_t* status) {
	printf("HAL_ReadSerial\n");
	int32_t n = read(serial_port, buffer, count);
  	return n;
}

int32_t HAL_WriteSerial(int32_t handle, const char* buffer,
                        int32_t count, int32_t* status) {
	printf("HAL_WriteSerial\n");
	int32_t n = write(serial_port, buffer, count);
  	return n;
}

void HAL_CloseSerial(int32_t handle, int32_t* status) {
	printf("HAL_CloseSerial\n");
	close(serial_port);
	serial_port = 0;
}
