/*
*********************************************************************************************************


*********************************************************************************************************
* File : PC.h
* By : Minglie
* Date :
*********************************************************************************************************
*/

/* Function header file, all the function be used in program */

#ifndef __PC_H
#define __PC_H

void pc_init();
void serial_init();
void pc_serial_sendDat(char dat[]);
void pc_createHandle();
void pc_closeHandle();

#endif





