#ifndef _DEFINE_H_
#define _DEFINE_H_

#define  Enable_Txd_1()          P3_0 = 1		  //����2�ķ��ͣ������л���
#define  Enable_Rxd_1()          P3_0 = 0

#define  Enable_Txd()            P1_2 = 1		   //����1�ķ��ͣ������л���
#define  Enable_Rxd()            P1_2 = 0
#define  OUTPUT_YJ_ENABLE            P4_7 		   //�¼ܳ�վʹ�ܽţ��򿪵�ŷ�
#define  INPUT_YJ_ENABLE            P4_6		   //�¼ܽ�վ������Ӧ��ŷ�
#define  DONE_YJ_ENABLE            P4_5			   //�¼���ת����Ӧ��ŷ���
#define  MOTO_ENABLE               P3_4			   //���������
#define  LED1_ENABLE               P0_7
#define  LED2_ENABLE               P4_2
#define  BUZZ_ENABLE               P4_1
#define  Fram_Head          0xED
#define  Fram_End           0xEE
#define  Fram_Head_1          0x0A
#define  Fram_End_1           0x0D
#define  Fram_Head_1_MtoS		  0x09
#define  ID_NUM    0x09								//RFID���Ŀ���������

#define  DEV_TYPE         0x11
#define  BROAD_ADDRESS    0x00

#define  Max_DevAddr    64   //����豸��ַ
#define  Execute_Last_Time    440   //����վ��������ʱ��,5msһ����λ
#define  Worker_RFID_Frequency    400   //Ա��������Ƶ��,5msһ����λ
#define  RS485_LK_Frequency    153 
#define  Hanger_RFID_Frequency    233   //�¼ܶ�����Ƶ��,5msһ����λ

#define  HELLO            0x01					   //��Ӧ��Э�����
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

#define  LASER_NUMBER                      0x36	  //��λ���������ġ�������������



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
#define  SET_TEMP_ADDR        0x71		 //lcd����վλ���ʱ����Ϊֻ����һ�飬ÿ�ο�����ʱ����ʱ�������ĵ�ַΪվλ��ַ.Ϊ�˲���flash��ĵ�ַ��ͻ��
#define  LCD_KEY_TO_PC        0x72
#define  In_station_flag   P0_3
#define  scan_complete     P4_0
#define  scan_stop_moto_1  P0_4
#define  scan_stop_moto_2  P3_7

extern uword  idata  T0_5MS_count_infull,  T0_5MS_count_input, T0_5MS_count_output, T0_5MS_count_same_ID_re_read;  //4��5���붨ʱ�����������ֱ�Ӧ���ڣ���վ������������վ������������վ����ʱ�䣬��վ����ʱ��Ķ�ʱ��
extern ubyte     T0_5MS_count1,	//count1������Ӧ�����жϺ�����ͨ��ʱ���Ƿ����ʱʹ�á�5msһ��������	count_worker_idӦ���ڶ�ʱɨ���½��������
      T0_5MS_count_YJ_id,   T0_5MS_count_Waiting_CAN_Send_INTR_Flag,
	  T0_5MS_IDread_frame_count, T0_5MS_count_complete_scan, T0_5MS_count_scan_stop_moto_1, 
	  T0_5MS_count_scan_stop_moto_2;
	  //  count_KEY_SCAN����ʱɨ����̡�
extern bool   FRAME_start_1,  in_full,   	  
      //FRAME_start,������ͨ�ŵĿ�ʼ��Ƿ��� FRAME_start_1�Ͷ�����ͨ�ŵĿ�ʼ��Ƿ���
	  //FRAME_end��������ͨ�ŵĽ�����Ƿ���	in_full����վ����Ƿ���	out_full��վ����Ƿ���
	  //worker_quit_flag��Ա���˳���¼��Ƿ���
      FRAME_end_1, have_id_data,  ID_read_enable,  input_yj_flag, b_same_ID_re_read_flag,	 
	  // FRAME_end_1 �Ͷ�����ͨ�Ž�����Ƿ���have_id_data���ж������ݵı�Ƿ���
	  // load_success��¼�ɹ���Ƿ���	ID_read_enable��������ʹ�ܱ�ǡ�1��ʾԱ����½������ʹ�ܣ�0��ʾ���¼ܶ�����ʹ�ܡ�
	  // worker_load��Ա����½��ǡ�ͨ�����̵�½��ʱ��
	  // input_yj_flag����վ���������Ƿ�
	  //output_yj_flag ��վ���������Ƿ�
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
         // buff[27]��������ͨ�ŵ�buff��byte_count��������ͨ�ŵģ�һ֡ͨ���ֽڼ�������
		 //	byte_count_1���Ͷ�����ͨ�ŵ�ͨ���ֽڼ�������
		 //DEV_ADDR���豸��ַ��	 error_data[1]���������ݡ�	in_out_time[2]����վ�ͳ�վ��ʱʱ�䡣
          send_data[17],IDCARD_data[30], full_data[1], 
		  //send_data[17],   �Ͷ�����ͨ�ŵ�buff��  IDCARD_data[10]���洢���ŵ�buff��ͬʱҲ�������̵�½ʱ�򣬱����6λ���ź�4λ����	��
		  //full_data[1]��վ״̬�ֽڡ������Ƿ��½���Ƿ��վ�����Ƿ��վ��
		    push_count;
extern ubyte idata in_time_last, out_time_last, CAN_TX_BUFF[24], CAN_RX_BUFF[24], CAN_BYTE_DATA_COUNT,  can_tx_status, can_traning_frame_number;
extern ubyte idata TX_FIFO_FUNC[4], TX_FIFO_COUNTER;

extern ulong idata can_tx_id;
extern uword idata uw_T0_5MS_count_input_2, uw_T0_5MS_count_input_3;
extern ubyte pdata Version_and_Sequence[16];



extern ubyte idata ubPutDownYjDelay;
extern bool  b_PutDownYjFlag;
extern uword idata T0_5MS_count_PutDownYjDelay;
/********* ������ *************/
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