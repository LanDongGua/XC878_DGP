#ifndef _RS_485_2_H_
#define _RS_485_2_H_

void scan_rs_485_2(void);
void rs_485_2_tx_status(void);
bool compare_command_rs_485_2(ubyte tx_function_for_compare);
void rs_485_2_tx_func_fifo(ubyte tx_function);
void rs_485_2_FIFO_displace(void);
void send_command_rs485_2(ubyte send_buff[], ubyte Len);
#endif