/********************************************************************************/
/* Module Name  : Can_Int.h							*/
/* Author       : Hossam						        */
/* Purpose      : Header File for CAN Interface Module				*/
/********************************************************************************/

#ifndef __Can_Int_H__
#define __Can_Int_H__

/*******************************************************************************
 *                              File Includes                                  *
 *******************************************************************************/

#include "../../MCAL/CAN Driver/can.h"
#include "Can_Int_Cfg.h"

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

extern void CAN_Interface_Init (void);

extern void Send_Message (uint8);

extern void Receive_Message (void);

extern void Received_Msg_Ptr (uint8* CAN_Msg_R);

#endif /* __Can_Int_H__ */