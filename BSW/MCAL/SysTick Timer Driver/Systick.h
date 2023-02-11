/********************************************************************************/
/* Module Name  : Systick.h							*/
/* Author       : Hossam						        */
/* Purpose      : Header file for SysTick Timer Driver			        */
/********************************************************************************/

#ifndef __Systick_H__
#define __Systick_H__

/*******************************************************************************
 *                              File Includes                                  *
 *******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/systick.h"
#include "../../../Libraries/std_types.h"
#include "Systick_Cfg.h"

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

extern void SysTick_Init        (void);

extern void SET_Scheduler       (void (*)(void));

extern void SysTickHandler      (void);

extern uint8_t Get_SysTick_Flag (void);

extern void Set_SysTick_Flag    (uint8);

#endif /* __Systick_H__ */