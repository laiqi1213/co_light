#ifndef __KEY_H__
#define __KEY_H__
#include "main.h"
typedef struct _Key_Str
{
	//A1,B2,C3
	uint8_t now_key_num;     
	uint8_t last_key_num;
	
	//消抖状态位:0空闲,1按下消抖中,2消抖完成
	uint8_t Key_Fast_Get;//消抖前
	uint8_t Key_Last_Get;//消抖后
	uint8_t Key_State;
	uint8_t Key_Jump_Cnt;
}Key_Str;


void Key_Data_Init(void);


#endif








