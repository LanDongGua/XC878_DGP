#ifndef _RS485_LK_H_
#define _RS485_LK_H_


void rs485_lk_scan(void);
bool cmopare_IDcard_for_rs485_lcd_key(void);
ubyte createBCC_rs485_lk(ubyte Len);
void send_Frame_data_rs485_lk(ubyte FC_data, ubyte DEVE_TYPE_RS485_LK, ubyte DEV_ADDR_RS485_LK, ubyte send_data[], ubyte Len);
void send_command_rs485_lk(ubyte send_buff[], ubyte Len);
void rs_485_2_tx_func_fifo(ubyte tx_function);
void rs_485_2_FIFO_displace(void);
#endif