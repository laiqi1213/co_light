#include "u8g2.h"
#include "i2c.h"
#include "main.h"
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "oled.h"
#include "MENU.h"
u8g2_t u8g2;
QueueHandle_t Oled_State_Queue = NULL;


uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr)	
{	
	switch(msg){	
		
	case U8X8_MSG_GPIO_AND_DELAY_INIT:	
	    break;
		
	case U8X8_MSG_DELAY_MILLI:
			 HAL_Delay(arg_int);
	    break;
		
	case U8X8_MSG_GPIO_I2C_CLOCK:		
        break;							
		
    case U8X8_MSG_GPIO_I2C_DATA:			
        break;
		
	default:	
		return 0;
	}	
	return 1; // command processed successfully.
}	

//硬件iic回调函数
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)	
{
  static uint8_t buffer[32];		/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
  static uint8_t buf_idx;
  uint8_t *data;
  switch(msg){
		
    case U8X8_MSG_BYTE_SEND:
      data = (uint8_t *)arg_ptr;      
      while( arg_int > 0 ){
				buffer[buf_idx++] = *data;
				data++;
				arg_int--;
			}      
    break;
			
    case U8X8_MSG_BYTE_INIT:
      /* add your custom code to init i2c subsystem */
    break;
		
    case U8X8_MSG_BYTE_START_TRANSFER:
      buf_idx = 0;
    break;
		
    case U8X8_MSG_BYTE_END_TRANSFER:
   HAL_I2C_Master_Transmit_DMA(&hi2c1,u8x8_GetI2CAddress(u8x8), buffer, buf_idx);
    break;
		
    default:
      return 0;
  }
  return 1;
}

void OLED_init(void)
{
	Oled_State_Queue = xQueueCreate(oled_state_NUM,sizeof(uint16_t)); //定义队列
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2,U8G2_R0,u8x8_byte_hw_i2c,u8g2_gpio_and_delay_stm32);  //oled驱动
	u8g2_SetFont(&u8g2, u8g2_font_wqy16_t_chinese1);
	u8g2_InitDisplay(&u8g2); // 
	u8g2_SetPowerSave(&u8g2, 0); // wake up display
	u8g2_ClearDisplay(&u8g2);
	MENU_RunMainMenu();//写显存，不要在显示循环中写
}

void OLED_Dis(void)
{
	u8g2_ClearDisplay(&u8g2);
	u8g2_SendBuffer(&u8g2);
	vTaskDelay(10);
}
















