
#include "stm32f10x.h"

 void LCD_IO_Init( void );
 void ILI9325_Initial(void);
  void Write_Data(uint16_t DATA);
	 void Write_Cmd(uint16_t CMD);
	  void Write_Cmd_Data (uint16_t cmd, uint16_t data);
		 void  Write_Data_U16(uint16_t y);
		  u16 LCD_RD_DATA(void);
void LCD_Clear(u16 Color);
void LCD_DrawPoint(u16 x,u16 y,u16 color);
 void Draw_Line(u16 x1,u16 y1,u16 x2, u16 y2,u16 color );

 void LCD_SetPos(u16 x1,u16 x2 ,u16 y1,u16 y2);
 void delays(uint16_t count);
   void Paint_Screen(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2, uint16_t bColor );
 void delays(uint16_t count);
 
 void Put_number(unsigned short x, unsigned short  y, unsigned char value, unsigned int fColor,unsigned int bColor);
 void Put1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
 void LCD_PutChar8x16(unsigned short x, unsigned short y,unsigned char c, unsigned int fColor, unsigned int bColor);
 	 void LCD_PutChar(unsigned short x, unsigned short y,unsigned char c, unsigned int fColor, unsigned int bColor) ;
	 void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor);
	 void PutGB3232(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
	 void LCD_PutString32(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor);

  #define TFT_RS  0x0001     //PC0
  #define TFT_RW  0x0002     //PC1
  #define TFT_RD  0x0004	 //PC2
  #define TFT_CS  0x1000     //PD12
  #define RESET   0x0400     //PD10 

  #define  RS_1  GPIOC->BSRR |=TFT_RS  //PC0
  #define  RS_0  GPIOC->BRR |=TFT_RS

  #define  RW_1  GPIOC->BSRR |=TFT_RW	//PC1
  #define  RW_0  GPIOC->BRR |=TFT_RW

  #define  RD_1  GPIOC->BSRR |=TFT_RD	//PC2
  #define  RD_0  GPIOC->BRR |=TFT_RD

  #define  CS_1  GPIOD->BSRR |=TFT_CS  //PD12
  #define  CS_0  GPIOD->BRR |=TFT_CS

  #define  TFT_Rst_1  GPIOD->BSRR |=RESET	//PD10
  #define  TFT_Rst_0  GPIOD->BRR |=RESET

  #define  Data_IO   GPIOE->ODR
	

#define WINDOW_XADDR_START	0x0050 // Horizontal Start Address Set
#define WINDOW_XADDR_END	0x0051 // Horizontal End Address Set
#define WINDOW_YADDR_START	0x0052 // Vertical Start Address Set
#define WINDOW_YADDR_END	0x0053 // Vertical End Address Set
#define GRAM_XADDR		    0x0020 // GRAM Horizontal Address Set
#define GRAM_YADDR		    0x0021 // GRAM Vertical Address Set
#define GRAMWR 			    0x0022 // memory write

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

