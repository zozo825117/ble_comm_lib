ble_comm_lib
========

# 概述
提供供应用层调用的库文件，可快速实现Faking BLE(伪蓝牙)的功能
# 硬件
* mcu 
    * LSD2GW-32LC256
    * Cortex M0+ 32

* RF
    * 1600


# 特性
- [x] Get and set Device MAC address into BLE Stack's memory(RAM).
- [x] Get and set Device Advertisement name at BLE Stack's memory(RAM).
- [x] start Bluetooth device with Advertising.
- [x] ble send data to master.
- [x] ble device initiative disconnect with master.
- [x] gets the current bleState.
- [x] onStartSuccess
- [x] onStartFailure

# TODO
- [ ] Ble_pauseSession

# Project Organization
![](http://34.92.38.105/laizhi_doc/ble_comm_lib_mcu/2019-06-03_structure.png)

1. ble库文件`blecomm_api.lib`
2. ble库头文件 `blecomm.h`


# Useage

1. 初始化: `Ble_Init`,需要提供一个timer,mcu主频建议使用最大的16Mhz.需要实现一个回调方法,参见 **回调事件**
2. 打开模块:`Ble_Start`.
3. 在主循环中放置ble事件处理方法`Ble_ProcessEvents`,调用间隔建议不小于20ms.
4. 在提供的timer中断服务中放置`Ble_BackgroudProcess`ble协议调度方法.
5. 使用其他**主要方法**进行和master的数据交换,断开连接,关闭模块.
6. 在**回调事件**中,可获取ble事件信息.

# SPI接口

* `spi.c`和`spi.h`需要实现四个接口供ble库,需要实现的是三线的SPI:  
  1. `spi_init`  
  2. `DrvSPI_SendByte2PHASE`  
  3. `DrvSPI_ReceiveByte2PHASE`  
  4. `Chip_Reset`  
 


# 主要方法
见`blecomm.h`
```c
/*****************************************************************************
* Function Name: Ble_Init()
******************************************************************************
* Summary:
* This function performs will initialization RF chip and ble stack,
*
* \param TIMER_TypeDef* TIMERx:  ble stack need use one stack timer to working.
* \param IRQn_Type TIMERx_IRQn:  initial timer with interrupt interval is 10ms.
* \param uint32_t clock:   cpu main clock, it recommend mcu clock is HSI_VALUE.
* \param BLE_CALLBACK_T callbackFunc: getting the corresponding events from the BLE component, add application
*                                   code to handle events.
*
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*                       failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted when device is in connected state.
*
* Note:
*       after function bleState is BLE_STATE_INITIALIZING
*****************************************************************************/
BLE_API_RESULT_T Ble_Init(TIMER_TypeDef* TIMERx, IRQn_Type TIMERx_IRQn,
    uint32_t clock ,BLE_CALLBACK_T callbackFunc);

/******************************************************************************
* Function Name: Ble_GetMac
*******************************************************************************
* 
* This function gets the Bluetooth device address at BLE Stack's memory(RAM).
* 
* \param uint8_t * deviceMac:   return Bluetooth Device address retrieved from the BLE stack gets stored
*                               to a variable pointed to by this pointer. 
*                               default mac is read in mcu(AR32) chip id
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*                       failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted when device is in connected state.
*
* Note:
*        default mac is read in mcu(AR32) chip id
* 
******************************************************************************/
BLE_API_RESULT_T Ble_GetMac(uint8_t *deviceMac);

/******************************************************************************
* Function Name: Ble_SetMac
*******************************************************************************
* 
* This function sets the Bluetooth device address into BLE Stack's memory(RAM).
* 
* \param uint8_t * deviceMac:   Bluetooth Device address retrieved from the BLE stack gets stored
*                               to a variable pointed to by this pointer. 
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*                       failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted when device is in connected state.
*
******************************************************************************/
BLE_API_RESULT_T Ble_SetMac(uint8_t *deviceMac);

/******************************************************************************
* Function Name: Ble_GetName
*******************************************************************************
* 
* This function gets the Bluetooth device advertisement name at BLE Stack's memory(RAM).
* 
* \param uint8_t * deviceName:   return Bluetooth Device advertisement name retrieved from the BLE stack gets stored
*                               to a variable pointed to by this pointer. 
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*                       failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted when device is in connected state.
*
* Note:
*        default name is "ble comm"
******************************************************************************/
BLE_API_RESULT_T Ble_GetName(uint8_t *deviceName);

/******************************************************************************
* Function Name: Ble_SetName
*******************************************************************************
* 
* This function sets the Bluetooth device advertisement name into BLE Stack's memory(RAM).
* 
* \param uint8_t * deviceName:   Bluetooth Device advertisement name retrieved from the BLE stack gets stored
*                               to a variable pointed to by this pointer. 
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*                       failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted when device is in connected state.
*
* Note:
*        name length range is [1:15] bytes
******************************************************************************/
BLE_API_RESULT_T Ble_SetName(uint8_t *deviceName);


/******************************************************************************
* Function Name: Ble_Start
*******************************************************************************
* 
* This function start Bluetooth device with Advertising.
* 
* \param None
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*                       failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted when device is in connected state.
* 
* Note:
*       if already ble start will return BLE_ERROR_INVALID_OPERATION
******************************************************************************/
BLE_API_RESULT_T Ble_Start(void);

/******************************************************************************
* Function Name: Ble_SendData
*******************************************************************************
* 
* This function send data to master.
* 
* \param uint8_t len :  length of send data, range is [1:15]
* \param uint8_t *data :  data pointer 
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*                       failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted when device is in connected state.
* 
* Note:
*       if bleState isn't BLE_STATE_CONNECTED will return BLE_ERROR_INVALID_OPERATION
*       if data out of range will return CYBLE_ERROR_INVALID_PARAMETER
******************************************************************************/
BLE_API_RESULT_T Ble_SendData(uint8_t len, uint8_t *data);

/******************************************************************************
* Function Name: Ble_pauseSession
*******************************************************************************
* 
* This function is reversed now
* 
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted when device is in connected state.
*
******************************************************************************/
// BLE_API_RESULT_T Ble_pauseSession(void);

/******************************************************************************
* Function Name: Ble_DisConnect
***************************************************************************//**
* 
* This function is device initiative disconnect with master.
* 
* \param None
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*                       failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
*   CYBLE_ERROR_INVALID_PARAMETER    | On specifying NULL as input parameter.
*   CYBLE_ERROR_INVALID_OPERATION    | Operation is not permitted when device is in connected state.
* 
* Note:
*       if bleState isn't BLE_STATE_CONNECTED will return BLE_ERROR_INVALID_OPERATION
******************************************************************************/
BLE_API_RESULT_T Ble_DisConnect(void);

/******************************************************************************
* Function Name: Ble_Stop
***************************************************************************//**
* 
* This function is stop ble stack and ble stack timer.
* 
* \param None
* 
* \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or 
*                       failed. Following are the possible error codes.
*
*   Errors codes                     | Description
*   ------------                     | -----------
*   CYBLE_ERROR_OK                   | On successful operation.
* 
* Note:
*       None
******************************************************************************/
BLE_API_RESULT_T Ble_Stop(void);

/******************************************************************************
* Function Name: Ble_GetState
***************************************************************************//**
* 
* This function gets the current bleState.
* 
* \param 
*       None
* 
* \returns: BLE_STATE_T   bleState
*   
* Note:
*       None
******************************************************************************/
BLE_STATE_T Ble_GetState(void);

/******************************************************************************
* Function Name: Ble_ProcessEvents
***************************************************************************//**
*   
*  This function checks the internal task queue in the BLE Stack, and pending
*  operation of the BLE Stack, if any. This needs to be called at least once
*  every interval 't' where:
*   1. 't' is equal to connection interval or scan interval, whichever is
*       smaller, if the device is in GAP Central mode of operation, or
*   2. 't' is equal to connection interval or advertisement interval,
*       whichever is smaller, if the device is in GAP Peripheral mode
*       of operation. 
* 
*  On calling every interval 't', all pending operations of the BLE Stack are
*  processed. This is a blocking function and returns only after processing all
*  pending events of the BLE Stack Care should be taken to prevent this call
*  from any kind of starvation; on starvation, events may be dropped by the
*  stack. All the events generated will be propagated to higher layers of the
*  BLE Stack and to the Application layer only after making a call to this
*  function.
* 
* \return 
*  None
* 
******************************************************************************/
void Ble_ProcessEvents(void);

/******************************************************************************
* Function Name: Ble_BackgroudProcess
***************************************************************************//**
*   
*  This function need place in ble stack timer interrupt 
* 
* \return 
*  None
* 
******************************************************************************/
void Ble_BackgroudProcess(void);

```
# ble运行状态

```c
/** Event handler state machine type */
typedef enum
{
    BLE_STATE_STOPPED,                        /**< BLE is turned off */
    BLE_STATE_INITIALIZING,                   /**< Initializing state */
    BLE_STATE_CONNECTED,                      /**< Peer device is connected */
    BLE_STATE_ADVERTISING,                    /**< Advertising process */
    BLE_STATE_DISCONNECTED                    /**< Essentially idle state */
} BLE_STATE_T;
```

# 回调事件
```c
/** Host stack events.

*/
typedef enum
{
    /** ble stack ready, create at Ble_Init()*/
    BLE_EVT_STACK_ON = 0x01u,
    /** This event is received when there is a timeout and application needs to handle the event.  */
    BLE_EVT_TIMEOUT,

    /** This event indicates that some internal hardware error has occurred. Reset of the hardware may be required. */
    BLE_EVT_HARDWARE_ERROR,

    /** This event is received when there is advertisment start or stop and application needs to handle the event.  
        eventParam[0] : 
            1 start first tigger at Ble_Start() and auto tigger when ble disconnect
            0 stop  clear when ble connect 
    */
    BLE_EVT_GAPP_ADVERTISEMENT_START_STOP,

    /** This event is ble connect event.  
            eventParam : link_id[2]  characteristic value of current link, create at connecting. 
        */
    BLE_EVT_GAP_DEVICE_CONNECTED,

    /** This event is ble connect event.  
            eventParam : link_id[2]  characteristic value of current link, create at connecting. 
        */
    BLE_EVT_GAP_DEVICE_DISCONNECTED,
    
    /** Notification data received from server device. Event parameter
       is a pointer to a structure of type BLE_GATTC_HANDLE_VALUE_NTF_PARAM_T. */
    BLE_EVT_GATTC_HANDLE_VALUE_NTF,
    /** 'Prepare Write' Request from client device. Event parameter is a
       pointer to a structure of type BLE_GATTS_PREP_WRITE_REQ_PARAM_T. */
    BLE_EVT_GATTS_PREP_RECEIVE_DATA, 
}BLE_EVENT_T;

```
# 函数返回错误
```c
/** Common error codes received as API result */
typedef enum
{
    /** No Error occurred */
    BLE_ERROR_OK = 0x0000u,
    
    /** At least one of the input parameters is invalid */
    BLE_ERROR_INVALID_PARAMETER,
    
    /** Operation is not permitted */
    BLE_ERROR_INVALID_OPERATION,
  
}BLE_API_RESULT_T;
```
# 演示
![演示视频](https://github.com/zozo825117/ble_comm_lib/raw/master/res/ble_comm_lib.gif)