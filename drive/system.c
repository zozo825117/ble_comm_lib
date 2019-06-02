#include "system.h"

// u32 g_time=0;          //全局时间
//extern u8 adv_flag;
// extern u8 task_tick; 
//extern u8 update_time_flag;

/**
 * 功能：系统初始化
 * 参数：无
 * 返回：无
 * 备注：初始化定时器0，用作滴答定时器
 */
// void system_init(void)
// {
// 	TIMER_InitTypeDef TIMER_InitStruct;
	
// 	PORT_DeInit();	//IO所有寄存器复位
	
// 	CMU_APBPeriph0ClockCmd(CMU_APBPeriph0_TIMER1, ENABLE);
// 	TIMER_DeInit(TIMER_1);
// 	TIMER_StructInit(&TIMER_InitStruct);
// 	TIMER_InitStruct.TIMER_Mode = TIMER_Mode_CustomizeCounter;
// 	TIMER_InitStruct.TIMER_CntClkSel = TIMER_CntClkSel_APBusClk;
// 	TIMER_InitStruct.TIMER_PWMOutput = TIMER_PWMOutput_Disable;
// 	TIMER_InitStruct.TIMER_GateCtrl = TIMER_GateCtrl_Disable;
// 	TIMER_Init(TIMER_1, &TIMER_InitStruct);
	
// 	TIMER_SetLoadCounter0(TIMER_1, (16000000/1000)-1);
	
// 	TIMER_ClearAllITFlag();
// 	TIMER_ITConfig(TIMER_1, ENABLE);

// 	__disable_irq();
	
// 	NVIC_DisableIRQ(TIMER1_IRQn);
// 	NVIC_ClearPendingIRQ(TIMER1_IRQn);
// 	NVIC_SetPriority(TIMER1_IRQn, 0x1);
// 	NVIC_EnableIRQ(TIMER1_IRQn);	
	
// 	__enable_irq();	
	
// 	TIMER_Cmd(TIMER_1, ENABLE);
	
// }

/**
 * 功能：看门狗初始化
 * 参数：无
 * 返回：无
 */
void wdt_init(void)
{

}




// void system_tdma(void)
// {
// 	local_info.channel = ++local_info.channel%3;
// 	if(local_info.pair_time <= 250){
// 		local_info.pair_time++;
// 	}
// }


/**
  * @说明  	复位不重读代码选项
  * @参数  	无
  * @返回值 无
  * @注		无
  */
void ResetNoReadOption(void)
{
//	IAP_CMD = 0xF00F;
//	IAP_CMD = 0x8778;
}


/**
  * @说明  	复位重读代码选项
  * @参数  	无
  * @返回值 无
  * @注		无
  */
//void ResetReadOption(void)
//{
//	IAP_CMD = 0xF00F;
//	IAP_CMD = 0x7887;
//}

void NVIC_Init(void)
{
  __disable_irq();
  
  NVIC_DisableIRQ(SysTick_IRQn);
  NVIC_ClearPendingIRQ(SysTick_IRQn);
  NVIC_SetPriority(SysTick_IRQn, 0x0);
  NVIC_EnableIRQ(SysTick_IRQn); 
  
  __enable_irq(); 
}


void Timer2_init(void)
{
    /* timer x*/
  TIMER_InitTypeDef TIMER_InitStruct;
  CMU_APBPeriph0ClockCmd(CMU_APBPeriph0_TIMER2, ENABLE);
  TIMER_DeInit(TIMER_2);
  TIMER_StructInit(&TIMER_InitStruct);
  TIMER_InitStruct.TIMER_Mode = TIMER_Mode_CustomizeCounter;
  TIMER_InitStruct.TIMER_CntClkSel = TIMER_CntClkSel_APBusClk;
  TIMER_InitStruct.TIMER_PWMOutput = TIMER_PWMOutput_Disable;
  TIMER_InitStruct.TIMER_GateCtrl = TIMER_GateCtrl_Disable;
  TIMER_Init(TIMER_2, &TIMER_InitStruct);
  
  TIMER_SetLoadCounter0(TIMER_2, (16000000/1000)-1);

  TIMER_ClearAllITFlag();
  TIMER_ITConfig(TIMER_2, ENABLE);

  __disable_irq();
  
  NVIC_DisableIRQ(TIMER2_IRQn);
  NVIC_ClearPendingIRQ(TIMER2_IRQn);
  NVIC_SetPriority(TIMER2_IRQn, 0x1);
  NVIC_EnableIRQ(TIMER2_IRQn);  
  
  __enable_irq(); 

  TIMER_Cmd(TIMER_2, ENABLE);
}


