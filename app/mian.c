
// #include "GW32L0xx_port.h"

#define ALLOCATE_EXTERN

// #include "GW32L0xx_port.h"
#include "blecomm.h"
#include "uart.h"
#include "system.h"
#include <string.h>
//#include "os.h"
#include "delay.h"
// #include "spi.h"
#include "debug.h"


u8 g24_send(u8 *dat,u8 len,u8 ch);
u8 g24_init(void);

u8 bMacAddr[] = {0xCC,0xAA,0x11,0x00,0x21,0x11};

const u8 test_2_4_dat[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};


uint8_t device_name[] = "ble uart";
uint8_t wait2_4G = 0;
uint32_t time_tick=0;
uint32_t timeCloseTimer = 0;
uint32_t timeDisconnectTimer = 0;
uint32_t timeUartReceTimer = 0;
uint32_t runTimeTimer =0;
uint32_t send2_4GTimer = 0;

u8 uart_rx_buf[20];
u8 uart_rx_index;
u8 uart_rx_ok;
u8 rf_tx_len;
u8 test_step = 0;


void test_pin(void)
{
  PORT_InitTypeDef PORT_InitStruct;
  CMU_APBPeriph1ClockCmd(CMU_APBPeriph1_PORT, ENABLE);
  PORT_InitStruct.PORT_Pin = PORT_Pin_12;
  PORT_InitStruct.PORT_Mode = PORT_Mode_OUT;
  PORT_InitStruct.PORT_OutType = PORT_OutType_PP;
  PORT_InitStruct.PORT_PullHigh = PORT_PH_NoPullHigh;
  PORT_InitStruct.PORT_Properity= PORT_Properity_Digital;
  PORT_InitStruct.PORT_DriveSink= PORT_DS_DriveSinkStrength;
  PORT_Init(PORT_6, &PORT_InitStruct);
}

uint32_t Timer_Get_Time_Stamp(void)
{
    return time_tick;
}

uint8_t Timer_Time_Elapsed(uint32_t time_stamp, uint32_t interval)
{
    uint8_t result = 0;
    if((time_tick - time_stamp) >= interval)
    {
        result = 1;
    }
    else if((time_stamp > time_tick) && ((time_stamp+interval) >= time_tick))
    {
        /* Checking the overflow condition here */
        result = 1;
    }
    return result;
}

/***************************************************************************************
  * @说明  	T1中断服务函数
  *	@参数	无
  * @返回值 无
  * @注		无
***************************************************************************************/
void TIMER1_IRQHandler(void)
{
	if (TIMER_GetITStatus(TIMER_1) == SET)
	{

    TIMER_1->INTCLR = TIMER_1->INTCLR;
    
    Ble_BackgroudProcess();

	}
}

/*****************************************************************************
* Function Name: app_callback()
******************************************************************************
* Summary:
* This function is a callback that is registered with Ble_Init()
* for getting the corresponding events from the BLE component 
*
* Parameters:
* event - Event from the BLE Component
* eventParam - Pointer to the event parameters 
*
* Return:
* None
* 
* Note:
* None
*****************************************************************************/
void app_callback(u32 event, uint8_t * eventParam)
{
	u8 i;
	switch(event){
		case BLE_EVT_STACK_ON:
				Debug_Print(DEBUG_MESSAGE_LEVEL_4,"BLE_EVT_STACK_ON ble_state= %d\r\n", eventParam[0]);
			break;

		case BLE_EVT_TIMEOUT:
				Debug_Print(DEBUG_MESSAGE_LEVEL_4,"BLE_EVT_TIMEOUT link_id= 0x%x%x\r\n", eventParam[0],eventParam[1]);
			break;

		case BLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
				Debug_Print(DEBUG_MESSAGE_LEVEL_4,"BLE_EVT_GAPP_ADVERTISEMENT_START_STOP state= %d\r\n", eventParam[0]);
			break;

		case BLE_EVT_GAP_DEVICE_CONNECTED:
				Debug_Print(DEBUG_MESSAGE_LEVEL_4,"BLE_EVT_GAP_DEVICE_CONNECTED link_id= 0x%x%x\r\n", eventParam[0],eventParam[1]);

				//for ble no deal close
				timeDisconnectTimer = Timer_Get_Time_Stamp();
			break;

		case BLE_EVT_GAP_DEVICE_DISCONNECTED:
				Debug_Print(DEBUG_MESSAGE_LEVEL_4,"BLE_EVT_GAP_DEVICE_DISCONNECTED link_id= 0x%x%x\r\n", eventParam[0],eventParam[1]);
			break;

		case BLE_EVT_GATTC_HANDLE_VALUE_NTF:
				Debug_Print(DEBUG_MESSAGE_LEVEL_4,
						"BLE_EVT_GATTC_HANDLE_VALUE_NTF send len= 0x%x\r\n", eventParam[0]);
				Debug_Print(DEBUG_MESSAGE_LEVEL_4," data=0x");
				for(i=0;i<eventParam[0];i++){
					Debug_Print(DEBUG_MESSAGE_LEVEL_4," %x", eventParam[i+1]);
				}
				Debug_Print(DEBUG_MESSAGE_LEVEL_4,"\r\n");

				//for ble no deal close
				timeDisconnectTimer = Timer_Get_Time_Stamp();
			break;

		case BLE_EVT_GATTS_PREP_RECEIVE_DATA:
				Debug_Print(DEBUG_MESSAGE_LEVEL_4,
					"BLE_EVT_GATTS_PREP_RECEIVE_DATA recv len= 0x%x\r\n", eventParam[0]);
				Debug_Print(DEBUG_MESSAGE_LEVEL_4," data=0x");
				for(i=0;i<eventParam[0];i++){
					Debug_Print(DEBUG_MESSAGE_LEVEL_4," %x", eventParam[i+1]);
				}
				Debug_Print(DEBUG_MESSAGE_LEVEL_4,"\r\n");

				//for ble no deal close
				timeDisconnectTimer = Timer_Get_Time_Stamp();
				
			break;

	}
}

void testTask(void)
{
	u8 i;
		// *10ms
		if(test_step == 0){
			if(Ble_GetState() == BLE_STATE_INITIALIZING || Ble_GetState() == BLE_STATE_STOPPED){
				if(Ble_Start() == BLE_ERROR_OK){
					Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Ble_Start ok\r\n");
				}	
			}
			test_step = 1;

		}else if(test_step == 2){
			if(Timer_Time_Elapsed(timeCloseTimer, 100)){	//100ms
				if(Ble_GetState() != BLE_STATE_STOPPED){
					Debug_Print(DEBUG_MESSAGE_LEVEL_4,"now state is %d\r\n",Ble_GetState());
					if(Ble_Stop() == BLE_ERROR_OK){
						Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Ble_Stop ok\r\n");
						test_step = 0;
					}
				}
				timeCloseTimer = Timer_Get_Time_Stamp();
			}  
		}

		/*dis connect test*/
		if(Ble_GetState() == BLE_STATE_CONNECTED){
 				if(Timer_Time_Elapsed(timeDisconnectTimer, 50000)){   //50s
 					Debug_Print(DEBUG_MESSAGE_LEVEL_4,"not operated time exceed %d s\r\n", (50000/100));
 					
					if(Ble_DisConnect() == BLE_ERROR_OK){

							Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Ble_DisConnect ok\r\n");
							timeCloseTimer = Timer_Get_Time_Stamp();
							test_step = 2;
					}else{
						Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Ble_DisConnect error state=%d\r\n",Ble_GetState());
					}
					timeDisconnectTimer = Timer_Get_Time_Stamp();

 				}

 				if(uart_rx_ok){
 					if(Ble_SendData(uart_rx_buf[1],&uart_rx_buf[2]) == BLE_ERROR_OK){
							Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Ble_SendData ok\r\n");
					}
 					uart_rx_ok = 0;
 				}
		}

		if(Timer_Time_Elapsed(timeUartReceTimer,20)){

				if(uart_rx_index && uart_rx_ok==0){
					uart_rx_index = 0;
				}
		}
		
}

int main()
{
	
	u8 i;
	u8 state_tmp;
	
	uint8_t mac_buf[6];
	uint8_t name_buf[16];

	/*串口初始化*/
	Debug_Print_Init();
	Debug_Print_Start(DEBUG_MESSAGE_LEVEL_4);
	Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Debug_Print_Start\r\n");
	test_pin();
	// wdt_init();   //看门狗初始化

	uart_rx_ok = 0;
	SysTick_Configuration();
	/**/
	Ble_Init(TIMER_1,TIMER1_IRQn,CMU_APBPeriph0_TIMER1,HSI_VALUE,app_callback);



	if(Ble_GetMac(mac_buf) == BLE_ERROR_OK){
		Debug_Print(DEBUG_MESSAGE_LEVEL_4,
					"default mac = 0x%x%x%x%x%x%x\r\n", mac_buf[0],mac_buf[1],mac_buf[2],mac_buf[3],mac_buf[4],mac_buf[5]);
	}
	else{
		Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Ble_GetMac error\r\n");
	}

	if(Ble_SetMac(bMacAddr) == BLE_ERROR_OK){
			Ble_GetMac(mac_buf);
			Debug_Print(DEBUG_MESSAGE_LEVEL_4,
			"new mac = 0x%x%x%x%x%x%x\r\n", mac_buf[0],mac_buf[1],mac_buf[2],mac_buf[3],mac_buf[4],mac_buf[5]);
	}
	else{
		Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Ble_SetMac error\r\n");
	}

	memset(name_buf, 0 , sizeof(name_buf));
	if(Ble_GetName(name_buf) == BLE_ERROR_OK){
		Debug_Print(DEBUG_MESSAGE_LEVEL_4,"len=%d default name = %s\r\n", strlen((char *)name_buf),name_buf);

	}
	else{
		Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Ble_GetName error\r\n");
	}

	if(Ble_SetName(device_name) == BLE_ERROR_OK){
			memset(name_buf, 0 , sizeof(name_buf));
			Ble_GetName(name_buf);
			Debug_Print(DEBUG_MESSAGE_LEVEL_4,"len=%d default name =%s\r\n", strlen((char *)name_buf),name_buf);

	}
	else{
		Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Ble_SetName error\r\n");
	}

	// NVIC_Init();
	Timer2_init();

	while(1)
	{
		// 10ms
		if(Timer_Time_Elapsed(runTimeTimer,10)){
			Ble_ProcessEvents();
			testTask();
			runTimeTimer = Timer_Get_Time_Stamp();
		}

		if(!wait2_4G){
			if(Timer_Time_Elapsed(send2_4GTimer,7000)){

				Debug_Print(DEBUG_MESSAGE_LEVEL_4,"send 2.4G\r\n");
				state_tmp = Ble_pauseSession(1);
				Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Ble_pauseSession pause state = %d\r\n",state_tmp);
				g24_init();
				g24_send((u8 *)test_2_4_dat,sizeof(test_2_4_dat),48);
				send2_4GTimer = Timer_Get_Time_Stamp();
				wait2_4G = 1;
			}
		}else{
			if(Timer_Time_Elapsed(send2_4GTimer,50)){
				state_tmp = Ble_pauseSession(0);
				Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Ble_pauseSession resume state = %d\r\n",state_tmp);
				wait2_4G = 0;
			}
		}


		
		
	}
		
}


void DEBUG_UART_IRQ_HEADER(void)
{
	if (UART_GetITStatus(DEBUG_UART, UART_IntID_TXREmpty) == SET)
	{
		
	}


	if (UART_GetITStatus(DEBUG_UART, UART_IntID_ReceiveData) == SET)
	{
		uart_rx_buf[uart_rx_index++] = UART_ReceiveData(DEBUG_UART);

		if(uart_rx_index >= 3 ){ //&& uart_rx_buf[uart_rx_index-1] == '\n' && (uart_rx_buf[uart_rx_index-2]& 0x0F) == '\r'
				
				rf_tx_len = uart_rx_index-3;
				// Debug_Print(DEBUG_MESSAGE_LEVEL_4,"%d %d\r\n", uart_rx_buf[1], rf_tx_len);
				if((uart_rx_buf[1] == (rf_tx_len-1)) && (rf_tx_len <=16) ){
					uart_rx_ok = 1;
					uart_rx_index = 0;
				}
		}
		
		if(uart_rx_index>18){
			uart_rx_index = 0;
		}

		timeUartReceTimer = Timer_Get_Time_Stamp();
	}
}


u8 g24_regs[][2] = {
	{17,0x3A},
	{18,0x0C},
	{34,0x08},
	{45,0x00},
	{46,0x09},
	{52,0x19},
	{53,0x40},
	{80,0xF8},
	{64,0xA8},
	{73,0XC7},
	{79,0XC8},
	{78,0X03},
	{82,0X20},
	{81,0X41},
	{68,0X60},
	{41,0X70},
	{4,0XC2},
	{35,0X08},
	{255,255}
	
	
};

u8 g24_init(void)
{
	u8 i;


	for(i=0;i<8;i++)
	{
		phy_write_reg(g24_regs[i][0], g24_regs[i][1]);                      
		if(i!=4)
		{
			if(g24_regs[i][1] != phy_read_reg(g24_regs[i][0]))
			{
				while(1);
			}
		}
	}  

 //preamble Syncword 长度 trailer 长度设置
	phy_write_reg(64,0xA8);//3Byte SYNCWORD	
	phy_write_reg(82,0x20);//Miscellaneous REG1
	phy_write_reg(81,0x41);//syncword 阈值 1bit
	phy_write_reg(41,0x70);//关 Trailer LSB syncword 长度为奇数
	phy_write_reg(95,0x80|16);//固定包长
	
	phy_write_reg(04,0xC2);//Agc
	phy_write_reg(35,0x08);//Lna
	phy_write_reg(68,0x60);//CW	  

	phy_write_reg(73,0XC7);//0xEE	0x77
	phy_write_reg(78,0X03);//0x33	0xCC
	phy_write_reg(79,0XC8);//0xC0	0x03   
	phy_write_reg_bit(82,5,1);//关闭数据长度发送
	phy_write_reg_bit(33,1,1); //使能PKT_flag
	return 0;
}

const u8 null_dat[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

u8 g24_send(u8 *dat,u8 len,u8 ch)
{

	phy_write_reg(95,0x80|18);
	phy_write_fifo(100,dat,len);
	if(len<18){
		phy_write_fifo(100,(u8*)null_dat,18-len);
	}
	phy_write_reg(15,ch);
	phy_write_reg_bit(14,0,1);
	
	delay_ms(1);
	phy_write_reg_bit(14,0,0);//使能发射
	return 0;
}
