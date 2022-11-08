#include "touch.h"
#include "ltdc.h"
#include "tim.h"
#include "stdlib.h"
#include "math.h"
//#include "24cxx.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作��许可，不得用于其它任何用��1�7
// ALIENTEK STM32F407弢�发板
//触摸屏驱动（支持ADS7843/7846/UH7843/7846/XPT2046/TSC2046/OTT2001A等） 代码
//正点原子@ALIENTEK
//抢�术论坄1�7:www.openedv.com
//创建日期:2014/5/7
//版本：V1.2
//版权扢�有，盗版必究〄1�7
// Copyright(C) 广州市星翼电子科抢�有限公司 2014-2024
// All rights reserved
//********************************************************************************
//修改说明
// V1.1 20140721
//修正MDK圄1�7-O2优化旄1�7,触摸屏数据无法读取的bug.在TP_Write_Byte函数添加丢�个延旄1�7,解决问题.
// V1.2 20141130
//电容触摸屏增加FT5206的支挄1�7
//////////////////////////////////////////////////////////////////////////////////

_m_tp_dev tp_dev =
	{
		TP_Init,
		TP_Scan,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
};
//默认为touchtype=0的数捄1�7.
u8 CMD_RDX = 0XD0;
u8 CMD_RDY = 0X90;

//////////////////////////////////////////////////////////////////////////////////
//触摸按键扫描
// tp:0,屏幕坐标;1,物理坐标(校准等特殊场合用)
//返回倄1�7:当前触屏状��1�7.
// 0,触屏无触摄1�7;1,触屏有触摄1�7
u8 TP_Scan(u8 tp)
{

	return tp_dev.sta & TP_PRES_DOWN; //返回当前的触屏状怄1�7
}

//触摸屏初始化
//返回倄1�7:0,没有进行校准
//       1,进行过校凄1�7
u8 TP_Init(void)
{
	// GPIO_InitTypeDef GPIO_Initure;

	if (GT9147_Init() == 0) //是GT9147
	{
		tp_dev.scan = GT9147_Scan; //扫描函数指向GT9147触摸屏扫揄1�7
	}

	tp_dev.touchtype |= 0X80;				//电容屄1�7
	tp_dev.touchtype |= lcdltdc.dir & 0X01; //横屏还是竖屏
	return 0;

	// return 1;
}
