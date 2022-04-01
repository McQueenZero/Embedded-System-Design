
#include "stm32f10x.h"
#include "LED_Config.h"
#include "LCD_ILI9325.h"
#include "PCF8563.h"
#include "Touch.h"
//-----------------------------------------------------
#define  Buzzer_OFF	 GPIOB->BRR |= 0x0100//把PB8设置为低电平
#define  Buzzer_ON   GPIOB->BSRR |= 0x0100//把PB8设置为高电平


#define LED_light(x) ( GPIOD->BSRR |= 0x0001<<x ) //点亮某一颗LED
#define LED_Close(x) ( GPIOD->BRR |= 0x0001<<x )  //关闭某一颗LED


//-----------------------------------------------------
 u16 Xdata,Ydata;

 int main(void)
  {
	
    LED_Init(); //此处先要调用LED初始化函数
		LCD_IO_Init();
		ILI9325_Initial();
		PCF8563_IO_initial();
		Touch_IO_init();
		Buzzer_OFF;  //关
		
		//PCF8563_initial(15,10,5 ,5,6,3,8);
		
		//
		LCD_Clear(Red);
		//Paint_Screen(10,200,200,320, Blue );	
	  //LCD_PutString32(48,20,"内江师院",Red, Cyan);

	 LCD_PutString(70,70,"工程技术学院",Blue,Cyan);	  //  电压部分
			
	  // LCD_PutString(180,70,"V",Blue, Cyan);      //V 电压部分
	   //Put_number(140, 70, 12, Blue, Cyan);       //下点2 电压部分			 
		// Draw_Line(5,5,100, 100,Cyan );
		
		 //TP_adjust();
		
				
      while(1)
			{
				PCF8563_Read_Display_Time();
				delays(100);
				//Touch_pos_map(&Xdata, &Ydata);
				//LCD_DrawPoint(Xdata,Ydata,Blue);
				
			} //while end

  }//main end 


	


