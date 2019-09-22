/*
*********************************************************************************************************
*********************************************************************************************************
* File : ucos.c
* By : Minglie
* Date :
*********************************************************************************************************
*/

#include <windows.h>
#include "Main_Constant.h"
#include "ucos.h"


 OSTCB_TypeDef task[1];
//task0µÄ±äÁ¿
 unsigned char task0_dat_cur;
 unsigned char task0_wait_com_h_count;
 unsigned char task0_wait_com_l_count;
 unsigned char task0_tx_buf;
 unsigned char task0_tx_buf_temp;
 unsigned char task0_rx_buf;
 unsigned char task0_rx_buf_temp;
 unsigned char task0_level_count;
 unsigned char task0_bit_no_back;
 unsigned char task0_bit_level_s;
 unsigned char task0_bit_com_err;


void os_init()
{
	



}

#if config_single_wire_task0_mode==0
void task0()
{
	
	if (task[OSTCBCur].one.rdy)
	{
		switch (task[OSTCBCur].step)
		{
			case 0: {			
				COM_L();	
				OSTimeDly(5);
				task[OSTCBCur].step = 1;
				break;
			}
			case 1: {
				COM_H();	
				OSTimeDly(10);
				task[OSTCBCur].step = 2;
				break;
			}
			case 2: {
				COM_L();	
				OSTimeDly(1);
				task[OSTCBCur].step = 3;
				break;
			}
			case 3: {
				COM_H();	
				OSTimeDly(1);
				task[OSTCBCur].step = 4;
				break;
			}
			case 4: {
				COM_L();	
				OSTimeDly(25);
				task[OSTCBCur].step = 5;
				break;
			}
			case 5: {
				COM_H();	
				OSTimeDly(30);
				task[OSTCBCur].step = 6;
				break;
			}
			case 6: {
				COM_L();	
				OSTimeDly(3);
				task[OSTCBCur].step = 0;
				break;
			}
		
		}
	}
	
}
#endif

void OSTimeTick()
{
	if(task[0].delay ==0) task[0].one.rdy=1;
	else task[0].delay --;
	task0();
}