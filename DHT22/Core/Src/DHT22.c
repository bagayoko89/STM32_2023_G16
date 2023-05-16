/************** MAKE CHANGES HERE ********************/
#include "stm32l1xx_hal.h"
#include "DHT22.h"

/*******************************************     NO CHANGES AFTER THIS LINE      ****************************************************/

void DHT22_Start(void)
{
    Data_Output(DHT_PORT, DHT_PIN);
  	HAL_GPIO_WritePin(DHT_PORT, DHT_PIN, GPIO_PIN_RESET);//输出低电平1ms
  	DWT_Delay_us(1200);
  	HAL_GPIO_WritePin(DHT_PORT, DHT_PIN, GPIO_PIN_SET);  //释放总线，即输出高电平30us
  	DWT_Delay_us(30);
}
void Data_Output (GPIO_TypeDef *PORT, uint16_t PIN) //direction vers le capteur
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; //pushpull
	HAL_GPIO_Init(PORT, &GPIO_InitStruct);
}

void Data_Input (GPIO_TypeDef *PORT, uint16_t PIN) //direction vers le microcontroleur
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(PORT, &GPIO_InitStruct);
}
void Read_data (uint8_t *data)
  {
  	int i, k;
  	for (i=0;i<8;i++)
  	{
  		if (HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN) == GPIO_PIN_RESET)
  		{
  			(*data)&= ~(1<<(7-i)); //data bit is 0
  			while(!(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN)));
  			DWT_Delay_us(40);
  		}
  		else                       //data bit is 1
  		{
  			(*data)|= (1<<(7-i));
  			for (k=0;k<1000;k++)
  			{
  				if (HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN) == GPIO_PIN_RESET)
  				  {
  				  	break;
  				  }
  			}
  			while(!(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN)));
  			DWT_Delay_us(40);
  		}
  	 }
  }
uint8_t DHT22_Read_Byte(void)
{
	uint8_t i;
	uint8_t DHT22_Byte = 0;
	for(i = 0; i < 8; i++)
	{
		while (HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN) == GPIO_PIN_RESET);//等待低电平结束
		DWT_Delay_us(40); //等待40us，再判断IO口电平状态

		if(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN) == GPIO_PIN_SET)// 40 us后仍为高电平则表示数据“1”
		{
			/* 等待数据1的高电平结束 */
			while(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN) == GPIO_PIN_SET);

			DHT22_Byte |= (uint8_t)(0x01 << (7-i));  //把第7-i位置1，MSB先行
		}
		else// 40 us后为低电平则表示数据“0”
		{
			DHT22_Byte &= (uint8_t)~(0x01 << (7-i)); //把第7-i位置0，MSB先行
		}
	}

	return DHT22_Byte;//返回当前读取到的字节
}

void commence_la_reception_de_donnees(void){
    int k;
	while(!(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN)));
	            	  for(k=0;k<1000;k++)
	            	  {
	            		  if (HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN) == GPIO_PIN_RESET)
	            		  {
	            	  	  	break;
	            	  	  }
	            	  }

	            	  while(!(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN)));
	            	  DWT_Delay_us(40);
}

void obtenir_donnees(uint8_t *dataH1,uint8_t *dataH2,uint8_t *dataT1,uint8_t *dataT2,uint8_t * sum){

	  Read_data(dataH1);
	  Read_data(dataH2);
	  Read_data(dataT1);
	  Read_data(dataT2);
	  Read_data(sum);

}



