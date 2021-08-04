#ifdef __linux__

#ifdef __cplusplus
#include<cstdio>
#include<cstdlib>
#include<dlfcn.h>
#include<cstring>
#include<unistd.h>
#ifndef ECL_COMPILE_INSTRUCTION
	#define ECL_COMPILE_INSTRUCTION "g++ -fPIC -shared -o tmp.so tmp.c"
#endif
#define ECL_GET_DL_POINTER void (*init)()=reinterpret_cast<void(*)()>(dlsym(lib,"__init__"));
#endif

#ifndef __cplusplus
#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
#include<string.h>
#include<unistd.h>
#ifndef ECL_COMPILE_INSTRUCTION
	#define ECL_COMPILE_INSTRUCTION "gcc -fPIC -shared -o tmp.so tmp.c" 
#endif
#define ECL_GET_DL_POINTER void (*init)()=dlsym(lib,"__init__");
#endif

#define ECL_COMPILE system(ECL_COMPILE_INSTRUCTION);
#define ECL_LOAD_LIB()\
	void *lib;\
	lib=dlopen("./tmp.so",RTLD_LAZY);\
	ECL_GET_DL_POINTER;\
		dlclose(lib); init();\
		if(access("tmp.so",F_OK)==0) system("rm tmp.so");
	
void evalc(const char data[256]){
	FILE *fptr;
	fptr=fopen("tmp.c","w"); fprintf(fptr,"%s",data); fclose(fptr);
		ECL_COMPILE; ECL_LOAD_LIB();
		if(access("tmp.c",F_OK)==0) system("rm tmp.c");
}

void evalf(const char *file){
	char *buffer=(char*)malloc(512);
	strcat(buffer,"cp "); strcat(buffer,file); strcat(buffer," tmp.c "); system(buffer);
		ECL_COMPILE; ECL_LOAD_LIB();
		if(access("tmp.c",F_OK)==0)  system("rm tmp.c");
}

#endif
