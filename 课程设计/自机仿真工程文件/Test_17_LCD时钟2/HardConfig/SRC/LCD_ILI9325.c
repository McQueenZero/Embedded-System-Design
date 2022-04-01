
#include "LCD_ILI9325.h"
#include "GB1616.h"
#include "sz8x16.h"
#include "8X16.h"
#include "GB3232.h"	//32*32汉字字模




 void LCD_IO_Init( void )
  { 										  
    GPIO_InitTypeDef  LCD_GPIO;
 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PD端口时钟
	
    LCD_GPIO.GPIO_Pin = GPIO_Pin_All;
    LCD_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    LCD_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOE, &LCD_GPIO);					 //根据设定参数初始化

    LCD_GPIO.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;	//指定引脚 
    LCD_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    LCD_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOC, &LCD_GPIO);					 //根据设定参数初始化		
		
    LCD_GPIO.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_12;	//指定引脚 
    LCD_GPIO.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    LCD_GPIO.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOD, &LCD_GPIO);					 //根据设定参数初始化	



 } //end

//---------- ili9325 ------------//
 void ILI9325_Initial(void)
 { 

	 RD_1;
	 TFT_Rst_1;
	 delays(15); 
	 TFT_Rst_0;
	 delays(15);
	 TFT_Rst_1;
	 delays(12);
	 
	 Write_Cmd_Data(0x0000,0x0001);
	 
	Write_Cmd(0xCF);  
	Write_Data(0x00); 
	Write_Data(0xD9); 
	Write_Data(0X30); 
	 
	Write_Cmd(0xED);  
	Write_Data(0x64); 
	Write_Data(0x03); 
	Write_Data(0X12); 
	Write_Data(0X81); 
	 
	Write_Cmd(0xE8);  
	Write_Data(0x85); 
	Write_Data(0x10); 
	Write_Data(0x78); 
	 
	Write_Cmd(0xCB);  
	Write_Data(0x39); 
	Write_Data(0x2C); 
	Write_Data(0x00); 
	Write_Data(0x34); 
	Write_Data(0x02); 
	 
	Write_Cmd(0xF7);  
	Write_Data(0x20); 
	 
	Write_Cmd(0xEA);  
	Write_Data(0x00); 
	Write_Data(0x00); 
	 
	Write_Cmd(0xC0);    //Power control 
	Write_Data(0x21);   //VRH[5:0] 
	 
	Write_Cmd(0xC1);    //Power control 
	Write_Data(0x12);   //SAP[2:0];BT[3:0] 
	 
	Write_Cmd(0xC5);    //VCM control 
	Write_Data(0x32); 
	Write_Data(0x3C); 
	 
	Write_Cmd(0xC7);    //VCM control2 
	Write_Data(0XC1); 
	 
	Write_Cmd(0x36);    // Memory Access Control 
	Write_Data(0x08); 
	 
	Write_Cmd(0x3A);   
	Write_Data(0x55); 
	
	Write_Cmd(0xB1);   
	Write_Data(0x00);   
	Write_Data(0x18); 
	 
	Write_Cmd(0xB6);    // Display Function Control 
	Write_Data(0x0A); 
	Write_Data(0xA2); 
	
	 
	 
	Write_Cmd(0xF2);    // 3Gamma Function Disable 
	Write_Data(0x00); 
	 
	Write_Cmd(0x26);    //Gamma curve selected 
	Write_Data(0x01); 
	 
	Write_Cmd(0xE0);    //Set Gamma 
	Write_Data(0x0F); 
	Write_Data(0x20); 
	Write_Data(0x1E); 
	Write_Data(0x09); 
	Write_Data(0x12); 
	Write_Data(0x0B); 
	Write_Data(0x50); 
	Write_Data(0XBA); 
	Write_Data(0x44); 
	Write_Data(0x09); 
	Write_Data(0x14); 
	Write_Data(0x05); 
	Write_Data(0x23); 
	Write_Data(0x21); 
	Write_Data(0x00); 
	 
	Write_Cmd(0XE1);    //Set Gamma 
	Write_Data(0x00); 
	Write_Data(0x19); 
	Write_Data(0x19); 
	Write_Data(0x00); 
	Write_Data(0x12); 
	Write_Data(0x07); 
	Write_Data(0x2D); 
	Write_Data(0x28); 
	Write_Data(0x3F); 
	Write_Data(0x02); 
	Write_Data(0x0A); 
	Write_Data(0x08); 
	Write_Data(0x25); 
	Write_Data(0x2D); 
	Write_Data(0x0F); 
	 
	Write_Cmd(0x11);    //Exit Sleep 
	delays(120); 
	Write_Cmd(0x29);    //Display on 
  	
	LCD_Clear(Red);
 }



//========??????=========//

 void Write_Cmd_Data (uint16_t cmd, uint16_t data)
  {
			Write_Cmd(cmd);
      Write_Data(data);

  }


 void  Write_Data_U16(uint16_t y)
 {
	  CS_0;            //CS=0
		RS_1;            //RS=0    
		Data_IO = y;
		RW_0;            //RW=0
		RW_1;             //RW=1
		CS_1;             //CS=1

 }



//====================== ??? ==========================//

 void Write_Cmd(uint16_t CMD)
 {  
	  CS_0;            //CS=0
		RS_0;            //RS=0	    
		Data_IO = CMD;	
		RW_0;            //RW=0
		RW_1;             //RW=1
		CS_1;             //CS=1

 }

//============= =================//

 void Write_Data(uint16_t DATA)
 {
    CS_0;     //CS=0
	  RS_1;      //RS=1;
	  Data_IO = DATA;
	  RW_0;      //RW=0
 	  RW_1;      //RW=1
	  CS_1; 
 } 

 
 //清屏函数
//Color:要清屏的填充色
void LCD_Clear(u16 Color)
{
	u32 index=0;      
	Write_Cmd(0x2c);      //开始写入GRAM	 	  
	for(index=0;index<76800;index++)
	{
		Write_Data(Color);    
	}
} 

  
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_SetPos(x,x+1,y,y+1);//设置光标位置 
	//Write_Cmd(0x2c);//开始写入GRAM
	Write_Data(color); 
}  
 

  void Paint_Screen(u16 x1,u16 x2,u16 y1,u16 y2, u16 bColor )
  {
       unsigned int i,j;
				
				LCD_SetPos(x1,x2-1,y1,y2-1); 	
				for (j=y1;j<y2;j++)	//--- 320x240 
					{				  
					 for (i=x1;i<x2;i++)
						{							  
							Write_Data(bColor);
						}
					}				
   }//end

	 
//--------------TFT set pots-----------//
 void LCD_SetPos(u16 x1,u16 x2 ,u16 y1,u16 y2)
  {
		
	Write_Cmd(0x2a);
	Write_Data(x1 >> 8);
	Write_Data(x1 & 0x00ff);
	Write_Data(x2 >> 8);
	Write_Data(x2 & 0x00ff);

	Write_Cmd(0x2b);
	Write_Data(y1 >> 8);
	Write_Data(y1 & 0x00ff);			 
	Write_Data(y2 >> 8);
	Write_Data(y2 & 0x00ff);		
		
		Write_Cmd(0x2c); 
  }

 //-----delay-----
 void delays(uint16_t count)
 {
    u16 i,j;                                                                                
    for(i=0;i<(count*2);i++)                                                                    
     {
	    for(j=0;j<2500;j++);
     }                                                                                     
 }




//显示8x16数据
void Put_number(unsigned short x, unsigned short  y, unsigned char value, unsigned int fColor,unsigned int bColor)

{	unsigned int i,j;
    unsigned short m;

	LCD_SetPos(x, x+8-1,y, y+16-1);

     for(i=0;i<16;i++)
	  {
		 m=font8[value][i];
		for(j=0;j<8;j++)
		{
		  if( (m&0x80)==0x80 ) 
		   {
		     Write_Data_U16(fColor);
			}
		 else 
		  {
			 Write_Data_U16(bColor);
			}
			  m<<=1;
		 } 
	   }	
}

//------------显示1616汉字-------------------------
void Put1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor)
 {
	unsigned int i,j,k;
	unsigned short m;

		LCD_SetPos(x, x+16-1,y, y+16-1);//LCD_SetPos(x, x+16-1,y, y+16-1);

	for (k=0;k<20;k++)      //64标示自建汉字库中的个数20，循环查询内码
	{ 
	  if ((GB_16[k].Index[0]==c[0])&&(GB_16[k].Index[1]==c[1]))
	  { 
    	for(i=0;i<32;i++) 
			{
					 m = GB_16[k].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((m&0x80)==0x80) 
							{
								Write_Data_U16(fColor);
							 }
						else 
							{
							Write_Data_U16(bColor);
							 }
							m<<=1;
					} 
		  }
		}  
	  }	
}


/****--------------------------------------------------------------*****
****--------------------------显示汉字8x16---------------------------*****
****---------------------------------------------------------------****/


void LCD_PutChar8x16(unsigned short x, unsigned short y,unsigned char c, unsigned int fColor, unsigned int bColor)
 {
    unsigned int i,j;
 LCD_SetPos(x,x+8-1,y,y+16-1);
     for(i=0; i<16;i++) 
	  {
		unsigned char m=Font8x16[c*16+i];
		for(j=0;j<8;j++) 
		 {
			if((m&0x80)==0x80) 
			{
				Write_Data_U16(fColor);
			 }
			else 
			 {
				Write_Data_U16(bColor);
			  }
			m<<=1;
		  }
		}
 }
 
/****--------------------------------------------------------------*****
****--------------------------显示字符---------------------------*****
****---------------------------------------------------------------****/

	 void LCD_PutChar(unsigned short x, unsigned short y,unsigned char c, unsigned int fColor, unsigned int bColor) 
	  {
				LCD_PutChar8x16( x, y, c, fColor, bColor );
	  }


/****--------------------------------------------------------------*****
****--------------------------显示字符串和汉字---------------------*****
****---------------------------------------------------------------****/
void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor)
 {
	unsigned char l=0;
	  while(*s) 
	  {
		if( *s < 0x80) 
		    {
			  LCD_PutChar(x+l*8,y,*s,fColor,bColor);
			  s++;l++;
			}
		else
		    {
			  Put1616(x+l*8,y,(unsigned char*)s,fColor,bColor);
			  s+=2;l+=2;
			}
		}
 }//end



/****--------------------------------------------------------------*****
****--------------------------显示汉字32*32------------------------*****
****---------------------------------------------------------------****/


void PutGB3232(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor)
 {
       unsigned int i,j,k;
	   unsigned short m;  //=GB_32[k].Msk[i];
	LCD_SetPos(x,  x+32-1,y, y+32-1);

	for (k=0;k<15;k++) //15表示自建汉字库中的个数，循环查询内码
	{ 
	  if ((GB_32[k].Index[0]==c[0])&&(GB_32[k].Index[1]==c[1]))
	  { 
    	for(i=0;i<128;i++) 
		{ 
		 	m=GB_32[k].Msk[i];
		   for(j=0;j<8;j++) 
		   {	
			 if((m&0x80)==0x80)
			  {
				Write_Data_U16(fColor);
			  }
			 else 
			   {
				Write_Data_U16(bColor);
			   }
			  m<<=1;
			} 
		  }
		}  
	 }	
 } //end 

 /****--------------------------------------------------------------*****
****--------------------------显示字符串3232---------------------------*****
****---------------------------------------------------------------****/
void LCD_PutString32(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor)
 {
	 unsigned char l=0;
	 while(*s)
	  {
	
		PutGB3232(x+l*8,y,(unsigned char*)s,fColor,bColor);
		s+=2;
		l+=4;
	  }
	 
 }

//----------------------------------------------
 void Draw_Line(u16 x1,u16 y1,u16 x2, u16 y2,u16 color )
 {
    u16 i,xi;
		u16 dxy;
	  u16 y_point;

    if((y2>y1)&&(x2>x1))
		{			
			dxy = (y2-y1)/(x2-x1);
			//if((y2-y1)<(x2-x1))
			//{
					for(i=0;i<x2-x1;i++)	
					{				
							y_point = dxy*(x1+i) + y1;						
							xi = x1+i;									
											
							LCD_SetPos(xi,xi+1, y_point,y_point+1);
							Write_Data(color);		
					}	
			//}		
			//else
			//{
				
			//}			
		}
		else
		{
				if((y2>y1)&&(x2<=x1))
				{
					for(i=0;i<y2-y1;i++)	
					{				
							y_point = i + y1;						
							xi = x1;									
											
							LCD_SetPos(xi,xi+1, y_point,y_point+1);//LCD_SetPos(xi, y_point);
							Write_Data(color);		
					}							
				}
				else
				{
					if((y2<=y1)&&(x2>x1))
					{
						for(i=0;i<x2-x1;i++)	
						{				
								y_point = y1;						
								xi = x1+i;									
												
								LCD_SetPos(xi,xi+1, y_point,y_point+1);//LCD_SetPos(xi, y_point);
								Write_Data(color);		
						}					
					}
				}
		}
	//----------------------- 
 }
 





