/********************************************************************************/
/* Module Name  : Dio.c	                                                        */
/* Author       : Hossam						        */
/* Purpose      : Use Dio services		                                */
/********************************************************************************/

#include "Dio.h"
#include "Dio_MemMap.h"

  /* macro static */
#define HWREG(F)        (*((volatile uint32 *)(F)))

/********************************************************************************************************/
/*                                      [SWS_Dio_00133]                                                 */
/* \Syntax          : Dio_LevelType Dio_ReadChannel ( Dio_ChannelType ChannelId )                       */
/* \Description     : Returns the value of the specified DIO channel.                                   */                                                                         
/* \Sync\Async      : Synchronous                                                                       */ 
/* \Reentrancy      : Reentrant                                                                         */ 
/* \Parameters (in) : Channel ID                                                                        */
/* \Parameters (out): None                                                                              */
/* \Return value:   : Dio_LevelType (STD_HIGH: The physical level of the corresponding Pin is STD_HIGH, */
/*                                   STD_LOW: The physical level of the corresponding Pin is STD_LOW)   */                     
/********************************************************************************************************/

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
  if (HWREG(PORT(Channels[ChannelId].PortId) | DATA) & Channels[ChannelId].PinId)
        
  return STD_HIGH;
    
  else return STD_LOW;
}

/********************************************************************************************************/
/*                                      [SWS_Dio_00134]                                                 */
/* \Syntax          : void Dio_WriteChannel ( Dio_ChannelType ChannelId, Dio_LevelType Level )          */
/* \Description     : Service to set a level of a channel                                               */                                                                         
/* \Sync\Async      : Synchronous                                                                       */ 
/* \Reentrancy      : Reentrant                                                                         */ 
/* \Parameters (in) : Channel ID & Level                                                                */
/* \Parameters (out): None                                                                              */
/* \Return value:   : void                                                                              */                     
/********************************************************************************************************/

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
  if (Level)
  {
    HWREG(PORT(Channels[ChannelId].PortId) | DATA) |= Channels[ChannelId].PinId;
  }
  else
  {
    HWREG(PORT(Channels[ChannelId].PortId) | DATA) &= ~Channels[ChannelId].PinId;
  }
}

/********************************************************************************************************/
/*                                      [SWS_Dio_00135]                                                 */
/* \Syntax          : Dio_PortLevelType Dio_ReadPort ( Dio_PortType PortId )                            */
/* \Description     : Service to set a level of a channel                                               */                                                                         
/* \Sync\Async      : Synchronous                                                                       */ 
/* \Reentrancy      : Reentrant                                                                         */ 
/* \Parameters (in) : Port ID                                                                           */
/* \Parameters (out): None                                                                              */
/* \Return value:   : Dio_PortLevelType                                                                 */                     
/********************************************************************************************************/

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
  return HWREG(PORT(PortId) | DATA) & 0xFF;
}

/********************************************************************************************************/
/*                                      [SWS_Dio_00136]                                                 */
/* \Syntax          : void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level)                   */
/* \Description     : Service to set a level of a channel                                               */                                                                         
/* \Sync\Async      : Synchronous                                                                       */ 
/* \Reentrancy      : Reentrant                                                                         */ 
/* \Parameters (in) : PortId & Level                                                                    */
/* \Parameters (out): None                                                                              */
/* \Return value:   : void                                                                              */                     
/********************************************************************************************************/

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
  uint32 Pin_Index;
  
  for (Pin_Index = 0; Pin_Index < 8; Pin_Index++)
  {
    if (Level & (1U << Pin_Index))
    {
      HWREG(PORT(PortId) | DATA) |=  (1U << Pin_Index);
    }
    else
    {
      HWREG(PORT(PortId) | DATA) &= ~(1U << Pin_Index);
    }
  }
}

/****************************************************************************************************************/
/*                                      [SWS_Dio_00137]                                                         */
/* \Syntax          : Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr)     */
/* \Description     : Service to set a level of a channel                                                       */                                                                         
/* \Sync\Async      : Synchronous                                                                               */ 
/* \Reentrancy      : Reentrant                                                                                 */ 
/* \Parameters (in) : Channels Cfg struct                                                                       */
/* \Parameters (out): None                                                                                      */
/* \Return value:   : Dio_PortLevelType                                                                         */                     
/****************************************************************************************************************/

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr)
{
    return HWREG(PORT(ChannelGroupIdPtr -> port) | DATA) & ChannelGroupIdPtr -> mask;
}

/********************************************************************************************************************************/
/*                                      [SWS_Dio_00138]                                                                         */
/* \Syntax          : void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level)        */
/* \Description     : Service to set a level of a channel                                                                       */                                                                         
/* \Sync\Async      : Synchronous                                                                                               */ 
/* \Reentrancy      : Reentrant                                                                                                 */ 
/* \Parameters (in) : Channel Cfg struct & Level                                                                                */
/* \Parameters (out): None                                                                                                      */
/* \Return value:   : void                                                                                                      */                     
/********************************************************************************************************************************/

void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level)
{
  uint8 Pin_Index = 0;
        
  for (Pin_Index = 0; Pin_Index < 8; Pin_Index++)
  {
    if (ChannelGroupIdPtr -> mask & (1U << Pin_Index))
    {
      if (Level & (1U << Pin_Index))
      {
        HWREG(PORT(ChannelGroupIdPtr -> port) | DATA) |=  (1U << Pin_Index);
      }
      else
      {
        HWREG(PORT(ChannelGroupIdPtr -> port) | DATA) &= ~(1U << Pin_Index);
      }
    }
  }
}

/********************************************************************************************************/
/*                                      [SWS_Dio_00139]                                                 */
/* \Syntax          : void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level)                   */
/* \Description     : Service to set a level of a channel                                               */                                                                         
/* \Sync\Async      : Synchronous                                                                       */ 
/* \Reentrancy      : Reentrant                                                                         */ 
/* \Parameters (in) : Channel ID                                                                        */
/* \Parameters (out): None                                                                              */
/* \Return value:   : Dio_LevelType                                                                     */                     
/********************************************************************************************************/

Dio_LevelType DioFlipChannel(Dio_ChannelType ChannelId)
{
  if (HWREG(PORT(Channels[ChannelId].PortId)|DATA) & Channels[ChannelId].PinId)
  {
    HWREG(PORT(Channels[ChannelId].PortId)|DATA) &= ~Channels[ChannelId].PinId;
  }
  else
  {
    HWREG(PORT(Channels[ChannelId].PortId)|DATA) |= Channels[ChannelId].PinId;
  }
  
  if (HWREG(PORT(Channels[ChannelId].PortId)|DATA) & Channels[ChannelId].PinId)
  
  return        STD_HIGH;
  
  else return   STD_LOW;
}



