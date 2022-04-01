#include "stm32f10x.h"

//-------  PD7  SCL	---------------------
//-------  PB3  SDA	---------------------
//------  ¶Ë¿Ú ¶¨Òå  --------------------

 #define  PCF8563_SCL_1  GPIOD->BSRR |= 0x0080
 #define  PCF8563_SCL_0  GPIOD->BRR |= 0x00080

 #define  PCF8563_SDA_Out_1  GPIOB->BSRR |= 0x0008
 #define  PCF8563_SDA_Out_0  GPIOB->BRR |= 0x0008

 #define  PCF8563_SDA_In   GPIOB->IDR&0x0008
 
 #define  PCF8563_SDA_in()   {GPIOB->CRL &= 0xFFFF0FFF; GPIOB->CRL |= 0x00008000;}//dir_in)	//PB3
 #define  PCF8563_SDA_out()  {GPIOB->CRL &= 0xFFFF0FFF; GPIOB->CRL |= 0x00003000;}//dir_out);// 

//---------------------------------------
 void IIC1_Start(void);
  void IIC1_Stop(void);
   void IIC1_Send_1Byte(unsigned char banana);
    unsigned char IIC1_Receive_1Byte(void);
	 void Write_ADD_1Byte(u8 ADD, u8 BYTE); 
	  u8 Read_ADD_1Byte(u8 ADD);
	 void PCF8563_Read_Display_Time(void);
	  void PCF8563_initial(u8 year,u8 Month, u8 day, u8 week,u8 hour, u8 minute, u8 second);
    void delay_us(unsigned short x);
    void PCF8563_IO_initial(void);













