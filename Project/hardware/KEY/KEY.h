#ifndef __KEY_H__
#define __KEY_H__
#include "main.h"
typedef struct _Key_Str
{
	//A1,B2,C3
	uint8_t now_key_num;     
	uint8_t last_key_num;
	
	//����״̬λ:0����,1����������,2�������
	uint8_t Key_Fast_Get;//����ǰ
	uint8_t Key_Last_Get;//������
	uint8_t Key_State;
	uint8_t Key_Jump_Cnt;
}Key_Str;


void Key_Data_Init(void);


#endif








