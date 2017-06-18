#ifndef _UPAPP_H_
#define _UPAPP_H_

//下载命令宏定义 
#define  DownLoad_APP                                               0x55
#define  Check_DownLoad_Station								        0xD0
#define  Enable_UpAPP       								        0xD1
#define  Alarm_Dont_Enable_UpAPP       							    0xD2
#define  Lost_The_ADDR_Frame         							    0xD3
#define  Turn_To_APP         							            0xD4
#define  APP_Too_Large         							            0xD5
#define  APP_StartADDR_Too_Small         				            0xD6
#define  APP_Size_Too_Big         				                    0xD7

//站位板关于升级的命令宏定义
#define  CheckVersion_To_TrunTo_BootLoader         				    0xDA
#define  Dont_Have_BootLoader         				                0xDB
#define  Turn_To_BootLoader_APP        				                0xDC
#define  CheckVersion_For_Station      				                0xDD


//下载相关数据控制宏定义
#define  DownLoad_APP_Frame_Number  								74
#define  APP_INTR_LADDR      								        0x01
#define  APP_INTR_HADDR      								        0x02
#define  Last_Frame_APP_DATA  								        0x55
#define  APP_DownLoad_DATA_Number_Per_Frame                         64




//flash各存储数据，首地址宏定义
#define MCU_Start_ADDR_At_PFlash					                0x0000 

#define APP_LestStart_ADDR_At_PFlash				                0x0400
#define BootLoader_Start_ADDR_At_PFlash				                0xD000 


#define APP_DATA_StartADDR_At_DFlash                                0xF000
#define BootLoader_INTR_Table_Start_ADDR_At_DFlash					0xF100 
#define APP_INTR_Table_Start_ADDR_At_DFlash				        	0xF200 
#define BootLoader_APP_For_UpAPP_Data_Start_ADDR_At_DFlash			0xF300 

//XDATA区域，地址定义
#define For_Program_Flash_Temp_StartADDR_At_XDATA				        	0xF200 
#define THE_FIRST_ADDR_For_Store_LaserNumber_At_XDATA				        	        0xF400
//FLASH标记
#define ub_True_Flag                                                0x55

void Erase_Flash_One_Page(ubyte code * Flash_ADDR_Parameter);

void Program_BootLoader_Flag_DATA_To_DFlash(void);
void Load_DFlash_To_PFlash_Function(ubyte code* PFlash_ADDR_Parameter, ubyte code * DFlash_ADDR_Parameter, ubyte Load_Counter);
void Load_BootLoader_INTR_Table_To_MCU_Start_ADDR(void);


#endif 