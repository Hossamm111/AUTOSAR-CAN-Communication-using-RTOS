/********************************************************************************/
/* Module Name  : Port_PBcfg.c	                                                */
/* Author       : Hossam					                */
/* Purpose      : Post Configuration File for Port Driver		        */
/********************************************************************************/

#include "Port.h"

  /* PB structure used with Port_Init API */
const Port_ConfigType Port_Configuration =
{
 /*
  *
  *
  * PORTF PINS - CONFIGURED FOR LEDS & SWITCHES
  *
  *
  */
  PortConf_PORTF_ID, PortConf_PORTF_PIN0_ID, PORT_PIN_IN, PORT_PIN_MODE_DIO, PORT_PIN_Level_HIGH, PORT_PIN_PULL_UP_RESISTOR, PORT_PIN_DIRECTION_CHANGEABLE, PORT_PIN_MODE_CHANGEABLE,   /* Switch 1 */
  
  PortConf_PORTF_ID, PortConf_PORTF_PIN1_ID, PORT_PIN_OUT, PORT_PIN_MODE_DIO, PORT_PIN_Level_LOW, PORT_PIN_PULL_OFF_RESISTOR, PORT_PIN_DIRECTION_CHANGEABLE, PORT_PIN_MODE_CHANGEABLE,  /* RED LED */
  
  PortConf_PORTF_ID, PortConf_PORTF_PIN2_ID, PORT_PIN_OUT, PORT_PIN_MODE_DIO, PORT_PIN_Level_LOW, PORT_PIN_PULL_OFF_RESISTOR, PORT_PIN_DIRECTION_CHANGEABLE, PORT_PIN_MODE_CHANGEABLE,  /* BLUE LED */
  
  PortConf_PORTF_ID, PortConf_PORTF_PIN3_ID, PORT_PIN_OUT, PORT_PIN_MODE_DIO, PORT_PIN_Level_LOW, PORT_PIN_PULL_OFF_RESISTOR, PORT_PIN_DIRECTION_CHANGEABLE, PORT_PIN_MODE_CHANGEABLE,  /* GREEN LED */
    
  PortConf_PORTF_ID, PortConf_PORTF_PIN4_ID, PORT_PIN_IN, PORT_PIN_MODE_DIO, PORT_PIN_Level_HIGH, PORT_PIN_PULL_UP_RESISTOR, PORT_PIN_DIRECTION_CHANGEABLE, PORT_PIN_MODE_CHANGEABLE    /* Switch 2 */
};
