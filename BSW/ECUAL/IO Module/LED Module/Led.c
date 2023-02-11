/********************************************************************************/
/* Module Name  : Led.c							        */
/* Author       : Hossam						        */
/* Purpose      : LED Module ECU Abstraction                                    */
/********************************************************************************/

#include "Led.h"

#if (ENABLE_LED_FUNCTIONALITIES == YES)

/********************************************************************************/
/* Function Name: uint8 Read_LED (uint8 ChannelId)			        */
/* Inputs       : uint8 ChannelId		                                */
/* Outputs      : uint8 STD_level				 		*/
/* Reentrancy   : Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Reads & returns LED level (HIGH/LOW)	 		        */
/********************************************************************************/

uint8 Read_LED (uint8 ChannelId)
{
  return Dio_ReadChannel(ChannelId);
}

/********************************************************************************/
/* Function Name: void LED_On (uint8 ChannelId)				        */
/* Inputs       : uint8 ChannelId					        */
/* Outputs      : void				 			        */
/* Reentrancy   : Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Sets LED to HIGH	 				        */
/********************************************************************************/

void LED_On (uint8 ChannelId)
{
  uint8 Level = STD_HIGH;
    
  Dio_WriteChannel(ChannelId, Level);
}

/********************************************************************************/
/* Function Name: void LED_Off (uint8 ChannelId)				*/
/* Inputs       : uint8 ChannelId					        */
/* Outputs      : void				 			        */
/* Reentrancy   : Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Sets LED to LOW	 				        */
/********************************************************************************/

void LED_Off (uint8 ChannelId)
{
  uint8 Level = STD_LOW;
    
  Dio_WriteChannel(ChannelId, Level);
}

/********************************************************************************/
/* Function Name: void Toggle_LED (uint8 ChannelId)				*/
/* Inputs       : uint8 ChannelId					        */
/* Outputs      : void				 			        */
/* Reentrancy   : Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Toggles LED level	 				        */
/********************************************************************************/

void Toggle_LED (uint8 ChannelId)
{
  DioFlipChannel(ChannelId);
}

#endif