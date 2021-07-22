#ifdef __cplusplus
#include<cstdlib>
#include<string>
#include<fstream>
#define RCP_COMPILE(x)\
	ifs.open(x);\
	tmp_string.assign((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));\
		system(tmp_string.c_str());\
		ifs.close();
#endif

#ifndef __cplusplus
#include<stdio.h>
#include<stdlib.h>
#define RCP_COMPILE(x)\
	if(fptr==NULL) return;\
	fptr=fopen(x, "r");\
	while(getline(&line,&len,fptr)!=EOF) system(line);\
		fclose(fptr);

#endif

#if(RCP_AUTO_RECOMPILE!=0)
__attribute((destructor)) void END_PROG(){
	#ifdef __cplusplus 
	std::string tmp_string;std::ifstream ifs;
	#else
	FILE *fptr;char *line=NULL;size_t len=0;
	#endif
	#ifdef RCP_SOURCE_PATH
		#ifdef RCP_HEADER_PATH
			#if(RCP_PRECOMPILE_HEADERS!=0)
				RCP_COMPILE(RCP_HEADER_PATH);
			#endif
		#endif
		RCP_COMPILE(RCP_SOURCE_PATH);
	#endif	
}
#endif
