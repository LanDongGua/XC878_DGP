#ifndef _READ_IDCARD_H_
#define _READ_IDCARD_H_


void send_IdReader_Frame(ubyte ID_data, ubyte FC_data, ubyte IdReaer_data[], ubyte Len);
void Idreader_scan(void);
bool cmopare_IDcard(void);



#endif 