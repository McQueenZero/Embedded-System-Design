/***************************************************
* 标题：公历与阴历转换                             *
* 作者：Wujieflash                                 *
* 日期：2008年1月18日                              *
* 说明：阴历日期随公历变化                         *
* 修改者：赵敏琨																	 *
* 日期：2021年3月16日															 *
***************************************************/
const unsigned char	year_code[] = { 0x04, 0xAe, 0x53,                               /* 1901 */
					0x0A,	  0x57, 0x48,                           /* 1902 */
					0x55,	  0x26, 0xBd,                           /* 1903 */
					0x0d,	  0x26, 0x50,                           /* 1904 */
					0x0d,	  0x95, 0x44,                           /* 1905 */
					0x46,	  0xAA, 0xB9,                           /* 1906 */
					0x05,	  0x6A, 0x4d,                           /* 1907 */
					0x09,	  0xAd, 0x42,                           /* 1908 */
					0x24,	  0xAe, 0xB6,                           /* 1909 */
					0x04,	  0xAe, 0x4A,                           /* 1910 */
					0x6A,	  0x4d, 0xBe,                           /* 1911 */
					0x0A,	  0x4d, 0x52,                           /* 1912 */
					0x0d,	  0x25, 0x46,                           /* 1913 */
					0x5d,	  0x52, 0xBA,                           /* 1914 */
					0x0B,	  0x54, 0x4e,                           /* 1915 */
					0x0d,	  0x6A, 0x43,                           /* 1916 */
					0x29,	  0x6d, 0x37,                           /* 1917 */
					0x09,	  0x5B, 0x4B,                           /* 1918 */
					0x74,	  0x9B, 0xC1,                           /* 1919 */
					0x04,	  0x97, 0x54,                           /* 1920 */
					0x0A,	  0x4B, 0x48,                           /* 1921 */
					0x5B,	  0x25, 0xBC,                           /* 1922 */
					0x06,	  0xA5, 0x50,                           /* 1923 */
					0x06,	  0xd4, 0x45,                           /* 1924 */
					0x4A,	  0xdA, 0xB8,                           /* 1925 */
					0x02,	  0xB6, 0x4d,                           /* 1926 */
					0x09,	  0x57, 0x42,                           /* 1927 */
					0x24,	  0x97, 0xB7,                           /* 1928 */
					0x04,	  0x97, 0x4A,                           /* 1929 */
					0x66,	  0x4B, 0x3e,                           /* 1930 */
					0x0d,	  0x4A, 0x51,                           /* 1931 */
					0x0e,	  0xA5, 0x46,                           /* 1932 */
					0x56,	  0xd4, 0xBA,                           /* 1933 */
					0x05,	  0xAd, 0x4e,                           /* 1934 */
					0x02,	  0xB6, 0x44,                           /* 1935 */
					0x39,	  0x37, 0x38,                           /* 1936 */
					0x09,	  0x2e, 0x4B,                           /* 1937 */
					0x7C,	  0x96, 0xBf,                           /* 1938 */
					0x0C,	  0x95, 0x53,                           /* 1939 */
					0x0d,	  0x4A, 0x48,                           /* 1940 */
					0x6d,	  0xA5, 0x3B,                           /* 1941 */
					0x0B,	  0x55, 0x4f,                           /* 1942 */
					0x05,	  0x6A, 0x45,                           /* 1943 */
					0x4A,	  0xAd, 0xB9,                           /* 1944 */
					0x02,	  0x5d, 0x4d,                           /* 1945 */
					0x09,	  0x2d, 0x42,                           /* 1946 */
					0x2C,	  0x95, 0xB6,                           /* 1947 */
					0x0A,	  0x95, 0x4A,                           /* 1948 */
					0x7B,	  0x4A, 0xBd,                           /* 1949 */
					0x06,	  0xCA, 0x51,                           /* 1950 */
					0x0B,	  0x55, 0x46,                           /* 1951 */
					0x55,	  0x5A, 0xBB,                           /* 1952 */
					0x04,	  0xdA, 0x4e,                           /* 1953 */
					0x0A,	  0x5B, 0x43,                           /* 1954 */
					0x35,	  0x2B, 0xB8,                           /* 1955 */
					0x05,	  0x2B, 0x4C,                           /* 1956 */
					0x8A,	  0x95, 0x3f,                           /* 1957 */
					0x0e,	  0x95, 0x52,                           /* 1958 */
					0x06,	  0xAA, 0x48,                           /* 1959 */
					0x7A,	  0xd5, 0x3C,                           /* 1960 */
					0x0A,	  0xB5, 0x4f,                           /* 1961 */
					0x04,	  0xB6, 0x45,                           /* 1962 */
					0x4A,	  0x57, 0x39,                           /* 1963 */
					0x0A,	  0x57, 0x4d,                           /* 1964 */
					0x05,	  0x26, 0x42,                           /* 1965 */
					0x3e,	  0x93, 0x35,                           /* 1966 */
					0x0d,	  0x95, 0x49,                           /* 1967 */
					0x75,	  0xAA, 0xBe,                           /* 1968 */
					0x05,	  0x6A, 0x51,                           /* 1969 */
					0x09,	  0x6d, 0x46,                           /* 1970 */
					0x54,	  0xAe, 0xBB,                           /* 1971 */
					0x04,	  0xAd, 0x4f,                           /* 1972 */
					0x0A,	  0x4d, 0x43,                           /* 1973 */
					0x4d,	  0x26, 0xB7,                           /* 1974 */
					0x0d,	  0x25, 0x4B,                           /* 1975 */
					0x8d,	  0x52, 0xBf,                           /* 1976 */
					0x0B,	  0x54, 0x52,                           /* 1977 */
					0x0B,	  0x6A, 0x47,                           /* 1978 */
					0x69,	  0x6d, 0x3C,                           /* 1979 */
					0x09,	  0x5B, 0x50,                           /* 1980 */
					0x04,	  0x9B, 0x45,                           /* 1981 */
					0x4A,	  0x4B, 0xB9,                           /* 1982 */
					0x0A,	  0x4B, 0x4d,                           /* 1983 */
					0xAB,	  0x25, 0xC2,                           /* 1984 */
					0x06,	  0xA5, 0x54,                           /* 1985 */
					0x06,	  0xd4, 0x49,                           /* 1986 */
					0x6A,	  0xdA, 0x3d,                           /* 1987 */
					0x0A,	  0xB6, 0x51,                           /* 1988 */
					0x09,	  0x37, 0x46,                           /* 1989 */
					0x54,	  0x97, 0xBB,                           /* 1990 */
					0x04,	  0x97, 0x4f,                           /* 1991 */
					0x06,	  0x4B, 0x44,                           /* 1992 */
					0x36,	  0xA5, 0x37,                           /* 1993 */
					0x0e,	  0xA5, 0x4A,                           /* 1994 */
					0x86,	  0xB2, 0xBf,                           /* 1995 */
					0x05,	  0xAC, 0x53,                           /* 1996 */
					0x0A,	  0xB6, 0x47,                           /* 1997 */
					0x59,	  0x36, 0xBC,                           /* 1998 */
					0x09,	  0x2e, 0x50,                           /* 1999 294 */
					0x0C,	  0x96, 0x45,                           /* 2000 297 */
					0x4d,	  0x4A, 0xB8,                           /* 2001 */
					0x0d,	  0x4A, 0x4C,                           /* 2002 */
					0x0d,	  0xA5, 0x41,                           /* 2003 */
					0x25,	  0xAA, 0xB6,                           /* 2004 */
					0x05,	  0x6A, 0x49,                           /* 2005 */
					0x7A,	  0xAd, 0xBd,                           /* 2006 */
					0x02,	  0x5d, 0x52,                           /* 2007 */
					0x09,	  0x2d, 0x47,                           /* 2008 */
					0x5C,	  0x95, 0xBA,                           /* 2009 */
					0x0A,	  0x95, 0x4e,                           /* 2010 */
					0x0B,	  0x4A, 0x43,                           /* 2011 */
					0x4B,	  0x55, 0x37,                           /* 2012 */
					0x0A,	  0xd5, 0x4A,                           /* 2013 */
					0x95,	  0x5A, 0xBf,                           /* 2014 */
					0x04,	  0xBA, 0x53,                           /* 2015 */
					0x0A,	  0x5B, 0x48,                           /* 2016 */
					0x65,	  0x2B, 0xBC,                           /* 2017 */
					0x05,	  0x2B, 0x50,                           /* 2018 */
					0x0A,	  0x93, 0x45,                           /* 2019 */
					0x47,	  0x4A, 0xB9,                           /* 2020 */
					0x06,	  0xAA, 0x4C,                           /* 2021 */
					0x0A,	  0xd5, 0x41,                           /* 2022 */
					0x24,	  0xdA, 0xB6,                           /* 2023 */
					0x04,	  0xB6, 0x4A,                           /* 2024 */
					0x69,	  0x57, 0x3d,                           /* 2025 */
					0x0A,	  0x4e, 0x51,                           /* 2026 */
					0x0d,	  0x26, 0x46,                           /* 2027 */
					0x5e,	  0x93, 0x3A,                           /* 2028 */
					0x0d,	  0x53, 0x4d,                           /* 2029 */
					0x05,	  0xAA, 0x43,                           /* 2030 */
					0x36,	  0xB5, 0x37,                           /* 2031 */
					0x09,	  0x6d, 0x4B,                           /* 2032 */
					0xB4,	  0xAe, 0xBf,                           /* 2033 */
					0x04,	  0xAd, 0x53,                           /* 2034 */
					0x0A,	  0x4d, 0x48,                           /* 2035 */
					0x6d,	  0x25, 0xBC,                           /* 2036 */
					0x0d,	  0x25, 0x4f,                           /* 2037 */
					0x0d,	  0x52, 0x44,                           /* 2038 */
					0x5d,	  0xAA, 0x38,                           /* 2039 */
					0x0B,	  0x5A, 0x4C,                           /* 2040 */
					0x05,	  0x6d, 0x41,                           /* 2041 */
					0x24,	  0xAd, 0xB6,                           /* 2042 */
					0x04,	  0x9B, 0x4A,                           /* 2043 */
					0x7A,	  0x4B, 0xBe,                           /* 2044 */
					0x0A,	  0x4B, 0x51,                           /* 2045 */
					0x0A,	  0xA5, 0x46,                           /* 2046 */
					0x5B,	  0x52, 0xBA,                           /* 2047 */
					0x06,	  0xd2, 0x4e,                           /* 2048 */
					0x0A,	  0xdA, 0x42,                           /* 2049 */
					0x35,	  0x5B, 0x37,                           /* 2050 */
					0x09,	  0x37, 0x4B,                           /* 2051 */
					0x84,	  0x97, 0xC1,                           /* 2052 */
					0x04,	  0x97, 0x53,                           /* 2053 */
					0x06,	  0x4B, 0x48,                           /* 2054 */
					0x66,	  0xA5, 0x3C,                           /* 2055 */
					0x0e,	  0xA5, 0x4f,                           /* 2056 */
					0x06,	  0xB2, 0x44,                           /* 2057 */
					0x4A,	  0xB6, 0x38,                           /* 2058 */
					0x0A,	  0xAe, 0x4C,                           /* 2059 */
					0x09,	  0x2e, 0x42,                           /* 2060 */
					0x3C,	  0x97, 0x35,                           /* 2061 */
					0x0C,	  0x96, 0x49,                           /* 2062 */
					0x7d,	  0x4A, 0xBd,                           /* 2063 */
					0x0d,	  0x4A, 0x51,                           /* 2064 */
					0x0d,	  0xA5, 0x45,                           /* 2065 */
					0x55,	  0xAA, 0xBA,                           /* 2066 */
					0x05,	  0x6A, 0x4e,                           /* 2067 */
					0x0A,	  0x6d, 0x43,                           /* 2068 */
					0x45,	  0x2e, 0xB7,                           /* 2069 */
					0x05,	  0x2d, 0x4B,                           /* 2070 */
					0x8A,	  0x95, 0xBf,                           /* 2071 */
					0x0A,	  0x95, 0x53,                           /* 2072 */
					0x0B,	  0x4A, 0x47,                           /* 2073 */
					0x6B,	  0x55, 0x3B,                           /* 2074 */
					0x0A,	  0xd5, 0x4f,                           /* 2075 */
					0x05,	  0x5A, 0x45,                           /* 2076 */
					0x4A,	  0x5d, 0x38,                           /* 2077 */
					0x0A,	  0x5B, 0x4C,                           /* 2078 */
					0x05,	  0x2B, 0x42,                           /* 2079 */
					0x3A,	  0x93, 0xB6,                           /* 2080 */
					0x06,	  0x93, 0x49,                           /* 2081 */
					0x77,	  0x29, 0xBd,                           /* 2082 */
					0x06,	  0xAA, 0x51,                           /* 2083 */
					0x0A,	  0xd5, 0x46,                           /* 2084 */
					0x54,	  0xdA, 0xBA,                           /* 2085 */
					0x04,	  0xB6, 0x4e,                           /* 2086 */
					0x0A,	  0x57, 0x43,                           /* 2087 */
					0x45,	  0x27, 0x38,                           /* 2088 */
					0x0d,	  0x26, 0x4A,                           /* 2089 */
					0x8e,	  0x93, 0x3e,                           /* 2090 */
					0x0d,	  0x52, 0x52,                           /* 2091 */
					0x0d,	  0xAA, 0x47,                           /* 2092 */
					0x66,	  0xB5, 0x3B,                           /* 2093 */
					0x05,	  0x6d, 0x4f,                           /* 2094 */
					0x04,	  0xAe, 0x45,                           /* 2095 */
					0x4A,	  0x4e, 0xB9,                           /* 2096 */
					0x0A,	  0x4d, 0x4C,                           /* 2097 */
					0x0d,	  0x15, 0x41,                           /* 2098 */
					0x2d,	  0x92, 0xB5,                           /* 2099 */
};
const unsigned char	day_code1[9] = { 0x0, 0x1f, 0x3b, 0x5a, 0x78, 0x97, 0xb5,
					 0xd4,	  0xf3 };
const unsigned int	day_code2[3] = { 0x111, 0x130, 0x14e };
const unsigned char	table_week[12] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };        /* 月修正数据表 */

/* ********************************************************************************************************* */


/****************************************************************************
* 子函数,用于读取数据表中农历月的大月或小月,如果该月为大返回1,为小返回0
****************************************************************************/
unsigned char GetMoonDay( unsigned char month_p, unsigned short table_addr )
{
	switch ( month_p )
	{
	case 1:
		if ( (year_code[table_addr] & 0x08) == 0 )
			return(0);
		else
			return(1);
	case 2:
		if ( (year_code[table_addr] & 0x04) == 0 )
			return(0);
		else
			return(1);
	case 3:
		if ( (year_code[table_addr] & 0x02) == 0 )
			return(0);
		else
			return(1);
	case 4:
		if ( (year_code[table_addr] & 0x01) == 0 )
			return(0);
		else
			return(1);
	case 5:
		if ( (year_code[table_addr + 1] & 0x80) == 0 )
			return(0);
		else
			return(1);
	case 6:
		if ( (year_code[table_addr + 1] & 0x40) == 0 )
			return(0);
		else
			return(1);
	case 7:
		if ( (year_code[table_addr + 1] & 0x20) == 0 )
			return(0);
		else
			return(1);
	case 8:
		if ( (year_code[table_addr + 1] & 0x10) == 0 )
			return(0);
		else
			return(1);
	case 9:
		if ( (year_code[table_addr + 1] & 0x08) == 0 )
			return(0);
		else
			return(1);
	case 10:
		if ( (year_code[table_addr + 1] & 0x04) == 0 )
			return(0);
		else
			return(1);
	case 11:
		if ( (year_code[table_addr + 1] & 0x02) == 0 )
			return(0);
		else
			return(1);
	case 12:
		if ( (year_code[table_addr + 1] & 0x01) == 0 )
			return(0);
		else
			return(1);
	case 13:
		if ( (year_code[table_addr + 2] & 0x80) == 0 )
			return(0);
		else
			return(1);
	}
	return(0);
}

extern unsigned short	Nian, Yue, Ri;

/*********************************************************************************************************
** 函数名称:GetLunarCalendar
** 功能描述:公农历年、月、日转换(只允许1901-2099年)
** 输　入:  year        公历年
**          month       公历月
**          day         公历日
**
** 输　出:  1           成功
**          0           失败
** 作　者:  wujie
** 日　期:  2007年05月06日
******-------------------------------------------------------------------------------------------------------
** 修改人: 赵敏琨
** 日　期: 2021年03月16日
** 说  明：增加了农历年份判断
******------------------------------------------------------------------------------------------------------
********************************************************************************************************/
unsigned char GetLunarCalendar( unsigned short year, unsigned char month, unsigned char day )
{

	unsigned char	SFm, SFd, SF_NYds, month_p, yearH, yearL;
	unsigned char	flag_y;
	unsigned short day_NYds, table_addr;

	year=year+2000;	//匹配原程序与本万年历系统年格式
	
	yearH	= year / 100;
	yearL	= year % 100;
	if ( (yearH != 19) && (yearH != 20) )
		return(0);

	/* 定位数据表地址 */
	if ( yearH == 20 )
		table_addr = (yearL + 100 - 1) * 3;
	else
		table_addr = (yearL - 1) * 3;

	/* 取当年春节所在的公历月份 */
	SFm	= year_code[table_addr + 2] & 0x60;
	SFm	>>= 5;

	/* 取当年春节所在的公历日 */
	SFd = year_code[table_addr + 2] & 31;

	/* 计算当年春节离当年元旦的天数,春节只会在公历1月或2月 */
	if ( SFm == 1 )
		SF_NYds = SFd - 1;
	else
		SF_NYds = SFd + 31 - 1;

	/* 计算公历日离当年元旦的天数 */
	if ( month < 10 )
		day_NYds = day_code1[month - 1] + day - 1;
	else
		day_NYds = day_code2[month - 10] + day - 1;
	/* 如果公历月大于2月并且该年的2月为闰月,天数加1 */
	if ( (month > 2) && (yearL % 4 == 0) )
		day_NYds++;

	/* 判断公历日在春节前还是春节后 */
	/* 公历日在春节后使用下面代码进行运算 */
	if ( day_NYds >= SF_NYds )
	{
		day_NYds	-= SF_NYds;
		month	= 1;
		month_p = 1;

		flag_y = 0;
		if ( GetMoonDay( month_p, table_addr ) == 0 )
			SFm = 29;     /* 小月29天 */
		else
			SFm = 30;     /* 大月30天 */
		/* 从数据表中取该年的闰月月份,如为0则该年无闰月 */
		SFd = year_code[table_addr] / 16;
		while ( day_NYds >= SFm )
		{
			day_NYds -= SFm;
			month_p++;
			if ( month == SFd )
			{
				flag_y = ~flag_y;
				if ( flag_y == 0 )
					month++;
			}else
				month++;
			if ( GetMoonDay( month_p, table_addr ) == 0 )
				SFm = 29;
			else
				SFm = 30;
		}
		day = day_NYds + 1;
	}
	/* 公历日在春节前使用下面代码进行运算 */
	else{
		SF_NYds -= day_NYds;
		if ( yearL == 0 )
		{
			yearL	= 100 - 1;
			yearH	= 19;
		}else
			yearL--;
		table_addr	-= 3;
		month		= 12;
		SFd		= year_code[table_addr] / 16;
		if ( SFd == 0 )
			month_p = 12;
		else
			month_p = 13;

		flag_y = 0;
		if ( GetMoonDay( month_p, table_addr ) == 0 )
			SFm = 29;
		else
			SFm = 30;
		while ( SF_NYds > SFm )
		{
			SF_NYds -= SFm;
			month_p--;
			if ( flag_y == 0 )
				month--;
			if ( month == SFd )
				flag_y = ~flag_y;
			if ( GetMoonDay( month_p, table_addr ) == 0 )
				SFm = 29;
			else
				SFm = 30;
		}
		day = SFm - SF_NYds + 1;
		year=year-1;
	}
	Nian = year;
	Yue = month;
	Ri	= day;
	
	return(1);
}
