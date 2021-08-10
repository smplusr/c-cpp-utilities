#ifdef __linux__

#include<unistd.h>
#include<fcntl.h>
#include<linux/input.h>

#ifndef RSI_KEYBOARD_INPUT_FILE
#define RSI_KEYBOARD_INPUT_FILE "/dev/input/by-path/platform-i8042-serio-0-event-kbd"
#endif

#define RSI_KEY_RELEASE 0
#define RSI_KEY_PRESSED 1
#define RSI_KEY_REPEATS 2

#ifndef RSI_MOUSE_INPUT_FILE
#define RSI_MOUSE_INPUT_FILE "/dev/input/mice"
#endif

int keybr_fd,mouse_fd;

void (*KeyCallback)(int key,int act);
void (*MouseCallback)(int x,int y,int b[3]);

void rsiBindCallback(void (*key_callback)(int,int),void (*mouse_callback)(int,int,int*)){
	const char *keybr_dev=RSI_KEYBOARD_INPUT_FILE,*mouse_dev=RSI_MOUSE_INPUT_FILE;
	if(!mouse_fd) mouse_fd=open(mouse_dev,O_RDONLY | O_NONBLOCK);
	if(!keybr_fd) keybr_fd=open(keybr_dev,O_RDONLY | O_NONBLOCK);
	KeyCallback=key_callback; MouseCallback=mouse_callback;
}

void keybrPollEvents(){
	struct input_event ev; int bytes;
	bytes=read(keybr_fd,&ev,sizeof ev);
	if(bytes>0) if(ev.type=EV_KEY && ev.value==0|1|2 && ev.code!=0) KeyCallback((int)ev.code,(int)ev.value);
	else return;
}

void mousePollEvents(){
	unsigned char data[4]; int bytes;
	int l,m,r; signed char x,y;
	bytes=read(mouse_fd,data,sizeof(data));
	if(bytes>0){
		x=data[1]; y=data[2];
		l=data[0]&0x1; r=data[0]&0x2; m=data[0]&0x4;
		int b[3]={l,m,r};
		MouseCallback(x,y,b);
	}else{return;}
}

void rsiPollEvents(){keybrPollEvents(); mousePollEvents();}

#endif
