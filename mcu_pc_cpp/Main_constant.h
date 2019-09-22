
/*
*********************************************************************************************************
*********************************************************************************************************
* File : Main_constant.h
* By : Minglie
* Date :
*********************************************************************************************************
*/


#ifndef __Main_Constant_H
#define __Main_Constant_H





//----------------------------global variable define---------------------------------------------------
#ifdef OS_GLOBALS
#define OS_EXT
#else
#define OS_EXT extern
#endif


typedef union
{
	struct
	{
		unsigned low : 4;
		unsigned up : 4;

	}half;
	struct
	{
		unsigned b0 : 1;
		unsigned b1 : 1;
		unsigned b2 : 1;
		unsigned b3 : 1;
		unsigned b4 : 1;
		unsigned b5 : 1;
		unsigned b6 : 1;
		unsigned b7 : 1;
	}one;
	unsigned char all;
}CHAR_TypeDef;


typedef union
{
	struct
	{
		unsigned snow_comand_b0 : 1; //扫雪命令
		unsigned walk_comand_b321 : 3; //行走命令
		unsigned swing_comand_b54 : 2; //转向命令
		unsigned nc_comand_b76 : 2; //
	}one;
	unsigned char all;
} ptl_tx_stack_TypeDef;

typedef union
{
	struct
	{
		unsigned low_vol_num_b210 : 3; //低包电压值
		unsigned up_vol_num_b543 : 3; //高包电压值
		unsigned charge_b6 : 1; //充电器插入标志
		unsigned bat_low_up_b7 : 1; //当前正在充电的包，0为下，1为上
	}one;
	unsigned char all;
} ptl_rx_stack_TypeDef;


typedef struct
{
	struct struct_tcb
	{
		unsigned rdy : 1;
		unsigned enable : 1;
	}one;
	unsigned char delay;
	unsigned char step;
}OSTCB_TypeDef;



OS_EXT  union bits_decompound //announce a union save special bits
{
	struct struct0
	{
		unsigned ms1_s : 1; //
		unsigned serial_e : 1;//使能串口发送
	}one;
	unsigned char all[2];
}bt;



OS_EXT unsigned char system_counter;
OS_EXT unsigned char system_step;
OS_EXT unsigned char key_num;
OS_EXT unsigned char key_temp; //键值暂存
OS_EXT CHAR_TypeDef key;
OS_EXT char outputData[100];//输出数据缓存
OS_EXT HANDLE hCom;//句柄，用于初始化串口
OS_EXT char _pc0;//模拟io口

#endif
