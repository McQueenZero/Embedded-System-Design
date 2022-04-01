
#include "stdlib.h"
#include "math.h"
#include "Touch.h"
//#include "Graphic.h"
#include "LCD_ILI9325.h" 
 // PA5    SPI1_SCK
 // PA6    SPI1_MISO   TP_OUT
 // PA7    SPI1_MOSI   TP_IN
 // PB0    TP_CS
 // PF11   TP_PEN
 // PA4    TP_BUSY
 
#define CLK_0  (GPIOA->BRR |= 0x0020) //PA5
#define CLK_1  (GPIOA->BSRR |= 0x0020)
#define SPI_MO_0  (GPIOA->BRR |= 0x0080)//PA7
#define SPI_MO_1  (GPIOA->BSRR |= 0x0080)
#define SPI_MI  (GPIOA->IDR&0x0040) //PA6
#define SPI_CS_0  (GPIOC->BRR|= 0x0020) //PC5
#define SPI_CS_1  (GPIOC->BSRR|= 0x0020)  

//-------------------------------------------------------

 #define ERR_Range 50
//------------------------------------------------------- 
static void delays2(u16 x);
static  u8 Get_TP_PEN(void);
static u8 Get_TP_BUSY(void);
static void SPI_sendByte(u8 data)	;
static u16 SPI_readByte(void);
 void SPI_TOUCH_Read_XY(u16 *x,u16 *y);

static void delays2(u16 x)
 {
   u16 i,j;
		for(i=0;i<300;i++)
			{
				for(j=0;j<x;j++);
			}
 }
 
 void Touch_IO_init(void)
 {
 			GPIO_InitTypeDef  Touch_IO;
		//----------------------   GPIO   --------------------------------------
				//  ----- PA ----------
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	
	 
	 //-------------- MI ------------------------------
			//	GPIOA->CRL &= 0xF0FFFFFF; 
				//GPIOA->CRL |= 0x08000000;
	 
			Touch_IO.GPIO_Pin = GPIO_Pin_6;	 
			Touch_IO.GPIO_Mode = GPIO_Mode_IPU; 			//				
			GPIO_Init(GPIOA, &Touch_IO);
	 //---------------------------------------
			Touch_IO.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7;	 
			Touch_IO.GPIO_Mode = GPIO_Mode_Out_PP; 			//		//
			Touch_IO.GPIO_Speed = GPIO_Speed_50MHz; 	//		
			GPIO_Init(GPIOA, &Touch_IO);
	 		 	 		 
	 //---------------------------------------------------
			Touch_IO.GPIO_Pin = GPIO_Pin_4;
			Touch_IO.GPIO_Mode = GPIO_Mode_IPU; 			//	
			GPIO_Init(GPIOC, &Touch_IO);		 
//-------------------- PC5 CS ------------------------
			Touch_IO.GPIO_Pin = GPIO_Pin_5;
			Touch_IO.GPIO_Mode = GPIO_Mode_Out_PP; 			//
			Touch_IO.GPIO_Speed = GPIO_Speed_50MHz; 	//		
			GPIO_Init(GPIOC, &Touch_IO);	
//------------------- PEN PB0 ----------------------------
			Touch_IO.GPIO_Pin = GPIO_Pin_0;
			Touch_IO.GPIO_Mode = GPIO_Mode_IPU; 			//		
			GPIO_Init(GPIOB, &Touch_IO);	
			
			CLK_0;
			SPI_CS_0;
			SPI_MO_0;
			
 }


 
void SPI_sendByte(u8 chr)
{
	
   u8 k;
    CLK_0;
    for(k=0; k<8; k++)
	  {       
			if(chr&0x80)
        SPI_MO_1;
			else 
				SPI_MO_0;
			
        CLK_0;
        delays2(1);
        CLK_1;
        delays2(1);
			
			 chr <<= 1;
     }
 }
 //--------------------------------
 u16 SPI_readByte(void)
{
    u8 k;
    u16 ret = 0;
    for(k=0; k<16; k++)
	  {
        ret <<= 1;
        CLK_0;
        delays2(1);
        CLK_1;
        delays2(1);
        if(SPI_MI)
            ret++;
    }
    return ret>>4;
}


 //----------- pen PF11 -----------------
static  u8 Get_TP_PEN(void)
   {
		 if( (GPIOB->IDR&0x0001))
       return(0);
		 else
			return(1); 
   }

//--------  busy -----------------  
static u8 Get_TP_BUSY(void)
   {
		 if( (GPIOA->IDR&0x0010) == 0x0010)
       return(1);
		 else
			return(0); 
   }
 	 
 //----------------------------------------
 void SPI_TOUCH_Read_XY(u16 *x,u16 *y)
 {
		SPI_CS_0;

		SPI_sendByte(0x90);

      //  CLK_1;
       // delays2(1);
      //  CLK_0;	 
		*x = SPI_readByte();
	 
		SPI_sendByte(0xD0);

      //  CLK_1;
      //  delays2(1);
      //  CLK_0;	 
		*y = SPI_readByte();
		SPI_CS_1;

 }
//----------------------------------------------
 void get_XY(u16 *a,u16 *b)
 {
		u8 i,j,k;		
	  u16 xx[5],yy[5];	
		u16 temp1,temp2;
	 
		j=4; //比较次数	 
			 for(i=0;i<5;i++) //连续读5个数据
				{
						SPI_TOUCH_Read_XY(&xx[i],&yy[i]);				
				}
	  //-------------------------
			 for(k=0;k<4;k++)
			 {
					for(i=0;i<j;i++)
					{
							if(xx[k]>xx[i+k+1])
							{
									temp1 = xx[k+i];	//取小的
								
									xx[k+1] = xx[k];	
									xx[k] = temp1;							
							}
					}
			  	j -= 1;	
			 }		
			temp1 = (xx[1]+xx[2]+xx[3])/3; //
			temp2 = (yy[1]+yy[2]+yy[3])/3;	
			*a= temp1;
		  *b= temp2;	 		 
 }
//----------------------------------
 void TP_getXY(u16 *x, u16 *y)
 {
		
		u16 x_data1,y_data1,x_data2,y_data2;	 
		*x = 0;
		*y = 0;
	//if( Get_TP_PEN() ) 
		//{
	 //----------------------------------------
			get_XY(&x_data1,&y_data1);
			get_XY(&x_data2,&y_data2);
			 
		if( ( (x_data2<=x_data1&&x_data1<x_data2+ERR_Range)||(x_data1<=x_data2&&x_data2<x_data1+ERR_Range)) \
					&&((y_data2<=y_data1&&y_data1<y_data2+ERR_Range)||(y_data1<=y_data2&&y_data2<y_data1+ERR_Range)) )	 
			{
					*x += (x_data1+x_data2)/2;
					*y += (y_data1+y_data2)/2;

			}
		//}
 }

//-----------------------------------

struct TP_point{
						
								u16 x;
								u16 y;
								float x_fac;
								float y_fac;
								float x_off;
								float y_off;

							}tp_point;


//----------------------------------------------
		signed short tp_value[4][2]; 
 void TP_adjust(void)
 {

	  u8 step=0;
		u8 cnt=0;
	  u8 tp_adj=0;
	 
		u16 delt1,delt2;
		float faction;
	  u32 temp_1,temp_2;
	  
	 tp_point.x_fac=0;
	 tp_point.y_fac=0;
	 tp_point.x_off=0;
	 tp_point.y_off=0;

	while(1)
	{
		switch(step)
		{
			case 0:{
								display_adj_cusor(cnt+1);//xn,yn十字光标
								 while(1)
									{		 
										delays2(1000);							
											if( Get_TP_PEN() ) //
												{			
														Paint_Screen(0,240,0,320, Red );
														
														TP_getXY(&tp_point.x, &tp_point.y);	
														tp_value[cnt][0] = tp_point.x;
														tp_value[cnt][1] = tp_point.y;
														
														//delays2(500);
														cnt +=1;														
													  step = 1;
													  break;
												}																																					
									}				
								break;
							}
			case 1:{							
								while(1)
								{
									delays2(500);
									if( Get_TP_PEN()==0 )//手放开后
									{
										display_adj_cusor(cnt+1);
										
										break;
									}																	
								}
														
								if(cnt == 4 )
									{
										cnt = 0;
										step = 2;
									}									
								else{step = 0;}
								break;
							}
			case 2:{								
									temp_1 = abs(tp_value[0][0]-tp_value[1][0]);//x1-x2
									temp_2 = abs(tp_value[0][1]-tp_value[2][1]);//y1-y2
									temp_1 *=temp_1;
									temp_2 *=temp_2;
									delt1 = sqrt(temp_1+temp_2); //1,3的距离

									temp_1 = abs(tp_value[1][0]-tp_value[3][0]);//x2-x4
									temp_2 = abs(tp_value[1][1]-tp_value[3][1]);//y2-y4
									temp_1 *=temp_1;
									temp_2 *=temp_2;
									delt2 = sqrt(temp_1+temp_2); //2,4的距离				
									
									faction = (float)delt1/delt2;// 对角线误差
									if((faction<0.8)||(faction>1.05))//不合格
									{
										step = 0;
									}				
									else{step=3;}
								break;
							}
			case 3:{
								temp_1 = abs(tp_value[1][0]-tp_value[2][0]);//x2-x3
								temp_2 = abs(tp_value[1][1]-tp_value[2][1]);//y2-y3
								temp_1 *=temp_1;
								temp_2 *=temp_2;
								delt1 = sqrt(temp_1+temp_2); //2,3的距离

								temp_1 = abs(tp_value[0][0]-tp_value[3][0]);//x1-x4
								temp_2 = abs(tp_value[0][1]-tp_value[3][1]);//y1-y4
								temp_1 *=temp_1;
								temp_2 *=temp_2;
								delt2 = sqrt(temp_1+temp_2); //1,4的距离				
								
								faction = (float)delt1/delt2;// 对边误差
								if((faction<0.8)||(faction>1.051))//不合格
								{
										step = 0;
								}	
								
							 tp_point.y_fac =(float)300/(tp_value[3][0]-tp_value[0][0]);//xfac
							 tp_point.x_fac =(float)220/(tp_value[2][1]-tp_value[0][1]);//yfac
							
							 tp_point.x_off=(320- tp_point.x_fac*(tp_value[1][0]+tp_value[0][0]))/2;// xoff
							 tp_point.y_off=(240- tp_point.y_fac*(tp_value[2][1]+tp_value[0][1]))/2;// yoff					
								
								return;
							}							
						default:break;
			}
	 	}	
 }

 //------  显示屏分辨率 ---------------------
void Touch_pos_map(u16 *LCD_x, u16 *LCD_y) 
 {
  u16 tp_x,tp_y,temp; 
	 
	 while(1)
	 {
		 delays2(8);	
		 if( Get_TP_PEN() )
		 {
			TP_getXY(&tp_x, &tp_y);
			temp= tp_point.x_fac*(float)tp_x + tp_point.x_off;
			temp= tp_point.y_fac*(float)tp_y + tp_point.y_off;			 
			 
			*LCD_y = tp_point.x_fac*(float)tp_x + tp_point.x_off;
			*LCD_x= tp_point.y_fac*(float)tp_y + tp_point.y_off;	
			// LCD_DrawPoint(*LCD_x,*LCD_y,Blue);
			break;
		 }
		}
		 
 }
 
//-----------------------------------------------
 void display_adj_cusor(u8 x)
 {
	  switch(x-1)
			{
			 case 0:{ //x1,y1 左上角
								Draw_Line(10,20, 31, 20,Blue );//heng
								Draw_Line(20,10, 20, 31,Blue );	//shu
				 
								Draw_Line(18,20, 23, 20,White );//heng
								Draw_Line(20,18, 20, 23,White );		//shu 				 

								break;
							}
			case 1: {// x2,y2右上角
									Draw_Line(210,20, 231, 20,Blue );//heng
									Draw_Line(220,10, 220, 31,Blue );	//shu
										 
									Draw_Line(218,20, 223, 20,White );//heng
									Draw_Line(220,18, 220, 23,White );	//shu				

								break;
							}	
			case 2: {//x3,y3
									Draw_Line(210,300, 231, 300,Blue );//heng
									Draw_Line(220,290, 220, 311,Blue );	//shu
										 
									Draw_Line(218,300, 223, 300,White );//heng
									Draw_Line(220,298, 220, 303,White );	//shu	
								break;
							}		
			case 3: { //x4,y4
									Draw_Line(10,300, 31, 300,Blue );//heng
									Draw_Line(20,290, 20, 311,Blue );	//shu
										 
									Draw_Line(18,300, 23, 300,White );//heng
									Draw_Line(20,298, 20, 303,White );	//shu
								break;
							}								
			default:break;
//--------------------------------------------
			}
 }
 
 
 
 
