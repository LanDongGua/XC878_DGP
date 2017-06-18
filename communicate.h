#ifndef _COMMUNICATE_H_
#define _COMMUNICATE_H_







bool check_BCC(ubyte Len);
bool check_BCC_1(ubyte Len);
ubyte createBCC(ubyte Len);
ubyte createBCC_1(ubyte Len);


ubyte Hex_TurnTO_ASC(ubyte hex_data);
ubyte ASC_TurnTO_Hex(ubyte Asc_data);
void send_Frame_data(ubyte FC_data, ubyte send_data[], ubyte Len);
void send_command(ubyte send_buff[], ubyte Len);
//void send_command_1(ubyte send_buff[], ubyte Len);
#endif 