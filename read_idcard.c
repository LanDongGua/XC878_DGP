#include "MAIN.H" 

//读卡器扫描
void Idreader_scan(void)
{
    ubyte  i;
	bool have_id_data_temp;
	have_id_data_temp    =    0;


	  //
	  if((Hanger_RFID_Frequency <= T0_5MS_count_YJ_id))
	 // if(Hanger_RFID_Frequency <= T0_5MS_count_YJ_id)
	  {
	      T0_5MS_count_YJ_id = 0;
		  rs_485_2_tx_func_fifo(READ_ID_READER);
	    
	  }	
	  

	  if(FRAME_start_1&&(!FRAME_end_1)&&(8 <= T0_5MS_IDread_frame_count))
	  {
	      T0_5MS_IDread_frame_count = 0;
	      byte_count_1     =    0;
		  FRAME_end_1      =  0;
		  FRAME_start_1    =    0;
	      return;
	  }
	  if(!FRAME_end_1)
	  {
	      return;
	  }

	  b_rs_485_2_traning = 0;
	  ub_T0_5MS_count_re_485_2_wait_recieve = 0;
	  T0_5MS_IDread_frame_count  =  0;
	  FRAME_end_1      =    0; 
	  if(byte_count_1 < 16)
	  {	      
		  FRAME_end_1       =    0;	
		  FRAME_start_1     =    0;
		  byte_count_1      =    0;
		  return;
	  }
	        	      
      if(check_BCC_1(byte_count_1 - 7))
	  {
	      IDCARD_data[0] = full_data[0];
		  if(!b_IDNumber_With_LaserNumber_flag)
		  {
			  if(cmopare_IDcard())
			  {
			      
			      for(i = 0; (i + 7) < byte_count_1; i++)
				  {
				      IDCARD_data[i + 1]  = send_data[i + 4];
				      
				  }	
				  have_id_data = 1;
				  			     
				  can_tx_func_fifo(YJ_ID_send);	  		
			  }
			  else
			  {
			      if(have_id_data)
				  {
				      for(i = 0; (i + 7) < byte_count_1; i++)
					  {
					      IDCARD_data[i + 1]  = send_data[i + 4];   
					  }	
					  have_id_data = 1;		    			  
				  }
				  else if(!b_send_ID_enable)
				  {
				      for(i = 0; (i + 7) < byte_count_1; i++)
					  {
					      IDCARD_data[i + 1]  = send_data[i + 4];				      
					  }	
					  have_id_data = 1;	
					  can_tx_func_fifo(YJ_ID_send);	
				  }
				  
				  else
				  {
				      byte_count_1 = 0;
				      have_id_data = 0;			      			  
				  }		      			 
			  }
		  }
		  else
		  {
		      if(cmopare_IDcard())
			  {			      
			      for(i = 0; (i + 7) < byte_count_1; i++)
				  {
				      IDCARD_data[i + 1]  = send_data[i + 4];				      
				  }	
				  have_id_data = 1;
				  Output_Laser_Number_ADDR_IN_XDATA = (THE_FIRST_ADDR_For_Store_LaserNumber_At_XDATA + (20 * ub_Output_Count_LaserNumber_In_XDATA_ADDR));
				  ub_Send_LaserNumber_Count = *Output_Laser_Number_ADDR_IN_XDATA;
				  Output_Laser_Number_ADDR_IN_XDATA++;
				  for(i = 0; i < ub_Send_LaserNumber_Count; i++)
				  {
				      IDCARD_data[i + 10] = *Output_Laser_Number_ADDR_IN_XDATA;
					  Output_Laser_Number_ADDR_IN_XDATA++;
				  }
				  if(9 == ub_Output_Count_LaserNumber_In_XDATA_ADDR)
				  {
				      ub_Output_Count_LaserNumber_In_XDATA_ADDR = 0;
				  }
				  else if(ub_Output_Count_LaserNumber_In_XDATA_ADDR < 9)
				  {
				      ub_Output_Count_LaserNumber_In_XDATA_ADDR++;
				  }
				  else
				  {
				      b_IDNumber_With_LaserNumber_flag = 0;
				  }
				  			     
				  can_tx_func_fifo(YJ_ID_With_LaserNumber_send);	  		
			  }
			  else
			  {
			      if(have_id_data)
				  {
				      for(i = 0; (i + 7) < byte_count_1; i++)
					  {
					      IDCARD_data[i + 1]  = send_data[i + 4];   
					  }							    			  
				  }
				  else if(!b_send_ID_enable)
				  {
				      for(i = 0; (i + 7) < byte_count_1; i++)
					  {
					      IDCARD_data[i + 1]  = send_data[i + 4];				      
					  }	
					  have_id_data = 1;	
					  can_tx_func_fifo(YJ_ID_With_LaserNumber_send);	
				  }
				  
				  else
				  {
				      byte_count_1 = 0;
				      have_id_data = 0;			      			  
				  }		      			 
			  }
		  }
	      	 	      
	  }
	  else
	  {		 
		  byte_count_1     =    0;
		  FRAME_end_1      =  0;
		  FRAME_start_1    =    0;	  	  
	  }	  	  
}		 	


//	   异卡比较
bool cmopare_IDcard(void)
{
	ubyte i;

	for(i = 0; i < (ID_NUM); i++)
	{
	  if(IDCARD_data[i + 1]  != send_data[i + 4])
	  {	     
		 return 1;
	  }	
	}	
	return 0;    
} 

/****   组装发送包  *********/
void send_IdReader_Frame(ubyte ID_data, ubyte FC_data, ubyte IdReaer_data[], ubyte Len)
{
    ubyte i,BCC_DATA,  BCC1_DATA,  BCC2_DATA;
	if(Len > 9)
	{
	    Len = 9;
	}
    send_data[0]  =   Fram_Head_1_MtoS;
	send_data[1]  =    'A';
	send_data[2]  =    ID_data;
	send_data[3]  =    FC_data;
	for(i = 0; i < Len; i++)
	{
	   
	    send_data[i+4]  =  IdReaer_data[i];  
	}

	BCC_DATA = 	createBCC_1(Len);
	BCC1_DATA = Hex_TurnTO_ASC((BCC_DATA&0xF0)>>4);

	send_data[Len + 4] = BCC1_DATA;

	BCC2_DATA = Hex_TurnTO_ASC(BCC_DATA&0x0F);
	send_data[Len + 5] = BCC2_DATA;
	send_data[Len + 6] = Fram_End_1;    
}




