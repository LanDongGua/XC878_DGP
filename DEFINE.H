#ifndef _DEFINE_H_
#define _DEFINE_H_

#define  Enable_Txd_1()          P3_0 = 1		  //串口2的发送，接收切换。
#define  Enable_Rxd_1()          P3_0 = 0

#define  Enable_Txd()            P1_2 = 1		   //串口1的发送，接收切换。
#define  Enable_Rxd()            P1_2 = 0
#define  OUTPUT_YJ_ENABLE            P4_7 		   //衣架出站使能脚，打开电磁阀
#define  INPUT_YJ_ENABLE            P4_6		   //衣架进站，打开相应电磁阀
#define  DONE_YJ_ENABLE            P4_5			   //衣架中转的相应电磁阀。
#define  MOTO_ENABLE               P3_4			   //驱动电机。
#define  LED1_ENABLE               P0_7
#define  LED2_ENABLE               P4_2
#define  BUZZ_ENABLE               P4_1
#define  Fram_Head          0xED
#define  Fram_End           0xEE
#define  Fram_Head_1          0x0A
#define  Fram_End_1           0x0D
#define  Fram_Head_1_MtoS		  0x09
#define  ID_NUM    0x09								//RFID卡的考号数量。

#define  DEV_TYPE         0x11
#define  BROAD_ADDRESS    0x00

#define  Max_DevAddr    64   //最大设备地址
#define  Execute_Last_Time    440   //进出站动作持续时间,5ms一个单位
#define  Worker_RFID_Frequency    400   //员工读卡器频率,5ms一个单位
#define  RS485_LK_Frequency    153 
#define  Hanger_RFID_Frequency    233   //衣架读卡器频率,5ms一个单位

#define  HELLO            0x01					   //相应的协议命令。
#define  ACT              0x02
#define  ASK              0x0A
#define  ANS              0x0B
#define  EEROR            0x0E
#define  TOTAL_AND_EFFICIENCY        0x13
#define  LOAD_FAIL        0x14
#define  LOAD_SUCCESS     0x16
#define  ERROR_WORKERID_OR_PASS     0x15
#define  WORKER_QUIT_TURE     0x17
//#define  IN_STATION_STATUS     0x6F
//#define  OUT_STATION_STATUS     0x6E
#define  IN_OUT_STATION_STATUS     0x70
#define  YJ_ID_send               0x71

#define  YJ_ID_With_LaserNumber_send               0x73

#define  IN_OUT_TIME          0x25
#define  DEMO_COMPLETE          0x26
#define  SET_ADDRESS          0x28
#define  SET_SEQUENCE         0x29
#define  PutDownYjDelayCommand  0x2A

#define  Turn_LED_Status         0x2B

#define  LASER_NUMBER                      0x36	  //工位机传上来的。条形码命令字



#define  INPUT_YJ         0x83
#define  OUTPUT_YJ        0x85
#define  IN_TIME_LAST          0x86
#define  OUT_TIME_LAST          0x87
#define  BUZZER_LED          0x88
#define  LOCK_COMPLETE_KEY          0x8A
#define  UNLOCK_COMPLETE_KEY          0x8B
#define  DEMO_do              0x99
#define  DEMO_complete_for_station              0x89

#define  WORKER_ID                   0x50					 
#define  WORKER_NUM_AND_PASS        0x51
#define  WORKER_QUIT        0x52

#define  YJ_ID                      0x55

#define  VersionH          0x33
#define  VersionL          0x30


// ??????2??????
#define  READ_ID_READER        0xFE
#define  PC_TO_LCD_KEY        0x70
#define  SET_TEMP_ADDR        0x71		 //lcd链接站位板的时候，因为只连着一块，每次开机的时候，临时设置他的地址为站位地址.为了不和flash里的地址冲突。
#define  LCD_KEY_TO_PC        0x72
#define  In_station_flag   P0_3
#define  scan_complete     P4_0
#define  scan_stop_moto_1  P0_4
#define  scan_stop_moto_2  P3_7

extern uword  idata  T0_5MS_count_infull,  T0_5MS_count_input, T0_5MS_count_output, T0_5MS_count_same_ID_re_read;  //4个5毫秒定时计数变量。分别应用于，进站传感器满、出站传感器满、进站持续时间，出站持续时间的定时。
extern ubyte     T0_5MS_count1,	//count1计数。应用于判断和主机通信时间是否过长时使用。5ms一个计数。	count_worker_id应用于定时扫描登陆读卡器。
      T0_5MS_count_YJ_id,   T0_5MS_count_Waiting_CAN_Send_INTR_Flag,
	  T0_5MS_IDread_frame_count, T0_5MS_count_complete_scan, T0_5MS_count_scan_stop_moto_1, 
	  T0_5MS_count_scan_stop_moto_2;
	  //  count_KEY_SCAN。定时扫描键盘。
extern bool   FRAME_start_1,  in_full,   	  
      //FRAME_start,和主机通信的开始标记符。 FRAME_start_1和读卡器通信的开始标记符。
	  //FRAME_end，和主机通信的结束标记符。	in_full，进站满标记符。	out_full出站满标记符。
	  //worker_quit_flag，员工退出登录标记符。
      FRAME_end_1, have_id_data,  ID_read_enable,  input_yj_flag, b_same_ID_re_read_flag,	 
	  // FRAME_end_1 和读卡器通信结束标记符。have_id_data，有读卡数据的标记符。
	  // load_success登录成功标记符。	ID_read_enable，读卡器使能标记。1表示员工登陆读卡器使能，0表示，衣架读卡器使能。
	  // worker_load，员工登陆标记。通过键盘登陆的时候。
	  // input_yj_flag，进站动作命令，标记符
	  //output_yj_flag 出站动作命令，标记符
	  output_yj_flag, b_send_ID_enable,    b_T0_5MS_flag, b_COMPLETE_DONE_flag,  b_COMPLETE_KEY_LOCK_STATUS,
	  b_input_yj_flag_2, b_input_yj_flag_3,
	   b_stop_moto_1_flag, b_stop_moto_2_flag, b_buzzer_led_1S_3;
extern bool  b_CAN_franme_start, b_CAN_franme_stop,  b_Communicate_Error, b_Waiting_CAN_Send_Interupt_Flag,	  b_CAN_Send_Fail_Flag,
             b_CAN_traning, b_CAN_waiting_interrupt, b_CAN_tran_complete;

extern bool b_rs_485_2_traning, FRAME_start_rs485_lk, FRAME_end_rs485_lk, b_have_LCD_KEY_DATA, b_check_have_lcd_key;
extern ubyte idata ub_rs_485_2_TX_FIFO_COUNTER, ub_rs485_2_TX_FIFO_FUNC[4], ub_rs485_2_TX_status, ub_T0_5MS_count_re_485_2_wait_recieve;
extern ubyte pdata LCD_KEY_DATA[24], byte_count_rs485_lk, T0_5MS_rs485_lk_frame_count, T0_5MS_count_rs485_lk, RS485_LK_buff[24],
                   ub_send_lcd_key_data_number, ub_lcd_key_send_pc_number;

extern ubyte       byte_count_1, DEV_ADDR, error_data[1], in_out_time[2], 		
         // buff[27]，和主机通信的buff。byte_count，和主机通信的，一帧通信字节计数器。
		 //	byte_count_1，和读卡器通信的通信字节计数器。
		 //DEV_ADDR，设备地址。	 error_data[1]，报错内容。	in_out_time[2]，进站和出站延时时间。
          send_data[17],IDCARD_data[30], full_data[1], 
		  //send_data[17],   和读卡器通信的buff。  IDCARD_data[10]，存储卡号的buff。同时也用作键盘登陆时候，保存的6位卡号和4位密码	、
		  //full_data[1]工站状态字节。包括是否登陆，是否进站满，是否出站满
		    push_count;
extern ubyte idata in_time_last, out_time_last, CAN_TX_BUFF[24], CAN_RX_BUFF[24], CAN_BYTE_DATA_COUNT,  can_tx_status, can_traning_frame_number;
extern ubyte idata TX_FIFO_FUNC[4], TX_FIFO_COUNTER;

extern ulong idata can_tx_id;
extern uword idata uw_T0_5MS_count_input_2, uw_T0_5MS_count_input_3;
extern ubyte pdata Version_and_Sequence[16];



extern ubyte idata ubPutDownYjDelay;
extern bool  b_PutDownYjFlag;
extern uword idata T0_5MS_count_PutDownYjDelay;
/********* 绑定条码 *************/
extern bool b_IDNumber_With_LaserNumber_flag,	b_Have_Got_LaserNumber_Flag;
extern ubyte ub_A_LaserNumber_Count, ub_Send_LaserNumber_Count,  ub_STORE_Count_LaserNumbers_In_XDATA_ADDR, ub_Output_Count_LaserNumber_In_XDATA_ADDR;
extern ubyte xdata *Store_Laser_Number_ADDR_IN_XDATA;
extern ubyte xdata *Output_Laser_Number_ADDR_IN_XDATA;
extern ubyte pdata Laser_Temp_DATA[20];


/*****UPdata*****/
extern ubyte ub_Have_BootLoader_APP;
extern bool b_Turn_To_BootLoader_Flag;

extern bool b_Flag;
extern ubyte  code *DFlash_ADDR;
extern ubyte  xdata *XDATA_P;
extern ubyte  code *PFlash_ADDR;



void Delay_function(int num);
void Ram_Init(void);

void clear_communicate_flag(void);
void on_buzzer_led(void);
void off_buzzer_led(void);
//void clear_buff(void);
#endif 