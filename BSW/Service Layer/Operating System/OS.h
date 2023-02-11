/********************************************************************************/
/* Module Name  : OS.h							        */
/* Author       : Hossam						        */
/* Purpose      : Header File for Operating System			        */
/********************************************************************************/

#ifndef __OS_H__
#define __OS_H__

/*******************************************************************************
 *                              File Includes                                  *
 *******************************************************************************/

#include <stdio.h>
#include "../../../Libraries/Std_Types.h"
#include "../../ECUAL/IO Module/Button Module/Button.h"
#include "../../ECUAL/IO Module/LED Module/Led.h"
#include "../../ECUAL/CAN Interface Module/can_int.h"
#include "../../ECUAL/Timer Module/Timer.h"
#include "../../MCAL/Port Driver/Port.h"
#include "OS_Cfg.h"

/*******************************************************************************
 *                            Function Prototypes                              *
 *******************************************************************************/
   
extern void Scheduler_Start             (void);

extern void Scheduler                   (void);

extern void Create_Task1                (void (*)(void),uint16);

extern void Create_Task2                (void (*)(void),uint16 );

#endif /* __OS_H__ */