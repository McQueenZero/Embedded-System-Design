#include "stm32f10x.h"
#include "Nixietube.h"
#include "KEYs_Config.h"

#define  Buzzer_OFF	 GPIOB->BRR |= 0x0100	//��PB8����Ϊ�͵�ƽ
#define  Buzzer_ON   GPIOB->BSRR |= 0x0100	//��PB8����Ϊ�ߵ�ƽ
#define LED_light(x) ( GPIOD->BSRR |= 0x0004<<x ) //����ĳһ��LED
#define LED_Close(x) ( GPIOD->BRR |= 0x0004<<x )  //�ر�ĳһ��LED

void initial(void);

unsigned int flag=0;	//ʱ��ģʽ��ʶ��
unsigned int alarmflag=0;	//���ӱ�ʶ��
int num=1;
const u8 gSystemTime[16]=__TIME__;	//��ȡ��ǰ�ı���(Ҫ����ʱ��������)����ʱ�䣨ϵͳʱ�䣩
int hour_n; int min_n; int sec_n;	//��Ȼʱ��
int hour; int min; int sec;	//��ʾʱ��
u8 digt[6]={0,0,0,0,0,0};	//ʱ��������
 
int main(void)
{
	unsigned int tmp=0;
	int i;	
	int KEYtime=0;	//������ѹʱ��
	initial();	//��ʼ������

	//gSystemTimeΪchar��hour_n��Ϊint����Ҫ��ASCII��ת��Ϊint
	hour_n=(gSystemTime[0]-48)*10+gSystemTime[1]-48;
	min_n=(gSystemTime[3]-48)*10+gSystemTime[4]-48;
	sec_n=(gSystemTime[6]-48)*10+gSystemTime[7]-48;
	hour=hour_n; min=min_n; sec=sec_n;	//��ʼ��ϵͳʱ��=��Ȼʱ��
	
	TIM_Cmd(TIM2, ENABLE);
  
	while(1)
	{
		/*---��Ȼʱ�ӽ�λ---*/
		if(sec_n>59){sec_n=0; min_n=min_n+1;}
		if(min_n>59){min_n=0; hour_n=hour_n+1;}
		if(hour_n>23){hour_n=0;}			
		/*------------ϵͳʱ��ʱ��------------*/
		/*---ʱ�ӽ�λ������---*/
		if(flag==0)	//ʱ������״̬
		{		
			if(sec>59){sec=0; min=min+1;}
			if(min>59){min=0; hour=hour+1;}
			if(hour>23){hour=0;}
			if(alarmflag==1)	//����
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
		/*---ʱ�ӽ�λ������ʱ����---*/
		if(flag==3)	//ʱ���Լ�״̬
		{
			if(sec<0){sec=59; min=min-1;}
			if(min<0){min=59; hour=hour-1;}
			if(hour<0){hour=59;}
			if(hour==0&&min==0&&sec==0)	//����ʱ����
			{
				for(i=0;i<6;i++)
				{
					Buzzer_ON;delay_ms(100);
					Buzzer_OFF;delay_ms(100);					
				}
				flag=2;	//�����趨ʱ��״̬
			}
		}
		/*-----ϵͳʱ����ʾ-----*/	
		if(flag!=2)	//��ʱ������״̬
		{
			/*---����ʾ---*/	
			if(sec<=9){
				Nixietube_light(6, sec);delay(1);
				Nixietube_light(5, 0);delay(1);
			}
			else{ 
				Nixietube_light(5, sec/10);delay(1); //ʮλ
				Nixietube_light(6, sec%10);delay(1); //��λ
			}	
			/*---������ʾ---*/
			if(min<=9){
				Nixietube_light(4, min);delay(1);
				Nixietube_light(3, 0);delay(1);
			}
			else{ 
				Nixietube_light(3, min/10);delay(1); //ʮλ
				Nixietube_light(4, min%10);delay(1); //��λ
			}		
			/*---Сʱ��ʾ---*/
			if(hour<=9){
				Nixietube_light(2, hour);delay(1);
				Nixietube_light(1, 0);delay(1);
			}
			else{ 
				Nixietube_light(1, hour/10);delay(1); //ʮλ
				Nixietube_light(2, hour%10);delay(1); //��λ
			}
		}
		/*-----�趨ʱ����ʾ-----*/
		else	//ʱ������״̬
		{
				Nixietube_light(1,digt[1-1]);delay(1);
				Nixietube_light(2,digt[2-1]);delay(1);
				Nixietube_light(3,digt[3-1]);delay(1);
				Nixietube_light(4,digt[4-1]);delay(1);
				Nixietube_light(5,digt[5-1]);delay(1);
				Nixietube_light(6,digt[6-1]);delay(1);			
		}
		/*---����ʱ���֣���С���㳣��---*/
		if(key3_state_check()!=0)
		{
			Nixietube_light(2,10);delay(1);	//�ڶ�λС����
			Nixietube_light(4,10);delay(1);	//����λС����
		}				
		
		/*------����KEY2ɨ��,��ʱ��ͣ���ָ�����������ʱ------*/
		if(key2_state_check()==0)	
		{				
			delay_ms(50);	//����
				
			if(key2_state_check()==0)
			{
				if(flag==0||flag==3)
				{
					tmp=flag;
					flag=1;	//������ͣ״̬
				}
				else if(flag==2)
				{
					flag=3;	//��������ʱ
				}
				else
				{
					flag=tmp;	//�ָ���ʱ״̬
				}	
			}

		}
			
		/*-------------����KEY3��KEY4ɨ�裬�趨ʱ��-------------*/
		if(key3_state_check()==0)	//���°���KEY3,ѡ��������һλ
		{				
			delay_ms(50);	//����
			
			if(key3_state_check()==0)
			{			
				num=num-1;	//��һ��KEY3����һ��
				if(num<1) num=6;	//������һ�����ص�����
				Nixietube_index(num);	//����ָʾλС����
				delay_ms(70);	//Լ1s��ʱ
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
						KEYtime=0;	//���ð�ѹʱ��
						sec=sec_n; min=min_n; hour=hour_n;	//��λ
						flag=0;	//����Ĭ����Ȼʱ��ģʽ
					}
				}				
			}

		}

		//��������ʱ�䲽�裺�Ȱ�KEY5�������ӣ��ٰ�KEY3��KEY4��������ʱ�䣬��󳤰�KEY3����Ϊ��Ȼʱ��
		//���õ���ʱʱ�䲽�裺�Ȱ�KEY3��KEY4���õ���ʱʱ�䣬���KEY2��������ʱ���ٰ�KEY2����ͣ/�ָ���ʱ(���¼�ʱ��Ҫ�ٰ�KEY4������ʱ�丳ֵ��ϵͳʱ��)
		//����ϵͳʱ�䲽�裺�Ȱ�KEY3��KEY4����ϵͳʱ�䣬���KEY1����ϵͳʱ��
		if(key4_state_check()==0)	//���°���KEY4��ѡ������0~9����
		{
			delay_ms(50);	//����
				
			if(key4_state_check()==0)
			{
				flag=2;	//��������ʱ��״̬				
				digt[num-1]=digt[num-1]+1;	//��һ��KEY4��Ӧλ��������
				if(digt[num-1]>9) digt[num-1]=0;	//������9��Ϊ0
				//���ӿ���ʱ��������ʱ��(��������ʱ��)
				//���ӹر�ʱ���õ���ʱʱ���ϵͳʱ��(������ʱ��)
				if(alarmflag==0)
				{
					sec=digt[5-1]*10+digt[6-1];
					min=digt[3-1]*10+digt[4-1];
					hour=digt[1-1]*10+digt[2-1];			
				}				
			}
		}
			
		/*------����KEY5ɨ�裬����/�ر�ϵͳʱ������------*/
		if(key5_state_check()==0)
		{
			delay_ms(50);	//����
				
			if(key5_state_check()==0)
			{
				if(alarmflag==0){
					alarmflag=1;	//���ӿ���
					LED_light(1);
				}
				else{
					alarmflag=0;	//���ӹر�
					LED_Close(1);
				}
			}
		}
	}
	
}
