/********************************************************************************/
/* Module Name  : Can.c							        */
/* Author       : Hossam						        */
/* Purpose      : Use CAN Services						*/
/********************************************************************************/

#include "Can.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

uint8 *CAN_Data_Msg;

volatile bool Error_Flag = false;

volatile bool Tx_Flag    = false;

volatile bool RX_Flag    = false;

tCANMsgObject TX_CANMessage;
uint8_t TX_pui8MsgData;

tCANMsgObject RX_CANMessage;
uint8_t RX_pui8MsgData;

/********************************************************************************/
/* Function Name: void CAN_Msg_Ptr (uint8* Msg)			                */
/* Inputs       : uint8* Msg		                                        */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Pass the Message Address to the CAN Driver	                */
/********************************************************************************/

void CAN_Msg_Ptr (uint8* Msg)
{
  CAN_Data_Msg = Msg;
}

/********************************************************************************/
/* Function Name: void CAN_Init (void)			                        */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Initialize the CAN Module	                                */
/********************************************************************************/

void CAN_Init (void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);                                    /* GPIO port B needs to be enabled so these pins can be used */
  
  GPIOPinConfigure(GPIO_PB5_CAN0TX);                                              /* Configure the GPIO pin muxing to select CAN0 functions for these pins */
  GPIOPinConfigure(GPIO_PB4_CAN0RX);
  
  GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);                       /* Enable the alternate function on the GPIO pins */
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);                                     /* The GPIO port and pins have been set up for CAN.  The CAN peripheral must be enabled */
  
  CANInit(CAN0_BASE);                                                             /* Initialize the CAN controller */
  
  CANBitRateSet(CAN0_BASE, SysCtlClockGet(), Bit_Rate);                             /* Set up the bit rate for the CAN bus */ 
  
  CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);       /* Enable interrupts on the CAN peripheral */ 
  
  IntEnable(INT_CAN0);                                                            /* Enable the CAN interrupt on the processor (NVIC) */
  
  CANEnable(CAN0_BASE);                                                           /* Enable the CAN for operation */
}

/********************************************************************************/
/* Function Name: void CAN_TXInit (void)			                */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Initialize the CAN TX Message	                                */
/********************************************************************************/

void CAN_TXInit (void)
{
  TX_pui8MsgData = Data_Initialize;
  
  TX_CANMessage.ui32MsgID = CAN0_TX_ID;
  
  TX_CANMessage.ui32MsgIDMask = Mask_Initialize;
  
  TX_CANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
  
  TX_CANMessage.ui32MsgLen = sizeof(TX_pui8MsgData);
  
  TX_CANMessage.pui8MsgData = (uint8_t *)&TX_pui8MsgData;
}

/********************************************************************************/
/* Function Name: void CAN_RXInit (void)			                */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Initialize the CAN RX Message	                                */
/********************************************************************************/

void CAN_RXInit (void)
{
  RX_CANMessage.ui32MsgID = CAN0_RX_ID;
  
  RX_CANMessage.ui32MsgIDMask = Mask_Initialize;
  
  RX_CANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
  
  RX_CANMessage.ui32MsgLen = sizeof(RX_pui8MsgData);
  
  CANMessageSet(CAN0_BASE, CAN0_RX_ID, &RX_CANMessage, MSG_OBJ_TYPE_RX);
}

/********************************************************************************/
/* Function Name: void CAN_Send (void)			                        */
/* Inputs       : uint8 State		                                        */
/* Outputs      : None				 	                        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Send a CAN Message	                                        */
/********************************************************************************/

void CAN_Send (uint8 State)
{
  Tx_Flag = false;
  
  TX_pui8MsgData = State;
  
  CANMessageSet (CAN0_BASE, CAN0_TX_ID, &TX_CANMessage, MSG_OBJ_TYPE_TX);
}

/********************************************************************************/
/* Function Name: void CAN_Receive (void)			                */
/* Inputs       : None		                                                */
/* Outputs      : uint8 RX_pui8MsgData				 	        */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Receive a CAN Message	                                        */
/********************************************************************************/

uint8 CAN_Receive (void)
{ 
  RX_Flag = false;

  CANMessageGet(CAN0_BASE, CAN0_RX_ID, &RX_CANMessage, bClrPendingInt);
 
  RX_CANMessage.pui8MsgData = (uint8_t *)&RX_pui8MsgData;
  
  return RX_pui8MsgData;
}

/********************************************************************************/
/* Function Name: void CAN0IntHandler (void)			                */
/* Inputs       : None		                                                */
/* Outputs      : None				 	                        */
/* Reentrancy   : Reentrant				 			*/
/* Synchronous  : Asynchronous							*/
/* Description  : Handler function for CAN Communication	                */
/********************************************************************************/

void CAN0_IntHandler (void)
{
  uint32_t Status;
  
  Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
  
  if(Status == CAN_INT_INTID_STATUS)
  {
    Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
    
    Error_Flag = true;
  }
  
  else if(Status == RX_OBJECT)
  {
    CANIntClear(CAN0_BASE, RX_OBJECT);
    
    RX_Flag = true;
    
    Error_Flag = false;
    
    *CAN_Data_Msg = CAN_Receive();
  }
  
  else if(Status == TX_OBJECT)
  {
    CANIntClear(CAN0_BASE, TX_OBJECT);
    
    Tx_Flag = true;
    
    Error_Flag  = false;
  }
  
  else
  {
    /* do nothing */
  }
}





