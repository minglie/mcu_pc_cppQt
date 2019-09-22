
/*
*********************************************************************************************************


*********************************************************************************************************
* File : subprogram.c
* By : Minglie
* Date :
*********************************************************************************************************
*/

#include <iostream>
using namespace std;

#define OS_GLOBALS
#include <windows.h>
#include <stdio.h>
#include "Function.h"
#include "Main_Constant.h"
#include "PC.h"
#include "ucos.h"
#include "MingStopWatch.h"

class Box
{
   public:
      double length;   // 盒子的长度
      double breadth;  // 盒子的宽度
      double height;   // 盒子的高度
};



//--------------------Mcu pow-up initialize-----------------
void mcu_init()
{
	 variable_init();

}

void variable_init()
{
	bt.all[0] = 0;
	bt.all[1] = 0;
	
}






int max(int a, int b)  
{  
    return a > b ? a : b;  
}  



void key_scan(){

     key_num=key.all;

}


void key_serve(){

	char p[10]="abc";
		
	if(key_num>0){
		cout <<p;
		printf("wwwwwwwwwwwwwwwww%dwwwwwwwwwww",strlen(p));
		printf("-------执行按键%d的服务----------\n",key_num);
		switch (key_num){
			case 1: break;
			case 2: break;
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: break;
			case 7: pc_serial_sendDat(p); break;
		}
	}
	
	key.all=0;
}




void mcu_task()
{
	MingStopWatch timer;
	long long t_us=0;
	int count=0;
	while(1){

		if(1){	
			
		    t_us=timer.getDeltatTime_us();
		    count++;
		    if(count>50){
				count=0;
				cout<<"mcu_us:"<<t_us<<endl;
			}
		}
		 
		 key_scan();
	     key_serve();
		 OSTimeTick();
	     Sleep(10);
	}
}
