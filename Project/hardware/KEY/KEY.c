#include "KEY.h"
#include "main.h"
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "cmsis_os.h"
Key_Str Key_Num;
extern osMessageQueueId_t KEY_NUM_QueueHandle;


void Key_Data_Init(void)
{
	Key_Num.now_key_num=0;
	Key_Num.last_key_num=0;
	Key_Num.Key_State=0;
	Key_Num.Key_Jump_Cnt=10;
	Key_Num.Key_Fast_Get=0;
	Key_Num.Key_Last_Get=0;
}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		if(Key_Num.Key_State==0)
		{
			Key_Num.Key_State=1; //开启消抖
			if (GPIO_Pin==GPIO_PIN_8) 
			{

				Key_Num.Key_Fast_Get=1;
			}  
			else if(GPIO_Pin==GPIO_PIN_9)
			{
				
				Key_Num.Key_Fast_Get=2;
			}
			else if(GPIO_Pin==GPIO_PIN_12)
			{

				Key_Num.Key_Fast_Get=3;
			}
		}
		if(Key_Num.Key_State==2)//消抖完成
		{
			if (GPIO_Pin==GPIO_PIN_8) 
			{
				Key_Num.Key_Last_Get=1;
			}  
			else if(GPIO_Pin==GPIO_PIN_9)
			{
				Key_Num.Key_Last_Get=2;
			}
			else if(GPIO_Pin==GPIO_PIN_12)
			{
				Key_Num.Key_Last_Get=3;
			}
			
		}
		else
			return ;
}

//消抖和传递
void Key_DisJump(void)
{
	if(Key_Num.Key_State==1)
	{
		vTaskDelay(Key_Num.Key_Jump_Cnt);
	}
	if(Key_Num.Key_State==2)
	{
		if(Key_Num.Key_Last_Get==Key_Num.Key_Fast_Get)
		{
			Key_Num.last_key_num=Key_Num.now_key_num;
			Key_Num.now_key_num=Key_Num.Key_Last_Get;
			osMessageQueuePut(KEY_NUM_QueueHandle,&Key_Num.now_key_num,1,0);//值进队列KEY_NUM_QUEUE
			Key_Num.Key_State=0;
		}
		if(Key_Num.Key_Last_Get!=Key_Num.Key_Fast_Get)
		{
			Key_Num.last_key_num=0;
			Key_Num.now_key_num=0;
			Key_Num.Key_State=0;
		}
	}
}














