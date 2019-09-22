
/*
*********************************************************************************************************


*********************************************************************************************************
* File : subprogram.c
* By : Minglie
* Date :
*********************************************************************************************************
*/
#include <iostream>
#include <fstream>   
#include <string>
#include <windows.h>
#include <stdio.h>
#include "Function.h"
#include "Main_Constant.h"
#include "ucos.h"
#include "PC.h"


using namespace std;


class MingStopWatch
{
public:
    MingStopWatch();
	double now();
    void start();
    void stop();
    double getElapsedTime(); //in s
	double getDeltatTime();
	long long getDeltatTime_us();
		
private:
    LARGE_INTEGER m_start;
	LARGE_INTEGER m_now;
	LARGE_INTEGER m_old;
    LARGE_INTEGER m_stop;
    LARGE_INTEGER m_frequency;
};












HANDLE HRead,HWrite,HMessure;//


void pc_init(){

   serial_init();
	
}


void serial_init(){
    // 初始化串口
    hCom = CreateFile(TEXT("COM2"), GENERIC_READ | GENERIC_WRITE , 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    // 获取和设置串口参数
    DCB myDCB;
    GetCommState(hCom, &myDCB);  // 获取串口参数
    printf("baud rate is %d",(int)myDCB.BaudRate);
    fflush(stdout);
    myDCB.BaudRate = 9600;       // 波特率
    myDCB.Parity  =  NOPARITY;   // 校验位
    myDCB.ByteSize = 8;          // 数据位
    myDCB.StopBits = ONESTOPBIT; // 停止位
    SetCommState(hCom, &myDCB);  // 设置串口参数
}


void pc_serial_sendDat(char dat[]){ 

    DWORD strLength = strlen(dat);
	WriteFile(hCom,dat,strLength,&strLength,NULL);
	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR); 
}



DWORD WINAPI threadWrite(LPVOID lpParameter)
{  
    if( hCom==INVALID_HANDLE_VALUE ){
        puts("打开串口失败");
        return 0;
    }
    DWORD strLength = 0;
    while(1)
    {      
		if(0){
			  strLength = strlen(outputData);
			  printf("string length is %d\n",strLength);              // 打印字符串长度
              WriteFile(hCom,outputData,strLength,&strLength,NULL); // 串口发送字符串
              PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);            //清空缓冲区	
			  bt.one.serial_e=0;
		}	
        Sleep(1000);
    }
    return 0;
}

DWORD WINAPI threadRead(LPVOID lpParameter)
{
    if( hCom==INVALID_HANDLE_VALUE )   //INVALID_HANDLE_VALUE表示出错，会设置GetLastError
    {
        puts("打开串口失败");
        return 0;
    }

    char getputData[100]={0x00};//输入数据缓存
    // 利用错误信息来获取进入串口缓冲区数据的字节数
    DWORD dwErrors;     // 错误信息
    COMSTAT Rcs;        // COMSTAT结构通信设备的当前信息
    int Len=0;
    DWORD length = 100;               //用来接收读取的字节数
    while(1){
        for(int i=0;i<100;i++){
            getputData[i]=0;
        }
        ClearCommError(hCom,
                &dwErrors,
                &Rcs);                                // 获取读缓冲区数据长度
        Len = Rcs.cbInQue;
        ReadFile(hCom,getputData,Len,&length,NULL);   //获取字符串
        PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);  //清空缓冲区
        if(Len>0)
        {
            printf("%s\n",getputData);
            fflush(stdout);
        }	
		key.all= getputData[0];      
	    Sleep(100);
    }
    return 0;
}


/*
DWORD WINAPI threadMessure(LPVOID lpParameter)
{    
	char p[5]="1";
    while(1)
    {     
		if(COM){
			p[0]='1';
		}else{
			p[0]='0';
		}
	
		pc_serial_sendDat(p);

		Sleep(1);
    }
    return 0;
}
*/





DWORD WINAPI threadMessure(LPVOID lpParameter)
{    
	ofstream out("wave.txt");  
	int count=0;
	char p[5]="1";
	
	//MingStopWatch timer;
 
	while(1)
    {    
		//cout<<"MessureTask:"<<timer.getDeltatTime_us()<<endl;
		count++;
		if(COM){
			p[0]='1';
		}else{
			p[0]='0';
		}
		out << p[0];	 
		if(count>10){			
			 out.flush();
		}
	    Sleep(10);
    }
	out.close();  
    return 0;
}



void pc_createHandle(){	

    HWrite = CreateThread(NULL,0,threadWrite,NULL,0,NULL);
    HRead  = CreateThread(NULL,0,threadRead,NULL,0,NULL);
	HMessure=CreateThread(NULL,0,threadMessure,NULL,0,NULL);
}



void pc_closeHandle(){
	CloseHandle(HRead);
    CloseHandle(HWrite);
	CloseHandle(HMessure);
}