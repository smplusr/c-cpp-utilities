#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>

#define FGE_RESOLUTION 4096

typedef struct FGEglobals{
	int 		fd,width,height,px,py;
	size_t 		screen_len;
	unsigned char 	*map;
	struct 		fb_var_screeninfo info;
} FGEglobals;
FGEglobals fge_globals;

typedef struct FGEpixel{
	unsigned char r,g,b;
} FGEpixel;

typedef FGEpixel FGEline[FGE_RESOLUTION];
typedef FGEline FGEdisplay[FGE_RESOLUTION];

void fgeInit(){
	fge_globals.fd=getenv("FRAMEBUFFER")?open(getenv("FRAMEBUFFER"),O_RDWR):open("/dev/fb0",O_RDWR);
	ioctl(fge_globals.fd,FBIOGET_VSCREENINFO,&fge_globals.info);

	if(getenv("WIDTH"))	fge_globals.width=atoi(getenv("WIDTH"));	
	else fge_globals.width=fge_globals.info.xres;
	if(getenv("HEIGHT"))	fge_globals.height=atoi(getenv("HEIGHT"));
	else fge_globals.height=fge_globals.info.yres;
	if(getenv("POSX"))	fge_globals.px=atoi(getenv("POSX"));
	else fge_globals.px=0;
	if(getenv("POSY"))	fge_globals.py=atoi(getenv("POSY"));
	else fge_globals.py=0;

	fge_globals.screen_len=fge_globals.info.xres*fge_globals.info.yres*fge_globals.info.bits_per_pixel/8;
	fge_globals.map=mmap(NULL,fge_globals.screen_len,PROT_WRITE,MAP_SHARED,fge_globals.fd,0);
}
void fgeExit(){
	munmap(fge_globals.map,fge_globals.screen_len);
	close(fge_globals.fd);
}

void fgeFillBuffer(int x,int y,int w,int h,FGEpixel pixel,FGEdisplay display){
	for(int i=0;i<h-y;i++){
		for(int j=0;j<w-x;j++){
			display[i+y][j+x]=pixel;
		}
	}
}
void fgeSwapBuffers(FGEdisplay display){
	unsigned char *surface=fge_globals.map+(fge_globals.py)*fge_globals.info.xres*fge_globals.info.bits_per_pixel/8+(fge_globals.px)*fge_globals.info.bits_per_pixel/8;
	for(int i=0;i<fge_globals.height;i++){
		for(int j=0;j<fge_globals.width;j++){
			surface[fge_globals.info.bits_per_pixel/8*j+2]=display[i][j].r;	
			surface[fge_globals.info.bits_per_pixel/8*j+1]=display[i][j].g;
			surface[fge_globals.info.bits_per_pixel/8*j+0]=display[i][j].b;
		}
		surface+=fge_globals.info.xres*fge_globals.info.bits_per_pixel/8;
	}
}
