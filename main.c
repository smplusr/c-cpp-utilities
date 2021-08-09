// Raw Key Input (Handler/Mapper/Binding) 

/* Must be defined before including the rki header file.
 * If the file is not declared before including rki.h, it will be defined
 * inside the rki.h with default input file (same as following). */
#define RKI_INPUT_FILE "/dev/input/by-path/platform-i8042-serio-0-event-kbd"
#define KMI_INPUT_FILE "/dev/input/mice"
#include"rki.h"
#include"rmi.h"

#include<stdio.h>

int key_buffer[256];

void key_callback(int key,int act){
	if(act==RKI_KEY_PRESSED) key_buffer[key]=1;
	if(act==RKI_KEY_RELEASE) key_buffer[key]=0;
}
void mouse_callback(int x,int y,int button[3]){
	printf("x=%d, y=%d, l=%d, m=%d, r=%d\n",x,y,button[0],button[1],button[2]);
}

int main(void){
	/* Defining callbacks for keyboard and mouse. */
	rkiBindCallback(&key_callback);
	rmiBindCallback(&mouse_callback);
	while(1){
		/* The key is in raw format (KEY_Q or code 16 is mapped on A
		 * azerty keyboards). */
		if(key_buffer[KEY_Q]) printf("%s\n","Hello World!");
		/* Polling events from keyboard and mouse. */
		rkiPollEvent(); rmiPollEvent();
	}
		
}
