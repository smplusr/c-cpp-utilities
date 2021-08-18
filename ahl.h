#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define AHL_MAX_CHAR_DATA (int)(65535/sizeof(int))

typedef void (*(*ahl_funcptr)())(void);
unsigned char ahl_buffer[AHL_MAX_CHAR_DATA];

void (*(*ahlAttribPointer(unsigned char arg[]))())(void){
	return ((void (*(*)())(void))(void (*)(void))arg);
}

void ahlUpdateBuffer(char *v){
	char c[AHL_MAX_CHAR_DATA];
	int i=0;
	strcat(c,v);	
	for(int i=0;i<(strlen(c)+5);i++){
		sscanf(c,"%hhx",c);
		ahl_buffer[i]=*c;
		for(int j=0;j<3;j++) memmove(c,c+1,strlen(c+1)+1);
	}
}

void ahlReadInput(){	
	char c[AHL_MAX_CHAR_DATA];
	scanf("%[^\n]",c);
	ahlUpdateBuffer(c);
}

void ahlReadFile(const char *file){	
	char c[AHL_MAX_CHAR_DATA];
	FILE *fptr=fopen(file,"r");
	while(1) if(fscanf(fptr,"%[^_]",c)==EOF) break;
	ahlUpdateBuffer(c);
}