/********************************************************************************/
/* Module Name  : Button.c							*/
/* Author       : Hossam						        */
/* Purpose      : Button Module ECU Abstraction				        */
/********************************************************************************/

#include "Button.h"

#if (ENABLE_BUTTON_FUNCTIONALITIES == YES)

/********************************************************************************/
/* Function Name: uint8 Read_Button (uint8 ChannelId)			        */
/* Inputs       : uint8 ChannelId		                                */
/* Outputs      : uint8 STD_level				 	        */
/* Reentrancy   : Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Reads & returns the level of the buttons (HIGH/LOW)	        */
/********************************************************************************/

uint8 Read_Button (uint8 ChannelId)
{
  return Dio_ReadChannel(ChannelId);
}

#endif