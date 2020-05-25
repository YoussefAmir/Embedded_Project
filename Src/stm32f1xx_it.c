/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"

extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern char s[8];
extern int flg;
//extern int flg2;
//extern char out[5];
extern int ctt;
uint32_t res;
extern char out[4];
int i;
extern char y[6];

//extern volatile char line_buffer[5 + 1]; // Holding buffer with space for terminating NUL
//extern volatile int line_valid;
//extern uint32_t count;
//extern __IO uint32_t uwTick;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
	
if(flg == 1)
	{
	ctt++;
		HAL_ADC_Start(&hadc1);
	//HAL_ADC_Start_IT(&hadc1);
	//s	HAL_UART_Transmit_IT(&huart1,(uint8_t *) &ctt,sizeof(ctt));
	}
	
	
	//if( ctt < (((8000000) / 10) - 1)*100)
	//{
//			sprintf(out, "%d\n\r", ctt);
//		HAL_UART_Transmit_IT(&huart1,(uint8_t*)&out,sizeof(out));
	//}

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles ADC1 and ADC2 global interrupts.
  */
void ADC1_2_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_2_IRQn 0 */

	res = HAL_ADC_GetValue(&hadc1);
	sprintf(out, "%d", res);
	//flg2 = 1;
	HAL_UART_Transmit_IT(&huart1,(uint8_t*)&out,sizeof(out));
  /* USER CODE END ADC1_2_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  /* USER CODE BEGIN ADC1_2_IRQn 1 */

  /* USER CODE END ADC1_2_IRQn 1 */
}

/**
  * @brief This function handles TIM1 break interrupt.
  */
//void TIM1_BRK_IRQHandler(void)
//{
//  /* USER CODE BEGIN TIM1_BRK_IRQn 0 */
//	char m = 'B';
//	HAL_UART_Transmit_IT(&huart1,(uint8_t*)&m,sizeof(m));

//  /* USER CODE END TIM1_BRK_IRQn 0 */
//  HAL_TIM_IRQHandler(&htim1);
//  /* USER CODE BEGIN TIM1_BRK_IRQn 1 */

//  /* USER CODE END TIM1_BRK_IRQn 1 */
//}

///**
//  * @brief This function handles TIM1 update interrupt.
//  */
//void TIM1_UP_IRQHandler(void)
//{
//  /* USER CODE BEGIN TIM1_UP_IRQn 0 */
//char m = 'U';
//	HAL_UART_Transmit_IT(&huart1,(uint8_t*)&m,sizeof(m));

//  /* USER CODE END TIM1_UP_IRQn 0 */
//  HAL_TIM_IRQHandler(&htim1);
//  /* USER CODE BEGIN TIM1_UP_IRQn 1 */

//  /* USER CODE END TIM1_UP_IRQn 1 */
//}

///**
//  * @brief This function handles TIM1 trigger and commutation interrupts.
//  */
//void TIM1_TRG_COM_IRQHandler(void)
//{
//  /* USER CODE BEGIN TIM1_TRG_COM_IRQn 0 */
////HAL_TIM_Base_Stop_IT(&htim1);
//	//HAL_UART_Transmit_IT(&huart1,(uint8_t *) &"koko",sizeof("koko"));
//	char m = 'M';
//	HAL_UART_Transmit_IT(&huart1,(uint8_t*)&m,sizeof(m));

//  /* USER CODE END TIM1_TRG_COM_IRQn 0 */
//  HAL_TIM_IRQHandler(&htim1);
//  /* USER CODE BEGIN TIM1_TRG_COM_IRQn 1 */

//  /* USER CODE END TIM1_TRG_COM_IRQn 1 */
//}

///**
//  * @brief This function handles TIM1 capture compare interrupt.
//  */
//void TIM1_CC_IRQHandler(void)
//{
//  /* USER CODE BEGIN TIM1_CC_IRQn 0 */
//char m = 'C';
//	HAL_UART_Transmit_IT(&huart1,(uint8_t*)&m,sizeof(m));

//  /* USER CODE END TIM1_CC_IRQn 0 */
//  HAL_TIM_IRQHandler(&htim1);
//  /* USER CODE BEGIN TIM1_CC_IRQn 1 */

//  /* USER CODE END TIM1_CC_IRQn 1 */
//}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
	//HAL_UART_IRQHandler(&huart1);
  	HAL_UART_Receive_IT(&huart1,(uint8_t*)&s,sizeof(s));

	
		
	//	HAL_UART_Transmit(&huart1,(uint8_t*)&s,sizeof(s),10);



  //HAL_UART_Transmit_IT(&huart1,(uint8_t *) &s,sizeof(s));
	
	//HAL_UART_Transmit_IT(&huart1,(uint8_t *) &s,sizeof(s));
	//HAL_ADC_Start(&hadc1);
	//HAL_SYSTICK_Config(7999);
//	count++;	
	//HAL_UART_Transmit_IT(&huart1,(uint8_t *) &out,sizeof(out));
	
	//__HAL_TIM_SET_AUTORELOAD(&htim1,125000);
	//TIM1->ARR = (8*10^6) / 150;
	//__HAL_TIM_SET_COUNTER(&htim1,(8*10^6) / 1);
	//TIM1->ARR = (8*10^6) / 1;
	//HAL_TIM_Base_Start_IT(&htim1);
		
//	if(__HAL_TIM_GET_COUNTER(&htim1) == ((8*10^6) / 80000))
//	{
//		HAL_TIM_Base_Stop_IT(&htim1);
//		HAL_ADC_Start_IT(&hadc1);
//	}
	//__HAL_TIM_SET_PRESCALER(&htim1,125000);
//		char k = 'l';
//		  HAL_UART_Transmit_IT(&huart1,(uint8_t *) &k,sizeof(k));

//	char str2[5];
//	strncpy( str2, s, 5);
//	
//	sscanf(str2, "%d", &i);
  
	//((8*10^6) / 80000) - 1
	
	//HAL_ADC_Start(&hadc1);
	//res = HAL_ADC_GetValue(&hadc1);
	//sprintf(out, "%d\n\r", res);
  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
