#ifndef _LED_H_
#define _LED_H_
extern ubyte pdata ub_T0_5MS_count_led, ub_LED_Status;

#define  Enable_LED()  			    P4_3 = 1
#define  DisEnable_LED()  			P4_3 = 0
#define  TurnOff_LED  		        0
#define  TurnOn_LED  		        1
#define  Flash_LED  		        2

void Flash_LED_Fun(void);
void Scan_LED(void);


#endif