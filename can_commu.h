#ifndef _CAN_COMMUNICATE_2_H_
#define _CAN_COMMUNICATE_2_H_


void clear_can_rx_buff_fun(void);
void clear_can_tx_buff_fun(void);
void Recover_CAN_BUS(void);
void Cancel_CAN_vTransmit(ubyte ubObjNr);
void can_tx_status_scan_function(void);
ubyte CAN_createBCC(ubyte Len);

void can_send_data(ubyte CAN_TX_BUFF_TEMP[], ubyte Len);
void send_command(ubyte send_buff[], ubyte Len);
void can_tx_for_traning(void);
void scan_can_tx_frame(void);
void can_tx_status_traning(void);
void can_tran_complete_for_delay(void);
void can_tx_func_fifo(ubyte tx_function);
void FIFO_displace(void);
bool compare_command(ubyte tx_function_for_compare);
void check_can_trans_time_out(void);
void RE_circulation_FIFO(ubyte repend_function);
void send_Frame_data_for_can(ubyte FC_data, ubyte send_data[], ubyte Len);
void Get_CAN_Data(void);

#endif