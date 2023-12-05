#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define __USE_GNU
#include <dlfcn.h>
#include <wiringPi.h>

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

int
set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                printf("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void
set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                printf ("error %d setting term attributes", errno);
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
	serial_port = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);
	if(serial_port < 0) {
		printf("error opening port\n");
		return -1;
	}
	set_interface_attribs (serial_port, 115200, 0);
	set_blocking (serial_port, 0);

	return 0;
}

int32_t HAL_InitializeSerialPortDirect(int32_t port,
                                                    const char* portName,
                                                    int32_t* status) {
	printf("HAL_InitializeSerialPortDirect: %s %d\n", portName, port);
	serial_port = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);
	if(serial_port < 0) {
		printf("error opening port\n");
		return -1;
	}
	set_interface_attribs (serial_port, 115200, 0);
	set_blocking (serial_port, 0);

	return 0;
}

int32_t HAL_ReadSerial(int32_t handle, char* buffer, int32_t count,
                       int32_t* status) {
	int32_t n = read(serial_port, buffer, count);
	buffer[n+1] = 0;
	//printf("HAL_ReadSerial %d %s\n", n, buffer);
  	return n;
}

int32_t HAL_WriteSerial(int32_t handle, const char* buffer,
                        int32_t count, int32_t* status) {
	int32_t n = write(serial_port, buffer, count);
	//printf("HAL_WriteSerial %d %s\n", n, buffer);
  	return n;
}

void HAL_CloseSerial(int32_t handle, int32_t* status) {
	printf("HAL_CloseSerial\n");
	close(serial_port);
	serial_port = 0;
}

void HAL_SetPWMPosition(int32_t pwmPortHandle, double position,
                     int32_t* status) {
	//  printf("Set PWM Position\n");
	wiringPiSetup();
	pinMode(26, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(16);
	delay(10);
	pwmWrite(26,position*1023);
}