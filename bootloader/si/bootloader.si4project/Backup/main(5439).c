/*
 ============================================================================
 Name        : main.c
 Author      : tbf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello RISC-V World in C
 ============================================================================
 */


#include "lib_include.h"


#define	APP_RUN_ADDR				(0x10101000)		// APP运行地址
#define	BAK_CODE_ADDR				(0x10110000)		// BAK区地址
#define APP_UPDATEFLG_AREA			(0x1011F000)		// 升级标志区地址
#define APP_INTACTFLG_AREA			(0x1011F400)		// APP完整标志区地址
#define BAK_INTACTFLG_AREA			(0x1011F800)		// BAK区完整标志地址

#define APP_UPDATEFLG_VAL			(0x5AA55AA5)		// APP升级标志值
#define APP_INTACTFLG_VAL			(0xA55AA55A)		// APP完整标志值
#define BAK_INTACTFLG_VAL			(0x5AA5A55A)		// BAK区完整标志值

#define APP_MAX_SIZE				(0xF000)			// APP区大小
#define FLASH_PAGE_SIZE				(0x200)				// FLASH一页大小

#define LED_RED   GPIO_PIN13
#define LED_GREEN GPIO_PIN12

#define LED_ON(pin)  GPIO_SetPin(pin)
#define LED_OFF(pin) GPIO_ClrPin(pin)

// 搬运BAK区代码
BOOL carry_bak_code(void)
{
	u16 tLen = 0;
	u32 u32Val;
	u32 appVal, bakVal;

	// 清除APP完整标志
	if(EFC_PageErase(APP_INTACTFLG_AREA) != EFC_SUCCESS)
		return FALSE;
	if(EFC_PageErase(APP_INTACTFLG_AREA+512) != EFC_SUCCESS)
		return FALSE;

	for(tLen = 0; tLen < APP_MAX_SIZE; tLen += FLASH_PAGE_SIZE)
	{
		if(EFC_PageLoad(BAK_CODE_ADDR + tLen) != EFC_SUCCESS)
			return FALSE;

		if(EFC_PAGE_BUFFERWrite(APP_RUN_ADDR + tLen) != EFC_SUCCESS)
			return FALSE;
	}

	// APP<--->BAK对比校验
	for(tLen = 0; tLen < APP_MAX_SIZE; tLen += 4)
	{
		appVal = REG32(APP_RUN_ADDR+tLen);
		bakVal = REG32(BAK_CODE_ADDR+tLen);

		if(appVal != bakVal)
			return FALSE;
	}

	// 搬运成功，写APP完整性标志
	u32Val = APP_INTACTFLG_VAL;
	if(EFC_FlashPageWrite(APP_INTACTFLG_AREA, &u32Val, 1, EFC_FLASH_WRITE_WORD) != EFC_SUCCESS)
		return FALSE;
	u32Val = ~APP_INTACTFLG_VAL;
	if(EFC_FlashPageWrite(APP_INTACTFLG_AREA+512, &u32Val, 1, EFC_FLASH_WRITE_WORD) != EFC_SUCCESS)
		return FALSE;

	// 清除升级标志
	if(EFC_PageErase(APP_UPDATEFLG_AREA) != EFC_SUCCESS)
		return FALSE;
	if(EFC_PageErase(APP_UPDATEFLG_AREA+512) != EFC_SUCCESS)
		return FALSE;
	
	return TRUE;
}

/**延时1ms*/
static void delay_1ms(void)
{
	volatile u16 i;
	for (i=0;i<714;i++)
	{
		asm("nop");
	}
}

/**
*@brief ms级硬延时
*@param[in] n 延时时间，单位ms
*@return void
*/
void delay_ms(u16 n)
{
	for (volatile u16 j=0; j < n; j++)
	{
		delay_1ms();
	}
}

void Jump_to_APP(void)
{
	void (*Jump_To_Application)(void);

	// 关闭全局中断
	DisableGlobleIRQ();
 
	Jump_To_Application = (void (*)(void))APP_RUN_ADDR;
	Jump_To_Application();
}

void Fault_Display(void)
{
	while(1)
	{
		LED_ON(LED_GREEN | LED_RED);
		delay_ms(2000);
		LED_OFF(LED_GREEN | LED_RED);
		delay_ms(2000);
	}
}

int main(void)
{
	u8 carryCnt;
	u32  u32Val1,u32Val2;

	// 关闭全局中断
	DisableGlobleIRQ();
	delay_ms(1000);
	EFC_Init();
	
	GPIO_PinConfigure(LED_GREEN | LED_RED, DISABLE, ENABLE, DISABLE, DISABLE, DISABLE);
	LED_OFF(LED_GREEN | LED_RED);

	carryCnt = 0;
	while(1)
	{
		// 读取升级标志区
		u32Val1 = REG32(APP_UPDATEFLG_AREA);
		u32Val2 = REG32(APP_UPDATEFLG_AREA + 512);
		// 升级区标志有效
		if((u32Val1==(~u32Val2)) && (u32Val1==APP_UPDATEFLG_VAL))
		{
			// 需要升级，搬运BAK区代码
			if(carry_bak_code() == FALSE)
			{
				if(carryCnt++ >= 4)
				{
					Fault_Display();
				}
				continue;
			}
		}

		carryCnt = 0;
		
		// 读取程序完整性标志区
		u32Val1 = REG32(APP_INTACTFLG_AREA);
		u32Val2 = REG32(APP_INTACTFLG_AREA + 512);
		// APP完整性标志有效
		if((u32Val1==(~u32Val2)) && (u32Val1==APP_INTACTFLG_VAL))
		{
			// 程序完整，跳转到APP区
			Jump_to_APP();
		}
		else
		{
			// 程序不完整，判断BAK是否完整
			u32Val1 = REG32(BAK_INTACTFLG_AREA);
			u32Val2 = REG32(BAK_INTACTFLG_AREA + 512);
			// BAK完整性标志有效
			if((u32Val1==(~u32Val2)) && (u32Val1==BAK_INTACTFLG_VAL))
			{
				// 搬运BAK区代码
				if(carry_bak_code() == FALSE)
				{
					// 搬运失败
					Fault_Display();
				}
			}
			else
			{
				// APP和BAK都不完整
				Fault_Display();
			}
		}
	}
	
	return 0;
}

