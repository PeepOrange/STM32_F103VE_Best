/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                         Evaluation Board
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : EHS
*                 DC
*********************************************************************************************************
*/

#ifndef  INCLUDES_PRESENT
#define  INCLUDES_PRESENT

//#ifndef SOFTRESET
//#define SOFTRESET
//#endif
#define CALADD  510*4096

/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/

#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include <string.h>  
#include  <math.h>


/*
*********************************************************************************************************
*                                              LIBRARIES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_ascii.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <lib_str.h>


/*
*********************************************************************************************************
*                                              APP / BSP
*********************************************************************************************************
*/
#include  "common.h"
#include  "bsp.h"
#include  "bsp_led.h"  
#include  "key.h"
#include  "beep.h" 
#include  "TouchPad.h"
#include  "fatfs_flash_spi.h"
#include  "bsp_usart1.h"
#include  "bsp_ili9341_lcd.h"
#include  "bsp_xpt2046_lcd.h"
#include  "bsp_breathing.h" 
#include  "bsp_i2c_ee.h"
#include  "bsp_i2c_gpio_ee.h"
#include  "bsp_rtc.h"
#include  "bsp_ov7725.h"
#include  "bsp_usart2.h"
#include  "sim900a.h"

#include  "ff.h"
#include  "app_cfg.h"
#include  "MyApp.h"
/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/

#include  <os.h>	
#include "os_type.h"
#include "os_cfg_app.h"
/*
*********************************************************************************************************
*                                                 ST
*********************************************************************************************************
*/

#include  <stm32f10x.h>

/*
*********************************************************************************************************
*                                               emWin
*********************************************************************************************************
*/
#include "GUI.H"
#include "DIALOG.h"
#include "MESSAGEBOX.h"

/*
*********************************************************************************************************
*                                              FUNCTION
*********************************************************************************************************
*/
#define bsp_DelayMS(ms)		bsp_DelayUS(1000*ms)
void Touch_MainTask(void);
void bsp_DelayUS(uint32_t _ulDelayTime);
void Soft_Reset(void);
/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/


#endif

