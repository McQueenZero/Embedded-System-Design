/***************************************************
* 标题：16x32数字字模库                            *
* 作者：赵敏琨														 				 *
* 日期：2021年3月10日															 *
* 说明：包括全部所用到的16x32数字								 	 *
***************************************************/
 
 unsigned char font16[][64] = {
/*--  黑体，对应的点阵为：宽x高=16x32   --*/
/*--  文字:  0  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xE0,0x0F,0xF0,
0x1C,0x38,0x38,0x38,0x38,0x1C,0x30,0x1C,0x70,0x0C,0x70,0x0C,0x70,0x0C,0x70,0x0C,
0x70,0x0C,0x70,0x0C,0x70,0x0C,0x70,0x0C,0x70,0x0C,0x30,0x1C,0x38,0x1C,0x38,0x18,
0x1C,0x38,0x1F,0xF0,0x07,0xE0,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  1  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xC0,0x01,0xC0,
0x03,0xC0,0x07,0xC0,0x1D,0xC0,0x19,0xC0,0x11,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,
0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,
0x01,0xC0,0x01,0xC0,0x01,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  2  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x1F,0xF8,
0x3C,0x38,0x38,0x1C,0x70,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x18,0x00,0x38,0x00,0x38,
0x00,0x70,0x00,0xE0,0x00,0xC0,0x01,0xC0,0x03,0x80,0x07,0x00,0x0E,0x00,0x1C,0x00,
0x3C,0x00,0x3F,0xFC,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  3  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xE0,0x0F,0xF8,
0x1C,0x38,0x38,0x1C,0x30,0x1C,0x10,0x1C,0x00,0x1C,0x00,0x18,0x00,0x78,0x03,0xE0,
0x03,0xF0,0x00,0x78,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x10,0x0C,0x70,0x1C,0x38,0x1C,
0x3C,0x38,0x1F,0xF8,0x0F,0xE0,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  4  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x70,
0x00,0x70,0x00,0xF0,0x01,0xF0,0x01,0xB0,0x03,0xB0,0x07,0x30,0x0E,0x30,0x0C,0x30,
0x1C,0x30,0x38,0x30,0x30,0x30,0x70,0x30,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0x00,0x30,
0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  5  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xF8,0x1F,0xF8,
0x18,0x00,0x18,0x00,0x18,0x00,0x38,0x00,0x30,0x00,0x37,0xC0,0x3F,0xF0,0x78,0x78,
0x70,0x38,0x00,0x1C,0x00,0x1C,0x00,0x0C,0x00,0x0C,0x20,0x1C,0x60,0x1C,0x70,0x1C,
0x70,0x78,0x3F,0xF0,0x1F,0xE0,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  6  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0xE0,
0x01,0xC0,0x03,0x80,0x03,0x80,0x07,0x00,0x0E,0x00,0x0E,0x00,0x1F,0xF0,0x1F,0xF8,
0x3C,0x1C,0x38,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x38,0x0E,
0x3C,0x1C,0x1F,0xF8,0x0F,0xF0,0x01,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  7  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFE,0x7F,0xFE,
0x00,0x0E,0x00,0x1C,0x00,0x18,0x00,0x38,0x00,0x30,0x00,0x70,0x00,0x60,0x00,0xE0,
0x00,0xC0,0x01,0xC0,0x01,0xC0,0x01,0x80,0x03,0x80,0x03,0x80,0x03,0x00,0x07,0x00,
0x07,0x00,0x06,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  8  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x1F,0xF0,
0x38,0x38,0x30,0x1C,0x30,0x1C,0x30,0x1C,0x30,0x1C,0x38,0x38,0x3C,0x78,0x0F,0xE0,
0x1F,0xF0,0x3C,0x78,0x78,0x1C,0x70,0x1C,0x60,0x0C,0x60,0x0C,0x70,0x0C,0x70,0x1C,
0x78,0x3C,0x3F,0xF8,0x1F,0xF0,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  9  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x1F,0xF0,
0x3C,0x78,0x70,0x3C,0x70,0x1C,0x60,0x1C,0x60,0x1C,0x60,0x1C,0x60,0x1C,0x70,0x38,
0x78,0x78,0x3F,0xF8,0x1F,0xF0,0x00,0xE0,0x00,0xE0,0x01,0xC0,0x01,0xC0,0x03,0x80,
0x03,0x80,0x07,0x00,0x06,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

//比号:	  10
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x03,0x80,0x03,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0x80,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

//连字符-	  11
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFE,
0x7F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

//小数点	  12
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x38,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

};
 
