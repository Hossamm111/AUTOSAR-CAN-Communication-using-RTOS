/********************************************************************************/
/* Module Name  : Dio.h	                                                        */
/* Author       : Hossam						        */
/* Purpose      : Header file for Dio Driver		                        */
/********************************************************************************/

#ifndef __DIO_H__
#define __DIO_H__

/*******************************************************************************
 *                              File Includes                                  *
 *******************************************************************************/

#include "../../../Libraries/Std_Types.h"
#include "Dio_Cfg.h"

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

typedef uint8 Dio_ChannelType   ;
typedef uint8 Dio_PortType      ;
typedef uint8 Dio_LevelType     ;
typedef uint8 Dio_PortLevelType ;

typedef struct
{   uint8           mask        ;
    uint8           offset      ;
    Dio_PortType    port        ;
}Dio_ChannelGroupType           ;

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

extern Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

extern void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level);

extern Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

extern void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level);

extern Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr);

extern void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);

extern Dio_LevelType DioFlipChannel(Dio_ChannelType ChannelId);

#endif /* __DIO_H__ */
