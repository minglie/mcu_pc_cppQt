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


#define config_max_tasks 1 //����������
#define configTICK_RATE_us 800 //800us ������������

#define config_single_wire_task0_mode 0 //���߹���ģʽ��0Ϊ������1Ϊ�ӻ�
#define config_com_task0_lengh 8 //����ͨ����Чλ����ֻ��ȡ2,4,6,8

#define  COM_L() _pc0=0
#define  COM_H() _pc0=1
#define  COM     _pc0
 


#endif

