
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
    // ��ʼ������
    hCom = CreateFile(TEXT("COM2"), GENERIC_READ | GENERIC_WRITE , 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    // ��ȡ�����ô��ڲ���
    DCB myDCB;
    GetCommState(hCom, &myDCB);  // ��ȡ���ڲ���
    printf("baud rate is %d",(int)myDCB.BaudRate);
    fflush(stdout);
    myDCB.BaudRate = 9600;       // ������
    myDCB.Parity  =  NOPARITY;   // У��λ
    myDCB.ByteSize = 8;          // ����λ
    myDCB.StopBits = ONESTOPBIT; // ֹͣλ
    SetCommState(hCom, &myDCB);  // ���ô��ڲ���
}


void pc_serial_sendDat(char dat[]){ 

    DWORD strLength = strlen(dat);
	WriteFile(hCom,dat,strLength,&strLength,NULL);
	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR); 
}



DWORD WINAPI threadWrite(LPVOID lpParameter)
{  
    if( hCom==INVALID_HANDLE_VALUE ){
        puts("�򿪴���ʧ��");
        return 0;
    }
    DWORD strLength = 0;
    while(1)
    {      
		if(0){
			  strLength = strlen(outputData);
			  printf("string length is %d\n",strLength);              // ��ӡ�ַ�������
              WriteFile(hCom,outputData,strLength,&strLength,NULL); // ���ڷ����ַ���
              PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);            //��ջ�����	
			  bt.one.serial_e=0;
		}	
        Sleep(1000);
    }
    return 0;
}

DWORD WINAPI threadRead(LPVOID lpParameter)
{
    if( hCom==INVALID_HANDLE_VALUE )   //INVALID_HANDLE_VALUE��ʾ����������GetLastError
    {
        puts("�򿪴���ʧ��");
        return 0;
    }

    char getputData[100]={0x00};//�������ݻ���
    // ���ô�����Ϣ����ȡ���봮�ڻ��������ݵ��ֽ���
    DWORD dwErrors;     // ������Ϣ
    COMSTAT Rcs;        // COMSTAT�ṹͨ���豸�ĵ�ǰ��Ϣ
    int Len=0;
    DWORD length = 100;               //�������ն�ȡ���ֽ���
    while(1){
        for(int i=0;i<100;i++){
            getputData[i]=0;
        }
        ClearCommError(hCom,
                &dwErrors,
                &Rcs);                                // ��ȡ�����������ݳ���
        Len = Rcs.cbInQue;
        ReadFile(hCom,getputData,Len,&length,NULL);   //��ȡ�ַ���
        PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);  //��ջ�����
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