#ifdef __linux__

#include<unistd.h>
#include<fcntl.h>
#include<linux/input.h>

#ifndef RKI_INPUT_FILE
#define RKI_INPUT_FILE "/dev/input/by-path/platform-i8042-serio-0-event-kbd"
#endif

#define RKI_KEY_RELEASE 0
#define RKI_KEY_PRESSED 1
#define RKI_KEY_REPEATS 2

int rki_fd;

void (*KeyCallback)(int key,int act);

void rkiBindCallback(void (*key_callback)(int,int)){
	const char *dev=RKI_INPUT_FILE;
	if(!rki_fd) rki_fd=open(dev,O_RDONLY | O_NONBLOCK);
	KeyCallback=key_callback;
}

void rkiPollEvents(){
	struct input_event ev; int bytes;
	bytes=read(rki_fd,&ev,sizeof ev);
	if(bytes>0) if(ev.type=EV_KEY && ev.value==0|1|2 && ev.code!=0) KeyCallback((int)ev.code,(int)ev.value);
	else return;
}

#endif
