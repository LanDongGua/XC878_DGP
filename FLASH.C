#include "MAIN.H"


bit FLASH_Erase (unsigned char code* FlashDstAddr,unsigned char KindOfErase)
{
	volatile bit tmpEA, success;						// bit tmpEA --> overwrites CY ( in KEIL )
														// that's why use second var

	(EA)?(tmpEA = 1,EA=0):(tmpEA = 0);					// save EA bit for restoring at end
														// required by UM
	 ACC = KindOfErase;									// desire MASS or PAGE erase 

	DPTR = (unsigned int) FlashDstAddr;


	MEX1 = 0x02;


	((void (code *) (void)) FLASH_ERASE) ();			// BROM call KEIL



	MEX1 = 0x00;

	success = CY;
	EA = tmpEA;											// restore old EA state either '0' or '1' 
	return(!success);
}

bit FLASH_Prog (ubyte code * DestWordLine, unsigned char NrOfBytes, ubyte xdata *xdata_addr)	
{
	volatile bit tmpEA, success;						// bit tmpEA --> overwrites CY ( in KEIL )
														// that's why use second var

	(EA)?(tmpEA = 1,EA=0):(tmpEA = 0);					// save EA bit for restoring at end
														// required by UM


	MEX1 = 0x02;


	REG[0x0001] = NrOfBytes;							// Number of bytes to be programmed - max. 32 DFLASH

	EO |= 0x01;											// select DPTR1 to hold Buffer Address
	DPTR = xdata_addr;
	EO &= ~(0x01);										// ensure DPTR0 is set as active before leave

	DPTR = (unsigned int)DestWordLine;


	((void (code *) (void)) FLASH_PROG) ();				// BROM call KEIL




	MEX1 = 0x00;

	success = CY;
	EA = tmpEA;											// restore old EA state either '0' or '1' 
	return(!success);
}
void Read_Parameter_To_Ram(void)
{
    ubyte VersionNumber;
	DFlash_ADDR    =  APP_DATA_StartADDR_At_DFlash;	
	DEV_ADDR         =    *DFlash_ADDR;	
	if(DEV_ADDR < 1 || DEV_ADDR > Max_DevAddr)
	{
		DEV_ADDR = 1;
	}
	DFlash_ADDR++;

	in_out_time[0]   =    *DFlash_ADDR;
	if(in_out_time[0] > 25)
	{
	    in_out_time[0] = 2;  
	}
	DFlash_ADDR++;
	
	in_out_time[1]   =    *DFlash_ADDR;
	if(in_out_time[1] > 25)
	{
	    in_out_time[1] = 2;
	
	}
	DFlash_ADDR++;
	in_time_last = *DFlash_ADDR;
	if((in_time_last < 3)||(in_time_last > 30))
	{
	    in_time_last  =  20;
	}
	
	DFlash_ADDR++;
	out_time_last = *DFlash_ADDR;
	if((out_time_last < 3)||(out_time_last > 30))
	{
	    out_time_last  =  8;
	}
	DFlash_ADDR++;
	for(VersionNumber= 0; VersionNumber < 16; VersionNumber++)
	{
		Version_and_Sequence[VersionNumber] = *DFlash_ADDR;
		DFlash_ADDR++;
	}
	Version_and_Sequence[0] = VersionH;
    Version_and_Sequence[1] = VersionL;
	
	
	ubPutDownYjDelay = *DFlash_ADDR;
	DFlash_ADDR++;
	if((ubPutDownYjDelay > 100))
	{
	    ubPutDownYjDelay  =  15;
	}

	DFlash_ADDR    =  BootLoader_APP_For_UpAPP_Data_Start_ADDR_At_DFlash;
//	ub_Have_APP_Flag = *DFlash_ADDR;
	DFlash_ADDR++;
//	ub_Updata_APP_Flag = *DFlash_ADDR;
	DFlash_ADDR++;
//	ub_Have_BootLoader_INTR_Table = *DFlash_ADDR;
	DFlash_ADDR++;
//	ub_Have_APP_INTR_Table = *DFlash_ADDR;
	DFlash_ADDR++;
	ub_Have_BootLoader_APP = *DFlash_ADDR;
	DFlash_ADDR++;
}
void write_parameter_to_flash(void)
{
    ubyte n;
	DFlash_ADDR    =  APP_DATA_StartADDR_At_DFlash;
	XDATA_P = For_Program_Flash_Temp_StartADDR_At_XDATA;
	
	*XDATA_P  =	 DEV_ADDR;
	XDATA_P++;
	DFlash_ADDR++;
	
	*XDATA_P  = in_out_time[0];
	XDATA_P++;
	DFlash_ADDR++;
	
	*XDATA_P  = in_out_time[1];
	XDATA_P++;
	DFlash_ADDR++;
	
	*XDATA_P = in_time_last;	
	XDATA_P++;
	DFlash_ADDR++;
	
	
	*XDATA_P = out_time_last;
	XDATA_P++;
	DFlash_ADDR++;
    for(n = 0; n<16; n++)
    {
        *XDATA_P    =    Version_and_Sequence[n];
		XDATA_P++;
		DFlash_ADDR++;
    }
	


	*XDATA_P = ubPutDownYjDelay;
	XDATA_P++;
	DFlash_ADDR++;


						   			  				  
	FLASH_Erase (0xF000,0);
	Delay_function(600);
	FLASH_Prog (APP_DATA_StartADDR_At_DFlash, 32, For_Program_Flash_Temp_StartADDR_At_XDATA);

}


void set_Can_ID(void)
{

	can_tx_id = 0;
    can_tx_id =  (DEV_ADDR + 1);
    can_tx_id = (can_tx_id << 18);
    CAN_vWriteCANAddress(CAN_MOAR0);
    can_tx_id = (0xC0000000)|(can_tx_id);
    CAN_vWriteAMData(can_tx_id); 

}

