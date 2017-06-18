//****************************************************************************
// @Module        Project Settings
// @Filename      MAIN.C
// @Project       161018.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC878CM-16FF
//
// @Compiler      Keil
//
// @Codegenerator 2.2
//
// @Description   This file contains the Project initialization function.
//
//----------------------------------------------------------------------------
// @Date          2016-11-23 15:47:20
//
//****************************************************************************

// USER CODE BEGIN (MAIN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (MAIN_General,2)
uword  idata  T0_5MS_count_infull,  T0_5MS_count_input, T0_5MS_count_output, T0_5MS_count_same_ID_re_read;  //4个5毫秒定时计数变量。分别应用于，进站传感器满、出站传感器满、进站持续时间，出站持续时间的定时。
ubyte     T0_5MS_count1,	//count1计数。应用于判断和主机通信时间是否过长时使用。5ms一个计数。	count_worker_id应用于定时扫描登陆读卡器。
      T0_5MS_count_YJ_id,  T0_5MS_IDread_frame_count,  T0_5MS_count_Waiting_CAN_Send_INTR_Flag,
	   T0_5MS_count_complete_scan, T0_5MS_count_scan_stop_moto_1, T0_5MS_count_scan_stop_moto_2;
	  //  count_KEY_SCAN。定时扫描键盘。
bool   FRAME_start_1,  in_full,   	b_same_ID_re_read_flag,	   
      //FRAME_start,和主机通信的开始标记符。 FRAME_start_1和读卡器通信的开始标记符。
	  //FRAME_end，和主机通信的结束标记符。	in_full，进站满标记符。	out_full出站满标记符。
	  //worker_quit_flag，员工退出登录标记符。
      FRAME_end_1, have_id_data,  ID_read_enable,  input_yj_flag, b_input_yj_flag_2,  b_input_yj_flag_3,
	  // FRAME_end_1 和读卡器通信结束标记符。have_id_data，有读卡数据的标记符。
	  // load_success登录成功标记符。	ID_read_enable，读卡器使能标记。1表示员工登陆读卡器使能，0表示，衣架读卡器使能。
	  // worker_load，员工登陆标记。通过键盘登陆的时候。
	  // input_yj_flag，进站动作命令，标记符
	  //output_yj_flag 出站动作命令，标记符
	  output_yj_flag, b_send_ID_enable,    b_T0_5MS_flag, b_COMPLETE_DONE_flag,  b_COMPLETE_KEY_LOCK_STATUS,
	   b_stop_moto_1_flag, b_stop_moto_2_flag;

bool  b_CAN_franme_start, b_CAN_franme_stop, b_Communicate_Error, b_Waiting_CAN_Send_Interupt_Flag,	 b_CAN_Send_Fail_Flag,
      b_CAN_traning, b_CAN_waiting_interrupt, b_CAN_tran_complete;

bool b_rs_485_2_traning, FRAME_start_rs485_lk, FRAME_end_rs485_lk, b_have_LCD_KEY_DATA, b_check_have_lcd_key;
ubyte idata ub_rs_485_2_TX_FIFO_COUNTER, ub_rs485_2_TX_FIFO_FUNC[4], ub_rs485_2_TX_status, ub_T0_5MS_count_re_485_2_wait_recieve;
ubyte pdata LCD_KEY_DATA[24], byte_count_rs485_lk, T0_5MS_rs485_lk_frame_count, T0_5MS_count_rs485_lk, RS485_LK_buff[24],
            ub_send_lcd_key_data_number, ub_lcd_key_send_pc_number;
ubyte       byte_count_1, DEV_ADDR, error_data[1], in_out_time[2], 		
         // buff[27]，和主机通信的buff。byte_count，和主机通信的，一帧通信字节计数器。
		 //	byte_count_1，和读卡器通信的通信字节计数器。
		 //DEV_ADDR，设备地址。	 error_data[1]，报错内容。	in_out_time[2]，进站和出站延时时间。
          send_data[17],IDCARD_data[30], full_data[1], 
		  //send_data[17],   和读卡器通信的buff。  IDCARD_data[10]，存储卡号的buff。同时也用作键盘登陆时候，保存的6位卡号和4位密码	、
		  //full_data[1]工站状态字节。包括是否登陆，是否进站满，是否出站满
		    push_count;
		  // password_count，键盘输入密码的时候，密码位数的计数器。
		  //worker_ID_count键盘输入的时候，工号输入的位数计数器。
		  //push_count，按按钮计数器。确保预出站的地方大于三个衣架的时候，禁止完成按钮。

ubyte idata in_time_last, out_time_last, CAN_TX_BUFF[24], CAN_RX_BUFF[24], CAN_BYTE_DATA_COUNT,  can_tx_status, can_traning_frame_number;
ubyte idata TX_FIFO_FUNC[4], TX_FIFO_COUNTER;

ulong idata can_tx_id;
uword idata uw_T0_5MS_count_input_2, uw_T0_5MS_count_input_3;
ubyte pdata Version_and_Sequence[16];

ubyte idata ubPutDownYjDelay;
bool  b_PutDownYjFlag;
uword idata T0_5MS_count_PutDownYjDelay;
/********* 绑定条码 *************/
bool b_IDNumber_With_LaserNumber_flag,	b_Have_Got_LaserNumber_Flag;
ubyte ub_A_LaserNumber_Count, ub_Send_LaserNumber_Count, ub_STORE_Count_LaserNumbers_In_XDATA_ADDR, ub_Output_Count_LaserNumber_In_XDATA_ADDR;
ubyte xdata *Store_Laser_Number_ADDR_IN_XDATA;
ubyte xdata *Output_Laser_Number_ADDR_IN_XDATA;
ubyte pdata Laser_Temp_DATA[20];

/********LED IN LED.H************/
ubyte pdata ub_T0_5MS_count_led, ub_LED_Status;
/*****UPdata*****/
ubyte ub_Have_BootLoader_APP;
bool b_Turn_To_BootLoader_Flag;
bool b_Flag;
ubyte code *DFlash_ADDR;
ubyte xdata *XDATA_P;
ubyte code *PFlash_ADDR;

//ubyte code error[] = {"工号超出范围"};

//ubyte xdata ADDR_BUFF _at_ 0xF3E0;
//ubyte xdata IN_TIME  _at_ 0xF3E1;		
//ubyte xdata OUT_TIME  _at_ 0xF3E2;
//ubyte xdata IN_TIME_FOR_LAST _at_ 0xF3E3;
//ubyte xdata OUT_TIME_FOR_LAST _at_ 0xF3E4;
// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (MAIN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (MAIN_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (MAIN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************


// USER CODE BEGIN (MAIN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (MAIN_General,9)

// USER CODE END


//****************************************************************************
// @Function      void MAIN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes the microcontroller. It is 
//                assumed that the SFRs are in their reset state.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2016-11-23
//
//****************************************************************************

// USER CODE BEGIN (MAIN_Init,1)

// USER CODE END

void MAIN_vInit(void)
{
  // USER CODE BEGIN (MAIN_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the System Clock:
  ///  -----------------------------------------------------------------------
  ///  - External Osc is selected (configuration is done in the startup file 
  ///    'START_XC.A51')
  ///  - PLL Mode, NDIV =  36, PDIV =  2, KDIV =  1
  ///  - input frequency is 8 MHz


  //   FCLK for MultiCAN runs at 2 times the frequency of PCLK.
  //   FCLK for CCU6 runs at 2 times the frequency of PCLK.
  //   FCLK for T2CCU runs at 2 times the frequency of PCLK.
  SFR_PAGE(_su1, noSST);         // switch to page1

  CMCON         =  0x10;         // load Clock Control Register
  CR_MISC       =  0x30;         // load Clock and Reset Miscellaneous 
                                 // Register

  SFR_PAGE(_su0, noSST);         // switch to page0


  ///  *********************************************************************************
  ///  Note : All peripheral related IO configurations are done in the 
  ///  respective peripheral modules (alternate functions selection)
  ///  *********************************************************************************

  ///  Initialization of module 'GPIO'
  IO_vInit();

  ///  Initialization of module 'Interrupt Unit'
  INT_vInit();

  ///  Initialization of module 'Timer 0/1'
  T01_vInit();

  ///  Initialization of module 'Watch Dog Timer'
  WDT_vInit();

  ///  Initialization of module 'MultiCAN Controller '
  CAN_vInit();

  ///  Initialization of module 'UART1 (Serial Interface)'
  UART1_vInit();

  ///  Initialization of  'Shared interrupts'
  SHINT_vInit();

  ///  -----------------------------------------------------------------------
  ///  Configuration of the External Interface Control Register (EINTCON):
  ///  -----------------------------------------------------------------------
  ///  - External interface globally disabled
  ///  - External data direction: Input
  ///  - All Bits of EINTCON can be written
  ///  - Address lines A8 to A15 disabled
  ///  - Address line A16 disabled
  ///  - Address line A17 disabled
  ///  - Address line A18 disabled
  ///  - Address line A19 disabled

  ///  *********************************************************************************
  ///  Note : Please make sure that proper Off-chip XDATA memory start 
  ///  address and size should be entered in the Off-chip Xdata memory 
  ///  section under Target settings option of Keil compiler.
  ///
  ///  Ex : If 0xFD00 is start address and 0x0100 is the size,
  ///  For KEIL these values should be entered in the keil IDE Off-chip Xdata 
  ///  memory section with ubyte xdata extmem_data[256] _at_ (0xFD00) 
  ///  declaration.
  ///  For SDCC it should be done using xdata at 0xfd00 ubyte 
  ///  extmem_data[256] declaration.
  ///  For IAR it should be done using __xdata __no_init ubyte 
  ///  extmem_data[256] @ 0xFD00 declaration.
  ///  *********************************************************************************

  SFR_PAGE(_su3, SST0);          // switch to page3
  EINTCON       =  0x00;         // External Interface Control Register
  SFR_PAGE(_su3, RST0);          // restore original page




  //   Interrupt Priority

  IP            =  0x00;         // load Interrupt Priority Register
  IPH           =  0x20;         // load Interrupt Priority High Register
  IP1           =  0x00;         // load Interrupt Priority 1 Register
  IPH1          =  0x00;         // load Interrupt Priority 1 High Register


  // USER CODE BEGIN (MAIN_Init,3)

  // USER CODE END

  //// Interrupt structure 2 mode 0 is selected.

  //// Interrupt service routine choice 2 is selected.

  //   globally enable interrupts
  EA            =  1;           

} //  End of function MAIN_vInit


//****************************************************************************
// @Function      void main(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the main function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2016-11-23
//
//****************************************************************************

// USER CODE BEGIN (MAIN_Main,1)
void Delay_function(int num)//延时函数
{
	while(num--);
}

void Ram_Init(void)
{
  FRAME_start_1  =    0;

  FRAME_end_1    =    0;



  b_COMPLETE_KEY_LOCK_STATUS = 0;

  b_send_ID_enable   = 0;

  b_T0_5MS_flag   =  0;
  
  b_same_ID_re_read_flag = 0;
  
//  T0_5MS_count1  =    0;	//5ms定时计数器2.用于判断通信中断超过长处理。

 // byte_count     =    0;	//接收数据计数器。也是buff【】数组的下标。

  byte_count_1   = 0;

  push_count    =  0;

 // LCD_check_busy_flag = 0;

 // T0_5MS_count_LCD_check_busy = 0;
  
  in_full        =    0;

 

  have_id_data     =    0;

 

  ID_read_enable   =    0;


 // in_out_time[2]   =    25;

 // in_out_time[3]   =    10;
  input_yj_flag  =  0;
  b_input_yj_flag_2 = 0;
  b_input_yj_flag_3 = 0;
  output_yj_flag =  0;

  INPUT_YJ_ENABLE   =     0;
  OUTPUT_YJ_ENABLE  =     0;
  DONE_YJ_ENABLE    =     0;
  MOTO_ENABLE       =     0;
  DisEnable_LED();
  P4_4              =     0;
  P3_6              =     0;
  P3_5              =     0;

  b_COMPLETE_DONE_flag = 0;
 
 // ID_reader_wrong_count = 0;
	
  T0_5MS_count_infull = 0;

  uw_T0_5MS_count_input_2 = 0;
  uw_T0_5MS_count_input_3 = 0;

  T0_5MS_count_input = 0;

  T0_5MS_count_output = 0;

 // T0_5MS_count_worker_id = 0;

  T0_5MS_count_YJ_id = 0;

  T0_5MS_count_same_ID_re_read = 0;

  
  
  b_PutDownYjFlag = 0;
  T0_5MS_count_PutDownYjDelay = 0;

  b_Communicate_Error = 0;
  b_Turn_To_BootLoader_Flag = 0;
  b_have_LCD_KEY_DATA = 0;
  b_check_have_lcd_key = 0;
  full_data[0] &= 0xBF;

  b_IDNumber_With_LaserNumber_flag = 0;
  b_Have_Got_LaserNumber_Flag = 0;

  Store_Laser_Number_ADDR_IN_XDATA = THE_FIRST_ADDR_For_Store_LaserNumber_At_XDATA;
  Output_Laser_Number_ADDR_IN_XDATA = THE_FIRST_ADDR_For_Store_LaserNumber_At_XDATA;
  ub_STORE_Count_LaserNumbers_In_XDATA_ADDR = 0;
  ub_Output_Count_LaserNumber_In_XDATA_ADDR = 0;


  Enable_Rxd();				//使能485芯片的接收功能。
}
// USER CODE END

void main(void)
{
  // USER CODE BEGIN (MAIN_Main,2)
  
  // USER CODE END

  MAIN_vInit();

  // USER CODE BEGIN (MAIN_Main,3)
 // DEV_ADDR       =    3;
  Read_Parameter_To_Ram();
  Ram_Init();
  set_Can_ID();

  


  
  
  

  // USER CODE END

  while(1)
  {

  // USER CODE BEGIN (MAIN_Main,4)


	  ubyte n;

	  WDT_vRefresh();
	  
	  execute_scan();
	  Scan_LED();	  
	  Idreader_scan();

	  COMPLEGE_DONE_SCAN();
	  T0_INT_SCAN();
	  rs485_lk_scan();
	  scan_rs_485_2();
	  rs_485_2_tx_status();
	  scan_can_tx_frame();
	  if(b_Turn_To_BootLoader_Flag)
	  {

		  WDT_vRefresh();
		  EA = 0;
	      Load_BootLoader_INTR_Table_To_MCU_Start_ADDR();
          ((void (code *) (void)) MCU_Start_ADDR_At_PFlash) ();
	  }
	 
	  if(b_Communicate_Error)
	  {
	      b_Communicate_Error = 0;
	      //can_tx_func_fifo(EEROR);
		  Get_CAN_Data();
	  }
	






      if(b_CAN_franme_start&&(!b_CAN_franme_stop)&&(8 <= T0_5MS_count1))
	  {
	      T0_5MS_count1  =    0;
		  clear_can_rx_buff_fun();
		  continue;
	  //此函数为判断，收到帧头后，中间间隔10ms以上没有收到帧尾，说明通信错误。
	  }

/***********************
if(!b_CAN_franme_stop) 
未接收到报尾。默认结束本次循环。不进行后续的处理。
************************/

      if(!b_CAN_franme_stop)       //接收完整一帧的标志。1为接收完一帧。0为未接收完。全局变量。
	  {						//在串口接收函数中处理。
	      continue;
	  }

	  T0_5MS_count1 = 0;

/***********************
if((buff[2] != DEV_ADDR)&&(buff[2] != BROAD_ADDRESS))
接收到完整正确的报文。进行设备地址判断。如果不是本设备地址或者广播地址。丢弃该报文。
并把各个标记复位。等待下个报文
推出本次循环。

不返回信息
************************/



	  if((CAN_RX_BUFF[2] != DEV_ADDR)&&(CAN_RX_BUFF[2] != BROAD_ADDRESS))
	  {
	      clear_can_rx_buff_fun();

		  continue;  
	  }



      if(CAN_RX_BUFF[1] != DEV_TYPE)		 //	第2个字节的数据如果不是本下位机需要的设备类型号码。则丢弃不做处理。
	  {
	      for(n = 0; n < ub_send_lcd_key_data_number; n++)
		  {
		      LCD_KEY_DATA[n] =  CAN_RX_BUFF[n];
		  }
	  
	      rs_485_2_tx_func_fifo(PC_TO_LCD_KEY); 

	      clear_can_rx_buff_fun();
		  continue;	  
	  }





/***********************
if(BROAD_ADDRESS == buff[2])
接收到完整正确的报文。进行设备地址判断。如果是广播地址。进行相应处理
并把各个标记复位。等待下个报文。
退出本次循环。

广播地址命令。无法返回信息。下位机会冲突。
************************/


	  if(BROAD_ADDRESS == CAN_RX_BUFF[2])	//地址为广播地址
	  {
	      //调用广播命令。 
		  
		  switch(CAN_RX_BUFF[3])
		  {
		      case INPUT_YJ:			      	   //衣架进站命令。这里只负责打开相应命令标记。input_yj_flag。
			                                       //再根据设定，execute_scan(void)里面进站打开相应电磁阀 				  
				      if(CAN_RX_BUFF[14-((DEV_ADDR-1)/6)]&(0x01<<((DEV_ADDR-1)%6)))
					  {
					      if((!input_yj_flag) && (!b_input_yj_flag_2) && (!b_input_yj_flag_3))
						  {
						      T0_5MS_count_input    =    0;	
							  input_yj_flag          =    1;
							  
						  }
						  else if((input_yj_flag) && (!b_input_yj_flag_2) && (T0_5MS_count_input >= 200))
						  {
						      uw_T0_5MS_count_input_2 = 0;
						      b_input_yj_flag_2 = 1;
						  }
						  else if((!input_yj_flag) && (b_input_yj_flag_2) && (uw_T0_5MS_count_input_2 >= 200))
						  {
						      T0_5MS_count_input    =    0;	
							  input_yj_flag          =    1;    
						  }
						  else if((input_yj_flag) && (b_input_yj_flag_2) && (uw_T0_5MS_count_input_2 >= 200) && (T0_5MS_count_input >= 200))
						  {
						      uw_T0_5MS_count_input_3 = 0;
						      b_input_yj_flag_3 = 1;    
						  }
					      					 
					  }					 				 		      			  				 				  			 	
			       break;  
					  
			  case OUTPUT_YJ:			    
					   
				      if(CAN_RX_BUFF[14-((DEV_ADDR-1)/6)]&(0x01<<((DEV_ADDR-1)%6)))
					  {
						  if(push_count > 0)
						  {
						      push_count--;
						  }
						  byte_count_1 = 0;
						  
						  output_yj_flag     = 1;						 
						  T0_5MS_count_output  =    0;
						  b_send_ID_enable     =    1;
						  have_id_data    =    0;
						  T0_5MS_count_same_ID_re_read = 0;
						  b_same_ID_re_read_flag = 1;
						  if((0x01 & (full_data[0])) != 0)
					      {
						      full_data[0]    &=    0xFE;
							 // can_tx_status    =     OUT_STATION_STATUS;
							
				
				
							  // if(have_id_data&&ID_read_enable)	 //有卡号数据的时候。并且使能的是衣架读卡器，并且还没发送5次，把衣架卡号回复给主机
				              if(have_id_data)
							  {			     
							      if(!b_IDNumber_With_LaserNumber_flag)
								  {
									  can_tx_func_fifo(YJ_ID_send); 
								  }	
								  else
								  {
								      can_tx_func_fifo(YJ_ID_With_LaserNumber_send);
								  }  			     
			
							  }
				
							  else //if((0 != full_data[0])&&load_success)	 回复本机状态。
							  {
							      can_tx_func_fifo(IN_OUT_STATION_STATUS);
				
							  }
						  }					  
					  }					  				 		
				  break;

			  case DEMO_complete_for_station:			    
					   
				      if((CAN_RX_BUFF[14-((DEV_ADDR-1)/6)]&(0x01<<((DEV_ADDR-1)%6))) && (!b_COMPLETE_KEY_LOCK_STATUS))
					  {
					        if(have_id_data&&(push_count >= 2))
							{
							    
							    MOTO_ENABLE       =    0;
							    P3_5              =    0;
							    P4_4              =    0;
							    if((0x01 & (full_data[0])) == 0)
							    {
							        full_data[0]     |=    0x01;
								   // can_tx_status    =     OUT_STATION_STATUS;
									
						
									  // if(have_id_data&&ID_read_enable)	 //有卡号数据的时候。并且使能的是衣架读卡器，并且还没发送5次，把衣架卡号回复给主机
				                      if(have_id_data)
									  {			     
									      if(!b_IDNumber_With_LaserNumber_flag)
										  {
											  can_tx_func_fifo(YJ_ID_send); 
										  }	
										  else
										  {
										      can_tx_func_fifo(YJ_ID_With_LaserNumber_send);
										  } 			     
						
									  }
						
									  else //if((0 != full_data[0])&&load_success)	 回复本机状态。
									  {
									      can_tx_func_fifo(IN_OUT_STATION_STATUS);
						
									  }
							    }
							}
							else
							{
							    if(have_id_data)
								{
								    //如果有衣架,完成按钮++
								    push_count++;
								}
								else
								{
								//只要没有衣架,完成按钮就清0
								    push_count = 0;		
								}
						
							    if((0x01 & (full_data[0])) != 0)
								{
								    full_data[0]    &=    0xFE;
									//can_tx_status    =     OUT_STATION_STATUS;
									
						
						
									  // if(have_id_data&&ID_read_enable)	 //有卡号数据的时候。并且使能的是衣架读卡器，并且还没发送5次，把衣架卡号回复给主机
				                      if(have_id_data)
									  {			     
									      if(!b_IDNumber_With_LaserNumber_flag)
										  {
											  can_tx_func_fifo(YJ_ID_send); 
										  }	
										  else
										  {
										      can_tx_func_fifo(YJ_ID_With_LaserNumber_send);
										  } 		     
						
									  }
						
									  else //if((0 != full_data[0])&&load_success)	 回复本机状态。
									  {
									      can_tx_func_fifo(IN_OUT_STATION_STATUS);
						
									  }
								}
							    b_PutDownYjFlag    =    1;  //下放衣架
							    MOTO_ENABLE       =    1;   //提升电机
							    P3_5              =    1;
							    P4_4              =    1;
							}					  
					  }					  				 		
				  break;
				  
			  case LOCK_COMPLETE_KEY:			    
					  if(CAN_RX_BUFF[14-((DEV_ADDR-1)/6)]&(0x01<<((DEV_ADDR-1)%6))) 
				      
					  {
						 b_COMPLETE_KEY_LOCK_STATUS = 1;				  
					  }					  				 		
				  break;
			 case UNLOCK_COMPLETE_KEY:			    
					  if(CAN_RX_BUFF[14-((DEV_ADDR-1)/6)]&(0x01<<((DEV_ADDR-1)%6))) 
				      
					  {
						 b_COMPLETE_KEY_LOCK_STATUS = 0;				  
					  }					  				 		
				  break;

			  
				  
			  case SET_ADDRESS:				 //给设备设定相应地址。并存储到flash。

				   
				   DEV_ADDR =  ASC_TurnTO_Hex(CAN_RX_BUFF[4]);
				   DEV_ADDR <<= 4;
				   DEV_ADDR +=  ASC_TurnTO_Hex(CAN_RX_BUFF[5]);

				   write_parameter_to_flash();                 			      				  		  				 				 				  
				   set_Can_ID();
			       break;
			  case IN_TIME_LAST:				  
				  in_time_last    =    CAN_RX_BUFF[4];	
				  write_parameter_to_flash();
                 //  Delay_function(60000); 
				  
				 // Delay_function(100); //485芯片的发送接收切换需要延时。
				 
	


				  break;

			  case OUT_TIME_LAST:				  
				  out_time_last    =    CAN_RX_BUFF[4];	
				  write_parameter_to_flash();
   				  break;
			  case CheckVersion_To_TrunTo_BootLoader:				  
//				   if((CAN_RX_BUFF[4] < Version_and_Sequence[0]) || ((CAN_RX_BUFF[5] <= Version_and_Sequence[1]) && (CAN_RX_BUFF[4] == Version_and_Sequence[0])))
//				  {
//				      can_tx_func_fifo(CheckVersion_To_TrunTo_BootLoader);
//					  
//				  }
//	
//				  else if(ub_Have_BootLoader_APP != ub_True_Flag)

				  if(ub_Have_BootLoader_APP != ub_True_Flag)
				  {
					  can_tx_func_fifo(Dont_Have_BootLoader);
				  }
				  else
				  {
				      can_tx_func_fifo(Turn_To_BootLoader_APP);    
				  }
				  break;
			 
			  case DEMO_COMPLETE:
					  	 
					if(!b_COMPLETE_KEY_LOCK_STATUS)
					{
						if(have_id_data&&(push_count >= 2))
						{
						    
						    
						    MOTO_ENABLE       =    0;
						    P3_5              =    0;
						    P4_4              =    0;
						    if((0x01 & (full_data[0])) == 0)
						    {
						        full_data[0]     |=    0x01;
							    //can_tx_status    =     OUT_STATION_STATUS;
								
					
								  // if(have_id_data&&ID_read_enable)	 //有卡号数据的时候。并且使能的是衣架读卡器，并且还没发送5次，把衣架卡号回复给主机
					              if(have_id_data)
								  {			     
								      if(!b_IDNumber_With_LaserNumber_flag)
									  {
										  can_tx_func_fifo(YJ_ID_send); 
									  }	
									  else
									  {
									      can_tx_func_fifo(YJ_ID_With_LaserNumber_send);
									  }   			     
					
								  }
					
								  else //if((0 != full_data[0])&&load_success)	 回复本机状态。
								  {
								      can_tx_func_fifo(IN_OUT_STATION_STATUS);
					
								  }
						    }
						}
						else
						{
						    if(have_id_data)
							{
							    //如果有衣架,完成按钮++
							    push_count++;
							}
							else
							{
							//只要没有衣架,完成按钮就清0
							    push_count = 0;		
							}
					
						    if((0x01 & (full_data[0])) != 0)
							{
							    full_data[0]    &=    0xFE;
								//can_tx_status    =     OUT_STATION_STATUS;
								 
					
					
								  // if(have_id_data&&ID_read_enable)	 //有卡号数据的时候。并且使能的是衣架读卡器，并且还没发送5次，把衣架卡号回复给主机
					              if(have_id_data)
								  {			     
								      
									  if(!b_IDNumber_With_LaserNumber_flag)
									  {
										  can_tx_func_fifo(YJ_ID_send); 
									  }	
									  else
									  {
									      can_tx_func_fifo(YJ_ID_With_LaserNumber_send);
									  }   			     
					
								  }
					
								  else //if((0 != full_data[0])&&load_success)	 回复本机状态。
								  {
								      can_tx_func_fifo(IN_OUT_STATION_STATUS);
					
								  }
							}
						    b_PutDownYjFlag    =    1;  //下放衣架
						    MOTO_ENABLE       =    1;   //提升电机
						    P3_5              =    1;
						    P4_4              =    1;
						}
					}
				 
			      break;	
				  
		      default :
			      error_data[0] = 0x02;	 //广播命令，没有所属命令字。报错02；
                 // can_tx_status = EEROR;
				// can_tx_func_fifo(EEROR);
				b_Communicate_Error = 1;
			      clear_can_rx_buff_fun();
			  
		          break;		  	    
		  
		  }
		  
		  clear_can_rx_buff_fun();		  	      
		  continue;
	  
	  }




/***********************
switch(buff[3])
接收到正确报文，并通过以上判断确定为没有任何错误的，属于本机的独立报文。
并被给予总线发送权。
跟进命令类型进入各个命令处理函数。
************************/

	  
     
      switch(CAN_RX_BUFF[3])	  //以上都符合本机要求。则对命令类型进行判断处理
	  {


/***********************
进入HELLO命令。

************************/

	      case HELLO:
			  //can_tx_status = ACT;

			
			  can_tx_func_fifo(ACT);
			  clear_can_rx_buff_fun();
			  break;


		  case ASK:
			  //can_tx_status = ACT;
			

			  // if(have_id_data&&ID_read_enable)	 //有卡号数据的时候。并且使能的是衣架读卡器，并且还没发送5次，把衣架卡号回复给主机
			  if(have_id_data)
			  {	
			      if(!b_IDNumber_With_LaserNumber_flag)
				  {
					  can_tx_func_fifo(YJ_ID); 
				  }	
				  else
				  {
				      can_tx_func_fifo(YJ_ID_With_LaserNumber_send);
				  }	     		         			     
			  }

			  else //if((0 != full_data[0])&&load_success)	 回复本机状态。
			  {
			      can_tx_func_fifo(ASK);

			  }
			  
			  clear_can_rx_buff_fun();
			  break;	   

/***********************
进入ASK命令。
根据协议。进行相应处理。并返回信息。并把各个标记位复位。等待下个报文
ask命令可以取消。下位机信息全部主动发送。有任何状态变化都发送数据
************************/

		  
		  case LOAD_SUCCESS:	//主机接到登陆请求后，发送来允许登陆，并告知登陆成功 后，本机的操作。
		      			 
			 // load_success    =    1;
			  
			  full_data[0]	  |=   0x80; 		   //最高位用作表示登陆状态。在机子登陆过后，工站突然断电。让主机能进行判断
			  
			  have_id_data    =    0;
				  
			  ID_read_enable  =  1;
			 		
			  T0_5MS_count_YJ_id = 0;
			  can_tx_func_fifo(LOAD_SUCCESS);
			  clear_can_rx_buff_fun();


			  break;

		   case LOAD_FAIL:			  
			//  load_success    =    0;
			  full_data[0]	  &=   0x7F;
			  
			  have_id_data    =    0;
			  
			  ID_read_enable  =  0;			 			
			  T0_5MS_count_YJ_id = 0;
			 // T0_5MS_count_worker_id  =  0;
			  can_tx_func_fifo(LOAD_FAIL);

	          clear_can_rx_buff_fun();
		


			  break;

		  case CheckVersion_To_TrunTo_BootLoader:



			  if(ub_Have_BootLoader_APP != ub_True_Flag)
			  {
				  can_tx_func_fifo(Dont_Have_BootLoader);
			  }
			  else
			  {
			      can_tx_func_fifo(Turn_To_BootLoader_APP);    
			  }
			  
			  clear_can_rx_buff_fun();

			  break;
		  case WORKER_QUIT_TURE:


			 ID_read_enable  =  0;
			  
			  have_id_data    =    0;
			  
			  
			  full_data[0]	  &=   0x7F;
			 

			  T0_5MS_count_YJ_id = 0;
			//  T0_5MS_count_worker_id  =  0;
			  can_tx_func_fifo(WORKER_QUIT_TURE);
			  clear_can_rx_buff_fun();

			  break;	  

			   case IN_OUT_TIME:
		  			  	  
				
				  for(n = 0; n<2; n++)
				  {
				      in_out_time[n]    =    CAN_RX_BUFF[n+4];
				  }	
				  write_parameter_to_flash();

    			   clear_can_rx_buff_fun();


				  break;
			  case PutDownYjDelayCommand:
		  			  	  				
				  ubPutDownYjDelay    =    CAN_RX_BUFF[4];
				  
				  write_parameter_to_flash();

    			   clear_can_rx_buff_fun();
				  break;
			 case YJ_ID_With_LaserNumber_send:
		  			  	  				
				  if(CAN_RX_BUFF[4])
				  {
				      b_IDNumber_With_LaserNumber_flag = 1;
				  }
				  else
				  {
				      b_IDNumber_With_LaserNumber_flag = 0;
				  }
    			   clear_can_rx_buff_fun();
				  break;

			  case SET_SEQUENCE:
		  			  	  
				  
				    for(n = 0; n<14; n++)
				    {
				        Version_and_Sequence[n + 2]    =    CAN_RX_BUFF[n+4];
					
				    }
					write_parameter_to_flash();

	
				  clear_can_rx_buff_fun();
			
	


				  break;
			  

			  case Turn_LED_Status:
		  			  	  
				  ub_LED_Status =  CAN_RX_BUFF[4];
				  can_tx_func_fifo(Turn_LED_Status);
	
				  clear_can_rx_buff_fun();
				  break;

			  





/***********************
没有任何符合报文传输的命令。
根据协议。进行相应处理。并返回信息。并把各个标记位复位。等待下个报文
报错。命令错误。
************************/


		  default:
		  //返回错误信息，或者调用错误函数
		      error_data[0] = 0x01;
			  b_Communicate_Error = 1;
             // can_tx_status = EEROR;
		//	  can_tx_func_fifo(EEROR);
			  clear_can_rx_buff_fun();
			  
		      break;

	  
	  }









  // USER CODE END

  }

} //  End of function main


// USER CODE BEGIN (MAIN_General,10)

// USER CODE END

