#ifdef __cplusplus
#include<iostream>
#define LOG(imp,dat)\
	std::cout<<"["<<imp<<"]: "<<dat<<std::endl;
#endif

#ifndef __cplusplus
#include<stdio.h>
#define LOG(imp,dat)\
	printf("[",imp,"]: ",x);
#endif

#define INFO(x)\
	LOG("INFO",x);
#define WARN(x)\
	LOG("WARN",x);
#define ERR(x)\
	LOG("ERR",x);
