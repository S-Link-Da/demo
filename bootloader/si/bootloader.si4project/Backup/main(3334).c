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


#define	APP_RUN_ADDR				(0x10102000)
#define	BAK_CODE_ADDR				(0x10110000)
#define APP_MAX_SIZE				(0xF000)
#define APP_UPDATEFLG_AREA			(0x1011F000)
#define APP_INTACTFLG_AREA			(0x1011F400)
#define BAK_INTACTFLG_AREA			(0x1011F400)

#define APP_UPDATEFLG_VAL			(0x5AA55AA5)
#define APP_INTACTFLG_VAL			(0xA55AA55A)
#define BAK_INTACTFLG_VAL			(0xA55AA55A)

BOOL hand_bak_code(void)
{
//	EFC_PageLoad(BAK_CODE_ADDR);
//	EFC_FlashPageWrite();
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

	delay_ms(5000);
	EFC_Init();

	u32Val2 = 0x12345678;
	EFC_FlashPageWrite(0x1011FEE0, &u32Val2, 1, EFC_FLASH_WRITE_WORD);
	EFC_FlashPageWrite(0x1011FE00, &u32Val2, 1, EFC_FLASH_WRITE_WORD);
	u32Val1 = REG32(0x1011FEE0);
	printf("u32Val1 = 0x%x\n", u32Val1);
//	EFC_PageErase(0x1011FEE0);
	u32Val1 = REG32(0x1011FE00);
	printf("u32Val1 = 0x%x\n", u32Val1);

	printf("bootloader\n");
	while(1)
	{
		// 读取升级标志区
		u32Val1 = REG32(APP_UPDATEFLG_AREA);
		u32Val2 = REG32(APP_UPDATEFLG_AREA + 512);
		// 升级区标志有效
		if((u32Val1==(~u32Val2)) && (u32Val1==APP_UPDATEFLG_VAL))
		{
			// 需要升级，搬运BAK区代码
			if(hand_bak_code() == FALSE)
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
				hand_bak_code();
			}
			else
			{
				// APP和BAK都不完整，延时5s跳转
				delay_ms(5000);
				printf("delay_ms(5000)\n");
				Jump_to_APP();
			}
		}
	}
	
	return 0;
}

