
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


u8 bMacAddr[] = {0xCC,0xAA,0x11,0x00,0x21,0x11};
uint8_t device_name[] = "ble uart";
uint32_t time_tick=0;
uint32_t timeCloseTimer = 0;
uint32_t timeDisconnectTimer = 0;
uint32_t timeUartReceTimer = 0;
uint32_t runTimeTimer =0;
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
 				if(Timer_Time_Elapsed(timeDisconnectTimer, 30000)){   //30s
 					Debug_Print(DEBUG_MESSAGE_LEVEL_4,"not operated time exceed %d s\r\n", (3000/100));
 					
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
	
	uint8_t mac_buf[6];
	uint8_t name_buf[16];

	/*串口初始化*/
	Debug_Print_Init();
	Debug_Print_Start(DEBUG_MESSAGE_LEVEL_4);
	Debug_Print(DEBUG_MESSAGE_LEVEL_4,"Debug_Print_Start\r\n");
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




	test_pin();
	// wdt_init();   //看门狗初始化
	uart_rx_ok = 0;
	SysTick_Configuration();
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
