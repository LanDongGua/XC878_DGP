#include "MAIN.H"



void Erase_Flash_One_Page(ubyte code * Flash_ADDR_Parameter)
{
    b_Flag = 0;
	do
	{
	    b_Flag =  FLASH_Erase (Flash_ADDR_Parameter, 0);   
	}
    while(0 == b_Flag);
	b_Flag = 0;
}



void Load_DFlash_To_PFlash_Function(ubyte code* PFlash_ADDR_Parameter, ubyte code * DFlash_ADDR_Parameter, ubyte Load_Counter)
{
    ubyte i;
			

    b_Flag = 0;
	XDATA_P = For_Program_Flash_Temp_StartADDR_At_XDATA;
	DFlash_ADDR = DFlash_ADDR_Parameter;		
	
	for(i = 0; i < Load_Counter; i++)
	{
		*XDATA_P = *DFlash_ADDR;
		XDATA_P++;
		DFlash_ADDR++;
	}


	PFlash_ADDR = PFlash_ADDR_Parameter;
   
	Erase_Flash_One_Page(PFlash_ADDR);


	XDATA_P = For_Program_Flash_Temp_StartADDR_At_XDATA;
    PFlash_ADDR = PFlash_ADDR_Parameter;
	for(i = 0; i < 2; i++)
	{    	    
		do
		{
		    b_Flag =  FLASH_Prog (PFlash_ADDR, 64, XDATA_P); 
		}
	    while(0 == b_Flag);
		b_Flag = 0;  
		
		PFlash_ADDR += 64;
		XDATA_P     += 64;  
	}    

}
void Load_BootLoader_INTR_Table_To_MCU_Start_ADDR(void)
{
    
    Load_DFlash_To_PFlash_Function(MCU_Start_ADDR_At_PFlash, BootLoader_INTR_Table_Start_ADDR_At_DFlash,  128);

}