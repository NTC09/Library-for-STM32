//Coded by Nguyen Thanh Cuong
#include "dht11.h"
//==========================================================================
uint8_t Read_Data_DHT11[5];
uint8_t Buff;
uint16_t TIM_Count;
//==========================================================================
void Clear_Data(uint8_t* data)
{
	for(int i=0;i<sizeof(data);i++)
		data[i]=NULL;
}
//==========================================================================
int Start_DHT11(TIM_HandleTypeDef *htim,GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
	//Bat dau giao tiep voi DHT11
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	//------------------------------------------------------------------------
	//Cho DHT11 keo chan DATA len cao
	__HAL_TIM_SetCounter(htim,0);
	while(__HAL_TIM_GetCounter(htim)<20) //Cho 20us
		if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin))
			break;
	TIM_Count=__HAL_TIM_GetCounter(htim);
	if(TIM_Count>=20) return 0; //Thoat
	//------------------------------------------------------------------------
	//Cho DHT11 keo chan DATA xuong thap
	__HAL_TIM_SetCounter(htim,0);
	while(__HAL_TIM_GetCounter(htim)<40) //Cho 40us
		if(!HAL_GPIO_ReadPin(GPIOx, GPIO_Pin))
			break;
	TIM_Count=__HAL_TIM_GetCounter(htim);
	if(TIM_Count<=5||TIM_Count>=40) return 0; //Thoat 
	//------------------------------------------------------------------------
		//Cho DHT11 keo chan DATA len cao
	__HAL_TIM_SetCounter(htim,0);
	while(__HAL_TIM_GetCounter(htim)<95) //Cho 95us
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
			break;
	TIM_Count=__HAL_TIM_GetCounter(htim);
	if(TIM_Count<=70||TIM_Count>=95) return 0; //Thoat
	//------------------------------------------------------------------------
	//Cho DHT11 keo chan DATA xuong thap
	__HAL_TIM_SetCounter(htim,0);
	while(__HAL_TIM_GetCounter(htim)<95) //Cho 95us
		if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
			break;
	TIM_Count=__HAL_TIM_GetCounter(htim);
	if(TIM_Count<=70||TIM_Count>=95) return 0; //Thoat 
	//------------------------------------------------------------------------
	return 1;
}
//==========================================================================
int Read_DHT11(TIM_HandleTypeDef *htim,GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
	//Clear_Data(Read_Data_DHT11);
//	uint8_t Check=Start_DHT11();
//	if(Check==0) return 0;
	Start_DHT11(htim,GPIOx,GPIO_Pin);
	for(int n=0;n<5;n++)
	{
	for(int i=0;i<8;i++)
		{
			//Cho DHT11 keo chan DATA len cao
			__HAL_TIM_SetCounter(htim,0);
			while(__HAL_TIM_GetCounter(htim)<60) //Cho 55us
				if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin))
					break;
				
			TIM_Count=__HAL_TIM_GetCounter(htim);
			if(TIM_Count<=40||TIM_Count>=60) return 0; //Thoat
			//Cho DHT11 keo chan DATA xuong thap
			__HAL_TIM_SetCounter(htim,0);
			while(__HAL_TIM_GetCounter(htim)<80) //Cho 100us
				if(!HAL_GPIO_ReadPin(GPIOx, GPIO_Pin))
					break;
				TIM_Count=__HAL_TIM_GetCounter(htim);
			Read_Data_DHT11[n]<<=1;
			if(TIM_Count<=30) 		//26~28us la bit 0
				Read_Data_DHT11[n] &= ~1;
			else if(TIM_Count>40) //lon hon la bit 1
				Read_Data_DHT11[n] |= 1;
		}
	}
	if (Check_Pairity()==0)
		return 0;
	return 1;
}
//==========================================================================
int Check_Pairity(void) //Kiem tra loi
{
	uint8_t Check_sum=Read_Data_DHT11[0]+Read_Data_DHT11[1]+Read_Data_DHT11[2]+Read_Data_DHT11[3];
	if(Read_Data_DHT11[4]!=Check_sum)
		return 0;
	return 1;
}
//==========================================================================
//Coded by Nguyen Thanh Cuong
