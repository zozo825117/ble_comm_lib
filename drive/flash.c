#include "flash.h"
#include <string.h>


/**
 * 功能：flash初始化
 * 参数:
 * 返回：无
 */
void flash_init(void)
{
	//HCLK is @16MHz
  FLASH_SetTNVS(0x64);
  FLASH_SetTPGS(0xC8);
  FLASH_SetTPROG(0x1E0);
  FLASH_SetTNVH(0x64);
  FLASH_SetTRCV(0x14);
  FLASH_SetTERASE(0x61A80);
  FLASH_SetTME(0x61A80);
  FLASH_SetTNVH1(0x7D0);
	
//	//HCLK is @32MHz
//	FLASH_SetTNVS(0xC8);
//	FLASH_SetTPGS(0x190);
//	FLASH_SetTPROG(0x3C0);
//	FLASH_SetTNVH(0xC8);
//	FLASH_SetTRCV(0x28);
//	FLASH_SetTERASE(0xC3500);
//	FLASH_SetTME(0xC3500);
//	FLASH_SetTNVH1(0xFA0);
}

/**
 * 功能：擦除flash
 * 参数：addr---擦除地址
 * 返回：无
 * 备注：一次擦除128 byte
 */
void flash_erase_section(u16 addr)
{
	
}

/**
 * 功能：从flash中读取数据
 * 参数：addr---起始地址，buf---读取缓存，len---读取长度
 * 返回：无
 */
void flash_read_buf(u16 addr,u8 *buf,u8 len)
{

}

/**
 * 功能：往flash中写入数据
 * 参数：addr---起始地址，buf---数据缓存，len---写入长度长度
 * 返回：无
 * 写之前要先判断是否需要擦除
 */
void flash_write_buf(u16 addr,u8 *buf,u8 len)
{

}

/**
 * 功能：从flash中读取mac 地址
 * 参数：addr---起始地址，buf---读取缓存
 * 返回：无
 */
void flash_read_mac_addr(u16 addr,u8 *buf)
{
//	u8 i;
//	for(i=0;i<6;i++){
//		buf[5-i] = *((unsigned char code *)(addr++));//读取数据
//	}
}

u8 flash_crc(u8 *dat,u8 len)
{
	u8 i;
	u8 crc = 0;
	for(i=0;i<len;i++){
		crc ^= dat[i];
	}
	
	return crc;
}
