/********************************************************************************/
/* Module Name  : Can.h							        */
/* Author       : Hossam						        */
/* Purpose      : Header File for CAN Driver					*/
/********************************************************************************/

#ifndef __CAN_H__
#define __CAN_H__

/*******************************************************************************
 *                              File Includes                                  *
 *******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "../../../Libraries/std_types.h"
#include "../../../Libraries/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/can.h"
#include "driverlib/interrupt.h"
#include "inc/hw_memmap.h"
#include "Can_Cfg.h"

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

extern void CAN_Msg_Ptr (uint8*);

extern void CAN_Init (void);

extern void CAN_TXInit (void);

extern void CAN_RXInit (void);

extern void CAN_Send (uint8);

extern uint8 CAN_Receive (void);

extern void CAN0_IntHandler (void);

#endif /* __CAN_H__ */