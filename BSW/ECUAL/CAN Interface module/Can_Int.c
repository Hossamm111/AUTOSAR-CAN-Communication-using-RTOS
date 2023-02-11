/********************************************************************************/
/* Module Name  : Can_Int.c							*/
/* Author       : Hossam						        */
/* Purpose      : CAN Interface Module Abstraction			        */
/********************************************************************************/

#include "Can_Int.h"

uint8* CAN_Msg;

/********************************************************************************/
/* Function Name: void CAN_Interface_Init (void)			        */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Initialize the CAN Interface	                                */
/********************************************************************************/

void CAN_Interface_Init (void)
{
  #if (CAN_ENABLE == YES)
  
  CAN_Init();
  
  CAN_TXInit();
  
  CAN_RXInit();

  #endif
}

/********************************************************************************/
/* Function Name: void CAN_Send_Msg (void)			                */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Send a Message	                                        */
/********************************************************************************/

void Send_Message (uint8 State)
{
  CAN_Send(State);
}

/********************************************************************************/
/* Function Name: void CAN_Receive_Msg (void)			                */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Receive a Message     	                                */
/********************************************************************************/

void Receive_Message (void)
{
  CAN_Receive();
}

/********************************************************************************/
/* Function Name: void Received_Msg_Ptr (uint8* CAN_Msg_R)			*/
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Initialize Message Pointer	                                */
/********************************************************************************/

void Received_Msg_Ptr (uint8* CAN_Msg_R)
{
  CAN_Msg = CAN_Msg_R;
  
  CAN_Msg_Ptr(CAN_Msg);
}