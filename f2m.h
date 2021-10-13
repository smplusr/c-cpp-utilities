// Framebuffer 2D geometry Module-extension

#include "fge.h"

typedef struct FGEvec2{
	int x,y;
} FGEvec2;

typedef struct FGEedge2{
	FGEvec2 v1,v2;
} FGEedge2;

typedef struct FGEtris2{
	FGEedge2 e1;
	FGEedge2 e2;
	FGEedge2 e3;
} FGEtris2;

void fgeDrawSquare(int x,int y,int w,int h,int s,FGEpixel pixel,FGEdisplay display){
	for(size_t i=0;i<s;i++){
		for(size_t j=0;j<w-x+s;j++){
			display[i+x][j+x]=pixel;
			display[i+h][j+x]=pixel;
		}
		for(size_t j=0;j<h-y+s;j++){
			display[j+y][i+y]=pixel;
			display[j+y][i+w]=pixel;
		}

	}
}
void fgeFillSquare(int x,int y,int w,int h,FGEpixel pixel,FGEdisplay display){
	for(size_t i=0;i<h-y;i++){
		for(size_t j=0;j<w-x;j++){
			display[i+y][j+x]=pixel;
		}
	}
}
void fgeStrokeLine(FGEedge2 e,FGEpixel pixel,FGEdisplay display){
	for(double i=0;i<1;i+=.001){
		display[(int)(i*e.v2.y)+e.v1.y][(int)(i*e.v2.x)+e.v1.x]=pixel;
	}
}
void fgeDrawTriangle(FGEtris2 tris,FGEpixel pixel,FGEdisplay display){
	fgeStrokeLine(tris.e1,pixel,display);
	fgeStrokeLine(tris.e2,pixel,display);
	fgeStrokeLine(tris.e3,pixel,display);
}
