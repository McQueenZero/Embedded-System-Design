
#include "stm32f10x.h"
#include "string.h"
#include "LED_Config.h"
#include "LCD_ILI9325.h"
#include "Touch.h"
#include "KEYs_Config.h"
#include "Display.h"

//-----------------------------------------------------
#define  Buzzer_OFF	 GPIOB->BRR |= 0x0100	//��PB8����Ϊ�͵�ƽ
#define  Buzzer_ON   GPIOB->BSRR |= 0x0100	//��PB8����Ϊ�ߵ�ƽ
#define LED_light(x) ( GPIOD->BSRR |= 0x0004<<x ) //����ĳһ��LED
#define LED_Close(x) ( GPIOD->BRR |= 0x0004<<x )  //�ر�ĳһ��LED


//-----------------------------------------------------
void initial(void);
unsigned char Week_cal(unsigned short, unsigned char, unsigned char);
unsigned char GetLunarCalendar(unsigned short, unsigned char, unsigned char);
void DateTime_n_Process(void);
void DateTime_Process(void);

unsigned char flag=0;	//ʱ��ģʽ��ʶ��
unsigned char alarmflag=0;	//���ӱ�ʶ��
short digt_nb=0;	//����λ��ʶ��
unsigned char date=0;	//�������ÿ��ʶ��
unsigned char TOUCHinv=0;	//��������ѹ�Լ��������棩��ʶ��
unsigned char TSJR=0;	//������ձ�ʶ��

short k;	
unsigned char KEYtime=0;	//������ѹʱ��

/*��ȡ��ǰ�ı���(Ҫ����ʱ��������)����ʱ�䣨ϵͳʱ�䣩*/
const char gSystemTime[16]=__TIME__;	//��������__TIME__����ʽ��"09 30 05",�ŵ���ʮ��������
/*��ȡ��ǰ�ı���(Ҫ�������ڱ������)�������ڣ�ϵͳ���ڣ�*/
const char gSystemDate[16]=__DATE__;	//��������__DATE__����ʽ��"Mar 10 2021"�������һ������ʮ��

unsigned short year_n, month_n, day_n, week_n, hour_n, min_n, sec_n;	//��Ȼʱ��
short year, month, day, week, hour, min, sec;	//��ʾʱ��
unsigned short digt_d[6]={0,0,0,0,0,0};	//ʱ��������
unsigned short Nian, Yue, Ri;	//ũ��������

int main(void)
{
	
	int BGC;	//Background Color����ɫ����������ַ�ʱʹ��
	int Font_FGC;	//���ڡ�ʱ������foreground Colorǰ��ɫ
	int Font_BGC;	//���ڡ�ʱ������Background Color����ɫ
	
	initial();	//�ȵ��ó�ʼ������,����LED����������LCD��ʾģ�顢��������ʱ�����ⲿ�ж�
	ILI9325_Initial();	//Һ��������ILI9325��ʼ��
	Touch_IO_init();	//LCD����ģ���ʼ��
	TIM_Cmd(TIM2, ENABLE);	//����TIM2��ʱ��
	
	/*gSystemTimeΪchar��hour_n��Ϊint����Ҫ��ASCII��ת��Ϊint*/
	hour_n=(gSystemTime[0]-48)*10+gSystemTime[1]-48;
	min_n=(gSystemTime[3]-48)*10+gSystemTime[4]-48;
	sec_n=(gSystemTime[6]-48)*10+gSystemTime[7]-48;

	/*gSystemDateΪchar��year_n��Ϊint����Ҫ��ASCII��ת��Ϊint*/
	year_n=(gSystemDate[9]-48)*10+gSystemDate[10]-48;
	day_n=(gSystemDate[4]-48)*10+gSystemDate[5]-48;
	/*��Ϊ�·�ΪӢ����ĸ��������Ҫת��������*/
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

/*---------�ֶ�����������ϵͳ��Ȼʱ��---------*/
//	year_n=21; month_n=3; day_n=20; hour_n=9;
//	min_n=0; sec_n=0;	
/*--------------------------------------------*/

	hour=hour_n; min=min_n; sec=sec_n;	//��ʼ��ϵͳʱ��=��Ȼʱ�� 
	year=year_n; month=month_n; day=day_n;	//��ʼ��ϵͳ����=��Ȼ����
	
	/*---��ɫ�뱳������---*/
	Font_BGC=Yellow;	//���ڡ�ʱ�䱳��ɫ
	Font_FGC=Blue;	//���ڡ�ʱ��ǰ��ɫ
	BGC=Red;	//��ʼ����ɫ		
	
	Display_fixed(BGC, Font_FGC, Font_BGC);	//�̶���Ϣ��ʾ
	
	while(1)
	{	
		DateTime_n_Process();	//��Ȼʱ�ӡ����ڴ���
		DateTime_Process();		//ϵͳʱ�ӡ����ڴ���		
		
		Display_date(year, month, day, week, Font_FGC, Font_BGC);	//ϵͳ������ʾ
		if(GetLunarCalendar(year,month,day)==1)	
			Display_lunardate(Nian, Yue, Ri, BGC, Font_FGC, Font_BGC);	//ũ��������ʾ
		Display_jieqi(year, month, day, BGC, Font_FGC, Font_BGC);	//������ʾ
		Display_jieri(year, month, day, week, Yue, Ri, BGC, Font_FGC, Font_BGC);	//������ʾ		
	
		if(flag!=2)	//��ʱ������״̬��ϵͳʱ����ʾ		
			Display_time(hour, min, sec, Font_FGC, Font_BGC);
		else	//ʱ������״̬���趨ʱ����ʾ			
			Display_timeset(digt_d, Font_FGC, Font_BGC);
		
		Display_function(hour, min, sec, BGC, Black, White);	//��ʾ������ָʾ	
		Display_digtnum(digt_nb, BGC, Font_FGC, Font_BGC);	//���ָʾ���ڡ�ʱ������λ
		Display_datenum(digt_nb, BGC, Font_FGC, Font_BGC);	//������ָʾ��������
		
		
		/*-------------����KEY3ɨ�裬ѡ�����ڡ�ʱ������λ-------------*/
		if(key3_state_check()==0)	//���°���KEY3,ѡ��������һλ
		{				
			delay_ms(50);	//����
			
			if(key3_state_check()==0)
			{			
				digt_nb=digt_nb-1;	//��һ��KEY3����һ��
				if(digt_nb<0) digt_nb=6;	//������һ�����ص�����
				
				delay_ms(70);	//Լ0.5s��ʱ
				if(key3_state_check()==0)	//����KEY3���룬ϵͳʱ������Ϊ��Ȼʱ�� 
				{
					LED_Close(1);LED_Close(2);LED_Close(3);LED_Close(4);					
					KEYtime=KEYtime+1;
					LED_light(KEYtime);	//LEDx����ָʾ��ѹʱ��
					if(KEYtime>4)
					{
						//LED��ˮ����Ϩ��ָʾ��λ�ɹ�
						LED_light(1);delay(100);LED_light(2);delay(100);
						LED_light(3);delay(100);LED_light(4);delay(100);
						LED_Close(1);delay(100);LED_Close(2);delay(100);
						LED_Close(3);delay(100);LED_Close(4);delay(100);
						KEYtime=0; digt_nb=0;	//���ð�ѹʱ��,����λ��ʶ��
						year=year_n; month=month_n; day=day_n; week=week_n;
						sec=sec_n; min=min_n; hour=hour_n;	//��λ
						flag=0;	//����Ĭ����Ȼʱ��ģʽ
					}
				}				
			}

		}
		
		/*-------------����ɨ�裬��������-------------*/
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

		/*-------------����KEY4ɨ�裬����ʱ��-------------*/
		//��������ʱ�䲽�裺�Ȱ�KEY5�������ӣ��ٰ�KEY3��KEY4��������ʱ�䣬��󳤰�KEY3����Ϊ��Ȼʱ��
		//���õ���ʱʱ�䲽�裺�Ȱ�KEY3��KEY4���õ���ʱʱ�䣬���KEY2��������ʱ���ٰ�KEY2����ͣ/�ָ���ʱ(���¼�ʱ��Ҫ�ٰ�KEY4������ʱ�丳ֵ��ϵͳʱ��)
		//����ϵͳʱ�䲽�裺�Ȱ�KEY3��KEY4����ϵͳʱ�䣬���KEY1����ϵͳʱ��
		if(key4_state_check()==0)	//���°���KEY4��ѡ������0~9����
		{
			delay_ms(50);	//����
				
			if(key4_state_check()==0)
			{
				flag=2;	//��������ʱ��״̬				
				digt_d[digt_nb-1]=digt_d[digt_nb-1]+1;	//��һ��KEY4��Ӧλ��������
				if(digt_d[digt_nb-1]>9) digt_d[digt_nb-1]=0;	//������9��Ϊ0
				//���ӿ���ʱ��������ʱ��(��������ʱ��)
				//���ӹر�ʱ���õ���ʱʱ���ϵͳʱ��(������ʱ��)
				if(alarmflag==0)
				{
					sec=digt_d[5-1]*10+digt_d[6-1];
					min=digt_d[3-1]*10+digt_d[4-1];
					hour=digt_d[1-1]*10+digt_d[2-1];			
				}				
			}
		}
			
		/*------����KEY5ɨ�裬��һ�´��������Լ�/�����������¿���/�ر�ϵͳʱ������------*/
		if(key5_state_check()==0)
		{
			delay_ms(50);	//����
				
			if(key5_state_check()==0)
			{
				if(TOUCHinv==0){
					TOUCHinv=1;		//���������Լ�
				}
				else{
					if(alarmflag==0){
						alarmflag=1;	//���ӿ���
						LED_light(1);
					}
					else{
						alarmflag=0;	//���ӹر�
						LED_Close(1);
					}					
					TOUCHinv=0;		//������������
				}
			}
		}
	}

}


/*------------��Ȼʱ�ӡ����ڴ���------------*/
void DateTime_n_Process(void)
{
	/*---��Ȼʱ�ӡ����ڽ�λ---*/
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
	week_n=Week_cal(year_n, month_n, day_n);	//ͬ��������
	
}

/*------------ϵͳʱ�ӡ����ڴ���------------*/
void DateTime_Process(void)
{
	/*---ʱ�ӽ�λ������---*/
	if(flag==0)	//ʱ������״̬
	{		
		if(sec>59){sec=0; min++;}
		if(min>59){min=0; hour++;}
		if(hour>23){hour=0; day++; }
		
		if(alarmflag==1)	//���ӣ�������ÿ�춼�죩
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

	/*---ʱ�ӽ�λ������ʱ����---*/
	if(flag==3)	//ʱ���Լ�״̬
	{
		if(hour==0&&min==0&&sec==0)	//����ʱ����
		{
			for(k=0;k<6;k++)
			{
				Buzzer_ON;delay_ms(100);
				Buzzer_OFF;delay_ms(100);					
			}
				
			flag=2;	//�����趨ʱ��״̬
		}
		if(sec<0){sec=59; min=min-1;}
		if(min<0){min=59; hour=hour-1;}
		if(hour<0){hour=59;}
	
	}
		
	/*---���ڽ�λ���λ---*/
	if(TOUCHinv==0){	
		if(month==2){	//����������
			if(year%4==0){
				if(day>29){day=1;month++;}
			}
			else{
				if(day>28){day=1;month++;}
			}
		}
		else if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
			if(day>31){day=1;month++;}	//����
		}
		else{
			if(day>30){day=1;month++;}	//С��
		}
		if(month>12){month=1;year++;}	
		if(year>99) year=0;	
		if(week>7) week=1;
	}
	else{
		if((month-1)==2){	//��һ��������������
			if(year%4==0){
				if(day<1){day=29;month--;}
			}
			else{
				if(day<1){day=28;month--;}
			}
		}
		else if((month-1)==1||(month-1)==3||(month-1)==5||(month-1)==7||(month-1)==8||(month-1)==10||(month-1)==0){
			if(day<1){day=31;month--;}	//����
		}
		else{
			if(day<1){day=30;month--;}	//С��
		}
		if(month<1) {month=12;year--;}
		if(year<0) {year=99;}		
		if(week<1) week=7;				
	}
	week=Week_cal(year, month, day);	//ͬ��������	
	
}
