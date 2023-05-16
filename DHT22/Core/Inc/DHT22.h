

#ifndef DHT_H_
#define DHT_H_

#include "timer.h"
#define DHT_PORT GPIOA
#define DHT_PIN GPIO_PIN_1

void Data_Output (GPIO_TypeDef *PORT, uint16_t PIN);
void Data_Input (GPIO_TypeDef *PORT, uint16_t PIN);
uint8_t DHT22_Read_Byte(void);
void DHT22_Start(void);
void Read_data (uint8_t *data);
void commence_la_reception_de_donnees(void);
void obtenir_donnees(uint8_t *dataH1,uint8_t *dataH2,uint8_t *dataT1,uint8_t *dataT2,uint8_t * sum);
void calculer(uint8_t sum,uint8_t check_sum,uint8_t dataH1,uint8_t dataH2,uint8_t dataT1,uint8_t dataT2 ,float *Humidite, float *Temperature);
#endif /* DHT_H_ */
