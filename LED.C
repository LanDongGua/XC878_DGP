#include "MAIN.H" 



void Flash_LED_Fun(void)
{
    if(ub_T0_5MS_count_led <= 100)
	{
	    Enable_LED();    
	}
	else
	{
	    DisEnable_LED();    
	}
}



void Scan_LED(void)
{

	switch(ub_LED_Status) 
	{
	    case TurnOff_LED:
		    DisEnable_LED(); 
		    break;
		case TurnOn_LED:
		    Enable_LED();   
		    break;
		case Flash_LED:
		    Flash_LED_Fun();
		    break;
		default:
		    break;	
	} 

}