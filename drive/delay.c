#include "delay.h"


void SysTick_Configuration(void)
{

  SysTick->VAL = 0;                     //当前值寄存器
  
  SysTick_SetReloadValue(0xFFFFFE);		//重装载值
  
  SysTick_CLKSourceConfig(SysTick_ClkSource_ExtRefClk_HSI);//选择时钟源
  
  SysTick_ITConfig(DISABLE);			//Systick 中断使能位
  SysTick_Cmd(ENABLE);                	//使能 SysTick计数器
}

/**
 * 功能：延时
 */
void delay_us(uint32_t u32Cnt)
{
    uint32_t u32end;
		u32end = 0x1000000 - SystemCoreClock/1000000;
	
    while(u32Cnt-- > 0)
    {
        SysTick->VAL = 0;
   
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }
}
/**
 * 功能：延时
 */
void delay_ms(uint32_t u32Cnt)
{
    uint32_t u32end;
		u32end = 0x1000000 - SystemCoreClock/1000;
    while(u32Cnt-- > 0)
    {
        SysTick->VAL = 0;

        
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }
}

void delay_0_5_ms(uint32_t u32Cnt)
{
    uint32_t u32end;
	
    while(u32Cnt-- > 0)
    {
        SysTick->VAL = 0;

        u32end = 0x1000000 - SystemCoreClock/2000;
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }
}
void delay_1_us(uint32_t u32Cnt)
{
	u8 i;

	while(u32Cnt-- > 0)
	{
			for(i = 0; i < 2; i++)
			{
			
			}
	}
}
