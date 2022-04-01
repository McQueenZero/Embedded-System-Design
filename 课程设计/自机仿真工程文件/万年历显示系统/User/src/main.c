
#include "stm32f10x.h"
#include "string.h"
#include "LED_Config.h"
#include "LCD_ILI9325.h"
#include "Touch.h"
#include "KEYs_Config.h"
#include "Display.h"

//-----------------------------------------------------
#define  Buzzer_OFF	 GPIOB->BRR |= 0x0100	//把PB8设置为低电平
#define  Buzzer_ON   GPIOB->BSRR |= 0x0100	//把PB8设置为高电平
#define LED_light(x) ( GPIOD->BSRR |= 0x0004<<x ) //点亮某一颗LED
#define LED_Close(x) ( GPIOD->BRR |= 0x0004<<x )  //关闭某一颗LED


//-----------------------------------------------------
void initial(void);
unsigned char Week_cal(unsigned short, unsigned char, unsigned char);
unsigned char GetLunarCalendar(unsigned short, unsigned char, unsigned char);
void DateTime_n_Process(void);
void DateTime_Process(void);

unsigned char flag=0;	//时钟模式标识符
unsigned char alarmflag=0;	//闹钟标识符
short digt_nb=0;	//设置位标识符
unsigned char date=0;	//日期设置块标识符
unsigned char TOUCHinv=0;	//触摸屏按压自减（触摸逆）标识符
unsigned char TSJR=0;	//特殊节日标识符

short k;	
unsigned char KEYtime=0;	//按键按压时间

/*获取当前的编译(要更新时间必须编译)下载时间（系统时间）*/
const char gSystemTime[16]=__TIME__;	//编译器宏__TIME__，格式例"09 30 05",九点三十分零五秒
/*获取当前的编译(要更新日期必须编译)下载日期（系统日期）*/
const char gSystemDate[16]=__DATE__;	//编译器宏__DATE__，格式例"Mar 10 2021"，二零二一年三月十日

unsigned short year_n, month_n, day_n, week_n, hour_n, min_n, sec_n;	//自然时间
short year, month, day, week, hour, min, sec;	//显示时间
unsigned short digt_d[6]={0,0,0,0,0,0};	//时间设置数
unsigned short Nian, Yue, Ri;	//农历年月日

int main(void)
{
	
	int BGC;	//Background Color背景色，用于清除字符时使用
	int Font_FGC;	//日期、时间字体foreground Color前景色
	int Font_BGC;	//日期、时间字体Background Color背景色
	
	initial();	//先调用初始化函数,包括LED、蜂鸣器、LCD显示模块、按键、定时器、外部中断
	ILI9325_Initial();	//液晶屏驱动ILI9325初始化
	Touch_IO_init();	//LCD触摸模块初始化
	TIM_Cmd(TIM2, ENABLE);	//开启TIM2定时器
	
	/*gSystemTime为char，hour_n等为int，需要从ASCII码转换为int*/
	hour_n=(gSystemTime[0]-48)*10+gSystemTime[1]-48;
	min_n=(gSystemTime[3]-48)*10+gSystemTime[4]-48;
	sec_n=(gSystemTime[6]-48)*10+gSystemTime[7]-48;

	/*gSystemDate为char，year_n等为int，需要从ASCII码转换为int*/
	year_n=(gSystemDate[9]-48)*10+gSystemDate[10]-48;
	day_n=(gSystemDate[4]-48)*10+gSystemDate[5]-48;
	/*因为月份为英文字母，所以需要转换成数字*/
	if(strncmp(gSystemDate,"Jun",3)==0) month_n=1;
	if(strncmp(gSystemDate,"Feb",3)==0) month_n=2;
	if(strncmp(gSystemDate,"Mar",3)==0) month_n=3;
	if(strncmp(gSystemDate,"Apr",3)==0) month_n=4;
	if(strncmp(gSystemDate,"May",3)==0) month_n=5;
	if(strncmp(gSystemDate,"Jun",3)==0) month_n=6;
	if(strncmp(gSystemDate,"Jul",3)==0) month_n=7;
	if(strncmp(gSystemDate,"Aug",3)==0) month_n=8;
	if(strncmp(gSystemDate,"Sep",3)==0) month_n=9;
	if(strncmp(gSystemDate,"Oct",3)==0) month_n=10;
	if(strncmp(gSystemDate,"Nov",3)==0) month_n=11;
	if(strncmp(gSystemDate,"Dec",3)==0) month_n=12;

/*---------手动设置万年历系统自然时间---------*/
//	year_n=21; month_n=3; day_n=20; hour_n=9;
//	min_n=0; sec_n=0;	
/*--------------------------------------------*/

	hour=hour_n; min=min_n; sec=sec_n;	//初始化系统时间=自然时间 
	year=year_n; month=month_n; day=day_n;	//初始化系统日期=自然日期
	
	/*---颜色与背景设置---*/
	Font_BGC=Yellow;	//日期、时间背景色
	Font_FGC=Blue;	//日期、时间前景色
	BGC=Red;	//初始清屏色		
	
	Display_fixed(BGC, Font_FGC, Font_BGC);	//固定信息显示
	
	while(1)
	{	
		DateTime_n_Process();	//自然时钟、日期处理
		DateTime_Process();		//系统时钟、日期处理		
		
		Display_date(year, month, day, week, Font_FGC, Font_BGC);	//系统日期显示
		if(GetLunarCalendar(year,month,day)==1)	
			Display_lunardate(Nian, Yue, Ri, BGC, Font_FGC, Font_BGC);	//农历日期显示
		Display_jieqi(year, month, day, BGC, Font_FGC, Font_BGC);	//节气显示
		Display_jieri(year, month, day, week, Yue, Ri, BGC, Font_FGC, Font_BGC);	//节日显示		
	
		if(flag!=2)	//非时间设置状态，系统时间显示		
			Display_time(hour, min, sec, Font_FGC, Font_BGC);
		else	//时间设置状态，设定时间显示			
			Display_timeset(digt_d, Font_FGC, Font_BGC);
		
		Display_function(hour, min, sec, BGC, Black, White);	//显示屏功能指示	
		Display_digtnum(digt_nb, BGC, Font_FGC, Font_BGC);	//光标指示日期、时间设置位
		Display_datenum(digt_nb, BGC, Font_FGC, Font_BGC);	//正负号指示日期增减
		
		
		/*-------------按键KEY3扫描，选择日期、时间设置位-------------*/
		if(key3_state_check()==0)	//按下按键KEY3,选择设置哪一位
		{				
			delay_ms(50);	//消抖
			
			if(key3_state_check()==0)
			{			
				digt_nb=digt_nb-1;	//按一下KEY3左跳一个
				if(digt_nb<0) digt_nb=6;	//跳过第一个跳回第六个
				
				delay_ms(70);	//约0.5s计时
				if(key3_state_check()==0)	//长按KEY3两秒，系统时间设置为自然时间 
				{
					LED_Close(1);LED_Close(2);LED_Close(3);LED_Close(4);					
					KEYtime=KEYtime+1;
					LED_light(KEYtime);	//LEDx点亮指示按压时间
					if(KEYtime>4)
					{
						//LED流水点亮熄灭指示复位成功
						LED_light(1);delay(100);LED_light(2);delay(100);
						LED_light(3);delay(100);LED_light(4);delay(100);
						LED_Close(1);delay(100);LED_Close(2);delay(100);
						LED_Close(3);delay(100);LED_Close(4);delay(100);
						KEYtime=0; digt_nb=0;	//重置按压时间,设置位标识符
						year=year_n; month=month_n; day=day_n; week=week_n;
						sec=sec_n; min=min_n; hour=hour_n;	//复位
						flag=0;	//进入默认自然时钟模式
					}
				}				
			}

		}
		
		/*-------------触摸扫描，设置日期-------------*/
		if(Get_TP_PEN()) {					
			if(TOUCHinv==0){					
				switch(date){
					case 1: year++; break;
					case 2: month++; break;
					case 3: day++; break;
				}
			}
			else{					
				switch(date){
					case 1: year--; break;
					case 2: month--; break;
					case 3: day--; break;				
				}	
			}
			delay_ms(50);
		}		

		/*-------------按键KEY4扫描，设置时间-------------*/
		//设置闹钟时间步骤：先按KEY5开启闹钟，再按KEY3、KEY4设置闹钟时间，完后长按KEY3重置为自然时间
		//设置倒计时时间步骤：先按KEY3、KEY4设置倒计时时间，完后按KEY2开启倒计时，再按KEY2作暂停/恢复计时(重新计时需要再按KEY4，设置时间赋值给系统时间)
		//设置系统时间步骤：先按KEY3、KEY4设置系统时间，完后按KEY1开启系统时钟
		if(key4_state_check()==0)	//按下按键KEY4，选择设置0~9数据
		{
			delay_ms(50);	//消抖
				
			if(key4_state_check()==0)
			{
				flag=2;	//进入设置时间状态				
				digt_d[digt_nb-1]=digt_d[digt_nb-1]+1;	//按一下KEY4对应位数据自增
				if(digt_d[digt_nb-1]>9) digt_d[digt_nb-1]=0;	//自增过9置为0
				//闹钟开启时设置闹钟时间(不赋设置时间)
				//闹钟关闭时设置倒计时时间或系统时间(赋设置时间)
				if(alarmflag==0)
				{
					sec=digt_d[5-1]*10+digt_d[6-1];
					min=digt_d[3-1]*10+digt_d[4-1];
					hour=digt_d[1-1]*10+digt_d[2-1];			
				}				
			}
		}
			
		/*------按键KEY5扫描，按一下触摸日期自减/自增，按两下开启/关闭系统时钟闹钟------*/
		if(key5_state_check()==0)
		{
			delay_ms(50);	//消抖
				
			if(key5_state_check()==0)
			{
				if(TOUCHinv==0){
					TOUCHinv=1;		//触摸日期自减
				}
				else{
					if(alarmflag==0){
						alarmflag=1;	//闹钟开启
						LED_light(1);
					}
					else{
						alarmflag=0;	//闹钟关闭
						LED_Close(1);
					}					
					TOUCHinv=0;		//触摸日期自增
				}
			}
		}
	}

}


/*------------自然时钟、日期处理------------*/
void DateTime_n_Process(void)
{
	/*---自然时钟、日期进位---*/
	if(sec_n>59){sec_n=0; min_n++;}
	if(min_n>59){min_n=0; hour_n++;}
	if(hour_n>23){hour_n=0; day_n++;}
	if(month_n==2){
		if(year_n%4==0){
			if(day_n>29){day_n=1;month_n++;}
		}
		else{
			if(day_n>28){day_n=1;month_n++;}
		}
	}
	else if(month_n==1||month_n==3||month_n==5||month_n==7||month_n==8||month_n==10||month_n==12){
		if(day_n>31){day_n=1;month_n++;}
	}
	else{
		if(day_n>30){day_n=1;month_n++;}
	}
	if(month_n>12){month_n=1;year_n++;}
	if(year_n>99) year_n=0;
	if(week_n>7) week_n=1;
	week_n=Week_cal(year_n, month_n, day_n);	//同步星期数
	
}

/*------------系统时钟、日期处理------------*/
void DateTime_Process(void)
{
	/*---时钟进位及闹钟---*/
	if(flag==0)	//时间自增状态
	{		
		if(sec>59){sec=0; min++;}
		if(min>59){min=0; hour++;}
		if(hour>23){hour=0; day++; }
		
		if(alarmflag==1)	//闹钟（开启后每天都响）
		{
			if(sec==digt_d[5-1]*10+digt_d[6-1]&&
				min==digt_d[3-1]*10+digt_d[4-1]&&
				hour==digt_d[1-1]*10+digt_d[2-1])
			{
				for(k=0;k<6;k++)
				{
					Buzzer_ON;delay_ms(100);
					Buzzer_OFF;delay_ms(100);
				}						
			}
		}								
	}

	/*---时钟借位及倒计时闹钟---*/
	if(flag==3)	//时间自减状态
	{
		if(hour==0&&min==0&&sec==0)	//倒计时闹钟
		{
			for(k=0;k<6;k++)
			{
				Buzzer_ON;delay_ms(100);
				Buzzer_OFF;delay_ms(100);					
			}
				
			flag=2;	//进入设定时间状态
		}
		if(sec<0){sec=59; min=min-1;}
		if(min<0){min=59; hour=hour-1;}
		if(hour<0){hour=59;}
	
	}
		
	/*---日期进位或借位---*/
	if(TOUCHinv==0){	
		if(month==2){	//闰年二月情况
			if(year%4==0){
				if(day>29){day=1;month++;}
			}
			else{
				if(day>28){day=1;month++;}
			}
		}
		else if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
			if(day>31){day=1;month++;}	//大月
		}
		else{
			if(day>30){day=1;month++;}	//小月
		}
		if(month>12){month=1;year++;}	
		if(year>99) year=0;	
		if(week>7) week=1;
	}
	else{
		if((month-1)==2){	//上一月是闰年二月情况
			if(year%4==0){
				if(day<1){day=29;month--;}
			}
			else{
				if(day<1){day=28;month--;}
			}
		}
		else if((month-1)==1||(month-1)==3||(month-1)==5||(month-1)==7||(month-1)==8||(month-1)==10||(month-1)==0){
			if(day<1){day=31;month--;}	//大月
		}
		else{
			if(day<1){day=30;month--;}	//小月
		}
		if(month<1) {month=12;year--;}
		if(year<0) {year=99;}		
		if(week<1) week=7;				
	}
	week=Week_cal(year, month, day);	//同步星期数	
	
}
