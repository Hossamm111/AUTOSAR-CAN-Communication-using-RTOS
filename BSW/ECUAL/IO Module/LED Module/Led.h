/********************************************************************************/
/* Module Name  : Led.h						                */
/* Author       : Hossam							*/
/* Purpose      : Header file for LED Module		 			*/
/********************************************************************************/

#ifndef __Led_H__
#define __Led_H__

/*******************************************************************************
 *                              File Includes                                  *
 *******************************************************************************/

#include "../../../MCAL/DIO Driver/Dio.h"
#include "Led_Cfg.h"

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

extern uint8 Read_LED (uint8 ChannelId);

extern void LED_On    (uint8 ChannelId);

extern void LED_Off   (uint8 ChannelId);

extern void Toggle_LED(uint8 ChannelId);

#endif /* __Led_H__ */