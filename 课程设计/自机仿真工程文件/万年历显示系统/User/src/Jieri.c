/**************************************************
* 标题：节日查询，星期计算                        *
* 作者：赵敏琨                                 		*
* 日期：2021年3月16日	                            *
* 说明：输入公/农历日期，输出节日编号             *
* 			输入公历日期，输出星期编号                *
**************************************************/

// ------------------  节日的数据结构定义 ------------------------ //
struct  Festival                 // 节日数据结构 
{
       unsigned char m;               // 节日月份	
       unsigned char d;               // 节日日期 
};

unsigned char i; 
unsigned char	GJRn=20, LJRn=9;	//节日个数
unsigned char n;

struct Festival Jieri_G[]=
{
	/*-------公历节日-------*/
	1,1,		/*元旦,1*/
	1,10,		/*人民警察节,2*/
	2,14,		/*情人节,3*/
	3,8,		/*妇女节,4*/
	3,12,		/*植树节,5*/
	3,15,		/*消费者权益日,6*/
	4,1,		/*愚人节,7*/
	5,1,		/*劳动节,8*/
	5,4,		/*青年节,9*/
	6,1,		/*儿童节,10*/
	7,1,		/*建党节,11*/
	8,1,		/*建军节,12*/
	9,3,		/*抗战胜利日,13*/
	9,10,		/*教师节,14*/
	10,1,		/*国庆节,15*/
	10,31,	/*万圣夜,16*/
	11,1,		/*万圣节,17*/
	12,13,	/*国家公祭日,18*/
	12,24,	/*平安夜,19*/
	12,25,	/*圣诞节,20*/
};

struct Festival Jieri_L[]=
{
	/*-------农历节日-------*/
	1,1,		/*春节,1*/
	1,15,		/*元宵节,2*/
	5,5,		/*端午节,3*/
	7,7,		/*七夕节,4*/
	7,15,		/*中元节,5*/
	8,15,		/*中秋节,6*/
	9,9,		/*重阳节,7*/
	12,8,		/*腊八节,8*/
	12,30,	/*除夕,9*/
};

//显示以节日编号switch，农历和公历不同编号循环查
unsigned char JieriG(unsigned char month,unsigned char day)
{
	for(i=1;i<=GJRn;i++)	//20个公历节日查询编号
	{
		if(Jieri_G[i-1].m==month&&Jieri_G[i-1].d==day){
			n=i;
			i=GJRn+1;
		}
		else n=0;
	}
	return n;
}

unsigned char JieriL(unsigned char Yue,unsigned char Ri)
{
	for(i=1;i<=LJRn;i++)	//9个农历节日查询编号
	{
		if(Jieri_L[i-1].m==Yue&&Jieri_L[i-1].d==Ri){
			n=i;
			i=LJRn+1;
		}
		else n=0;
	}
	return n;
}

/*由基姆拉尔森公式计算星期数*/
unsigned char Week_cal(unsigned short y,unsigned char m,unsigned char d)
{
	if(m==1||m==2){//一二月换算
		m+=12;
		y--;
	}
	int week = (d + 2*m +3*(m+1)/5 + y + y/4 - y/100 + y/400 + 1)%7;
	if (week==0) week=7;	//将0~6表示周日到周六换算
	return week;//其中1~7表示周一到周日
}

