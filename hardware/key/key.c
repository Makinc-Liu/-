#include "key.h"


#define Read_row1 HAL_GPIO_ReadPin(GPIOB , GPIO_PIN_6)
#define Read_row2 HAL_GPIO_ReadPin(GPIOB , GPIO_PIN_7)


#define Write_column1_H HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1 , GPIO_PIN_SET)
#define Write_column2_H HAL_GPIO_WritePin(GPIOB , GPIO_PIN_0 , GPIO_PIN_SET)
#define Write_column3_H HAL_GPIO_WritePin(GPIOA , GPIO_PIN_8 , GPIO_PIN_SET)

#define Write_column1_L HAL_GPIO_WritePin(GPIOB , GPIO_PIN_1 , GPIO_PIN_RESET)
#define Write_column2_L HAL_GPIO_WritePin(GPIOB , GPIO_PIN_0 , GPIO_PIN_RESET)
#define Write_column3_L HAL_GPIO_WritePin(GPIOA , GPIO_PIN_8 , GPIO_PIN_RESET)



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch(GPIO_Pin)
  {
    case GPIO_PIN_14: HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_0);
    default: break;
  }
}
void key_init(void)
{
	Write_column1_L;
	Write_column2_L;
	Write_column3_L;
	
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_6 , GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_7 , GPIO_PIN_RESET);
	
}
uint8_t key_scan(void)
{
	int key_val = 0;
	
	key_init();	
	
	Write_column1_H;
	if (Read_row1 == GPIO_PIN_SET) key_val=1;
	if (Read_row2 == GPIO_PIN_SET) key_val=4;
	Write_column1_L;
	
	Write_column2_H;
	if (Read_row1 == GPIO_PIN_SET) key_val=2;
	if (Read_row2 == GPIO_PIN_SET) key_val=5;
	Write_column2_L;

	Write_column3_H;
	if (Read_row1 == GPIO_PIN_SET) key_val=3;
	if (Read_row2 == GPIO_PIN_SET) key_val=6;
	Write_column3_L;

	
	return key_val;
	
}
