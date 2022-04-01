/***************************************************
* 标题：显示函数（上层）                           *
* 作者：赵敏琨														 				 *
* 日期：2021年3月17日															 *
* 说明：各种不同功能块的显示函数									 *
***************************************************/

#include "LCD_ILI9325.h"

unsigned char Conver_jieqi(unsigned short, unsigned char, unsigned char);
unsigned char JieriG(unsigned char, unsigned char);
unsigned char JieriL(unsigned char, unsigned char);

extern unsigned char TSJR, flag, alarmflag, TOUCHinv, date;

/*------------------------------------固定信息显示------------------------------------*/
void Display_fixed(int BGC, int Font_FGC, int Font_BGC)
{
	LCD_Clear(BGC);	
	LCD_PutString32(24,20,"西北工業大學",Blue,White);	
	LCD_PutString(24,60,"自动化学院",Black,White);
	LCD_PutString(168,60,"赵敏琨",Black,White);
	LCD_PutString(24,96,"电子万年历",Blue,White);
	Draw_Line(5,5,5,315,Yellow);
	Draw_Line(5,5,235,5,Yellow);
	Draw_Line(235,5,235,315,Yellow);
	Draw_Line(5,315,235,315,Yellow);
	//农历固定信息
	LCD_PutString(24, 240, "农历", Font_FGC, Font_BGC);
	Put1616(104, 240, "年", Font_FGC, Font_BGC); 
	Put1616(168, 240, "月", Font_FGC, Font_BGC);
	//公历固定信息
	LCD_PutString( 168, 96, "星期", Font_FGC, Font_BGC );
	Put_number16x32(8, 128, 2, Font_FGC, Font_BGC);
	Put_number16x32(24, 128, 0, Font_FGC, Font_BGC);
	PutGB3232(72, 128, "年", Font_FGC, Font_BGC);
	PutGB3232(136, 128, "月", Font_FGC, Font_BGC);
	PutGB3232(200, 128, "日", Font_FGC, Font_BGC);
	PutGB3232(56, 184, "时", Font_FGC, Font_BGC);
	PutGB3232(120, 184, "分", Font_FGC, Font_BGC);
	PutGB3232(184, 184, "秒", Font_FGC, Font_BGC); 
	
}

/*------------------------------------系统（公历）日期显示------------------------------------*/
void Display_date(short year, short month, short day, short week, int Font_FGC, int Font_BGC)
{

	/*---年显示---*/
	Put_number16x32( 40, 128, year/10, Font_FGC, Font_BGC );  //年十位
	Put_number16x32( 56, 128, year%10, Font_FGC, Font_BGC );   //年个位
	/*---月显示---*/
	Put_number16x32( 104, 128, month/10, Font_FGC, Font_BGC );  //月十位
	Put_number16x32( 120, 128, month%10, Font_FGC, Font_BGC );   //月个位
	/*---日显示---*/	
	Put_number16x32( 168, 128, day/10, Font_FGC, Font_BGC );  // 日十位
	Put_number16x32( 184, 128, day%10, Font_FGC, Font_BGC );   // 日个位
	/*---星期显示---*/
	switch(week){
		case 1: Put1616( 200, 96, "一", Font_FGC, Font_BGC ); break;
		case 2: Put1616( 200, 96, "二", Font_FGC, Font_BGC ); break;
		case 3: Put1616( 200, 96, "三", Font_FGC, Font_BGC ); break;
		case 4: Put1616( 200, 96, "四", Font_FGC, Font_BGC ); break;
		case 5: Put1616( 200, 96, "五", Font_FGC, Font_BGC ); break;
		case 6: Put1616( 200, 96, "六", Font_FGC, Font_BGC ); break;
		case 7: Put1616( 200, 96, "日", Font_FGC, Font_BGC ); break;
	}	
	
}

/*------------------------------------系统时间显示------------------------------------*/
void Display_time(short hour, short min, short sec, int Font_FGC, int Font_BGC)
{
	/*---小时显示---*/
	Put_number16x32( 24, 184, hour/10, Font_FGC, Font_BGC );  //小时十位
	Put_number16x32( 40, 184, hour%10, Font_FGC, Font_BGC );   //小时个位
	/*---分钟显示---*/
	Put_number16x32( 88, 184, min/10, Font_FGC, Font_BGC );  //分钟十位
	Put_number16x32( 104, 184, min%10, Font_FGC, Font_BGC );   //分钟个位
	/*---秒显示---*/	
	Put_number16x32( 152, 184, sec/10, Font_FGC, Font_BGC );  // 秒十位
	Put_number16x32( 168, 184, sec%10, Font_FGC, Font_BGC );   // 秒个位		
	
}

/*------------------------------------设定时间显示------------------------------------*/
void Display_timeset(unsigned short digt_d[], int Font_FGC, int Font_BGC)
{
	Put_number16x32( 24, 184, digt_d[1-1], Font_FGC, Font_BGC );
	Put_number16x32( 40, 184, digt_d[2-1], Font_FGC, Font_BGC );
	Put_number16x32( 88, 184, digt_d[3-1], Font_FGC, Font_BGC );
	Put_number16x32( 104, 184, digt_d[4-1], Font_FGC, Font_BGC );	
	Put_number16x32( 152, 184, digt_d[5-1], Font_FGC, Font_BGC );
	Put_number16x32( 168, 184, digt_d[6-1], Font_FGC, Font_BGC );			
	
}

/*------------------------------------日期、时间设置位指示------------------------------------*/
void Display_digtnum(short digt_nb, int BGC, int Font_FGC, int Font_BGC)
{
	switch(digt_nb){ //光标指示正设置的位，显示一个“^”，消除上一个“^”
		case 1: LCD_PutChar8x16(44, 216, 0x5e, BGC, BGC); LCD_PutChar8x16(28, 216, 0x5e, Font_FGC, Font_BGC); LCD_PutChar8x16(116, 160, 0x5e, BGC, BGC); LCD_PutChar8x16(52, 160, 0x5e, Font_FGC, Font_BGC); break;
		case 2: LCD_PutChar8x16(92, 216, 0x5e, BGC, BGC); LCD_PutChar8x16(44, 216, 0x5e, Font_FGC, Font_BGC); LCD_PutChar8x16(116, 160, 0x5e, BGC, BGC); LCD_PutChar8x16(52, 160, 0x5e, Font_FGC, Font_BGC); break;
		case 3: LCD_PutChar8x16(108, 216, 0x5e, BGC, BGC); LCD_PutChar8x16(92, 216, 0x5e, Font_FGC, Font_BGC); LCD_PutChar8x16(180, 160, 0x5e, BGC, BGC); LCD_PutChar8x16(116, 160, 0x5e, Font_FGC, Font_BGC); break;
		case 4: LCD_PutChar8x16(156, 216, 0x5e, BGC, BGC); LCD_PutChar8x16(108, 216, 0x5e, Font_FGC, Font_BGC); LCD_PutChar8x16(180, 160, 0x5e, BGC, BGC); LCD_PutChar8x16(116, 160, 0x5e, Font_FGC, Font_BGC); break;
		case 5: LCD_PutChar8x16(172, 216, 0x5e, BGC, BGC); LCD_PutChar8x16(156, 216, 0x5e, Font_FGC, Font_BGC); LCD_PutChar8x16(52, 160, 0x5e, BGC, BGC); LCD_PutChar8x16(180, 160, 0x5e, Font_FGC, Font_BGC); break;
		case 6: LCD_PutChar8x16(28, 216, 0x5e, BGC, BGC); LCD_PutChar8x16(172, 216, 0x5e, Font_FGC, Font_BGC); LCD_PutChar8x16(52, 160, 0x5e, BGC, BGC); LCD_PutChar8x16(180, 160, 0x5e, Font_FGC, Font_BGC); break;
	}	
	if(digt_nb==0){
		LCD_PutChar8x16(44, 216, 0x5e, BGC, BGC); LCD_PutChar8x16(92, 216, 0x5e, BGC, BGC); LCD_PutChar8x16(108, 216, 0x5e, BGC, BGC);
		LCD_PutChar8x16(156, 216, 0x5e, BGC, BGC); LCD_PutChar8x16(172, 216, 0x5e, BGC, BGC); LCD_PutChar8x16(28, 216, 0x5e, BGC, BGC);
		LCD_PutChar8x16(116, 160, 0x5e, BGC, BGC); LCD_PutChar8x16(180, 160, 0x5e, BGC, BGC); LCD_PutChar8x16(52, 160, 0x5e, BGC, BGC); 
	}	
	
}

/*------------------------------------日期设置指示------------------------------------*/
void Display_datenum(short digt_nb, int BGC, int Font_FGC, int Font_BGC)
{
	if(TOUCHinv==0){
		switch((digt_nb+1)/2){	//指示设置日期自增
			case 1:	date=1; LCD_PutChar8x16(84, 160, '+', Font_FGC, Font_BGC); LCD_PutChar8x16(148, 160, '+', BGC, BGC); break;
			case 2:	date=2; LCD_PutChar8x16(148, 160, '+', Font_FGC, Font_BGC); LCD_PutChar8x16(212, 160, '+', BGC, BGC); break;
			case 3: date=3; LCD_PutChar8x16(212, 160, '+', Font_FGC, Font_BGC); LCD_PutChar8x16(84, 160, '+', BGC, BGC); break;
			case 0: date=0; LCD_PutChar8x16(84, 160, '+', BGC, BGC); LCD_PutChar8x16(148, 160, '+', BGC, BGC); LCD_PutChar8x16(212, 160, '+', BGC, BGC); break;
		}	
	}
	else{
		switch((digt_nb+1)/2){	//指示设置日期自减
			case 1:	date=1; LCD_PutChar8x16(84, 160, '-', Font_FGC, Font_BGC); LCD_PutChar8x16(148, 160, '-', BGC, BGC); break;
			case 2:	date=2; LCD_PutChar8x16(148, 160, '-', Font_FGC, Font_BGC); LCD_PutChar8x16(212, 160, '-', BGC, BGC); break;
			case 3: date=3; LCD_PutChar8x16(212, 160, '-', Font_FGC, Font_BGC); LCD_PutChar8x16(84, 160, '-', BGC, BGC); break;
			case 0: date=0; LCD_PutChar8x16(84, 160, '-', BGC, BGC); LCD_PutChar8x16(148, 160, '-', BGC, BGC); LCD_PutChar8x16(212, 160, '-', BGC, BGC); break;
		}
	}	
	
}

/*------------------------------------农历日期显示------------------------------------*/
void Display_lunardate(unsigned short Nian, unsigned short Yue, unsigned short Ri, int BGC, int Font_FGC, int Font_BGC)
{
	/*农历年干支编号转换*/
	unsigned char GanN=8, ZhiN=2;	//计数编号，初始化为1901辛丑年天干地支（定义：当年春节后的干支）	
	unsigned short Years_1901;
	
	Years_1901=Nian-1901;	//计算该年距农历1901年的年份数
	GanN=Years_1901%10+GanN;
	if(GanN>10) GanN=GanN-10;
	ZhiN=Years_1901%12+ZhiN;
	if(ZhiN>12) ZhiN=ZhiN-12;	
	
	/*---农历年显示---*/
	switch(GanN){
		case 1: Put1616(56, 240, "甲", Font_FGC, Font_BGC); break; case 2: Put1616(56, 240, "乙", Font_FGC, Font_BGC); break;
		case 3: Put1616(56, 240, "丙", Font_FGC, Font_BGC); break; case 4: Put1616(56, 240, "丁", Font_FGC, Font_BGC); break;
		case 5: Put1616(56, 240, "戊", Font_FGC, Font_BGC); break; case 6: Put1616(56, 240, "己", Font_FGC, Font_BGC); break;
		case 7: Put1616(56, 240, "庚", Font_FGC, Font_BGC); break; case 8: Put1616(56, 240, "辛", Font_FGC, Font_BGC); break;
		case 9: Put1616(56, 240, "壬", Font_FGC, Font_BGC); break; case 10: Put1616(56, 240, "癸", Font_FGC, Font_BGC); break;
	}
	switch(ZhiN){
		case 1: LCD_PutString(72, 240, "子鼠", Font_FGC, Font_BGC); break; case 2: LCD_PutString(72, 240, "丑牛", Font_FGC, Font_BGC); break;
		case 3: LCD_PutString(72, 240, "寅虎", Font_FGC, Font_BGC); break; case 4: LCD_PutString(72, 240, "卯兔", Font_FGC, Font_BGC); break;
		case 5: LCD_PutString(72, 240, "辰龙", Font_FGC, Font_BGC); break; case 6: LCD_PutString(72, 240, "巳蛇", Font_FGC, Font_BGC); break;
		case 7: LCD_PutString(72, 240, "午马", Font_FGC, Font_BGC); break; case 8: LCD_PutString(72, 240, "未羊", Font_FGC, Font_BGC); break;
		case 9: LCD_PutString(72, 240, "申猴", Font_FGC, Font_BGC); break; case 10: LCD_PutString(72, 240, "酉鸡", Font_FGC, Font_BGC); break;
		case 11: LCD_PutString(72, 240, "戌狗", Font_FGC, Font_BGC); break; case 12: LCD_PutString(72, 240, "亥猪", Font_FGC, Font_BGC); break;
	}
	/*---农历月显示---*/ 
	switch(Yue){
		case 1:	Put1616(152, 240, "正", Font_FGC, Font_BGC); break;
		case 2:	Put1616(152, 240, "二", Font_FGC, Font_BGC); break;
		case 3:	Put1616(152, 240, "三", Font_FGC, Font_BGC); break;
		case 4:	Put1616(152, 240, "四", Font_FGC, Font_BGC); break;
		case 5:	Put1616(152, 240, "五", Font_FGC, Font_BGC); break;
		case 6:	Put1616(152, 240, "六", Font_FGC, Font_BGC); break;
		case 7:	Put1616(152, 240, "七", Font_FGC, Font_BGC); break;
		case 8:	Put1616(152, 240, "八", Font_FGC, Font_BGC); break;
		case 9:	Put1616(152, 240, "九", Font_FGC, Font_BGC); break;
		case 10: Put1616(152, 240, "十", Font_FGC, Font_BGC); break;
		case 12: Put1616(152, 240, "腊", Font_FGC, Font_BGC); break;
		case 11: LCD_PutString(136, 240, "十一", Font_FGC, Font_BGC); break;
	}
	if(Yue!=11) Paint_Screen(136, 152, 240, 256, BGC);
	/*---农历日显示---*/	
	switch(Ri/10){
		case 0: Put1616(184, 240, "初", Font_FGC, Font_BGC); break;
		case 1: {
			if(Ri%10==0) Put1616(184, 240, "初", Font_FGC, Font_BGC); 
			else Put1616(184, 240, "十", Font_FGC, Font_BGC); 
			break;
		}
		case 2: {
			if(Ri%10==0) Put1616(184, 240, "二", Font_FGC, Font_BGC);
			else Put1616(184, 240, "廿", Font_FGC, Font_BGC); 
			break;
		}
		case 3: Put1616(184, 240, "三", Font_FGC, Font_BGC); break;
	}
	switch(Ri%10){
		case 1:	Put1616(200, 240, "一", Font_FGC, Font_BGC); break;
		case 2:	Put1616(200, 240, "二", Font_FGC, Font_BGC); break;
		case 3:	Put1616(200, 240, "三", Font_FGC, Font_BGC); break;
		case 4:	Put1616(200, 240, "四", Font_FGC, Font_BGC); break;
		case 5:	Put1616(200, 240, "五", Font_FGC, Font_BGC); break;
		case 6:	Put1616(200, 240, "六", Font_FGC, Font_BGC); break;
		case 7:	Put1616(200, 240, "七", Font_FGC, Font_BGC); break;
		case 8:	Put1616(200, 240, "八", Font_FGC, Font_BGC); break;
		case 9:	Put1616(200, 240, "九", Font_FGC, Font_BGC); break;
		case 0:	Put1616(200, 240, "十", Font_FGC, Font_BGC); break;
	}	
	
}

/*------------------------------------节气显示------------------------------------*/
void Display_jieqi(short year, short month, short day, int BGC, int Font_FGC, int Font_BGC)
{
	switch(Conver_jieqi(year,month,day)){
		case 24: Paint_Screen(120,152,78,94,BGC); break;
		case 0: LCD_PutString(120, 78, "小寒", Font_FGC, Font_BGC); break;
		case 1: LCD_PutString(120, 78, "大寒", Font_FGC, Font_BGC); break;
		case 2: LCD_PutString(120, 78, "立春", Font_FGC, Font_BGC); break;
		case 3: LCD_PutString(120, 78, "雨水", Font_FGC, Font_BGC); break;
		case 4: LCD_PutString(120, 78, "惊蛰", Font_FGC, Font_BGC); break;
		case 5: LCD_PutString(120, 78, "春分", Font_FGC, Font_BGC); break;
		case 6: LCD_PutString(120, 78, "清明", Font_FGC, Font_BGC); break;		
		case 7: LCD_PutString(120, 78, "谷雨", Font_FGC, Font_BGC); break;
		case 8: LCD_PutString(120, 78, "立夏", Font_FGC, Font_BGC); break;
		case 9: LCD_PutString(120, 78, "小满", Font_FGC, Font_BGC); break;
		case 10: LCD_PutString(120, 78, "芒种", Font_FGC, Font_BGC); break;
		case 11: LCD_PutString(120, 78, "夏至", Font_FGC, Font_BGC); break;
		case 12: LCD_PutString(120, 78, "小暑", Font_FGC, Font_BGC); break;
		case 13: LCD_PutString(120, 78, "大暑", Font_FGC, Font_BGC); break;
		case 14: LCD_PutString(120, 78, "立秋", Font_FGC, Font_BGC); break;
		case 15: LCD_PutString(120, 78, "处暑", Font_FGC, Font_BGC); break;
		case 16: LCD_PutString(120, 78, "白露", Font_FGC, Font_BGC); break;
		case 17: LCD_PutString(120, 78, "秋分", Font_FGC, Font_BGC); break;
		case 18: LCD_PutString(120, 78, "寒露", Font_FGC, Font_BGC); break;
		case 19: LCD_PutString(120, 78, "霜降", Font_FGC, Font_BGC); break;
		case 20: LCD_PutString(120, 78, "立冬", Font_FGC, Font_BGC); break;
		case 21: LCD_PutString(120, 78, "小雪", Font_FGC, Font_BGC); break;	
		case 22: LCD_PutString(120, 78, "大雪", Font_FGC, Font_BGC); break;
		case 23: LCD_PutString(120, 78, "冬至", Font_FGC, Font_BGC); break;			
	}	
	
}

/*------------------------------------节日显示------------------------------------*/
void Display_jieri(short year, short month, short day, short week, short Yue, short Ri, int BGC, int Font_FGC, int Font_BGC)
{
	switch(JieriG(month,day)){
		case 0: if(TSJR==0) Paint_Screen(72,168,284,308,BGC); break;	
		case 1:	LCD_PutString(104, 284, "元旦", Font_FGC, Font_BGC); break;
		case 2:	LCD_PutString(80, 284, "人民警察节", Font_FGC, Font_BGC); break;
		case 3:	LCD_PutString(96, 284, "情人节", Font_FGC, Font_BGC); break;
		case 4:	LCD_PutString(96, 284, "妇女节", Font_FGC, Font_BGC); break;
		case 5:	LCD_PutString(96, 284, "植树节", Font_FGC, Font_BGC); break;
		case 6:	LCD_PutString(72, 284, "消费者权益日", Font_FGC, Font_BGC); break;
		case 7:	LCD_PutString(96, 284, "愚人节", Font_FGC, Font_BGC); break;
		case 8:	LCD_PutString(96, 284, "劳动节", Font_FGC, Font_BGC); break;
		case 9:	LCD_PutString(96, 284, "青年节", Font_FGC, Font_BGC); break;
		case 10:	LCD_PutString(96, 284, "儿童节", Font_FGC, Font_BGC); break;
		case 11:	LCD_PutString(96, 284, "建党节", Font_FGC, Font_BGC); break;
		case 12:	LCD_PutString(96, 284, "建军节", Font_FGC, Font_BGC); break;
		case 13:	LCD_PutString(80, 284, "抗战胜利日", Font_FGC, Font_BGC); break;
		case 14:	LCD_PutString(96, 284, "教师节", Font_FGC, Font_BGC); break;
		case 15:	LCD_PutString(96, 284, "国庆节", Font_FGC, Font_BGC); break;
		case 16:	LCD_PutString(96, 284, "万圣夜", Font_FGC, Font_BGC); break;
		case 17:	LCD_PutString(96, 284, "万圣节", Font_FGC, Font_BGC); break;
		case 18:	LCD_PutString(80, 284, "国家公祭日", Font_FGC, Font_BGC); break;
		case 19:	LCD_PutString(96, 284, "平安夜", Font_FGC, Font_BGC); break;
		case 20:	LCD_PutString(96, 284, "圣诞节", Font_FGC, Font_BGC); break;
	}
	switch(JieriL(Yue,Ri)){
		case 0: if(TSJR==0) Paint_Screen(96,144,268,284,BGC); break;
		case 1:	LCD_PutString(104, 268, "春节", Font_FGC, Font_BGC); break;
		case 2:	LCD_PutString(96, 268, "元宵节", Font_FGC, Font_BGC); break;
		case 3:	LCD_PutString(96, 268, "端午节", Font_FGC, Font_BGC); break;
		case 4:	LCD_PutString(96, 268, "七夕节", Font_FGC, Font_BGC); break;
		case 5:	LCD_PutString(96, 268, "中元节", Font_FGC, Font_BGC); break;
		case 6:	LCD_PutString(96, 268, "中秋节", Font_FGC, Font_BGC); break;
		case 7:	LCD_PutString(96, 268, "重阳节", Font_FGC, Font_BGC); break;
		case 8:	LCD_PutString(96, 268, "腊八节", Font_FGC, Font_BGC); break;
		case 9:	LCD_PutString(104, 268, "除夕", Font_FGC, Font_BGC); break;
	}
	if(Conver_jieqi(year,month,day)==6) {TSJR=1; LCD_PutString(96, 268, "清明节", Font_FGC, Font_BGC);}
	else if(month==5&&day>7&&day<=14&&week==7)	{TSJR=1; LCD_PutString(96, 284, "母亲节", Font_FGC, Font_BGC);}
	else if(month==6&&day>14&&day<=21&&week==7) {TSJR=1; LCD_PutString(96, 284, "父亲节", Font_FGC, Font_BGC);}
	else if(month==11&&day>21&&day<=28&&week==4) {TSJR=1; LCD_PutString(96, 284, "感恩节", Font_FGC, Font_BGC);}
	else TSJR=0;
	
}

/*------------------------------------显示屏功能指示------------------------------------*/
void Display_function(short hour, short min, short sec, int BGC, int Font_FGC, int Font_BGC)
{
	switch(flag){
		case 1: {
			if(sec+min+hour==0) LCD_PutString(16,276,"计时器",Font_FGC,Font_BGC);
			else LCD_PutString(16,276,"暂||停",Font_FGC,Font_BGC); 
			break;
		}
		case 2: LCD_PutString(16,276,"设XX置",Font_FGC,Font_BGC); break;
		case 3: LCD_PutString(16,276,"定时器",Font_FGC,Font_BGC); break;
		default: Paint_Screen(16,72,276,292,BGC); break;			
	}
	if(alarmflag==1) LCD_PutString(176,276,"闹钟开",Font_FGC,Font_BGC);
	else LCD_PutString(176,276,"闹钟关",Font_FGC,Font_BGC);	
	
}
