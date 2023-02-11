/********************************************************************************/
/* Module Name  : Port.c	                                                */
/* Author       : Hossam						        */
/* Purpose      : Use Port Services		                                */
/********************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

/*******************************************************************************
 *                          STATIC Global Definitions                          *
 *******************************************************************************/

STATIC const Port_ConfigChannel * Port_PortChannels = NULL_PTR;
STATIC volatile uint8 Port_Status = PORT_DIO_NOT_INITIALIZED;

/********************************************************************************/
/* Function Name: void Port_Init (const Port_ConfigType*configPtr)	        */
/* Inputs       : const Port_ConfigType*configPtr		                */
/* Outputs      : void				 		                */
/* Reentrancy   : Non-Reentrant				 			*/
/* Synchronous  : Synchronous							*/
/* Description  : Initializes Port Module	 		                */
/********************************************************************************/

void Port_Init (const Port_ConfigType *configPtr)
{        
  Port_Status = PORT_DIO_INITIALIZED;
  Port_PortChannels = configPtr -> Channels;    /* address of the first Channels structure --> Channels[0] */

  /*
   *
   *
   * SWITCH CONDITION TO INITIALIZE PORT
   *
   *
   */
  uint8 counter = 0;
  for (counter = 0; counter < PORT_CONFIGURED_CHANNLES; counter++)
  {
    if((counter > 15) && (counter < 20))
    {
      /* Do Nothing ...  this is the JTAG pins */
    }
    else
    {
      volatile uint32 *Port_Ptr = NULL_PTR; /* point to the required Port Registers base address */
      
      volatile uint32 delay = 0;
      
      switch(Port_PortChannels[counter].port_number)
      {
      case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
      break;
      
      case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
      break;
      
      case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
      break;
      
      case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
      break;
      
      case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
      break;
      
      case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
      break;
      }
      
      /*
      *
      *
      * ENABLING CLOCK FOR SPECIFIC PORT
      *
      *
      */
      
      /* Enable clock for PORTF and allow time for clock to start*/
      
      SYSCTL_RCGC2_R |= (1<<Port_PortChannels[counter].port_number);
      
      delay = SYSCTL_RCGC2_R;
      /*
      *
      *
      * IGNORE UNLOCKING
      *
      *
      */
      if(((Port_PortChannels[counter].port_number == 3) && (Port_PortChannels[counter].channel_number == 7)) || ((Port_PortChannels[counter].port_number == 5) && (Port_PortChannels[counter].channel_number == 0))) /* PD7 or PF0 */
      {
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = GPIO_LOCK_KEY;       /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , Port_PortChannels[counter].channel_number);     /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
      }
      
      else if((Port_PortChannels[counter].port_number == 2) && (Port_PortChannels[counter].channel_number <= 3))      /* PC0 to PC3 */
      {
        /* Do Nothing ...  this is the JTAG pins */
      }
      
      else
      {
        /* Do Nothing ... No need to unlock the commit register for this pin */
      }
      
     /*
      *
      *
      * INITIALIZING MODE (AMSEL - AFSEL - PMC - DEN)
      *
      *
      */
      if(Port_PortChannels[counter].Mode == PORT_PIN_MODE_DIO)
      {
        
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[counter].channel_number);  /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[counter].channel_number);         /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[counter].channel_number * 4)); /* Clear the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[counter].channel_number);     /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }
      
      else if(Port_PortChannels[counter].Mode == PORT_PIN_MODE_ADC)
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[counter].channel_number);    /* Set the corresponding bit in the GPIOAMSEL register to Enable analog functionality on this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[counter].channel_number);         /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[counter].channel_number * 4)); /* Clear the PMCx bits for this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[counter].channel_number);   /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
      }
      
      else if(Port_PortChannels[counter].Mode == PORT_PIN_MODE_UART)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[counter].channel_number);  /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[counter].channel_number);           /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
        
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[counter].channel_number * 4)) | (Port_PortChannels[counter].Mode));   /* Set the PMCx bits for this pin depending on the mode */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[counter].channel_number);     /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }
      
      else if(Port_PortChannels[counter].Mode == PORT_PIN_MODE_SSI)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[counter].channel_number);  /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[counter].channel_number);           /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
        
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[counter].channel_number * 4)) | (Port_PortChannels[counter].Mode));   /* Set the PMCx bits for this pin depending on the mode */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[counter].channel_number);     /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }
      
      else if(Port_PortChannels[counter].Mode == PORT_PIN_MODE_I2C)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[counter].channel_number);  /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[counter].channel_number);           /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
        
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[counter].channel_number * 4)) | (Port_PortChannels[counter].Mode));   /* Set the PMCx bits for this pin depending on the mode */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[counter].channel_number);     /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }
      
      else if(Port_PortChannels[counter].Mode == PORT_PIN_MODE_M0PWM)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[counter].channel_number);  /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[counter].channel_number);           /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
        
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[counter].channel_number * 4)) | (Port_PortChannels[counter].Mode));   /* Set the PMCx bits for this pin depending on the mode */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[counter].channel_number);     /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }
      
      else if(Port_PortChannels[counter].Mode == PORT_PIN_MODE_M1PWM)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[counter].channel_number);  /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[counter].channel_number);           /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
        
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[counter].channel_number * 4)) | (Port_PortChannels[counter].Mode));   /* Set the PMCx bits for this pin depending on the mode */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[counter].channel_number);     /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }
      
      else if(Port_PortChannels[counter].Mode == PORT_PIN_MODE_CAN)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[counter].channel_number);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[counter].channel_number);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
        
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[counter].channel_number * 4)) | (Port_PortChannels[counter].Mode));     /* Set the PMCx bits for this pin depending on the mode */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[counter].channel_number);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }
      
      else
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[counter].channel_number);  /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[counter].channel_number);         /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        
        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[counter].channel_number * 4)); /* Clear the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[counter].channel_number);     /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      }
      
      /*
      *
      *
      * SETTING PIN DIRECTION (DIR - DATAR)
      *
      *
      */
      if(Port_PortChannels[counter].Ch_Dir == PORT_PIN_OUT)
      {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[counter].channel_number);        /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
        if(Port_PortChannels[counter].InitialValue == PORT_PIN_Level_HIGH)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , Port_PortChannels[counter].channel_number);   /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , Port_PortChannels[counter].channel_number); /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
      }
      
      else if(Port_PortChannels[counter].Ch_Dir == PORT_PIN_IN)
      {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[counter].channel_number);      /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
        if(Port_PortChannels[counter].resistor == PORT_PIN_PULL_UP_RESISTOR)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_PortChannels[counter].channel_number);  /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        
        else if(Port_PortChannels[counter].resistor == PORT_PIN_PULL_DOWN_RESISTOR)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_PortChannels[counter].channel_number);        /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        
        else
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_PortChannels[counter].channel_number);        /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_PortChannels[counter].channel_number);      /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
      }
      
      else
      {
        /* Do Nothing */
      }
    }
  }
}

/************************************************************************************************/
/* Function Name: void Port_SetPinDirection (Port_PinType Pin, Port_PinDirectionType Direction) */
/* Inputs       : -Pin       --> Port Pin ID number                                             */
/*                -Direction --> Port Pin Direction                                             */
/* Outputs      : Void                                                                          */
/* Reentrancy   : Reentrant                                                                     */
/* Synchronous  : Synchronous                                                                   */
/* Description  : Sets the port pin direction                                                   */
/************************************************************************************************/

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)

void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
  volatile uint32 * Port_Ptr = NULL_PTR;    /* point to the required Port Registers base address */
  volatile uint32 delay = 0;
  
  switch(Port_PortChannels[Pin].port_number)
  {
  case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
  break;
  
  case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
  break;
  
  case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
  break;
  
  case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
  break;
  
  case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
  break;
  
  case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
  break;
  }
  
  if(Direction == PORT_PIN_OUT)
  {
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[Pin].channel_number);      /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
  }
  
  else
  {
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels[Pin].channel_number);    /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
  }
}

#endif /* (PORT_SET_PIN_DIRECTION_API == STD_ON) */

#if (Port_RefreshPortDirection_API == STD_ON)


/****************************************************************************************/
/* Function Name: void Port_RefreshPortDirection (void)                                 */
/* Inputs       : None                                                                  */
/* Outputs      : Void                                                                  */
/* Reentrancy   : Non Reentrant                                                         */
/* Synchronous  : Synchronous                                                           */
/* Description  : Refreshes port direction                                              */
/****************************************************************************************/

void Port_RefreshPortDirection(void)
{
  uint8 counter;
  for(counter = 0; counter < PORT_CONFIGURED_CHANNLES; counter++)
  {
    if( (counter > 15) && (counter < 20) )
    {
      /* Do Nothing ...  this is the JTAG pins */
    }
    
    else
    {
      if( (Port_PortChannels[counter].DirectionChangeability) == PORT_PIN_DIRECTION_CHANGEABLE)
      {
        /* Do Nothing  */
      }
      
      else
      {
        volatile uint32 * Port_Ptr = NULL_PTR;      /* point to the required Port Registers base address */
        volatile uint32 delay = 0;
        
        switch(Port_PortChannels[counter].port_number)
        {
        case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
        
        case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;
        
        case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;
        
        case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;
        
        case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;
        
        case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
        }
        
        if((Port_PortChannels[counter].Ch_Dir) == PORT_PIN_OUT)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET), Port_PortChannels[counter].channel_number);       /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        }
        
        else
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET), Port_PortChannels[counter].channel_number);     /* Clear the corresponding bit in the GPIODIR register to configure it as Input pin */
        }
      }
    }
  }
}

#endif

/****************************************************************************************/
/* Function Name: void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)         */
/* Inputs       : -Pin       --> Port Pin ID number                                     */
/*                -Mode      --> New Port Pin mode to be set on port pin                */
/* Outputs      : Void                                                                  */
/* Reentrancy   : Reentrant                                                             */
/* Synchronous  : Synchronous                                                           */
/* Description  : Sets the port pin mode                                                */
/****************************************************************************************/

#if (PORT_SET_PIN_MODE_API == STD_ON)

void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
  if((Pin > 15) && (Pin < 20))
  {
    /* Do Nothing ...  this is the JTAG pins */
  }
  
  else
  {
    volatile uint32 * Port_Ptr = NULL_PTR;  /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    
    switch(Port_PortChannels[Pin].port_number)
    {
    case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
    break;
    
    case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
    break;
    
    case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
    break;
    
    case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
    break;
    
    case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
    break;
    
    case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
    break;
    }
    
    if(Mode == PORT_PIN_MODE_DIO)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);               /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
      
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));       /* Clear the PMCx bits for this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
    
    else if(Mode == PORT_PIN_MODE_ADC)
    {
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);          /* Set the corresponding bit in the GPIOAMSEL register to Enable analog functionality on this pin */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);               /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
      
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));       /* Clear the PMCx bits for this pin */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);         /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
    }
    
    else if(Mode == PORT_PIN_MODE_UART)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);                 /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
      
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));       /* Clear the PMCx bits for this pin */
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);      /* Set the PMCx bits for this pin depending on the mode */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
    
    else if(Mode == PORT_PIN_MODE_SSI)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);                 /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
      
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));       /* Clear the PMCx bits for this pin */
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);      /* Set the PMCx bits for this pin depending on the mode */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
    
    else if(Mode == PORT_PIN_MODE_I2C)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);                 /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
      
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));       /* Clear the PMCx bits for this pin */
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);      /* Set the PMCx bits for this pin depending on the mode */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
    
    else if(Mode == PORT_PIN_MODE_M0PWM)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);                 /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
      
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));       /* Clear the PMCx bits for this pin */
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);      /* Set the PMCx bits for this pin depending on the mode */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
    
    else if(Mode == PORT_PIN_MODE_M1PWM)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);                 /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
      
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));       /* Clear the PMCx bits for this pin */
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);      /* Set the PMCx bits for this pin depending on the mode */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
    
    else if(Mode == PORT_PIN_MODE_CAN)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);                 /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
      
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));       /* Clear the PMCx bits for this pin */
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4)) | Mode);      /* Set the PMCx bits for this pin depending on the mode */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
    
    else
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels[Pin].channel_number);        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels[Pin].channel_number);               /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
      
      *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels[Pin].channel_number * 4));       /* Clear the PMCx bits for this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels[Pin].channel_number);           /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
  }
}

#endif /* (PORT_SET_PIN_MODE_API == STD_ON) */