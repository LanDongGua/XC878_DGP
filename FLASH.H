#ifndef _FLASH_H_
#define _FLASH_H_

#define FLASH_PROG					0xDFF6 
#define FLASH_ERASE					0xDFF9 
#define REG		((unsigned char volatile data *) 0)
sfr16 DPTR = 0x82;
bit FLASH_Prog (unsigned char code * DestWordLine, unsigned char NrOfBytes, ubyte xdata * xdata_addr);
bit FLASH_Erase (unsigned char code* FlashDstAddr,unsigned char KindOfErase);
void Read_Parameter_To_Ram(void);
void write_parameter_to_flash(void);
void set_Can_ID(void);


#endif 