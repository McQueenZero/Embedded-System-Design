#define SYSCLK_FREQ_72MHz  72000000
��
void SystemInit(void)	//ϵͳ��ʼ��
{
	��
	SetSysClock();	//ϵͳʱ�Ӷ������
	��
}
static void SetSysClock(void)
{
	#ifdef SYSCLK_FREQ_HSE
	��
	#elif defined SYSCLK_FREQ_72MHz
	SetSysClockTo72();	//�趨ϵͳʱ��Ϊ72MHz
	#endif
}
static void SetSysClockTo72(void)
{
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);	
	//stm32f10x.h�ж��壺#define  RCC_CR_HSEON	((uint32_t)0x00010000)	
	/*ʹ��ϵͳ�ⲿ����ʱ��*/
}