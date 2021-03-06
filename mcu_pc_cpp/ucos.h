/*
*********************************************************************************************************
*********************************************************************************************************
* File : ucos.h
* By : Minglie
* Date :
*********************************************************************************************************
*/

#ifndef __Ucos_H
#define __Ucos_H



void os_init();
void OSTimeTick();
void task0(void);

#define OSTCBCur 0
#define OSTimeDly(k) {task[OSTCBCur].one.rdy =0; task[OSTCBCur].delay =k-1; }


#define config_max_tasks 1 //最大任务个数
#define configTICK_RATE_us 800 //800us 配置心跳周期

#define config_single_wire_task0_mode 0 //单线工作模式，0为主机，1为从机
#define config_com_task0_lengh 8 //配置通信有效位数，只能取2,4,6,8

#define  COM_L() _pc0=0
#define  COM_H() _pc0=1
#define  COM     _pc0
 


#endif

