/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


#include "lib_lcd.h"
#include <stdio.h>
#include <string.h>
#include "DHT22.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	float Humidite = 0.0,Temperature = 0.0;
	rgb_lcd DataStruct;
	uint8_t dataH1;
	uint8_t dataH2;
	uint8_t dataT1;
	uint8_t dataT2;
	uint8_t check_sum;
	uint8_t sum;
	char buffH[32];
	char buffT[32];
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  DWT_Delay_Init();
  lcd_init(&hi2c1, &DataStruct);
  HAL_TIM_Base_Start(&htim2);

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_ADC_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  HAL_Init();
  DWT_Delay_Init();
  lcd_init(&hi2c1, &DataStruct);
  HAL_TIM_Base_Start(&htim2);

  int n = 0;

  char *cmdData = "AT";
  char cmdDataTmp[40];
  sprintf(cmdDataTmp,"%s\r\n",cmdData);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  //char buffer[128] = {0};
	  char buffer2[128] = {0};
	  HAL_UART_Receive(&huart1, buffer2, 128, 1000);
	  HAL_UART_Transmit (&huart2, (uint8_t *)buffer2, strlen (buffer2), 1000);

      //HAL_Delay(100);//pour serveur
      //if(n==2 || n==3){HAL_Delay(5000);}//pour serveur

	  HAL_Delay(5000);//pour client
	  if(n==7){HAL_Delay(1000);}//pour client
	  switch (n)
{
case 0:


	  HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);

		n = 1;

	break;

//服务器模式:
/*case 1:
	cmdData = "AT+CWMODE=2";
	sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);

		n = 2;
	break;
case 2:
	 cmdData = "AT+RST";
     sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);

		n = 3;
	break;
case 3:
	cmdData = "AT+CWSAP=\"ESP8266AB\",\"1234567890\",6,4";
     sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);

		n = 4;
	break;
case 4:
	cmdData = "AT+CIFSR";
     sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);
	 n=5;
	break;
case 5:
	cmdData = "AT+CIPMUX=1";
     sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);
		n = 6;
	break;
case 6:
	cmdData = "AT+CIPSERVER=1,8080";
     sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);

		n = 7;
	break;*/


//客户端模式:
case 1:
	  cmdData = "AT+RST";
	sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);

		n = 2;
	break;
case 2:
	cmdData = "AT+CWMODE=1";
     sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);

		n = 3;
	break;
case 3:
	cmdData = "AT+CIPMUX=0";
     sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);

		n = 4;
	break;
case 4:
	cmdData = "AT+CWJAP=\"ESP8266AAA\",\"1234567890\"";
     sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);
	 n=5;
	break;
case 5:
	cmdData = "AT+CIPMODE=1";
     sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);
		n = 6;
	break;
case 6:
	cmdData = "AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080";
     sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);

		n = 7;
	break;

case 7:
	cmdData = "AT+CIPSEND";
     sprintf(cmdDataTmp,"%s\r\n",cmdData);
	 HAL_UART_Transmit(&huart1,(uint8_t *)cmdDataTmp,strlen(cmdDataTmp),1000);

		n = 8;
	break;

case 8:
		 HAL_UART_Transmit(&huart1,(uint8_t *)buffH,strlen(buffH),1000);
		 HAL_UART_Transmit(&huart1,(uint8_t *)buffT,strlen(buffT),1000);
		break;


}

	                  DHT22_Start(); //demarrer le DHT22,dans le fichier DHT22.c
	    	          Data_Input(DHT_PORT, DHT_PIN);
	    	          commence_la_reception_de_donnees();
	    	          obtenir_donnees(&dataH1,&dataH2,&dataT1,&dataT2,&sum);
	                  check_sum = (uint8_t)(dataH1 + dataH2 + dataT1 + dataT2);
	                  if(check_sum == sum){
	                  Humidite = (float)((256 * dataH1 + dataH2) / 10.0);
	 	         	  Temperature = (float)((256 * dataT1 + dataT2) / 10.0);
	                  }
	                  else{
	                  lcd_print(&hi2c1,"SUM != CHECK");
	                  }
	                  affichage(Humidite,Temperature,buffH,buffT);
	                  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
