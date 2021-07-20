#ifdef __cplusplus
#include<cstdlib>
#include<string>
#include<fstream>
#define COMPILE(x)\
	ifs.open(x);\
	tmp_string.assign((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));\
		system(tmp_string.c_str());\
		ifs.close();

#else
#include<stdio.h>
#include<stdlib.h>
#define COMPILE(x)\
	if(fptr==NULL) return;\
	fptr=fopen(x, "r");\
	while(getline(&line,&len,fptr)!=EOF) system(line);\
		fclose(fptr);

#endif

#if(AUTO_RECOMPILE!=0)
__attribute((destructor)) void END_PROG(){
	#ifdef __cplusplus 
	std::string tmp_string;std::ifstream ifs;
	#else
	FILE *fptr;char *line=NULL;size_t len=0;
	#endif
	#ifdef SOURCE_PATH
		#ifdef HEADER_PATH
			#if(PRECOMPILE_HEADERS!=0)
				COMPILE(HEADER_PATH);
			#endif
		#endif
		COMPILE(SOURCE_PATH);
	#endif	
}
#endif
