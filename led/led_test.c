#include <pthread.h>
#include <unistd.h>
#include "dev_so.h"

//=======================================================================================
//LED_CMD_NUM 该值尽量设大一些，可避免数待执行命令的条数
#define LED_CMD_NUM 128
#define LED_COLORFUL_CMD_NUM 80

#define LED_ON_GPIOEX(X,L)	\
                        "echo " #X " >/sys/class/gpio/unexport", \
						"echo " #X" >/sys/class/gpio/export",	\
						"echo out >/sys/class/gpio/gpio" #X "/direction",	\
						"echo " #L " >/sys/class/gpio/gpio" #X "/value",	\
						"echo " #X " >/sys/class/gpio/unexport"

#define LED1_ON		"gpio 0 func 0","gpio 0 out 1"
#define LED1_OFF	"gpio 0 func 0","gpio 0 out 0"

#define LED2_ON		"gpio 1 func 0","gpio 1 out 0"

#define LED3_ON		"gpio 4 func 0","gpio 4 out 1"
#define LED3_OFF	"gpio 4 func 0","gpio 4 out 0"

#define LED4_ON		"gpio 11 func 0","gpio 11 out 0"

#define LED5_ON		"gpio 14 func 0","gpio 14 out 0"

#define LED6_ON		"gpio 16 func 0","gpio 16 out 0"

#define LED7_ON		LED_ON_GPIOEX(54,0)
#define LED7_OFF	LED_ON_GPIOEX(54,1)

#define LED8_ON		LED_ON_GPIOEX(55,0)
#define LED8_OFF	LED_ON_GPIOEX(55,1)

#define LED9_ON		LED_ON_GPIOEX(56,0)

#define LED10_ON	LED_ON_GPIOEX(57,0)

#define LED11_ON	LED_ON_GPIOEX(58,0)

#define LED12_ON	LED_ON_GPIOEX(59,0)

#define LED13_ON	LED_ON_GPIOEX(60,0)

#define LED14_ON	LED_ON_GPIOEX(34,0)
#define LED14_OFF	LED_ON_GPIOEX(34,1)

#define LED15_ON	LED_ON_GPIOEX(35,0)
#define LED15_OFF	LED_ON_GPIOEX(35,1)

#define LED16_ON	LED_ON_GPIOEX(36,0)
#define LED16_OFF	LED_ON_GPIOEX(36,1)

#define LED17_ON	LED_ON_GPIOEX(37,0)
#define LED17_OFF	LED_ON_GPIOEX(37,1)

#define LED18_ON    LED_ON_GPIOEX(47,0)
#define LED19_ON    LED_ON_GPIOEX(46,0)

#define LED_CMD		LED1_OFF,LED2_ON,LED3_ON,LED4_ON,LED5_ON,LED6_ON,LED7_OFF,LED8_ON,LED9_ON,	\
					LED10_ON,LED11_ON,LED12_ON,LED13_ON,LED14_OFF,LED15_ON,LED16_OFF,LED17_ON,  \
					LED18_ON,LED19_ON
					
#define COLOR_CHANGE
#define CHANGE_TIMES	3
#define LED_COLORFUL_CMD	LED3_OFF,LED1_ON,LED8_OFF,LED7_ON,LED15_OFF,LED14_ON,LED17_OFF,LED16_ON,	\
							LED1_OFF,LED3_ON,LED7_OFF,LED8_ON,LED14_OFF,LED15_ON,LED16_OFF,LED17_ON

							

//=======================================================================================================================================================

extern DEV_TEST_GLOBAL_DATA_T stGlobalData;

COMMON_ERROR_ENUM led_test(DEV_TEST_INFO_T *pstDevTestInfo)//led灯测试
{
    if(NULL == pstDevTestInfo)
    {
	  return CommonError_NullPointer;
    }	
	
	char *apcCtrlLedCmdList[] = {LED_CMD};

	int iLoop;

	COMMON_ERROR_ENUM enComRet;

    int iCmdNums = sizeof(apcCtrlLedCmdList)/sizeof(char *);
    printf("iCmdNums == %d\n",iCmdNums);
   
	for(iLoop=0; iLoop < iCmdNums; iLoop++)
	{
		SystemCall(apcCtrlLedCmdList[iLoop]);
	}	
	
	int times = CHANGE_TIMES;
	for(;times > 0; times--)
	{
		sleep(1);
		char *apcCtrlLedCmdList[] = {LED_COLORFUL_CMD};
		iCmdNums = sizeof(apcCtrlLedCmdList)/sizeof(char *);
		for(iLoop=0; iLoop < iCmdNums; iLoop++)
		{
			if((iCmdNums/2) == iLoop)
			{
				sleep(1);				
			}
			SystemCall(apcCtrlLedCmdList[iLoop]);
			debug_msg("[%s][%d][Show Info] SystemCall: %s\n", __func__, __LINE__, apcCtrlLedCmdList[iLoop]);			
		}
	}
	
    return CommonError_OK;
}

