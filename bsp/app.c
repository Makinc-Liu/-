#include "app.h"
#include "oled.h"
#include "stdio.h"
#include "usart.h"

char lcdLine_1st_line[16];
char lcdLine_2st_line[16];
uint8_t Rdata[10];

void user_oled_init()
{
	HAL_UART_Receive_IT(&huart2,Rdata,1);
	
	OLED_PowerControl(ENABLE);
	HAL_Delay(200);
	OLED_Init();
	sprintf(lcdLine_1st_line, "Makinc_liu");
	sprintf(lcdLine_2st_line, "Hello World    ");

	OLED_ShowString(0, 0, (unsigned char *)lcdLine_1st_line, 16);
	OLED_ShowString(0, 2, (unsigned char *)lcdLine_2st_line, 16);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch(GPIO_Pin)
  {
    case GPIO_PIN_14: HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_0);
    default: break;
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	HAL_UART_Transmit(&huart2,Rdata,1,0xff);
	HAL_UART_Receive_IT(&huart2,Rdata,1);
}
