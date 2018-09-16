#ifndef __MyAPP_H__
#define __MyAPP_H__

#include "includes.h"
#include "GUI.h"
#include "DIALOG.h"
#include  <os.h>	
#include  <stm32f10x.h>




static void CreateAppWin(void);
static void CreateTopWin(void);
 void AppShow_CallBack(WM_MESSAGE * pMsg);
static void APP1_Click(void);
static void APP2_Click(void);
static void APP3_Click(void);
static void APP4_Click(void);
static void APP5_Click(void);
static void APP6_Click(void);


void UserAPP(void);




#endif



