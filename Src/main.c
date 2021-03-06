/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "crc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mylcd.h"
#include "stdio.h"
#include "GUI.h" 
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
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

int fputc(int ch,FILE *fp)
{
	return HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,1000);
}

 

void delay_us(uint16_t us)
{
    uint16_t differ=0xffff-us-5;
    /*为防止因中断打断延时，造成计数错误.
     如从0xfffE开始延时1us,但由于中断打断
    （此时计数器仍在计数），本因计数至0xffff）
    便停止计数，但由于错过计数值，并重载arr值，
    导致实际延时(0xffff+1)us
    */

    HAL_TIM_Base_Start(&htim8);

    __HAL_TIM_SetCounter(&htim8,differ);

    while(differ<0xffff-5)
    {
        differ=__HAL_TIM_GetCounter(&htim8);
    }

    HAL_TIM_Base_Stop(&htim8);
}

void Test_Demo(void)
{   
     GUI_Init();
     /* 设置字体 */   
     GUI_SetFont(&GUI_Font8x16);
     /* 设置背景颜色 */   
     GUI_SetBkColor(GUI_BLUE);
     GUI_Clear();      
     /* 设置画笔的粗细以及颜色，只有矢量函数才能设置Size */
     GUI_SetPenSize(10);   
     GUI_SetColor(GUI_RED);
     GUI_DrawLine(80, 10, 240, 90);   
     GUI_DrawLine(80, 90, 240, 10);
     GUI_SetBkColor(GUI_BLACK);
     GUI_SetColor(GUI_WHITE);      
     /* 设置正常模式 */
     GUI_SetTextMode(GUI_TM_NORMAL);  
     GUI_DispStringHCenterAt("GUI_TM_NORMAL" , 160, 10);
     /* 翻转文本 */   
     GUI_SetTextMode(GUI_TM_REV);
     GUI_DispStringHCenterAt("GUI_TM_REV" , 160, 26);        
     /* 透明文本 */
     GUI_SetTextMode(GUI_TM_TRANS);   
     GUI_DispStringHCenterAt("GUI_TM_TRANS" , 160, 42);
     /* 异或文本 */   
     GUI_SetTextMode(GUI_TM_XOR);
     GUI_DispStringHCenterAt("GUI_TM_XOR" , 160, 58);   
     /* 设置文本模式 */
     GUI_SetTextMode(GUI_TM_TRANS | GUI_TM_REV);   
     GUI_DispStringHCenterAt("GUI_TM_TRANS | GUI_TM_REV", 160, 74);
		 while(1)
		{ 
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin); 
			rt_thread_mdelay(500); 
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
	uint8_t lcd_id[18];
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  //HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  //SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  //MX_GPIO_Init();
  //MX_CRC_Init();
  //MX_FSMC_Init();
  //MX_USART1_UART_Init();
  //MX_TIM8_Init();
  /* USER CODE BEGIN 2 */ 
	LCD_Init();           													//初始化LCD FSMC接口
	
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);	//将LCD ID打印到lcd_id数组。
	//STemWin 移植
	GUI_Init(); 
	GUI_Clear();
	GUI_Exec(); //解决GUI_Delay失效问题！
	GUI_SetBkColor(GUI_BLUE);
	
	GUI_SetFont(GUI_FONT_24_1);
	GUI_SetColor(GUI_GREEN);
	GUI_DrawLine(10,20,30,40);
	GUI_DispString("hello world"); 
	GUI_DispStringAt("hello world",50,50);  
	GUI_DispStringAt(lcd_id,50,100);
	

	//Test_Demo();	//STemWin  测试代码
	 
	//原始的TFT驱动
	//POINT_COLOR=RED;     					//画笔颜色：红色
	//sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。
	//LCD_Clear(WHITE); 
	//POINT_COLOR=RED;	  
	// 
	//LCD_ShowString(30,40,210,24,24,"ELITE STM32 ^_^");	
	//LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
	//LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	//LCD_ShowString(30,110,200,16,16,lcd_id);		//显示LCD ID	      					 
	//LCD_ShowString(30,130,200,12,12,"2019/9/27");	 
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */ 
		 
		HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
		//修复出现Emwin的字符串输出时串口驱动不正常的现象，进行重新初始化串口。
		HAL_UART_DeInit(&huart1);
		MX_USART1_UART_Init();
		
		rt_kprintf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		rt_kprintf("HELLO RT-THREAD Nano!\n");
		rt_kprintf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		
		
		GUI_Exec(); 
    rt_thread_mdelay(400);

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
