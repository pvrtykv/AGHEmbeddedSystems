/**
  ******************************************************************************
  * @file    Templates/Src/main.c 
  * @author  MCD Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdbool.h>
#define MAX 100
/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
typedef struct {
	int significant;
	int exponent;
} ExponentialNumber;

ExponentialNumber to_exponential_number(char *number){
	ExponentialNumber result = {};
	bool counting = false;
	while (*number != '\0') {
		char current = *number;
		if (current == '.') {
			counting = true;   //zliczamy liczby po kropce
		}
		else {
			if (counting)
				result.exponent--;
			int current_digit = current - '0';
			result.significant = result.significant * 10 + current_digit;
		}

		number++;
	}
	return result;
}

/*char* to_string(ExponentialNumber number){
	char *buff = (char*)malloc(25);
	int number_length = count_digits(number.significant);
	for (int i = 0; i < number_length; i++){
		buff[number_length - i - 1] = number.significant %10 + '0';
	}

}*/

int count_digits(int number){
	if (number == 0){
		return 1;
	}
	int counter = 0;
	while (number != 0){
		number /= 10;
		counter++;
	}
	return counter;
}

int power (int number, int exponent){
	int result = 1;
	if (exponent == 0){
		return 1;
	}
	for (int i = 0; i < exponent; i++){
		result *= number;
	}
	return result;
}

ExponentialNumber add(ExponentialNumber first, ExponentialNumber second){
	if (first.exponent < second.exponent){
		second.significant *= power(10, second.exponent - first.exponent);
		second.exponent = first.exponent;
	}
	else if (first.exponent > second.exponent){
		first.significant *= power(10, first.exponent - second.exponent);
		first.exponent = second.exponent;
	}
	ExponentialNumber result = {first.significant + second.significant, first.exponent};
	return result;
}

ExponentialNumber substract(ExponentialNumber first, ExponentialNumber second){
	second.significant *= -1;
	return add(first, second);
}

ExponentialNumber multiply(ExponentialNumber first, ExponentialNumber second){
	ExponentialNumber result = {first.significant * second.significant, first.exponent + second.exponent};
	return result;
}

//mnożymy mantysę dzielnej tak, by była jak największa (9cyfrowa, bo INT_MAX = 2147483647 to liczba 10cyfrowa)

ExponentialNumber divide(ExponentialNumber first, ExponentialNumber second){
	int counter = count_digits(first.significant);
	if (counter < 9){
		first.significant *= power(10, 9-counter);
		first.exponent -= (9-counter);
	}
	ExponentialNumber result = {first.significant / second.significant, first.exponent - second.exponent};


	while (result.significant % 10 == 0){
			result.significant /= 10;
			result.exponent++;
	}
	return result;
}




int main(void)
{

  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user 
             can eventually implement his proper time base source (a general purpose 
             timer for example or other time source), keeping in mind that Time base 
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
             handled in milliseconds basis.
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the System clock to 180 MHz */
  //SystemClock_Config();


  /* Add your application code here
     */

  char floatnumber1[] = "1.23";
  char floatnumber2[] = "1.1";
  ExponentialNumber number1 = to_exponential_number(floatnumber1);
  ExponentialNumber number2 = to_exponential_number(floatnumber2);
  trace_printf( "%s = %de%d   %s = %de%d\n", floatnumber1, number1.significant, number1.exponent, floatnumber2, number2.significant,
		  number2.exponent);

  ExponentialNumber result_add = add(number1, number2);
  trace_printf("%de%d + %de%d = %de%d\n", number1.significant, number1.exponent,
  		  number2.significant, number2.exponent, result_add.significant, result_add.exponent);

  ExponentialNumber result_substract = substract(number1, number2);
  trace_printf("%de%d - %de%d = %de%d\n", number1.significant, number1.exponent,
		  number2.significant, number2.exponent, result_substract.significant, result_substract.exponent);

  ExponentialNumber result_multiply = multiply(number1, number2);
  trace_printf("%de%d * %de%d = %de%d\n", number1.significant, number1.exponent,
		  number2.significant, number2.exponent, result_multiply.significant, result_multiply.exponent);

  ExponentialNumber result_divide = divide(number1, number2);
  trace_printf("%de%d / %de%d = %de%d\n", number1.significant, number1.exponent,
		  number2.significant, number2.exponent,  result_divide.significant, result_divide.exponent);


/*
  ExponentialNumber test_number1 = {123, -2};
  ExponentialNumber test_number2 = {11, -1};

  ExponentialNumber result_add = add(test_number1, test_number2);
  trace_printf("%de%d + %de%d = %de%d\n", test_number1.significant, test_number1.exponent,
		  test_number2.significant, test_number2.exponent, result_add.significant, result_add.exponent);

  ExponentialNumber result_substract = substract(test_number1, test_number2);
  trace_printf("%de%d - %de%d = %de%d\n", test_number1.significant, test_number1.exponent,
		  test_number2.significant, test_number2.exponent, result_substract.significant, result_substract.exponent);

  ExponentialNumber result_multiply = multiply(test_number1, test_number2);
  trace_printf("%de%d * %de%d = %de%d\n", test_number1.significant, test_number1.exponent,
		  test_number2.significant, test_number2.exponent, result_multiply.significant, result_multiply.exponent);

  ExponentialNumber result_divide = divide(test_number1, test_number2);
  trace_printf("%de%d / %de%d = %de%d\n", test_number1.significant, test_number1.exponent,
		  test_number2.significant, test_number2.exponent,  result_divide.significant, result_divide.exponent);
		  */
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
