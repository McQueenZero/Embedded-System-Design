#include "stm32f10x.h"
#include "Nixietube.h"
#include "KEYs_Config.h"

#define  Buzzer_OFF	 GPIOB->BRR |= 0x0100	//把PB8设置为低电平
#define  Buzzer_ON   GPIOB->BSRR |= 0x0100	//把PB8设置为高电平
#define LED_light(x) ( GPIOD->BSRR |= 0x0004<<x ) //点亮某一颗LED
#define LED_Close(x) ( GPIOD->BRR |= 0x0004<<x )  //关闭某一颗LED

void initial(void);

unsigned int flag=0;	//时钟模式标识符
unsigned int alarmflag=0;	//闹钟标识符
int num=1;
const u8 gSystemTime[16]=__TIME__;	//获取当前的编译(要更新时间必须编译)下载时间（系统时间）
int hour_n; int min_n; int sec_n;	//自然时间
int hour; int min; int sec;	//显示时间
u8 digt[6]={0,0,0,0,0,0};	//时间设置数
 
int main(void)
{
	unsigned int tmp=0;
	int i;	
	int KEYtime=0;	//按键按压时间
	initial();	//初始化函数

	//gSystemTime为char，hour_n等为int，需要从ASCII码转换为int
	hour_n=(gSystemTime[0]-48)*10+gSystemTime[1]-48;
	min_n=(gSystemTime[3]-48)*10+gSystemTime[4]-48;
	sec_n=(gSystemTime[6]-48)*10+gSystemTime[7]-48;
	hour=hour_n; min=min_n; sec=sec_n;	//初始化系统时间=自然时间
	
	TIM_Cmd(TIM2, ENABLE);
  
	while(1)
	{
		/*---自然时钟进位---*/
		if(sec_n>59){sec_n=0; min_n=min_n+1;}
		if(min_n>59){min_n=0; hour_n=hour_n+1;}
		if(hour_n>23){hour_n=0;}			
		/*------------系统时钟时间------------*/
		/*---时钟进位及闹钟---*/
		if(flag==0)	//时间自增状态
		{		
			if(sec>59){sec=0; min=min+1;}
			if(min>59){min=0; hour=hour+1;}
			if(hour>23){hour=0;}
			if(alarmflag==1)	//闹钟
			{
				if(sec==digt[5-1]*10+digt[6-1]&&
					min==digt[3-1]*10+digt[4-1]&&
					hour==digt[1-1]*10+digt[2-1])
				{
					for(i=0;i<6;i++)
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
			if(sec<0){sec=59; min=min-1;}
			if(min<0){min=59; hour=hour-1;}
			if(hour<0){hour=59;}
			if(hour==0&&min==0&&sec==0)	//倒计时闹钟
			{
				for(i=0;i<6;i++)
				{
					Buzzer_ON;delay_ms(100);
					Buzzer_OFF;delay_ms(100);					
				}
				flag=2;	//进入设定时间状态
			}
		}
		/*-----系统时间显示-----*/	
		if(flag!=2)	//非时间设置状态
		{
			/*---秒显示---*/	
			Nixietube_light(5, sec/10);delay(1); //十位
			Nixietube_light(6, sec%10);delay(1); //个位
			/*---分钟显示---*/
			Nixietube_light(3, min/10);delay(1); //十位
			Nixietube_light(4, min%10);delay(1); //个位
			/*---小时显示---*/
			Nixietube_light(1, hour/10);delay(1); //十位
			Nixietube_light(2, hour%10);delay(1); //个位
		}
		/*-----设定时间显示-----*/
		else	//时间设置状态
		{
			Nixietube_light(1,digt[1-1]);delay(1);
			Nixietube_light(2,digt[2-1]);delay(1);
			Nixietube_light(3,digt[3-1]);delay(1);
			Nixietube_light(4,digt[4-1]);delay(1);
			Nixietube_light(5,digt[5-1]);delay(1);
			Nixietube_light(6,digt[6-1]);delay(1);			
		}
		/*---划分时：分：秒小数点常亮---*/
		if(key3_state_check()!=0)
		{
			Nixietube_light(2,10);delay(1);	//第二位小数点
			Nixietube_light(4,10);delay(1);	//第四位小数点
		}				
		
		/*------按键KEY2扫描,计时暂停、恢复、开启倒计时------*/
		if(key2_state_check()==0)	
		{				
			delay_ms(50);	//消抖
				
			if(key2_state_check()==0)
			{
				if(flag==0||flag==3)
				{
					tmp=flag;
					flag=1;	//进入暂停状态
				}
				else if(flag==2)
				{
					flag=3;	//开启倒计时
				}
				else
				{
					flag=tmp;	//恢复计时状态
				}	
			}

		}
			
		/*-------------按键KEY3、KEY4扫描，设定时间-------------*/
		if(key3_state_check()==0)	//按下按键KEY3,选择设置哪一位
		{				
			delay_ms(50);	//消抖
			
			if(key3_state_check()==0)
			{			
				num=num-1;	//按一下KEY3左跳一个
				if(num<1) num=6;	//跳过第一个跳回第六个
				Nixietube_index(num);	//点亮指示位小数点
				delay_ms(70);	//约1s延时
				if(key3_state_check()==0)	//长按KEY3五秒，系统时间设置为自然时间 
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
						KEYtime=0;	//重置按压时间
						sec=sec_n; min=min_n; hour=hour_n;	//复位
						flag=0;	//进入默认自然时钟模式
					}
				}				
			}

		}

		//设置闹钟时间步骤：先按KEY5开启闹钟，再按KEY3、KEY4设置闹钟时间，完后长按KEY3重置为自然时间
		//设置倒计时时间步骤：先按KEY3、KEY4设置倒计时时间，完后按KEY2开启倒计时，再按KEY2作暂停/恢复计时(重新计时需要再按KEY4，设置时间赋值给系统时间)
		//设置系统时间步骤：先按KEY3、KEY4设置系统时间，完后按KEY1开启系统时钟
		if(key4_state_check()==0)	//按下按键KEY4，选择设置0~9数据
		{
			delay_ms(50);	//消抖
				
			if(key4_state_check()==0)
			{
				flag=2;	//进入设置时间状态				
				digt[num-1]=digt[num-1]+1;	//按一下KEY4对应位数据自增
				if(digt[num-1]>9) digt[num-1]=0;	//自增过9置为0
				//闹钟开启时设置闹钟时间(不赋设置时间)
				//闹钟关闭时设置倒计时时间或系统时间(赋设置时间)
				if(alarmflag==0)
				{
					sec=digt[5-1]*10+digt[6-1];
					min=digt[3-1]*10+digt[4-1];
					hour=digt[1-1]*10+digt[2-1];			
				}				
			}
		}
			
		/*------按键KEY5扫描，开启/关闭系统时钟闹钟------*/
		if(key5_state_check()==0)
		{
			delay_ms(50);	//消抖
				
			if(key5_state_check()==0)
			{
				if(alarmflag==0){
					alarmflag=1;	//闹钟开启
					LED_light(1);
				}
				else{
					alarmflag=0;	//闹钟关闭
					LED_Close(1);
				}
			}
		}
	}
	
}
