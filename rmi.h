#ifdef __linux__

#include<unistd.h>
#include<fcntl.h>
#include<linux/input.h>

#ifndef RMI_INPUT_FILE
#define RMI_INPUT_FILE "/dev/input/mice"
#endif

int rmi_fd;

void (*MouseCallback)(int x,int y,int b[3]);

void rmiBindCallback(void (*mouse_callback)(int,int,int*)){
	const char *dev=RMI_INPUT_FILE;
	if(!rmi_fd) rmi_fd=open(dev,O_RDONLY | O_NONBLOCK);
	MouseCallback=mouse_callback;
}

void rmiPollEvents(){
	unsigned char data[4]; int bytes;
	int l,m,r; signed char x,y;
	bytes=read(rmi_fd,data,sizeof(data));
	if(bytes>0){
		x=data[1]; y=data[2];
		l=data[0]&0x1; r=data[0]&0x2; m=data[0]&0x4;
		int b[3]={l,m,r};
		MouseCallback(x,y,b);
	}else{return;}
}

#endif
