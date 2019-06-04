/*****************************************************************************
   	Copyright (C), 2018-2019, Hangzhou Greenwhale Science & Technology Group Co.,Ltd
   	File name: DrvSPI.c
   	Author: 
    Version: V0
    Date: 13.Dec.2018
   	Description: ????SPI
   	
   	Function List: 
   	   	   	   	1-DrvSPI_Init()   	   	   	   	        SPI??IO
   	   	   	   	2-DrvSPI_SendByte2PHASE()   	   	   	????2
   	   	   	   	3-DrvSPI_ReceiveByte2PHASE()   	        ????2
   	   	   	   	4-DrvSPI_SendByte1PHASE()   	   	   	????1
   	   	   	   	5-DrvSPI_ReceiveByte1PHASE()   	        ????1
   	History:  
   	<author>  <time>  <version >  <desc>
******************************************************************************/

/* Private include files ----------------------------------------------------*/
#include "spi.h"
#include "delay.h"

/* Private Macros and Data type ---------------------------------------------*/      	   	   	   	   	   	   	   	   	
/* Private function declaration ----------------------------------------------*/
/* Private Data declaration --------------------------------------------------*/

/*******************************************************************************
   	Function:  	   	   	DrvSPI_Init
   	Description:   	    SPI???
   	Input: 	   	   	   	None
   	Output:	   	   	   	None
   	Return:	   	   	   	None
   	Others:	   	   	   	None
********************************************************************************/
void spi_init(void)
{      
#ifdef WIRE_SPI_MODE4

//  DRVSPI_MISO_INPUT;
//  DRVSPI_CLK_OUTPUT;
//  DRVSPI_MOSI_OUTPUT;
  PORT_InitTypeDef PORT_InitStruct;
  
  CMU_APBPeriph1ClockCmd(CMU_APBPeriph1_PORT, ENABLE);
  PORT_InitStruct.PORT_Pin = WL1601_MISO_Pin;
  PORT_InitStruct.PORT_Mode = PORT_Mode_IN;
  PORT_InitStruct.PORT_PullHigh = PORT_PH_NoPullHigh;
  PORT_InitStruct.PORT_Properity= PORT_Properity_Digital;
  PORT_InitStruct.PORT_DriveSink= PORT_DS_DriveSinkStrength;
  PORT_Init(WL1601_MISO_Port, &PORT_InitStruct);
  
  PORT_InitStruct.PORT_Pin = WL1601_SCK_Pin;
  PORT_InitStruct.PORT_Mode = PORT_Mode_OUT;
  PORT_InitStruct.PORT_OutType = PORT_OutType_PP;
  PORT_InitStruct.PORT_PullHigh = PORT_PH_NoPullHigh;
  PORT_InitStruct.PORT_Properity= PORT_Properity_Digital;
  PORT_InitStruct.PORT_DriveSink= PORT_DS_DriveSinkStrength;
  PORT_Init(WL1601_SCK_Port, &PORT_InitStruct);
  
  PORT_InitStruct.PORT_Pin = WL1601_MOSI_Pin;
  PORT_InitStruct.PORT_Mode = PORT_Mode_OUT;
  PORT_InitStruct.PORT_OutType = PORT_OutType_PP;
  PORT_InitStruct.PORT_PullHigh = PORT_PH_NoPullHigh;
  PORT_InitStruct.PORT_Properity= PORT_Properity_Digital;
  PORT_InitStruct.PORT_DriveSink= PORT_DS_DriveSinkStrength;
  PORT_Init(WL1601_MOSI_Port, &PORT_InitStruct);

  PORT_InitStruct.PORT_Pin = WL1601_CSN_Pin;
  PORT_InitStruct.PORT_Mode = PORT_Mode_OUT;
  PORT_InitStruct.PORT_OutType = PORT_OutType_PP;
  PORT_InitStruct.PORT_PullHigh = PORT_PH_NoPullHigh;
  PORT_InitStruct.PORT_Properity= PORT_Properity_Digital;
  PORT_InitStruct.PORT_DriveSink= PORT_DS_DriveSinkStrength;
  PORT_Init(WL1601_CSN_Port, &PORT_InitStruct);
  
  DRVSPI_CLK0;
  
#endif

#ifdef WIRE_SPI_MODE3

  PORT_InitTypeDef PORT_InitStruct;
//  DRVSPI_CLK_OUTPUT;
//  DRVSPI_MOSI_OUTPUT;
//  DRVSPI_CSN_OUTPUT;
	CMU_APBPeriph1ClockCmd(CMU_APBPeriph1_PORT, ENABLE);
  PORT_InitStruct.PORT_Pin = WL1601_SCK_Pin;
  PORT_InitStruct.PORT_Mode = PORT_Mode_OUT;
  PORT_InitStruct.PORT_OutType = PORT_OutType_PP;
  PORT_InitStruct.PORT_PullHigh = PORT_PH_NoPullHigh;
  PORT_InitStruct.PORT_Properity= PORT_Properity_Digital;
  PORT_Init(WL1601_SCK_Port, &PORT_InitStruct);
  
  PORT_InitStruct.PORT_Pin = WL1601_MOSI_Pin;
  PORT_InitStruct.PORT_Mode = PORT_Mode_OUT;
  PORT_InitStruct.PORT_OutType = PORT_OutType_PP;
  PORT_InitStruct.PORT_PullHigh = PORT_PH_PullHigh;
  PORT_InitStruct.PORT_Properity= PORT_Properity_Digital;
  PORT_Init(WL1601_MOSI_Port, &PORT_InitStruct);

  PORT_InitStruct.PORT_Pin = WL1601_CSN_Pin;
  PORT_InitStruct.PORT_Mode = PORT_Mode_OUT;
  PORT_InitStruct.PORT_OutType = PORT_OutType_PP;
  PORT_InitStruct.PORT_PullHigh = PORT_PH_NoPullHigh;
  PORT_InitStruct.PORT_Properity= PORT_Properity_Digital;
  PORT_Init(WL1601_CSN_Port, &PORT_InitStruct);
  DRVSPI_CLK0;
#endif

    DRVSPI_CE_OUTPUT;
    DRVSPI_CSN1; //禁止SPI传输
    DRVWL1601B_CE1;
  	
}

void delay_1ms(uint16_t u32Cnt){
  uint32_t counter = u32Cnt<<11;
  while (counter-- > 0) {
    __nop();
  }
}


/**
 * 函数：phy_read_reg
 * 功能：读RF寄存器
 * 参数：reg----要读取的寄存器地址
 * 返回：读取到的值
 */
u8 phy_read_reg(u8 reg)
{
   	unsigned char reg_val;	    
   	DRVSPI_CSN0;              	 //使能SPI传输     	   	
   	DrvSPI_SendByte2PHASE(reg | 0x80);    //发送寄存器号
   	reg_val = DrvSPI_ReceiveByte2PHASE();//读取寄存器内容
   	DRVSPI_CSN1;              	 //禁止SPI传输     	   	    
   	return(reg_val);           	 //返回状态值
	
}

/**
 * 函数：phy_write_reg
 * 功能：写RF寄存器
 * 参数：reg----要读取的寄存器地址
 * 			 val---值
 * 返回：无
 */
void phy_write_reg(u8 reg,u8 val)
{
   	DRVSPI_CSN0;    //使能SPI传输
   	DrvSPI_SendByte2PHASE(reg);     //发送寄存器号 
   	DrvSPI_SendByte2PHASE(val);   //写入寄存器的值
   	DRVSPI_CSN1;    //禁止SPI传输   
}

/**
 * 函数：phy_read_reg_bit
 * 功能：读RF寄存器某一位
 * 参数：reg----要读取的寄存器地址
 * 			 bits----位
 * 返回：0 或 1
 */

//u8 phy_read_reg_bit(u8 reg,u8 bits)
//{
//	data u8 val;
//	data u8 bit_val = (1 << bits);
//	
//	val = phy_read_reg(reg);
//	
//	return (val & bit_val) ? 1 : 0;
//}
/**
 * 函数：phy_write_reg_bit
 * 功能：写RF寄存器某一位
 * 参数：reg----要读取的寄存器地址
 * 			 bits----位
 * 			 val----值  0 或 1
 * 返回：无
 */
void phy_write_reg_bit(u8 reg,u8 bits,u8 val)
{

	u8 tmp;
	u8 bit_val = (1 << bits);
	
	tmp = phy_read_reg(reg);
	if (val) {
			tmp |= bit_val;
	} else {
			tmp &= ~bit_val;
	}

	phy_write_reg(reg, tmp);

}


/**
 * 函数：phy_read_fifo
 * 功能：读取RF FIFO中的数据
 * 参数：reg----要读取的寄存器地址
 * 			 buf----读取缓存地址
 * 			 len----读取长度
 * 返回：无
 */
void phy_read_fifo(u8 reg, u8 *buf, u8 len) 
{

   	unsigned char lu8i;

   	DRVSPI_CSN0;	//使能SPI传输
   	DrvSPI_SendByte2PHASE(reg | 0x80);	//发送寄存器号
   	for(lu8i=0; lu8i<len; lu8i++)
    {
        buf[lu8i]=DrvSPI_ReceiveByte2PHASE();
    }
   	DRVSPI_CSN1;	//禁止SPI传输

}

/**
 * 函数：phy_write_fifo
 * 功能：往RF FIFO中写数据
 * 参数：reg----寄存器地址
 * 			 buf----数据缓存地址
 * 			 len----写入长度
 * 返回：无
 */
void phy_write_fifo(u8 reg, u8 *buf, u8 len) 
{

   	unsigned char lu8i;    	
   	
   	DRVSPI_CSN0;        //使能SPI传输
   	DrvSPI_SendByte2PHASE(reg);    	 //发送寄存器号 
   	for(lu8i=0; lu8i<len; lu8i++)
    {
        DrvSPI_SendByte2PHASE(*buf++); //写入数据
    }
   	DRVSPI_CSN1;        //禁止SPI传输

}


/*******************************************************************************
    Function:           
    Description:        
    Input:              None
    Output:             None
    Return:             None
    Others:             None
********************************************************************************/
void Chip_Reset(void)
{
#ifndef WIRE_SPI_MODE3
  RF_DISABLE();
  RF_SPI_DESELECT();

  /* Reset WL1600 */
  RF_DISABLE();
  delay_us(50);
  
  RF_ENABLE();
  delay_ms(5);
#else
  /**
    SPI_CSN_I long low pulse (>10ms) defined as reset_n 
   */
  DRVSPI_CSN0;    //使能SPI传输
  DrvSPI_SendByte2PHASE(32);     //发送寄存器号 
  DrvSPI_SendByte2PHASE(0x04);   //写入寄存器的值
  DRVSPI_CSN1;    //禁止SPI传输   
  DRVSPI_CSN0;
  delay_1ms(20);
  DRVSPI_CSN1;
  delay_1ms(10);
  /** 
    设置3线SPI通信 
  */
  DRVSPI_CSN0;    //使能SPI传输
  DrvSPI_SendByte2PHASE(94);     //发送寄存器号 
  DrvSPI_SendByte2PHASE(0x80);   //写入寄存器的值
  DRVSPI_CSN1;    //禁止SPI传输   
#endif

}

/*******************************************************************************
   	Function:  	   	   	DrvSPI_SendByte2PHASE
   	Description:   	    ????
   	Input: 	   	   	   	None
   	Output:	   	   	   	None
   	Return:	   	   	   	None
   	Others:	   	   	   	None
********************************************************************************/
void DrvSPI_SendByte2PHASE(unsigned char dat)
{  	
   	unsigned char i;
#ifndef WIRE_SPI_MODE3
   	for(i=0;i<8;i++){
   	   	DRVSPI_CLK1;
   	   	if(dat&0x80)
        {
          DRVSPI_MOSI1;
        }
   	   	else
        {
          DRVSPI_MOSI0;
        }
   	   	dat<<=1;
   	   	DRVSPI_CLK0;
   	}
   	DRVSPI_CLK0;
#else
	DRVSPI_MOSI_OUTPUT;
   	for(i=0;i<8;i++){
   	   	DRVSPI_CLK0;
   	   	if(dat&0x80)
        {
          DRVSPI_MOSI1;
        }
   	   	else 
        {
          DRVSPI_MOSI0;
        }
   	   	dat<<=1;
   	   	DRVSPI_CLK1;
   	}
   	DRVSPI_CLK0;
#endif
}


/*******************************************************************************
   	Function:  	   	   	DrvSPI_ReceiveByte2PHASE
   	Description:   	    ????
   	Input: 	   	   	   	None
   	Output:	   	   	   	None
   	Return:	   	   	   	None
   	Others:	   	   	   	None
********************************************************************************/
unsigned char DrvSPI_ReceiveByte2PHASE(void)
{
   	unsigned char i,rec=0;
#ifndef WIRE_SPI_MODE3	
   	for(i=0;i<8;i++){
   	   	DRVSPI_CLK1;
   	   	rec<<=1;
   	   	if(DRVSPI_MISO)
   	   	   	rec|=0x01;
   	   	else 
   	   	   	rec&=0xfe;
   	   	DRVSPI_CLK0;
   	}
   	DRVSPI_CLK0;
#else
	DRVSPI_MOSI_INPUT;
   	for(i=0;i<8;i++){
   	   	
   	   	rec<<=1;
				DRVSPI_CLK1;
   	   	if(WL1601_MOSI_Read() == Bit_SET)//if(DRVSPI_MOSI)
   	   	   	rec|=0x01;
   	   	else
   	   	   	rec&=0xfe;
   	   	DRVSPI_CLK0;
   	}
   	DRVSPI_CLK0;
#endif	
   	return rec;
}
