
#include "stm32f10x.h"
#include "LED_Config.h"
#include "LCD_ILI9325.h"
#include "PCF8563.h"
#include "Touch.h"
//-----------------------------------------------------
#define  Buzzer_OFF	 GPIOB->BRR |= 0x0100//��PB8����Ϊ�͵�ƽ
#define  Buzzer_ON   GPIOB->BSRR |= 0x0100//��PB8����Ϊ�ߵ�ƽ


#define LED_light(x) ( GPIOD->BSRR |= 0x0001<<x ) //����ĳһ��LED
#define LED_Close(x) ( GPIOD->BRR |= 0x0001<<x )  //�ر�ĳһ��LED


//-----------------------------------------------------
 u16 Xdata,Ydata;

 int main(void)
  {
	
    LED_Init(); //�˴���Ҫ����LED��ʼ������
		LCD_IO_Init();
		ILI9325_Initial();
		PCF8563_IO_initial();
		Touch_IO_init();
		Buzzer_OFF;  //��
		
		//PCF8563_initial(15,10,5 ,5,6,3,8);
		
		//
		LCD_Clear(Red);
		//Paint_Screen(10,200,200,320, Blue );	
	  //LCD_PutString32(48,20,"�ڽ�ʦԺ",Red, Cyan);

	 LCD_PutString(70,70,"���̼���ѧԺ",Blue,Cyan);	  //  ��ѹ����
			
	  // LCD_PutString(180,70,"V",Blue, Cyan);      //V ��ѹ����
	   //Put_number(140, 70, 12, Blue, Cyan);       //�µ�2 ��ѹ����			 
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


	


