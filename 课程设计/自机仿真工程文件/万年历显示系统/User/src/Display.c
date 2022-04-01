/***************************************************
* ���⣺��ʾ�������ϲ㣩                           *
* ���ߣ�������														 				 *
* ���ڣ�2021��3��17��															 *
* ˵�������ֲ�ͬ���ܿ����ʾ����									 *
***************************************************/

#include "LCD_ILI9325.h"

unsigned char Conver_jieqi(unsigned short, unsigned char, unsigned char);
unsigned char JieriG(unsigned char, unsigned char);
unsigned char JieriL(unsigned char, unsigned char);

extern unsigned char TSJR, flag, alarmflag, TOUCHinv, date;

/*------------------------------------�̶���Ϣ��ʾ------------------------------------*/
void Display_fixed(int BGC, int Font_FGC, int Font_BGC)
{
	LCD_Clear(BGC);	
	LCD_PutString32(24,20,"�������I��W",Blue,White);	
	LCD_PutString(24,60,"�Զ���ѧԺ",Black,White);
	LCD_PutString(168,60,"������",Black,White);
	LCD_PutString(24,96,"����������",Blue,White);
	Draw_Line(5,5,5,315,Yellow);
	Draw_Line(5,5,235,5,Yellow);
	Draw_Line(235,5,235,315,Yellow);
	Draw_Line(5,315,235,315,Yellow);
	//ũ���̶���Ϣ
	LCD_PutString(24, 240, "ũ��", Font_FGC, Font_BGC);
	Put1616(104, 240, "��", Font_FGC, Font_BGC); 
	Put1616(168, 240, "��", Font_FGC, Font_BGC);
	//�����̶���Ϣ
	LCD_PutString( 168, 96, "����", Font_FGC, Font_BGC );
	Put_number16x32(8, 128, 2, Font_FGC, Font_BGC);
	Put_number16x32(24, 128, 0, Font_FGC, Font_BGC);
	PutGB3232(72, 128, "��", Font_FGC, Font_BGC);
	PutGB3232(136, 128, "��", Font_FGC, Font_BGC);
	PutGB3232(200, 128, "��", Font_FGC, Font_BGC);
	PutGB3232(56, 184, "ʱ", Font_FGC, Font_BGC);
	PutGB3232(120, 184, "��", Font_FGC, Font_BGC);
	PutGB3232(184, 184, "��", Font_FGC, Font_BGC); 
	
}

/*------------------------------------ϵͳ��������������ʾ------------------------------------*/
void Display_date(short year, short month, short day, short week, int Font_FGC, int Font_BGC)
{

	/*---����ʾ---*/
	Put_number16x32( 40, 128, year/10, Font_FGC, Font_BGC );  //��ʮλ
	Put_number16x32( 56, 128, year%10, Font_FGC, Font_BGC );   //���λ
	/*---����ʾ---*/
	Put_number16x32( 104, 128, month/10, Font_FGC, Font_BGC );  //��ʮλ
	Put_number16x32( 120, 128, month%10, Font_FGC, Font_BGC );   //�¸�λ
	/*---����ʾ---*/	
	Put_number16x32( 168, 128, day/10, Font_FGC, Font_BGC );  // ��ʮλ
	Put_number16x32( 184, 128, day%10, Font_FGC, Font_BGC );   // �ո�λ
	/*---������ʾ---*/
	switch(week){
		case 1: Put1616( 200, 96, "һ", Font_FGC, Font_BGC ); break;
		case 2: Put1616( 200, 96, "��", Font_FGC, Font_BGC ); break;
		case 3: Put1616( 200, 96, "��", Font_FGC, Font_BGC ); break;
		case 4: Put1616( 200, 96, "��", Font_FGC, Font_BGC ); break;
		case 5: Put1616( 200, 96, "��", Font_FGC, Font_BGC ); break;
		case 6: Put1616( 200, 96, "��", Font_FGC, Font_BGC ); break;
		case 7: Put1616( 200, 96, "��", Font_FGC, Font_BGC ); break;
	}	
	
}

/*------------------------------------ϵͳʱ����ʾ------------------------------------*/
void Display_time(short hour, short min, short sec, int Font_FGC, int Font_BGC)
{
	/*---Сʱ��ʾ---*/
	Put_number16x32( 24, 184, hour/10, Font_FGC, Font_BGC );  //Сʱʮλ
	Put_number16x32( 40, 184, hour%10, Font_FGC, Font_BGC );   //Сʱ��λ
	/*---������ʾ---*/
	Put_number16x32( 88, 184, min/10, Font_FGC, Font_BGC );  //����ʮλ
	Put_number16x32( 104, 184, min%10, Font_FGC, Font_BGC );   //���Ӹ�λ
	/*---����ʾ---*/	
	Put_number16x32( 152, 184, sec/10, Font_FGC, Font_BGC );  // ��ʮλ
	Put_number16x32( 168, 184, sec%10, Font_FGC, Font_BGC );   // ���λ		
	
}

/*------------------------------------�趨ʱ����ʾ------------------------------------*/
void Display_timeset(unsigned short digt_d[], int Font_FGC, int Font_BGC)
{
	Put_number16x32( 24, 184, digt_d[1-1], Font_FGC, Font_BGC );
	Put_number16x32( 40, 184, digt_d[2-1], Font_FGC, Font_BGC );
	Put_number16x32( 88, 184, digt_d[3-1], Font_FGC, Font_BGC );
	Put_number16x32( 104, 184, digt_d[4-1], Font_FGC, Font_BGC );	
	Put_number16x32( 152, 184, digt_d[5-1], Font_FGC, Font_BGC );
	Put_number16x32( 168, 184, digt_d[6-1], Font_FGC, Font_BGC );			
	
}

/*------------------------------------���ڡ�ʱ������λָʾ------------------------------------*/
void Display_digtnum(short digt_nb, int BGC, int Font_FGC, int Font_BGC)
{
	switch(digt_nb){ //���ָʾ�����õ�λ����ʾһ����^����������һ����^��
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

/*------------------------------------��������ָʾ------------------------------------*/
void Display_datenum(short digt_nb, int BGC, int Font_FGC, int Font_BGC)
{
	if(TOUCHinv==0){
		switch((digt_nb+1)/2){	//ָʾ������������
			case 1:	date=1; LCD_PutChar8x16(84, 160, '+', Font_FGC, Font_BGC); LCD_PutChar8x16(148, 160, '+', BGC, BGC); break;
			case 2:	date=2; LCD_PutChar8x16(148, 160, '+', Font_FGC, Font_BGC); LCD_PutChar8x16(212, 160, '+', BGC, BGC); break;
			case 3: date=3; LCD_PutChar8x16(212, 160, '+', Font_FGC, Font_BGC); LCD_PutChar8x16(84, 160, '+', BGC, BGC); break;
			case 0: date=0; LCD_PutChar8x16(84, 160, '+', BGC, BGC); LCD_PutChar8x16(148, 160, '+', BGC, BGC); LCD_PutChar8x16(212, 160, '+', BGC, BGC); break;
		}	
	}
	else{
		switch((digt_nb+1)/2){	//ָʾ���������Լ�
			case 1:	date=1; LCD_PutChar8x16(84, 160, '-', Font_FGC, Font_BGC); LCD_PutChar8x16(148, 160, '-', BGC, BGC); break;
			case 2:	date=2; LCD_PutChar8x16(148, 160, '-', Font_FGC, Font_BGC); LCD_PutChar8x16(212, 160, '-', BGC, BGC); break;
			case 3: date=3; LCD_PutChar8x16(212, 160, '-', Font_FGC, Font_BGC); LCD_PutChar8x16(84, 160, '-', BGC, BGC); break;
			case 0: date=0; LCD_PutChar8x16(84, 160, '-', BGC, BGC); LCD_PutChar8x16(148, 160, '-', BGC, BGC); LCD_PutChar8x16(212, 160, '-', BGC, BGC); break;
		}
	}	
	
}

/*------------------------------------ũ��������ʾ------------------------------------*/
void Display_lunardate(unsigned short Nian, unsigned short Yue, unsigned short Ri, int BGC, int Font_FGC, int Font_BGC)
{
	/*ũ�����֧���ת��*/
	unsigned char GanN=8, ZhiN=2;	//������ţ���ʼ��Ϊ1901��������ɵ�֧�����壺���괺�ں�ĸ�֧��	
	unsigned short Years_1901;
	
	Years_1901=Nian-1901;	//��������ũ��1901��������
	GanN=Years_1901%10+GanN;
	if(GanN>10) GanN=GanN-10;
	ZhiN=Years_1901%12+ZhiN;
	if(ZhiN>12) ZhiN=ZhiN-12;	
	
	/*---ũ������ʾ---*/
	switch(GanN){
		case 1: Put1616(56, 240, "��", Font_FGC, Font_BGC); break; case 2: Put1616(56, 240, "��", Font_FGC, Font_BGC); break;
		case 3: Put1616(56, 240, "��", Font_FGC, Font_BGC); break; case 4: Put1616(56, 240, "��", Font_FGC, Font_BGC); break;
		case 5: Put1616(56, 240, "��", Font_FGC, Font_BGC); break; case 6: Put1616(56, 240, "��", Font_FGC, Font_BGC); break;
		case 7: Put1616(56, 240, "��", Font_FGC, Font_BGC); break; case 8: Put1616(56, 240, "��", Font_FGC, Font_BGC); break;
		case 9: Put1616(56, 240, "��", Font_FGC, Font_BGC); break; case 10: Put1616(56, 240, "��", Font_FGC, Font_BGC); break;
	}
	switch(ZhiN){
		case 1: LCD_PutString(72, 240, "����", Font_FGC, Font_BGC); break; case 2: LCD_PutString(72, 240, "��ţ", Font_FGC, Font_BGC); break;
		case 3: LCD_PutString(72, 240, "����", Font_FGC, Font_BGC); break; case 4: LCD_PutString(72, 240, "î��", Font_FGC, Font_BGC); break;
		case 5: LCD_PutString(72, 240, "����", Font_FGC, Font_BGC); break; case 6: LCD_PutString(72, 240, "����", Font_FGC, Font_BGC); break;
		case 7: LCD_PutString(72, 240, "����", Font_FGC, Font_BGC); break; case 8: LCD_PutString(72, 240, "δ��", Font_FGC, Font_BGC); break;
		case 9: LCD_PutString(72, 240, "���", Font_FGC, Font_BGC); break; case 10: LCD_PutString(72, 240, "�ϼ�", Font_FGC, Font_BGC); break;
		case 11: LCD_PutString(72, 240, "�繷", Font_FGC, Font_BGC); break; case 12: LCD_PutString(72, 240, "����", Font_FGC, Font_BGC); break;
	}
	/*---ũ������ʾ---*/ 
	switch(Yue){
		case 1:	Put1616(152, 240, "��", Font_FGC, Font_BGC); break;
		case 2:	Put1616(152, 240, "��", Font_FGC, Font_BGC); break;
		case 3:	Put1616(152, 240, "��", Font_FGC, Font_BGC); break;
		case 4:	Put1616(152, 240, "��", Font_FGC, Font_BGC); break;
		case 5:	Put1616(152, 240, "��", Font_FGC, Font_BGC); break;
		case 6:	Put1616(152, 240, "��", Font_FGC, Font_BGC); break;
		case 7:	Put1616(152, 240, "��", Font_FGC, Font_BGC); break;
		case 8:	Put1616(152, 240, "��", Font_FGC, Font_BGC); break;
		case 9:	Put1616(152, 240, "��", Font_FGC, Font_BGC); break;
		case 10: Put1616(152, 240, "ʮ", Font_FGC, Font_BGC); break;
		case 12: Put1616(152, 240, "��", Font_FGC, Font_BGC); break;
		case 11: LCD_PutString(136, 240, "ʮһ", Font_FGC, Font_BGC); break;
	}
	if(Yue!=11) Paint_Screen(136, 152, 240, 256, BGC);
	/*---ũ������ʾ---*/	
	switch(Ri/10){
		case 0: Put1616(184, 240, "��", Font_FGC, Font_BGC); break;
		case 1: {
			if(Ri%10==0) Put1616(184, 240, "��", Font_FGC, Font_BGC); 
			else Put1616(184, 240, "ʮ", Font_FGC, Font_BGC); 
			break;
		}
		case 2: {
			if(Ri%10==0) Put1616(184, 240, "��", Font_FGC, Font_BGC);
			else Put1616(184, 240, "إ", Font_FGC, Font_BGC); 
			break;
		}
		case 3: Put1616(184, 240, "��", Font_FGC, Font_BGC); break;
	}
	switch(Ri%10){
		case 1:	Put1616(200, 240, "һ", Font_FGC, Font_BGC); break;
		case 2:	Put1616(200, 240, "��", Font_FGC, Font_BGC); break;
		case 3:	Put1616(200, 240, "��", Font_FGC, Font_BGC); break;
		case 4:	Put1616(200, 240, "��", Font_FGC, Font_BGC); break;
		case 5:	Put1616(200, 240, "��", Font_FGC, Font_BGC); break;
		case 6:	Put1616(200, 240, "��", Font_FGC, Font_BGC); break;
		case 7:	Put1616(200, 240, "��", Font_FGC, Font_BGC); break;
		case 8:	Put1616(200, 240, "��", Font_FGC, Font_BGC); break;
		case 9:	Put1616(200, 240, "��", Font_FGC, Font_BGC); break;
		case 0:	Put1616(200, 240, "ʮ", Font_FGC, Font_BGC); break;
	}	
	
}

/*------------------------------------������ʾ------------------------------------*/
void Display_jieqi(short year, short month, short day, int BGC, int Font_FGC, int Font_BGC)
{
	switch(Conver_jieqi(year,month,day)){
		case 24: Paint_Screen(120,152,78,94,BGC); break;
		case 0: LCD_PutString(120, 78, "С��", Font_FGC, Font_BGC); break;
		case 1: LCD_PutString(120, 78, "��", Font_FGC, Font_BGC); break;
		case 2: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;
		case 3: LCD_PutString(120, 78, "��ˮ", Font_FGC, Font_BGC); break;
		case 4: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;
		case 5: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;
		case 6: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;		
		case 7: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;
		case 8: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;
		case 9: LCD_PutString(120, 78, "С��", Font_FGC, Font_BGC); break;
		case 10: LCD_PutString(120, 78, "â��", Font_FGC, Font_BGC); break;
		case 11: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;
		case 12: LCD_PutString(120, 78, "С��", Font_FGC, Font_BGC); break;
		case 13: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;
		case 14: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;
		case 15: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;
		case 16: LCD_PutString(120, 78, "��¶", Font_FGC, Font_BGC); break;
		case 17: LCD_PutString(120, 78, "���", Font_FGC, Font_BGC); break;
		case 18: LCD_PutString(120, 78, "��¶", Font_FGC, Font_BGC); break;
		case 19: LCD_PutString(120, 78, "˪��", Font_FGC, Font_BGC); break;
		case 20: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;
		case 21: LCD_PutString(120, 78, "Сѩ", Font_FGC, Font_BGC); break;	
		case 22: LCD_PutString(120, 78, "��ѩ", Font_FGC, Font_BGC); break;
		case 23: LCD_PutString(120, 78, "����", Font_FGC, Font_BGC); break;			
	}	
	
}

/*------------------------------------������ʾ------------------------------------*/
void Display_jieri(short year, short month, short day, short week, short Yue, short Ri, int BGC, int Font_FGC, int Font_BGC)
{
	switch(JieriG(month,day)){
		case 0: if(TSJR==0) Paint_Screen(72,168,284,308,BGC); break;	
		case 1:	LCD_PutString(104, 284, "Ԫ��", Font_FGC, Font_BGC); break;
		case 2:	LCD_PutString(80, 284, "���񾯲��", Font_FGC, Font_BGC); break;
		case 3:	LCD_PutString(96, 284, "���˽�", Font_FGC, Font_BGC); break;
		case 4:	LCD_PutString(96, 284, "��Ů��", Font_FGC, Font_BGC); break;
		case 5:	LCD_PutString(96, 284, "ֲ����", Font_FGC, Font_BGC); break;
		case 6:	LCD_PutString(72, 284, "������Ȩ����", Font_FGC, Font_BGC); break;
		case 7:	LCD_PutString(96, 284, "���˽�", Font_FGC, Font_BGC); break;
		case 8:	LCD_PutString(96, 284, "�Ͷ���", Font_FGC, Font_BGC); break;
		case 9:	LCD_PutString(96, 284, "�����", Font_FGC, Font_BGC); break;
		case 10:	LCD_PutString(96, 284, "��ͯ��", Font_FGC, Font_BGC); break;
		case 11:	LCD_PutString(96, 284, "������", Font_FGC, Font_BGC); break;
		case 12:	LCD_PutString(96, 284, "������", Font_FGC, Font_BGC); break;
		case 13:	LCD_PutString(80, 284, "��սʤ����", Font_FGC, Font_BGC); break;
		case 14:	LCD_PutString(96, 284, "��ʦ��", Font_FGC, Font_BGC); break;
		case 15:	LCD_PutString(96, 284, "�����", Font_FGC, Font_BGC); break;
		case 16:	LCD_PutString(96, 284, "��ʥҹ", Font_FGC, Font_BGC); break;
		case 17:	LCD_PutString(96, 284, "��ʥ��", Font_FGC, Font_BGC); break;
		case 18:	LCD_PutString(80, 284, "���ҹ�����", Font_FGC, Font_BGC); break;
		case 19:	LCD_PutString(96, 284, "ƽ��ҹ", Font_FGC, Font_BGC); break;
		case 20:	LCD_PutString(96, 284, "ʥ����", Font_FGC, Font_BGC); break;
	}
	switch(JieriL(Yue,Ri)){
		case 0: if(TSJR==0) Paint_Screen(96,144,268,284,BGC); break;
		case 1:	LCD_PutString(104, 268, "����", Font_FGC, Font_BGC); break;
		case 2:	LCD_PutString(96, 268, "Ԫ����", Font_FGC, Font_BGC); break;
		case 3:	LCD_PutString(96, 268, "�����", Font_FGC, Font_BGC); break;
		case 4:	LCD_PutString(96, 268, "��Ϧ��", Font_FGC, Font_BGC); break;
		case 5:	LCD_PutString(96, 268, "��Ԫ��", Font_FGC, Font_BGC); break;
		case 6:	LCD_PutString(96, 268, "�����", Font_FGC, Font_BGC); break;
		case 7:	LCD_PutString(96, 268, "������", Font_FGC, Font_BGC); break;
		case 8:	LCD_PutString(96, 268, "���˽�", Font_FGC, Font_BGC); break;
		case 9:	LCD_PutString(104, 268, "��Ϧ", Font_FGC, Font_BGC); break;
	}
	if(Conver_jieqi(year,month,day)==6) {TSJR=1; LCD_PutString(96, 268, "������", Font_FGC, Font_BGC);}
	else if(month==5&&day>7&&day<=14&&week==7)	{TSJR=1; LCD_PutString(96, 284, "ĸ�׽�", Font_FGC, Font_BGC);}
	else if(month==6&&day>14&&day<=21&&week==7) {TSJR=1; LCD_PutString(96, 284, "���׽�", Font_FGC, Font_BGC);}
	else if(month==11&&day>21&&day<=28&&week==4) {TSJR=1; LCD_PutString(96, 284, "�ж���", Font_FGC, Font_BGC);}
	else TSJR=0;
	
}

/*------------------------------------��ʾ������ָʾ------------------------------------*/
void Display_function(short hour, short min, short sec, int BGC, int Font_FGC, int Font_BGC)
{
	switch(flag){
		case 1: {
			if(sec+min+hour==0) LCD_PutString(16,276,"��ʱ��",Font_FGC,Font_BGC);
			else LCD_PutString(16,276,"��||ͣ",Font_FGC,Font_BGC); 
			break;
		}
		case 2: LCD_PutString(16,276,"��XX��",Font_FGC,Font_BGC); break;
		case 3: LCD_PutString(16,276,"��ʱ��",Font_FGC,Font_BGC); break;
		default: Paint_Screen(16,72,276,292,BGC); break;			
	}
	if(alarmflag==1) LCD_PutString(176,276,"���ӿ�",Font_FGC,Font_BGC);
	else LCD_PutString(176,276,"���ӹ�",Font_FGC,Font_BGC);	
	
}
