/********************************************************************************/
/* Module Name  : Systick.c							*/
/* Author       : Hossam						        */
/* Purpose      : Use SysTick Timer Services					*/
/********************************************************************************/

#include "Systick.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

void (*SCHEDULER)(void);

uint8_t Systick_Flag = 0;

/********************************************************************************/
/* Function Name: void SysTick_Init (void)					*/
/* Inputs       : None		                                                */
/* Outputs      : None				 			        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Initialize SysTick Timer	 				*/
/********************************************************************************/

void SysTick_Init (void)
{
  SysTickDisable();
  
  SysTickPeriodSet(SysTick_Load);
  
  SysTickIntEnable();
}

/********************************************************************************/
/* Function Name: void SET_Scheduler (void (*Function)(void))			*/
/* Inputs       : void (*Function)(void)		                        */
/* Outputs      : None				 			        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Pass the Scheduler Address to the SysTick Driver	 	*/
/********************************************************************************/

void SET_Scheduler (void (*Function)(void))
{
  SCHEDULER = Function;
}
/********************************************************************************/
/* Function Name: void SysTickHandler (void)					*/
/* Inputs       : void		                                                */
/* Outputs      : None				 			        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Handler Function for SysTick Timer	 			*/
/********************************************************************************/

void SysTickHandler (void)
{
  SCHEDULER();
}

/********************************************************************************/
/* Function Name: uint8_t Get_SysTick_Flag (void)				*/
/* Inputs       : None		                                                */
/* Outputs      : uint8_t Systick_Flag				 		*/
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Return the Value of the SysTick Flag	 			*/
/********************************************************************************/

uint8_t Get_SysTick_Flag (void)
{
  return Systick_Flag;
}

/********************************************************************************/
/* Function Name: void systickHandler (void)					*/
/* Inputs       : uint8 Flag		                                        */
/* Outputs      : None				 			        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Reset the Value of the SysTick Flag	 			*/
/********************************************************************************/

void Set_SysTick_Flag (uint8 Flag)
{
  Systick_Flag = false;
}