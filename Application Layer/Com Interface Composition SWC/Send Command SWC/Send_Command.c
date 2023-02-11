/********************************************************************************/
/* Module Name  : Send_Command.c					        */
/* Author       : Hossam						        */
/* Purpose      : Send a Command				                */
/********************************************************************************/

#include "../../Application SWC/APP.h"

/********************************************************************************/
/* Function Name: void Send_Command (void)			                */
/* Inputs       : uint8 state		                                        */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Send a Command	                                        */
/********************************************************************************/

void Send_Command (uint8 state)
{
/*
 * Send a Command via the CAN Bus
 */
  Send_Message (state);
}
