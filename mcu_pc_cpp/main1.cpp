#include <windows.h>
#include <stdio.h>
#include "Function.h"
#include "Main_Constant.h"
#include "PC.h"



int main()
{
	pc_init();
	pc_createHandle();
   	mcu_task();
	pc_closeHandle();
	return 0;
}
