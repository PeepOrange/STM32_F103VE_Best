#include "MyApp.h"
#include "App_Icon1.c"
#include "App_Icon2.c"
#include "App_Icon3.c"
#include "App_Icon4.c"
#include "App_Icon5.c"
#include "App_Icon6.c"
#include "BackGrand_320-240.c"

ICONVIEW_Handle MIDWIN;
WM_HWIN   AppWin;
#define APP_Menu_ID  GUI_ID_USER+1





//中文字库回调函数及其参数
GUI_XBF_DATA XBF_Data;
GUI_FONT     XBF_Font;
static int _cbGetData(U32 Offset, U16 NumBytes, void * pVoid, void * pBuffer)
{
	SPI_FLASH_BufferRead(pBuffer,60*4096+Offset,NumBytes);
	return 0;
}











void UserAPP()
{
    OS_ERR err;
  //设置中文字库，保存在w25q64，起始地址64*4096，1.23MB  


    GUI_XBF_CreateFont(&XBF_Font,&XBF_Data,GUI_XBF_TYPE_PROP,_cbGetData,0);     
    GUI_UC_SetEncodeUTF8();
    GUI_SetDefaultFont(&XBF_Font);        
   
    GUI_DrawBitmap(&bmBackGrand_320240,0,0);
    CreateTopWin();  //创建最上方的工具栏
    CreateAppWin();  //创建APP界面
//	WM_SetCallback(WM_HBKWIN,(void*) AppShow_CallBack);
    GUI_CURSOR_Show();      
    GUI_CURSOR_Select(&GUI_CursorArrowS); //小光标


  while(1)
    
  {
      GUI_TOUCH_Exec();
      GUI_Exec(); 
      WM_Exec();
      OSTimeDly(10,OS_OPT_TIME_DLY,&err);
      
  }
    
}







static void CreateTopWin(void)
{
   	WM_HWIN hText;
	hText = TEXT_CreateEx(0, 0, 320 , 16, WM_HBKWIN, WM_CF_SHOW, GUI_TA_LEFT|TEXT_CF_VCENTER, GUI_ID_TEXT0, "Oragne OS");   
	TEXT_SetFont(hText, GUI_FONT_10_ASCII);
	TEXT_SetTextColor(hText,GUI_WHITE); 
}


static void CreateAppWin(void)
{
    AppWin= WM_CreateWindowAsChild(0,16,320,240-16,WM_HBKWIN,WM_CF_SHOW,(void *)AppShow_CallBack , 10);
    MIDWIN=ICONVIEW_CreateEx(70,30,180,160,AppWin,WM_CF_SHOW | WM_CF_HASTRANS,ICONVIEW_CF_AUTOSCROLLBAR_V,APP_Menu_ID,60,80); //ICONVIEW_CF_AUTOSCROLLBAR_V

    ICONVIEW_SetBkColor(MIDWIN,ICONVIEW_CI_SEL,GUI_DARKGRAY);     //被选中的小工具浅灰色
    ICONVIEW_SetFrame(MIDWIN, GUI_COORD_X, 0);//设置图标到IconView边框的间距
    ICONVIEW_SetFrame(MIDWIN, GUI_COORD_Y, 0);
    ICONVIEW_SetSpace(MIDWIN, GUI_COORD_X, 0);//设置图标和图标之间的间距
    ICONVIEW_SetSpace(MIDWIN, GUI_COORD_Y, 0);

    
    ICONVIEW_AddBitmapItem(MIDWIN, &bmApp_Icon1, "LED控制");
    ICONVIEW_AddBitmapItem(MIDWIN, &bmApp_Icon2, "Linkman联系人");
    ICONVIEW_AddBitmapItem(MIDWIN, &bmApp_Icon3, "WIFI网络");
    ICONVIEW_AddBitmapItem(MIDWIN, &bmApp_Icon4, "New信息");
    ICONVIEW_AddBitmapItem(MIDWIN, &bmApp_Icon5, "Set设置");
    ICONVIEW_AddBitmapItem(MIDWIN, &bmApp_Icon6, "Game游戏");
    

}    


 void AppShow_CallBack(WM_MESSAGE * pMsg)
{
    int NCode, Id;
    switch (pMsg->MsgId) 
    {
		case WM_NOTIFY_PARENT:
              Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
              NCode = pMsg->Data.v;                 /* Notification code */   
			switch (Id)  
            {
                case APP_Menu_ID:
                   switch (NCode) 
					{ 
						/* ICON控件点击消息 */
						case WM_NOTIFICATION_CLICKED:							
							break;  
						/* ICON控件点击消息 */
						case WM_NOTIFICATION_RELEASED: 
							switch(ICONVIEW_GetSel(pMsg->hWinSrc))
                            {
                                    case 0:	
									APP1_Click();	
									break;	
                                    
                                    case 1:	
									APP2_Click();			
									break;	

                                    case 2:	
									APP3_Click();			
									break;	

                                    case 3:	
									APP4_Click();			
									break;	    

                                    case 4:	
									APP5_Click();			
									break;	

                                    case 5:	
									APP6_Click();			
									break;	  
								
                                    default:break;                                    
                            }
                    break;        
                    }
             break;
            }
     break;
            
		case WM_PAINT: 
        {
		GUI_Delay(10); 				        
		break;	            
        }		
          default:
          WM_DefaultProc(pMsg);
          break;
    }
}





static void APP1_Click(void)
{
    
    LED1_TOGGLE;
    
}
static void APP2_Click(void)
{
    
    LED2_TOGGLE;
    
}
static void APP3_Click(void)
{
    
    LED3_TOGGLE;
    
}
static void APP4_Click(void)
{
    LED1_TOGGLE;
    
    
}
static void APP5_Click(void)
{
    LED2_TOGGLE;
    
    
}
static void APP6_Click(void)
{
    
    LED3_TOGGLE;
    
}









