#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define AHL_BUFFER_SIZE (int)(65535/sizeof(int))

typedef void (*(*AHLfuncptr)())(void);
typedef unsigned char AHLbuffer[AHL_BUFFER_SIZE];

void (*(*ahlAttribPointer(unsigned char arg[]))())(void){
	return ((void (*(*)())(void))(void (*)(void))arg);
}
void ahlUpdateBuffer(char *v,AHLbuffer b){
	AHLbuffer c;
	int i=0;
	strcat(c,v);	
	for(int i=0;i<(strlen(c)+5);i++){
		sscanf(c,"%hhx",c);
		b[i]=*c;
		for(int j=0;j<3;j++) memmove(c,c+1,strlen(c+1)+1);
	}
}
void ahlReadInput(AHLbuffer b){
	AHLbuffer c;
	scanf("%[^\n]",c);
	ahlUpdateBuffer(c,b);
}
void ahlReadFile(const char *file,AHLbuffer b){	
	AHLbuffer c;
	FILE *fptr=fopen(file,"r");
	while(1) if(fscanf(fptr,"%[^_]",c)==EOF) break;
	ahlUpdateBuffer(c,b);
}
