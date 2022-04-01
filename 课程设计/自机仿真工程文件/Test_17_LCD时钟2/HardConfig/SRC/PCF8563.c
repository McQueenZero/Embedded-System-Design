
#include "PCF8563.h"
#include "LCD_ILI9325.h" 


 //-------------  端口初始化  -----------------------
 void PCF8563_IO_initial(void)
  { 
    GPIO_InitTypeDef  PCF8563_GPIO;
 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PB端口时钟
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//
	
    PCF8563_GPIO.GPIO_Pin = GPIO_Pin_3;	
    PCF8563_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    PCF8563_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOB, &PCF8563_GPIO);    
		
    PCF8563_GPIO.GPIO_Pin = GPIO_Pin_7;	
    PCF8563_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    PCF8563_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOD, &PCF8563_GPIO); 
     
  }//end

//--------------------------------------------------

//----------------- 端口模拟IIC ---------------------
//------------------------------------------------
  void IIC1_Start(void)
   {
	   PCF8563_SDA_out();  //SDA1_out(); //输出
  	   PCF8563_SDA_Out_1;  //SDA1_Out = 1;
	   PCF8563_SCL_1;      //SCL1 = 1;

	   delay_us(2); 
  	   PCF8563_SDA_Out_0;  //SDA1_Out = 0;
	   delay_us(2);
	   PCF8563_SCL_0; //SCL1 = 0;
    }//end

//------------------------------------------------
  void IIC1_Stop(void)
   {
       PCF8563_SDA_out();  //SDA1_out();	 //输出
	   PCF8563_SCL_0;      // SCL1 = 0;
  	   PCF8563_SDA_Out_0;  //SDA1_Out = 0;
	   delay_us(2);
	   PCF8563_SCL_1;      //SCL1 = 1;
	   delay_us(2);
	   PCF8563_SDA_Out_1;  //SDA1_Out = 1; 
  	   delay_us(2);

    }//end
//------------------------------------------------
u8 IIC1_Wait_Ack(void)
{
	u8 ucErrTime=0;

	PCF8563_SDA_in();    //SDA1_in();      //SDA设置为输入
	PCF8563_SCL_0;       //SCL1=0;  
	PCF8563_SDA_Out_1;   //SDA1_Out=1;
	
	delay_us(2);	   
	PCF8563_SCL_1;  //SCL1=1;
	delay_us(2);	 
	while(PCF8563_SDA_In)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC1_Stop();
			return 1;
		}
	}
	PCF8563_SCL_0; //SCL1=0;//时钟输出0 	   
	return 0;  
} 


//----- 主应答(包含ack:sda=0和no_ack:sda=0) ---------
  void IIC1_Ack_to(u8 mn)
   {  
	  PCF8563_SCL_0; //SCL1=0;
      PCF8563_SDA_out();  //SDA1_out();//设置SDA 口为输出
      if(mn)
	    {
		  PCF8563_SDA_Out_1;  //SDA1_Out=1;
		}
	  else
	    {
		  PCF8563_SDA_Out_0;//SDA1_Out=0;
		}

	     delay_us(2);	  
	   PCF8563_SCL_1; //SCL1=1;
	     delay_us(2);
	   PCF8563_SCL_0;  //SCL1=0;

  }//end


//------------------------------------------------

 void IIC1_Send_1Byte(unsigned char banana)
   {
   	   unsigned char i;

	    PCF8563_SDA_out(); //SDA1_out();	 //输出
   	  //-------- 发送 ----------------------
	    PCF8563_SCL_0; //SCL1 = 0;
   	   for(i=0; i<8; i++ )
        {  
			 PCF8563_SCL_0; //SCL1 = 0;
			  delay_us(2);
		    if( (banana<<i)&0x80 )
			 {
			   PCF8563_SDA_Out_1;  //SDA1_Out = 1;
			 }
		    else 
			 {
		       PCF8563_SDA_Out_0;  //SDA1_Out = 0;
			 }
			delay_us(2);
			PCF8563_SCL_1; //SCL1 = 1;
		    delay_us(2);
		    PCF8563_SCL_0; //SCL1 = 0;
		}
	  //-------------------------------------------
	      IIC1_Wait_Ack();

   }//end



//*********************** 接收1 字节 *********************************
 unsigned char IIC1_Receive_1Byte(void)
  {
	   unsigned char j;
	   unsigned int Received=0;

  	   PCF8563_SDA_in(); //端口输入
  	   for(j=0; j<8;j++)
  		 {
		   Received <<= 1;
		   PCF8563_SCL_0; //SCL1 = 0;
		   delay_us(3);
		   PCF8563_SCL_1; //SCL1 = 1;
		   
		   delay_us(3);
		   if(PCF8563_SDA_In ) 
		    {
		     Received |=0x01;
		 	}
		   delay_us(3);
		 }

  		return(Received);
  }//end


//--------------- 写地址和数据 --------------------------------
  void Write_ADD_1Byte(u8 ADD, u8 BYTE)
    {
		  IIC1_Start();  
	   IIC1_Send_1Byte(0xa2);	//0xa2,写模式
	   IIC1_Send_1Byte(ADD);
	   IIC1_Send_1Byte(BYTE);
		  IIC1_Stop();
		
	}//end

//--------------- 读地址的数据 --------------------------------
  u8 Read_ADD_1Byte(u8 ADD)
    {
	   u8 Read;

		  IIC1_Start();  
	   IIC1_Send_1Byte(0xa2);	        
	   IIC1_Send_1Byte(ADD);            // 写入地址
	
		  IIC1_Start();
	   IIC1_Send_1Byte(0xa3);			//0xa3,读模式
	   Read = IIC1_Receive_1Byte();     //读到数据
		  IIC1_Stop();
	
	   return(Read);	
	}//end

//---------- PCF8563 初始化 --------------//
  void PCF8563_initial(u8 year, u8 Month,u8 day ,u8 week,u8 hour, u8 minute, u8 second)
	{ 	
			u8 YEARs, MONTH, DAY, WEEK, HOUR, MINUTE, SRCOND;

			  YEARs = ( (year/10)<<4 )|( (year%10) );
			  MONTH = ( (Month/10)<<4 )|( (Month%10) );
			  DAY = ( (day/10)<<4 )|( (day%10) );
			  WEEK =   week&0x07;
			  HOUR = ( (hour/10)<<4 )|( (hour%10) );
			  MINUTE = ( (minute/10)<<4 )|( (minute%10) );
			  SRCOND = ( (second/10)<<4 )|( (second%10) );

			 //Write_ADD_1Byte(0x00, 0x80);
			 Write_ADD_1Byte(0x00, 0x20);
			 //Write_ADD_1Byte(0x00, 0x00);
	
			 Write_ADD_1Byte(0x08, YEARs);
			 Write_ADD_1Byte(0x07, MONTH);
			 Write_ADD_1Byte(0x05, DAY);
			 Write_ADD_1Byte(0x06, WEEK);

			 Write_ADD_1Byte(0x04, HOUR);
			 Write_ADD_1Byte(0x03, MINUTE);
			 Write_ADD_1Byte(0x02, SRCOND);
			
			 Write_ADD_1Byte(0x00, 0x00);

	}//end


// ---------- 读出,并显示时间 --------------//

  void PCF8563_Read_Display_Time(void)
    {
	    unsigned char HH, MM,SS=0,Century,Years,Month,Weeks,Days;
		unsigned char HH_shi,HH_ge, MM_shi,MM_ge,SS_ge,SS_shi;
		
		unsigned char year_shi,year_ge;
		unsigned char week_shi,week_ge;
		unsigned char day_shi,day_ge;
		unsigned char month_shi,month_ge;							   
			  //IIC1_Start();
			  //IIC1_Send_1Byte(0xa2);
			  //delay_us(5);
			  //IIC1_Send_1Byte(0x02);
			  //IIC1_Start();
			 // IIC1_Send_1Byte(0xa3);
			 //IIC1_Stop();
		//-------------- 读取各种 -------------------
			 Years = Read_ADD_1Byte(0x08);	 //	年
			 Weeks = Read_ADD_1Byte(0x06);	 //星期
			 Days= Read_ADD_1Byte(0x05);	 //日
			 Month = Read_ADD_1Byte(0x07);	 //日

	         HH = Read_ADD_1Byte(0x04);	 //时
			 delay_us(10);
			 MM = Read_ADD_1Byte(0x03);	 //分
			 SS = Read_ADD_1Byte(0x02);  //秒
		  //------------- 以下换算 ---------------------------
			 year_shi =  (Years&0xf0)>>4;
			 year_ge =	(Years&0x0f);

			 month_shi = (Month&0x10)>>4;
			 month_ge  =  Month&0x0f;

			 week_shi = 0;//Weeks&0x07;
			 week_ge = Weeks&0x07;

			 day_shi = (Days&0x30)>>4;
			 day_ge =  Days&0x0f;

			 HH_shi = ( (HH&0x3f)>>4 );	    //	 获得小时十位
			 HH_ge =  (HH&0x0f);		    //	 获得小时个位

			 MM_shi = ( (MM&0x70)>>4 );		 //	 获得分钟十位
			 MM_ge = (MM&0x0f);				 //	 获得分钟个位

			 SS_shi = ( (SS&0x70)>>4 );
			 SS_ge =  SS&0x0f;
	 //--------------------------------------------------------------------
		  Put_number( 20, 100, year_shi, Blue, Yellow );  //	年
		  Put_number( 28, 100, year_ge, Blue, Yellow );   //

		  Put_number( 40, 100, month_shi, Blue, Yellow );//月
		  Put_number( 48, 100, month_ge, Blue, Yellow );

		  Put_number( 60, 100, day_shi, Blue, Yellow );  //	日
		  Put_number( 68, 100, day_ge, Blue, Yellow );   //  

		  Put_number( 90, 100, week_shi, Blue, Yellow );  //	星期 
		  Put_number( 98, 100, week_ge, Blue, Yellow );  //


		  Put_number( 20, 130, HH_shi, Blue, Yellow );  //小时十位
		  Put_number( 28, 130, HH_ge, Blue, Yellow );   //小时个位

		  Put_number( 50, 130, MM_shi, Blue, Yellow );  //分钟个位
		  Put_number( 58, 130, MM_ge, Blue, Yellow );   //分钟个位

		  Put_number( 80, 130, SS_shi, Blue, Yellow );  // 秒个位
		  Put_number( 88, 130, SS_ge, Blue, Yellow );   // 秒个位

	}//END



 void delay_us(unsigned short x)
  {
	 unsigned short i,j;
	 for(i=0;i<x;i++)
	 for(j=0;j<900;j++);

  }



