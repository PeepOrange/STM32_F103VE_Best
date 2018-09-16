#include "includes.h"

/*
*********************************************************************************************************
*                                                 TCB
*********************************************************************************************************
*/
static  OS_TCB	 AppTaskStartTCB;		     //����������ƿ�
static  OS_TCB   AppTaskUserappTCB;
/*
*********************************************************************************************************
*                                                STACKS
*********************************************************************************************************
*/
static	CPU_STK	 AppTaskStartStk[APP_TASK_START_STK_SIZE];	   //���������ջ
__align(8) static  CPU_STK  AppTaskUserappStk[APP_TASK_USERAPP_STK_SIZE];

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static  void   AppTaskStart(void *p_arg);
static  void   AppTaskCreate(void);
static  void   AppTaskUserapp(void *p_arg);
/*********************************************************************
*
*       data
*
**********************************************************************
*/
/*---------- FatFS data ----------*/
FIL 		file;				/* file objects */
FRESULT result; 
UINT 		bw;  			/* File R/W count */

uint8_t IsCal =0;
//uint8_t tpad_flag=0;
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	OS_ERR err;	
	
	/* ��ʼ��"uC/OS-III"�ں� */  
	OSInit(&err);	
	
	/*��������*/
	OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,              // ������ƿ�ָ��          
               (CPU_CHAR   *)"App Task Start",		          // ��������
               (OS_TASK_PTR )AppTaskStart, 	                  // �������ָ��
               (void       *)0,			                      // ���ݸ�����Ĳ���parg
               (OS_PRIO     )APP_TASK_START_PRIO,			  // �������ȼ�
               (CPU_STK    *)&AppTaskStartStk[0],	          // �����ջ����ַ
               (CPU_STK_SIZE)APP_TASK_START_STK_SIZE/10,	  // ��ջʣ�ྯ����
               (CPU_STK_SIZE)APP_TASK_START_STK_SIZE,		  // ��ջ��С
               (OS_MSG_QTY  )1u,			                      // �ɽ��յ������Ϣ������
               (OS_TICK     )0u,			                      // ʱ��Ƭ��תʱ��
               (void       *)0,			                      // ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // ����ѡ��
               (OS_ERR     *)&err);		                    // ����ֵ
	  
  /* ����������ϵͳ������Ȩ����uC/OS-III */
  OSStart(&err);  
}

/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static void  AppTaskStart(void *p_arg)
{
    OS_ERR      err;

   (void)p_arg;
	
	/* �弶��ʼ�� */	
    BSP_Init();                                                 /* Ӳ���ײ��ʼ��������GUI��ʼ��*/
    CPU_Init();                                                 //ϵͳ�ں˳�ʼ��
	BSP_Tick_Init();                                            //ϵͳ����ʱ�ӳ�ʼ��


#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* ����CPUͳ�ƹ���          */
#endif
    
    OS_INFO("Creating Application Tasks...\n\r");
    AppTaskCreate();                                            /* ����Ӧ������                            */
    OS_INFO("Creating Application Events...\n\r");
	
    while (DEF_TRUE) 
   {                                          /* 15ms���һ����Ļ����       */
        GUI_TOUCH_Exec();
        OSTimeDlyHMSM(0, 0, 0, 15,
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
   }
}




/**************  Ӳ�����󣨶�FLASH����   ***************/
void hardwareerr(void)
{
	OS_ERR  err;
	if(IsCal==0xE0)
	{
		printf("FLASH_FATFS mount fail!!!\n");
		GUI_Clear();
		GUI_DispStringHCenterAt("FLASH_FATFS mount fail", 120,120);
		LCD_BK_EN;
		while(1)
		{
			LED1_ON;
			OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err);
			LED1_OFF;	
			OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
		}
	}

}
/*
*********************************************************************************************************
*	�� �� ��: AppTaskUserapp
*	����˵��: LED4��˸
*	��    �Σ�p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ����2
*********************************************************************************************************
*/
static void AppTaskUserapp(void *p_arg)
{
	(void)p_arg;		/* ����������澯 */
	if(IsCal!=0x55)
	{
		hardwareerr();
	}
	while (1) 
	{   		
		UserAPP();          //�û�APP
        
	}
}
/*
*********************************************************************************************************
*	�� �� ��: AppTaskCreate
*	����˵��: ����Ӧ������
*	��    �Σ�p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static  void  AppTaskCreate(void)
{
	OS_ERR      err;
	

	
	/***********************************/
	OSTaskCreate((OS_TCB       *)&AppTaskUserappTCB,             
                 (CPU_CHAR     *)"�û�APP",
                 (OS_TASK_PTR   )AppTaskUserapp, 
                 (void         *)0,
                 (OS_PRIO       )APP_TASK_USERAPP_PRIO,
                 (CPU_STK      *)&AppTaskUserappStk[0],
                 (CPU_STK_SIZE  )APP_TASK_USERAPP_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_TASK_USERAPP_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);										 
}




/*********************************************END OF FILE**********************/
