#include "app.h"
#include "oled.h"
#include "stdio.h"
#include "usart.h"
#include "adc.h"

char lcdLine_1st_line[16];
char lcdLine_2st_line[16];
uint8_t Rdata[10];
uint16_t adc1 = 0;
uint16_t adc2 = 0;

void user_oled_init()
{
	HAL_UART_Receive_IT(&huart2,Rdata,1);
	
	OLED_PowerControl(ENABLE);
	HAL_Delay(200);
	OLED_Init();
	sprintf(lcdLine_1st_line, "adc test ");
	sprintf(lcdLine_2st_line, "%0.2f %0.2f",adc1*3.3/4096,adc2*3.3/4096);

	OLED_ShowString(0, 0, (unsigned char *)lcdLine_1st_line, 16);
	OLED_ShowString(0, 2, (unsigned char *)lcdLine_2st_line, 16);
}
void user_loop(void)
{
	EX_adc();
	
	sprintf(lcdLine_1st_line, "adc test ");
	sprintf(lcdLine_2st_line, "%0.2f %0.2f",adc1*3.3/4096,adc2*3.3/4096);

	OLED_ShowString(0, 0, (unsigned char *)lcdLine_1st_line, 16);
	OLED_ShowString(0, 2, (unsigned char *)lcdLine_2st_line, 16);	
	
	
	HAL_Delay(10);
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch(GPIO_Pin)
  {
    case GPIO_PIN_14: HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_6);
    default: break;
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	HAL_UART_Transmit(&huart2,Rdata,1,0xff);
	HAL_UART_Receive_IT(&huart2,Rdata,1);
}
void EX_adc(void)
{
	HAL_ADC_Start(&hadc);
	adc1 = HAL_ADC_GetValue(&hadc);
	HAL_ADC_Start(&hadc);
	adc2 = HAL_ADC_GetValue(&hadc);	
	printf("%d %d\n",adc1,adc2);

}
