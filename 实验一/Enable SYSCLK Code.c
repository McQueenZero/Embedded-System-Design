#define SYSCLK_FREQ_72MHz  72000000
…
void SystemInit(void)	//系统初始化
{
	…
	SetSysClock();	//系统时钟定义程序
	…
}
static void SetSysClock(void)
{
	#ifdef SYSCLK_FREQ_HSE
	…
	#elif defined SYSCLK_FREQ_72MHz
	SetSysClockTo72();	//设定系统时钟为72MHz
	#endif
}
static void SetSysClockTo72(void)
{
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);	
	//stm32f10x.h中定义：#define  RCC_CR_HSEON	((uint32_t)0x00010000)	
	/*使能系统外部高速时钟*/
}