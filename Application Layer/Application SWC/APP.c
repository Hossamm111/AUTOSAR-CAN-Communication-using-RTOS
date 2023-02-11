/********************************************************************************/
/* Module Name  : APP.c							        */
/* Author       : Hossam						        */
/* Purpose      : Initialize, Configure & Start the Application			*/
/********************************************************************************/

#include "APP.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/* Common Variables */

uint32 Elapsed_Idle_Time = RESET;

#ifdef MASTER

/* Master Variables */

volatile bool SW1, SW2;

uint8 State;

#else

/* Slave Variables */

uint8 State_Counter = RESET;
  
uint8 Received_Msg;

uint8 *Received_Msg_Address;

#endif

/********************************************************************************/
/* Function Name: void APP_INIT (void)			                        */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Initialize the Application	                                */
/********************************************************************************/

void APP_INIT (void)
{
/*
 * Initialize Port Driver
 */
  Port_Init(&Port_Configuration);
/*
 * Initialize Timer Stack
 */
  Timer_Init();
/*
 * Initialize CAN Interface Stack
 */
  CAN_Interface_Init();
}

/********************************************************************************/
/* Function Name: void APP_START (void)			                        */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Start the Application	                                        */
/********************************************************************************/

void APP_START (void)
{
/*
 * Initialize the Application
 */
  APP_INIT();
  
/*
 * Switch on the white LED
 */
  LED_Mode(WHITE);

/*
 * If the Master Mode is Selected, Create the Two Master Tasks & Assign their Periodicities
 */
#ifdef MASTER
  
  Create_Task1 (Master_CheckState, Ten_MS);
  Create_Task2 (Master_SendState, Half_Second);
  
/*
 * If the Slave Mode is Selected, Create the Two Slave Tasks & Assign their Periodicities
 */
#else
  
  Received_Msg_Address = &Received_Msg;
  Received_Msg_Ptr(Received_Msg_Address);
  
  Create_Task1 (Slave_CheckState, Ten_MS);
  Create_Task2 (Slave_SwitchState, One_Second);
  
#endif

/*
 * Start the Scheduler & the RTOS
 */
  Scheduler_Start();
  
  while(true);
}

/*
 * If the Master Mode is Selected, Make the Master Tasks Visible to the Preprocessor
 */
#ifdef MASTER

/********************************************************************************/
/* Function Name: void Master_CheckState (void)			                */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Check Master State	                                        */
/********************************************************************************/

void Master_CheckState (void)
{
/*
 * Check Which Buttons are Pressed
 */
  SW1 = Read_Button(Button1);
  SW2 = Read_Button(Button2);
  
  if (SW1 == STD_LOW && SW2 == STD_HIGH && Elapsed_Idle_Time <= Five_Seconds)
  {
    Elapsed_Idle_Time = RESET;
    
    State = CLOCKWISE;
    
    LED_Mode(VIOLET);
    
    while (Read_Button(Button1) == STD_LOW && Read_Button(Button2) == STD_HIGH);
  }
  
  else if (SW1 == STD_HIGH && SW2 == STD_LOW && Elapsed_Idle_Time <= Five_Seconds)
  {
    Elapsed_Idle_Time = RESET;
    
    State = COUNTERCLOCKWISE;
    
    LED_Mode(YELLOW);
    
    while (Read_Button(Button1) == STD_HIGH && Read_Button(Button2) == STD_LOW);
  }
  
  else if (SW1 == STD_LOW && SW2 == STD_LOW && Elapsed_Idle_Time <= Five_Seconds)
  {
    Elapsed_Idle_Time = RESET;
    
    State = BOTH_PRESSED;
    
    LED_Mode(RED);
    
    while (Read_Button(Button1) == STD_LOW || Read_Button(Button2) == STD_LOW);
  }
  
  else if (SW1 == STD_HIGH && SW2 == STD_HIGH && Elapsed_Idle_Time <= Five_Seconds)
  {
    Elapsed_Idle_Time++;
  }
  
  else if (Elapsed_Idle_Time > Five_Seconds)
  {
    Elapsed_Idle_Time   = RESET;
    
    LED_Mode(WHITE);
    
    Send_Command(IDLE);
  }
  else
  {
    /* do nothing */
  }
}

/********************************************************************************/
/* Function Name: void Master_SendState (void)			                */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Send State Command	                                        */
/********************************************************************************/

void Master_SendState (void)
{
/*
 * Send the Last State Coming From Master_CheckState
 */
  Send_Command(State);
  
  State = TEMP;
}

/*
 * If the Slave Mode is Selected, Make the Slave Tasks Visible to the Preprocessor
 */
#else

/********************************************************************************/
/* Function Name: void Slave_CheckState (void)			                */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Check Received State	                                        */
/********************************************************************************/

void Slave_CheckState (void)
{
/*
 * Check the Received Message
 */
  switch (Received_Msg)
  {
  case CLOCKWISE:
    
    if (State_Counter < MAX)
    {
      State_Counter++;
    }
    else
    { 
      State_Counter = MIN;
    }
    break;
    
  case COUNTERCLOCKWISE:
    
    if(State_Counter > MIN)
    {
      State_Counter--;
    }
    else
    {
      State_Counter = MAX;
    }
    break;
    
  case BOTH_PRESSED:
    
    State_Counter = MIN;
    
    LED_Mode(RED);
    
    break;
    
  case IDLE:
    State_Counter = RESET;
    
    LED_Mode(WHITE);
    
    break;
  }
  Received_Msg = TEMP;
}

/********************************************************************************/
/* Function Name: void Slave_SwitchState(void)		                        */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Switch the Current State	                                */
/********************************************************************************/

void Slave_SwitchState(void)
{
/*
 * Check the State Coming From Slave_CheckState & Switch to that State
 */
  switch (State_Counter)
  {
  case WHITE:
    
    LED_Mode(WHITE);
    
    break;
    
  case RED:
    
    LED_Mode(RED);
    
    break;
    
  case BLUE:
    
    LED_Mode(BLUE);
    
    break;
    
  case GREEN:
    
    LED_Mode(GREEN);
    
    break;
  }
}

#endif