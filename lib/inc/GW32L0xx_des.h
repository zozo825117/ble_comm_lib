/**
  ******************************************************************************
  * @file    GW32L0xx_des.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the des
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_DES_H
#define __GW32L0XX_DES_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	DES_RandomFunction_Disable = 0x1,
	DES_RandomFunction_Enable = 0x2

}	DES_RandomFunction_TypeDef;

typedef enum
{
	DES_OPMode_ECB = 0x0,
	DES_OPMode_CBC = 0x1

} DES_OPMode_TypeDef;

typedef enum
{
	DES_Mode_DES = 0x0,
	DES_Mode_3DES = 0x1

} DES_Mode_TypeDef;

typedef enum
{
	DES_KeySel_DES_KEY1 = 0x0,
	DES_KeySel_DES_KEY2 = 0x1,
	DES_KeySel_DES_KEY3 = 0x2,

	DES_KeySel_3DES_KEY1_2 = 0x0,
	DES_KeySel_3DES_KEY1_2_3 = 0x1

} DES_KeySel_TypyDef;

typedef enum
{
	DES_EncryptDecrypt_Encrypt = 0x0,
	DES_EncryptDecrypt_Decrypt = 0x1

} DES_EncryptDecrypt_TypeDef;

typedef struct
{
	DES_Mode_TypeDef DES_Mode;
	DES_EncryptDecrypt_TypeDef DES_EncryptDecrypt;
	DES_OPMode_TypeDef DES_OPMode;
	DES_KeySel_TypyDef DES_KeySel;	
	DES_RandomFunction_TypeDef DES_RandomFunction;

} DES_InitTypeDef;

void DES_DeInit(void);
void DES_StructInit(DES_InitTypeDef* DES_InitStruct);
void DES_Init(DES_InitTypeDef* DES_InitStruct);
void DES_Cmd(FunctionalState NewState);

FlagStatus DES_GetCompletedFlagStatus(void);

void DES_SetRandomNumber(uint32_t DES_RandomNumber);
void DES_SetKey(DES_KeySel_TypyDef DES_KeySel, uint64_t DES_KEY);
void DES_SetIV(uint64_t DES_IV);
void DES_SetData(uint64_t DES_DATA);
uint64_t DES_GetData(void);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_DES_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
