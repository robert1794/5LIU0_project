/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include  <errno.h>
#include  <sys/unistd.h> // STDOUT_FILENO, STDERR_FILENO
#include <stdint.h>
#include <stdbool.h>

#include "dsp_algorithms.h"
#include "adc_capture.h"

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
const char trigger_type_names[][20] = {
		"trigger_off",
		"trigger_rising",
		"trigger_falling",
		"trigger_any"
};


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/// \brief write for printf
/// Source: https://electronics.stackexchange.com/questions/206113/how-do-i-use-the-printf-function-on-stm32
/// Uses UART3 to transmit data
int _write(int file, char *data, int len)
{
	if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
	{
			errno = EBADF;
			return -1;
	}

	// arbitrary timeout 1000
	HAL_StatusTypeDef status = HAL_UART_Transmit(&huart3, (uint8_t*)data, len, 1000);

	// return # of bytes written - as best we can tell
	return (status == HAL_OK ? len : 0);
}


/// \brief clears the terminal by writing a lot of empty lines to it
/// \author R. Paauw
void clear_terminal()
{
	for (int i = 0; i < 80; i++)
	{
		printf("\r\n");
	}
}

/// \brief prints the menu options that are available on the system
/// \author R. Paauw
void print_menu_options()
{
	printf("(1) Capture microphones\r\n");
	printf("(2) Calculate time delay\r\n");
	printf("(3) Calibration mode\r\n");
	printf("(4) Print ADC buffers\r\n");
	printf("(R) Toggle continuous running mode\r\n");
	printf("(T) Select trigger mode\r\n");
	printf("(-) Decrease trigger level\r\n");
	printf("(+) Increase trigger level\r\n");
	printf("(C) Clear screen\r\n");
	printf("(H) Print menu options\r\n");
}



/// \brief Prints text at startup
/// \author R. Paauw
void print_startup_text()
{
	char startup_string[] = "| 5LIU0 project - TDOA angle estimation |";
	char lines[sizeof(startup_string)];
	for (int i = 1; i < (sizeof(lines) - 1); i++)
	{
		lines[i] = '=';
	}
	lines[0] = '+';
	lines[sizeof(lines) - 1] = '+';

	clear_terminal();
	printf("%s\r\n", lines);
	printf("%s\r\n", startup_string);
	printf("%s\r\n\r\n", lines);

	print_menu_options();

	printf("\r\n> ");
}


/// \brief prints the values of the ADC in decimal csv format with ';' as seperator
/// \param[in] buf_a pointer to first buffer
/// \param[in] buf_b pointer to second buffer
/// \param[in] nr_of_samples number of samples to print
void print_adc_buffers(int16_t *buf_a, int16_t *buf_b, uint32_t nr_of_samples)
{
	printf("\r\nIndex;Buffer A;BufferB\r\n");

	for (int i = 0; i < nr_of_samples; i++)
	{
		printf("%d;%d;%d\r\n", i, (int)buf_a[i], (int)buf_b[i]);
	}
}

/// \brief Process one character from the terminal
/// \param[in] rx_char The character received from the terminal
/// \author R. Paauw
void process_uart_command(uint8_t rx_char)
{
	int16_t trigger_level_mv;

	switch(rx_char)
	{
	case '1':
		printf("%c\r\n", rx_char);
		printf("Capturing microphones...\r\n");
		printf("FAIL: Not implemented\r\n");
		// ToDo Capture microphones here

		for (int i = 0; i < adc_buffer_size; i++)
		{
			adc_buffer_a[i] = 0;
			adc_buffer_a[i] = 0;
		}

		HAL_ADC_Start(&hadc1);
		HAL_TIM_Base_Start(&htim1);

		uint32_t starttime = HAL_GetTick();

		while((HAL_GetTick() - starttime) < 1000) ;

		HAL_TIM_Base_Stop(&htim1);
		HAL_ADC_Stop(&hadc1);

		printf("\r\n> ");
		break;
	case '2':
		printf("%c\r\n", rx_char);
		printf("Calculating time delay...\r\n");
		printf("FAIL: Not implemented\r\n");
		// ToDo Calculate time delay here

		printf("\r\n> ");
		break;
	case '3':
		printf("%c\r\n", rx_char);
		printf("Entering calibration mode...\r\n");
		printf("FAIL: Not implemented\r\n");
		// ToDo Implement calibration mode

		printf("\r\n> ");
		break;
	case '4':
		printf("%c\r\n", rx_char);
		printf("Displaying ADC buffers...\r\n");

		if (get_adc_index() == adc_buffer_size)
		{
			print_adc_buffers(adc_buffer_a, adc_buffer_b, adc_buffer_size);
		} else {
			printf("FAIL: ADC buffers not ready\r\n");
		}

		printf("\r\n> ");
		break;
	case 'R':
	case 'r':
		printf("%c\r\n", rx_char);
		printf("Entering continuous running mode...\r\n");
		printf("FAIL: Not implemented\r\n");
		// ToDo Implement continuous running mode here

		printf("\r\n> ");
		break;
	case 'T':
	case 't':
		printf("%c\r\n", rx_char);
		trigger_type_t trigger_mode = get_trigger_mode() + 1;
		if (trigger_mode >= nr_of_trigger_values)
			trigger_mode = trigger_off;
		set_trigger_mode(trigger_mode);
		printf("Trigger type set to: [%s]\r\n", trigger_type_names[(int)trigger_mode]);
		printf("\r\n> ");
		break;
	case '-':
		printf("%c\r\n", rx_char);
		trigger_level_mv = get_trigger_level();
		if ((trigger_level_mv - trigger_stepsize) >= trigger_min)
			set_trigger_level(trigger_level_mv - trigger_stepsize);
		printf("Decreased trigger level to %dmV\r\n", trigger_level_mv);
		printf("\r\n> ");
		break;
	case '+':
		printf("%c\r\n", rx_char);
		trigger_level_mv = get_trigger_level();
		if ((trigger_level_mv + trigger_stepsize) <= (trigger_max))
			set_trigger_level(trigger_level_mv + trigger_stepsize);
		printf("Increased trigger level to %dmV\r\n", trigger_level_mv);
		printf("\r\n> ");
		break;
	case 'C':
	case 'c':
		clear_terminal();
		printf("> ");
		break;
	case 'H':
	case 'h':
		printf("%c\r\n\r\n", rx_char);
		print_menu_options();
		printf("\r\n> ");
		break;
	default:
		if ((rx_char >= ' ') && (rx_char <= '~'))
			printf("Unknown command <%c> use (H) to show supported commands\r\n\r\n> ", rx_char);
		break;
	 }
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2S3_Init();
  MX_SPI1_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  setvbuf(stdout, NULL, _IONBF, 0); // Set stdout (and thus printf) to be unbuffered.

  print_startup_text();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	uint8_t rx_char;

	HAL_StatusTypeDef status = HAL_UART_Receive(&huart3, &rx_char, 1, 1);

	if (status == HAL_OK)
	{
		process_uart_command(rx_char);
	}

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
