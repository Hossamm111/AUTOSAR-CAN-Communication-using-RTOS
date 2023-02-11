/********************************************************************************/
/* Module Name  : Timer.c							*/
/* Author       : Hossam						        */
/* Purpose      : Timer Module ECU Abstraction			                */
/********************************************************************************/

#include "Timer.h"

uint8 Timer_Flag = 0;

void (*SchedulerT)(void);

/********************************************************************************/
/* Function Name: void Timer_Init (void)				        */
/* Inputs       : None		                                                */
/* Outputs      : None				 			        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Initialize Timer Module	 				*/
/********************************************************************************/

void Timer_Init (void)
{
  #if (ENABLE_TIMERS == YES)
  
  #if (SYSTICK_TIMER == YES)
  
  SysTick_Init();
  
  #endif
  
  #if (GPT == YES)
  
  GPT_Init();
  
  #endif
  
  #endif
}

/********************************************************************************/
/* Function Name: void Set_Scheduler (void (*Function)(void))			*/
/* Inputs       : void (*Function)(void)		                        */
/* Outputs      : None				 			        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Pass the Scheduler Address to the Timer Module	 	*/
/********************************************************************************/

void Set_Scheduler (void (*Function)(void))
{
  SchedulerT = Function;
  
  SET_Scheduler(SchedulerT);
}

/********************************************************************************/
/* Function Name: void Timer_Enable (void)				        */
/* Inputs       : None		                                                */
/* Outputs      : None				 			        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Enable the SysTick Timer	 				*/
/********************************************************************************/

void Timer_Enable (void)
{
  SysTickEnable();
}

/********************************************************************************/
/* Function Name: uint8_t Get_Timer_Flag (void)				        */
/* Inputs       : None		                                                */
/* Outputs      : uint8_t Systick_Flag  				 	*/
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Initialize Timer Module	 				*/
/********************************************************************************/

uint8_t Get_Timer_Flag (void)
{
  return Get_SysTick_Flag ();
}

/********************************************************************************/
/* Function Name: uint8_t Get_Timer_Flag (void)				        */
/* Inputs       : uint8 Flag		                                        */
/* Outputs      : None				 			        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Set the Timer Flag	 				        */
/********************************************************************************/

void Set_Timer_Flag (uint8 Flag)
{
  Set_SysTick_Flag (Flag);
}