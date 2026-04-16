/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
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
#include "axiocrypto.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* USER CODE BEGIN VTOR_TABLE */

/* Non-secure Vector table to jump to (internal Flash Bank2 here)             */
/* Caution: address must correspond to non-secure internal Flash where is     */
/*          mapped in the non-secure vector table                             */
#define VTOR_TABLE_NS_START_ADDR  0x08100000UL

/* USER CODE END VTOR_TABLE*/

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

RNG_HandleTypeDef hrng;

/* USER CODE BEGIN PV */
UART_HandleTypeDef huart3;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void NonSecure_Init(void);
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_GTZC_S_Init(void);
static void MX_ICACHE_Init(void);
static void MX_RNG_Init(void);
/* USER CODE BEGIN PFP */
static void MX_USART3_UART_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif

PUTCHAR_PROTOTYPE {
	HAL_UART_Transmit(&huart3, (uint8_t*) &ch, 1, 0xFFFF);
	return ch;
}

GETCHAR_PROTOTYPE {
	uint8_t ch = 0;
	HAL_UART_Receive(&huart3, &ch, 1, HAL_MAX_DELAY);
	return ch;
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();
	/* GTZC initialisation */
	MX_GTZC_S_Init();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_ICACHE_Init();
	MX_RNG_Init();
	MX_USART3_UART_Init();
	/* USER CODE BEGIN 2 */

	printf("\n\nHello Secure World\n");

	void example(void);
	example();

	/* USER CODE END 2 */

	/*************** Setup and jump to non-secure *******************************/

	NonSecure_Init();

	/* Non-secure software does not return, this code is not executed */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief  Non-secure call function
 *         This function is responsible for Non-secure initialization and switch
 *         to non-secure state
 * @retval None
 */
static void NonSecure_Init(void) {
	funcptr_NS NonSecure_ResetHandler;

	SCB_NS->VTOR = VTOR_TABLE_NS_START_ADDR;

	/* Set non-secure main stack (MSP_NS) */
	__TZ_set_MSP_NS((*(uint32_t*) VTOR_TABLE_NS_START_ADDR));

	/* Get non-secure reset handler */
	NonSecure_ResetHandler =
			(funcptr_NS) (*((uint32_t*) ((VTOR_TABLE_NS_START_ADDR) + 4U)));

	/* Start non-secure state software application */
	NonSecure_ResetHandler();
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

	while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {
	}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48
			| RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_DIGITAL;
	RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 250;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_1;
	RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
	RCC_OscInitStruct.PLL.PLLFRACN = 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		Error_Handler();
	}

	/** Configure the programming delay
	 */
	__HAL_FLASH_SET_PROGRAM_DELAY(FLASH_PROGRAMMING_DELAY_2);
}

/**
 * @brief GTZC_S Initialization Function
 * @param None
 * @retval None
 */
static void MX_GTZC_S_Init(void) {

	/* USER CODE BEGIN GTZC_S_Init 0 */

	/* USER CODE END GTZC_S_Init 0 */

	MPCBB_ConfigTypeDef MPCBB_Area_Desc = { 0 };

	/* USER CODE BEGIN GTZC_S_Init 1 */

	if (HAL_GTZC_TZSC_ConfigPeriphAttributes(GTZC_PERIPH_USART3,
			GTZC_TZSC_PERIPH_NSEC | GTZC_TZSC_PERIPH_NPRIV) != HAL_OK) {
		Error_Handler();
	}

	/* USER CODE END GTZC_S_Init 1 */
	if (HAL_GTZC_TZSC_ConfigPeriphAttributes(GTZC_PERIPH_USB,
			GTZC_TZSC_PERIPH_SEC | GTZC_TZSC_PERIPH_NPRIV) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_GTZC_TZSC_ConfigPeriphAttributes(GTZC_PERIPH_LPUART1,
			GTZC_TZSC_PERIPH_SEC | GTZC_TZSC_PERIPH_NPRIV) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_GTZC_TZSC_ConfigPeriphAttributes(GTZC_PERIPH_I2C3,
			GTZC_TZSC_PERIPH_SEC | GTZC_TZSC_PERIPH_NPRIV) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_GTZC_TZSC_ConfigPeriphAttributes(GTZC_PERIPH_ETHERNET,
			GTZC_TZSC_PERIPH_SEC | GTZC_TZSC_PERIPH_NPRIV) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_GTZC_TZSC_ConfigPeriphAttributes(GTZC_PERIPH_RNG,
			GTZC_TZSC_PERIPH_SEC | GTZC_TZSC_PERIPH_NPRIV) != HAL_OK) {
		Error_Handler();
	}
	MPCBB_Area_Desc.SecureRWIllegalMode = GTZC_MPCBB_SRWILADIS_ENABLE;
	MPCBB_Area_Desc.InvertSecureState = GTZC_MPCBB_INVSECSTATE_NOT_INVERTED;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[0] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[1] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[2] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[3] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[4] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[5] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[6] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[7] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[8] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[9] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[10] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[11] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[12] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[13] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[14] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[15] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[16] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[17] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[18] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_SecConfig_array[19] = 0x00000000;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[0] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[1] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[2] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[3] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[4] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[5] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[6] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[7] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[8] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[9] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[10] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[11] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[12] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[13] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[14] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[15] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[16] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[17] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[18] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_PrivConfig_array[19] = 0xFFFFFFFF;
	MPCBB_Area_Desc.AttributeConfig.MPCBB_LockConfig_array[0] = 0x00000000;
	if (HAL_GTZC_MPCBB_ConfigMem(SRAM3_BASE, &MPCBB_Area_Desc) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN GTZC_S_Init 2 */

	/* USER CODE END GTZC_S_Init 2 */

}

/**
 * @brief ICACHE Initialization Function
 * @param None
 * @retval None
 */
static void MX_ICACHE_Init(void) {

	/* USER CODE BEGIN ICACHE_Init 0 */

	/* USER CODE END ICACHE_Init 0 */

	/* USER CODE BEGIN ICACHE_Init 1 */

	/* USER CODE END ICACHE_Init 1 */
	/* USER CODE BEGIN ICACHE_Init 2 */

	/* USER CODE END ICACHE_Init 2 */

}

/**
 * @brief RNG Initialization Function
 * @param None
 * @retval None
 */
static void MX_RNG_Init(void) {

	/* USER CODE BEGIN RNG_Init 0 */

	/* USER CODE END RNG_Init 0 */

	/* USER CODE BEGIN RNG_Init 1 */

	/* USER CODE END RNG_Init 1 */
	hrng.Instance = RNG;
	hrng.Init.ClockErrorDetection = RNG_CED_ENABLE;
	if (HAL_RNG_Init(&hrng) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN RNG_Init 2 */

	/* USER CODE END RNG_Init 2 */

}

/**
 * @brief USART3 Initialization Function (Secure world usage)
 * @param None
 * @retval None
 */
static void MX_USART3_UART_Init(void) {
	huart3.Instance = USART3; /* S alias(0x50004800): Secure code must use S alias even on NSEC peripheral */
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart3) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/*Configure GPIO pins : RMII_MDC_Pin RMII_RXD0_Pin RMII_RXD1_Pin */
	GPIO_InitStruct.Pin = RMII_MDC_Pin | RMII_RXD0_Pin | RMII_RXD1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : RMII_REF_CLK_Pin RMII_MDIO_Pin RMII_CRS_DV_Pin */
	GPIO_InitStruct.Pin = RMII_REF_CLK_Pin | RMII_MDIO_Pin | RMII_CRS_DV_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : RMII_TXD1_Pin */
	GPIO_InitStruct.Pin = RMII_TXD1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(RMII_TXD1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : USB_FS_N_Pin USB_FS_P_Pin */
	GPIO_InitStruct.Pin = USB_FS_N_Pin | USB_FS_P_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF10_USB;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : RMII_TXT_EN_Pin RMI_TXD0_Pin */
	GPIO_InitStruct.Pin = RMII_TXT_EN_Pin | RMI_TXD0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/*Configure GPIO pins : ARD_D1_TX_Pin ARD_D0_RX_Pin */
	GPIO_InitStruct.Pin = ARD_D1_TX_Pin | ARD_D0_RX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF8_LPUART1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*IO attributes management functions */
	HAL_GPIO_ConfigPinAttributes(GPIOD, T_VCP_TX_Pin | T_VCP_RX_Pin,
			GPIO_PIN_NSEC);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
