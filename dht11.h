//Coded by Nguyen Thanh Cuong
#ifndef __DHT11_H
#define __DHT11_H

#include "main.h"
#include "stm32f1xx_hal.h"

int Start_DHT11(TIM_HandleTypeDef *htim,GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
int Read_DHT11(TIM_HandleTypeDef *htim,GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
void Clear_Data(uint8_t* data);
int Check_Pairity(void);
#endif
//Coded by Nguyen Thanh Cuong
