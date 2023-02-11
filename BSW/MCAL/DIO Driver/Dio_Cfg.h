/********************************************************************************/
/* Module Name  : Dio_Cfg.h	                                                */
/* Author       : Hossam 						        */
/* Purpose      : Configuration File for Dio Driver		                */
/********************************************************************************/

#ifndef __DIO_CFG_H__
#define __DIO_CFG_H__

/*******************************************************************************
 *                     Tiva Specific Register Definitions                      *
 *******************************************************************************/

#define DATA            (0x3FC)
#define PORTF_BASE      (0x40025000)
#define PORT(n)         (PORTF_BASE | ((n&4) << 15) | ((n&3) << 12))

#define SYSCTL_RCGC     (0x400FE108)

#define PORT_A          (0)
#define PORT_B          (1)
#define PORT_C          (2)
#define PORT_D          (3)
#define PORT_E          (4)
#define PORT_F          (5)
  
#define PIN_0           (1U << 0)
#define PIN_1           (1U << 1)
#define PIN_2           (1U << 2)
#define PIN_3           (1U << 3)
#define PIN_4           (1U << 4)
#define PIN_5           (1U << 5)
#define PIN_6           (1U << 6)
#define PIN_7           (1U << 7)

/*******************************************************************************
 *                          Module Data Definitions                            *
 *******************************************************************************/

typedef struct
{
  uint8 PortId;
  
  uint8 PinId;
  
}ChannelToPin;


static const ChannelToPin Channels[] =
{
  /*                                 
  * PORT_A Configured PINs           
  */
  
  /* #1: PORT_A_PIN_0 */
  {
    .PortId = PORT_A,           /* Port_Number */
    .PinId  = PIN_0,            /* Pin_Number */ 
  },
  /* #2: PORT_A_PIN_1 */
  {
    .PortId = PORT_A,           /* Port_Number */
    .PinId  = PIN_1,            /* Pin_Number */                 
  },                            
  /* #3: PORT_A_PIN_2 */        
  {
    .PortId  = PORT_A,          /* Port_Number */
    .PinId   = PIN_2,           /* Pin_Number */                
  },                            
  /* #4: PORT_A_PIN_3 */        
  {                             
    .PortId = PORT_A,           /* Port_Number */
    .PinId  = PIN_3,            /* Pin_Number */
  },
  /* #5: PORT_A_PIN_4 */
  {
    .PortId = PORT_A,           /* Port_Number */
    .PinId  = PIN_4,            /* Pin_Number */             
  },                              
  /* #6: PORT_A_PIN_5 */          
  {                               
    .PortId = PORT_A,           /* Port_Number */
    .PinId  = PIN_5,            /* Pin_Number */ 
  },                              
  /* #7: PORT_A_PIN_6 */          
  {                               
    .PortId = PORT_A,           /* Port_Number */
    .PinId  = PIN_6,            /* Pin_Number */                                  
  },                              
  /* #8: PORT_A_PIN_7 */          
  {                               
    .PortId = PORT_A,           /* Port_Number */
    .PinId  = PIN_7,            /* Pin_Number */                                
  },                              
                                     
  /*                                 
   * PORT_B Configured PINs           
   */
  
  /* #9: PORT_B_PIN_0 */
  {
    .PortId = PORT_B,           /* Port_Number */
    .PinId  = PIN_0,            /* Pin_Number */ 
  },
  /* #10: PORT_B_PIN_1 */
  {
    .PortId = PORT_B,           /* Port_Number */
    .PinId  = PIN_1,            /* Pin_Number */ 
  },
  /* #11: PORT_B_PIN_2 */
  {
    .PortId = PORT_B,           /* Port_Number */
    .PinId  = PIN_2,            /* Pin_Number */ 
  },
  /* #12: PORT_B_PIN_3 */
  {
    .PortId = PORT_B,           /* Port_Number */ 
    .PinId  = PIN_3,            /* Pin_Number */ 
  },
  /* #13: PORT_B_PIN_4 */
  {
    .PortId = PORT_B,           /* Port_Number */
    .PinId  = PIN_4,            /* Pin_Number */ 
  },
  /* #14: PORT_B_PIN_5 */
  {
    .PortId = PORT_B,           /* Port_Number */
    .PinId  = PIN_5,            /* Pin_Number */ 
  },
  /* #15: PORT_B_PIN_6 */
  {
    .PortId = PORT_B,           /* Port_Number */
    .PinId  = PIN_6,            /* Pin_Number */ 
  },
  /* #16: PORT_B_PIN_7 */
  {
    .PortId = PORT_B,           /* Port_Number */
    .PinId  = PIN_7,            /* Pin_Number */ 
  },
  
  /*
   * PORT_C Configured PINs
   */
  
  /* #17: PORT_C_PIN_4 */
  {
    .PortId = PORT_C,           /* Port_Number */
    .PinId  = PIN_4,            /* Pin_Number */ 
  },
  /* #18: PORT_C_PIN_5 */
  {
    .PortId = PORT_C,           /* Port_Number */
    .PinId  = PIN_5,            /* Pin_Number */ 
  },
  /* #19: PORT_C_PIN_6 */
  {
    .PortId = PORT_C,           /* Port_Number */
    .PinId  = PIN_6,            /* Pin_Number */   
  },
  /* #20: PORT_C_PIN_7 */
  {
    .PortId = PORT_C,           /* Port_Number */
    .PinId  = PIN_7,            /* Pin_Number */ 
  },
  
  /*
   * PORT_D Configured PINs
   */
  
  /* #21: PORT_D_PIN_0 */
  {
    .PortId = PORT_D,           /* Port_Number */
    .PinId  = PIN_0,            /* Pin_Number */ 
  },
  /* #22: PORT_D_PIN_1 */
  {
    .PortId = PORT_D,           /* Port_Number */
    .PinId  = PIN_1,            /* Pin_Number */ 
  },
  /* #23: PORT_D_PIN_2 */
  {
    .PortId = PORT_D,           /* Port_Number */
    .PinId  = PIN_2,            /* Pin_Number */ 
  },
  /* #24: PORT_D_PIN_3 */
  {
    .PortId = PORT_D,           /* Port_Number */
    .PinId  = PIN_3,            /* Pin_Number */ 
  },
  /* #25: PORT_D_PIN_4 */
  {
    .PortId = PORT_D,           /* Port_Number */
    .PinId  = PIN_4,            /* Pin_Number */ 
  },
  /* #26: PORT_D_PIN_5 */
  {
    .PortId = PORT_D,           /* Port_Number */
    .PinId  = PIN_5,            /* Pin_Number */ 
  },
  /* #27: PORT_D_PIN_6 */
  {
    .PortId = PORT_D,           /* Port_Number */
    .PinId  = PIN_6,            /* Pin_Number */ 
  },
  /* #28: PORT_D_PIN_7 */
  {
    .PortId = PORT_D,           /* Port_Number */
    .PinId  = PIN_7,            /* Pin_Number */ 
  },
  
  /*
   * PORT_E Configured PINs
   */
  
  /* #29: PORT_E_PIN_0 */
  {
    .PortId = PORT_E,           /* Port_Number */     
    .PinId  = PIN_0,            /* Pin_Number */          
  },
  /* #30: PORT_E_PIN_1 */
  {
    .PortId = PORT_E,           /* Port_Number */    
    .PinId  = PIN_1,            /* Pin_Number */         
  },
  /* #31: PORT_E_PIN_2 */
  {
    .PortId = PORT_E,           /* Port_Number */      
    .PinId  = PIN_2,            /* Pin_Number */           
  },
  /* #32: PORT_E_PIN_3 */
  {
    .PortId = PORT_E,           /* Port_Number */    
    .PinId  = PIN_3,            /* Pin_Number */         
  },
  /* #33: PORT_E_PIN_4 */
  {
    .PortId = PORT_E,           /* Port_Number */      
    .PinId  = PIN_4,            /* Pin_Number */           
  },
  /* #34: PORT_E_PIN_5 */
  {
    .PortId = PORT_E,           /* Port_Number */      
    .PinId  = PIN_5,            /* Pin_Number */           
  },
  
  /*                                 
  * PORT_F Configured PINs
  */
  
  /* #35: Switch 1 */
  {
    .PortId = PORT_F,           /* Port_Number */
    .PinId  = PIN_0,            /* Pin_Number */
  },
  /* #36: PORT_F_PIN_1 */
  {
    .PortId = PORT_F,           /* Port_Number */      
    .PinId  = PIN_1,            /* Pin_Number */ 
  },
  /* #37: PORT_F_PIN_2 */
  {
    .PortId = PORT_F,           /* Port_Number */        
    .PinId  = PIN_2,            /* Pin_Number */             
  },
  /* #38: PORT_F_PIN_3 */
  {
    .PortId = PORT_F,           /* Port_Number */        
    .PinId  = PIN_3,            /* Pin_Number */             
  },
  /* #39: SWitch 2 */
  {
    .PortId = PORT_F,           /* Port_Number */
    .PinId  = PIN_4             /* Pin_Number */
  }
};

#endif /* __DIO_CFG_H__ */
