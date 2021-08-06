#define TKH_KEY_UNKNOWN		-1
#define TKH_KEY_Q		113
#define TKH_KEY_W		119
#define TKH_KEY_E		101
#define TKH_KEY_R		114
#define TKH_KEY_T		116
#define TKH_KEY_Y		121
#define TKH_KEY_U		107
#define TKH_KEY_I		105
#define TKH_KEY_O		111
#define TKH_KEY_P		112
#define TKH_KEY_A		97
#define TKH_KEY_S		115
#define TKH_KEY_D		100
#define TKH_KEY_F		102
#define TKH_KEY_G		103
#define TKH_KEY_H		104
#define TKH_KEY_J		106
#define TKH_KEY_K		107
#define TKH_KEY_L		108
#define TKH_KEY_SEMICOLON	59
#define TKH_KEY_Z		122
#define TKH_KEY_X		120
#define TKH_KEY_C		99
#define TKH_KEY_V		118
#define TKH_KEY_B		98
#define TKH_KEY_N		110
#define TKH_KEY_M		109
#define TKH_KEY_TAB		9
#define TKH_KEY_1		49
#define TKH_KEY_2		50
#define TKH_KEY_3		51
#define TKH_KEY_4		52
#define TKH_KEY_5		53
#define TKH_KEY_6		54
#define TKH_KEY_7		55
#define TKH_KEY_8		56
#define TKH_KEY_9		57
#define TKH_KEY_0		48
#define TKH_KEY_SPACE		32
#define TKH_KEY_RETURN		42
#define TKH_KEY_SLASH		47
#define TKH_KEY_PERIOD		44
#define TKH_KEY_UP		65
#define TKH_KEY_DOWN		66
#define TKH_KEY_RIGHT		67
#define TKH_KEY_LEFT		68

int tkh_key_buffer[256];

#ifdef __linux__
#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
int _getch(void){
	int character; struct termios late,updated;
	
	tcgetattr(0,&late);
	updated=late;
	updated.c_lflag&=~ICANON; updated.c_lflag&=~ECHO;
	character=getchar();
	tcsetattr(0,TCSANOW,&late);
	
	return character;
}
int _kbhit(void){
	int character,late_signal; struct termios late,updated;
	 
	tcgetattr(STDIN_FILENO, &late);
	updated=late;
	updated.c_lflag&=~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &updated);
	late_signal=fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, late_signal | O_NONBLOCK);

	character = getchar();
	if(character!=EOF){ungetc(character, stdin); return 1;}
	return 0;
}
void tkhPollKeys(){
	if(_kbhit()) tkh_key_buffer[_getch()]=1;
	else for(int key=0;key<256;key++) tkh_key_buffer[key]=0;
}
#endif
