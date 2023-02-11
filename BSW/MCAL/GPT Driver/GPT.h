/********************************************************************************/
/* Module Name  : GPT.h							        */
/* Author       : Hossam						        */
/* Purpose      : Header file for GPT Driver			                */
/********************************************************************************/

#ifndef __GPT_H__
#define __GPT_H__

/*******************************************************************************
 *                              File Includes                                  *
 *******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "../../../Libraries/std_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "GPT_Cfg.h"

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

extern void GPT_Init (void);

extern void Timer0_Handler (void);

extern void Timer1_Handler (void);

#endif /* __GPT_H__ */