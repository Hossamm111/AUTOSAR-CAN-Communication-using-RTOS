/********************************************************************************/
/* Module Name  : Timer.h						        */
/* Author       : Hossam							*/
/* Purpose      : Header file for Timer Module		 			*/
/********************************************************************************/

#ifndef __Timer_H__
#define __Timer_H__

/*******************************************************************************
 *                              File Includes                                  *
 *******************************************************************************/

#include "../../MCAL/SysTick Timer Driver/Systick.h"
#include "../../MCAL/GPT Driver/GPT.h"
#include "Timer_Cfg.h"

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

extern void Timer_Init          (void);

extern void Set_Scheduler       (void (*)(void));

extern void Timer_Enable        (void);

extern uint8_t Get_Timer_Flag   (void);

extern void Set_Timer_Flag      (uint8);

#endif /* __Timer_H__ */