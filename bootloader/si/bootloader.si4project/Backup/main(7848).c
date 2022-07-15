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


#define	APP_RUN_ADDR				(0x10101000)
#define	BAK_CODE_ADDR				(0x10110000)
#define APP_UPDATEFLG_AREA			(0x1011F000)
#define APP_INTACTFLG_AREA			(0x1011F400)
#define BAK_INTACTFLG_AREA			(0x1011F800)

#define APP_UPDATEFLG_VAL			(0x5AA55AA5)
#define APP_INTACTFLG_VAL			(0xA55AA55A)
#define BAK_INTACTFLG_VAL			(0x5AA5A55A)

#define APP_MAX_SIZE				(0xF000)
#define FLASH_PAGE_SIZE				(0x200)

// 搬运BAK区代码
BOOL carry_bak_code(void)
{
	u16 tLen = 0;
	u32 u32Val;

	// 清除APP完整标志
	EFC_PageErase(APP_INTACTFLG_AREA);
	EFC_PageErase(APP_INTACTFLG_AREA+512);

	for(tLen = 0; tLen < APP_MAX_SIZE; tLen += FLASH_PAGE_SIZE)
	{
		if(EFC_PageLoad(BAK_CODE_ADDR + tLen) != EFC_SUCCESS)
			return FALSE;

		if(EFC_PAGE_BUFFERWrite(APP_RUN_ADDR + tLen) != EFC_SUCCESS)
			return FALSE;
	}

	// 搬运成功，写APP完整性标志
	u32Val = APP_INTACTFLG_VAL;
	EFC_FlashPageWrite(APP_INTACTFLG_AREA, &u32Val, 1, EFC_FLASH_WRITE_WORD);
	u32Val = ~APP_INTACTFLG_VAL;
	EFC_FlashPageWrite(APP_INTACTFLG_AREA+512, &u32Val, 1, EFC_FLASH_WRITE_WORD);

	// 清除升级标志
	EFC_PageErase(APP_UPDATEFLG_AREA);
	EFC_PageErase(APP_UPDATEFLG_AREA+512);
	
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

int main(void)
{
	u32  u32Val1,u32Val2;

	// 关闭全局中断
	DisableGlobleIRQ();
	delay_ms(1000);
	EFC_Init();

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
				continue;
		}
		
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
				carry_bak_code();
			}
			else
			{
				// APP和BAK都不完整，延时5s跳转
				delay_ms(5000);
				Jump_to_APP();
			}
		}
	}
	
	return 0;
}

