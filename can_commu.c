#include "MAIN.H"

void scan_can_tx_frame(void)
{
    can_tx_status_scan_function();
//	can_tx_for_traning();
	//can_tran_complete_for_delay();
//	check_can_trans_time_out();
//    if(T0_5MS_CAN_tran_complete_count > 1)
//	{
//	    T0_5MS_CAN_tran_complete_count = 0;
//	    can_tx_func_fifo(tx_buff_command);
//		tx_buff_command = 0;
//	}	 

}

void clear_can_rx_buff_fun(void)
{
    ubyte i;
	for(i = 0; i < 24; i++)
	{
	    CAN_RX_BUFF[i] = 0;
	}
	CAN_BYTE_DATA_COUNT = 0;
	b_CAN_franme_start = 0;
	b_CAN_franme_stop  = 0;
}

void clear_can_tx_buff_fun(void)
{
    ubyte i;
	for(i = 0; i < 16; i++)
	{
	    CAN_TX_BUFF[i] = 0;
	}

}

ubyte CAN_createBCC(ubyte Len)
{
       ubyte BCC_data = 0x55; 
	ubyte i;
	
	if(Len > 19)
	{
	    return BCC_data;
	}
	
	BCC_data = CAN_TX_BUFF[0];
	
	for(i = 1; i < (Len + 4); i++)	  //DATA的长度加上前面的4个字节，头，类型，地址，FC类型。
	{
	    BCC_data    ^=    CAN_TX_BUFF[i];	    	    
	}

	return BCC_data;
}

void send_Frame_data_for_can(ubyte FC_data, ubyte send_data[], ubyte Len)
{
	ubyte i;
	ubyte BCC_DATA,  BCC1_DATA,  BCC2_DATA;
	  
	//过长保护
	if(Len > 20)
	{
	    Len = 1;
	}
    CAN_TX_BUFF[0]  =    Fram_Head;    //包头
	CAN_TX_BUFF[1]  =    DEV_TYPE;     //类型
	CAN_TX_BUFF[2]  =    DEV_ADDR;     //命令
	CAN_TX_BUFF[3]  =    FC_data;     //命令
	//内容
	for(i = 0; i < Len; i++)
	{	    	    
	    CAN_TX_BUFF[i+4]  =  send_data[i]; 		
	}
	BCC_DATA = 	CAN_createBCC(Len);	   //为要发送的数据产生BCC吗，再转成2个字节的字符型BCC1，BCC2
	BCC1_DATA = Hex_TurnTO_ASC((BCC_DATA&0xF0)>>4);

	CAN_TX_BUFF[Len + 4] = BCC1_DATA;

	BCC2_DATA = Hex_TurnTO_ASC(BCC_DATA&0x0F);
	CAN_TX_BUFF[Len + 5] = BCC2_DATA;

	CAN_TX_BUFF[Len + 6] = Fram_End;	   //数据结束符
}

void can_send_data(ubyte CAN_TX_BUFF_TEMP[], ubyte Len)
{
    ubyte i, j,frame_number;
	frame_number = ((Len + 7)/8);
	if(((Len + 7)%8) != 0)
	{
	    frame_number++;    
	}
	for(j = 0; j < frame_number; j++)
	{
		i = j * 8;	
	    CAN_DATA0 = CAN_TX_BUFF_TEMP[i];  	// load to CAN Data register 0 
		i++; 
		CAN_DATA1 =	CAN_TX_BUFF_TEMP[i];
		i++;
		CAN_DATA2 = CAN_TX_BUFF_TEMP[i];  	// load to CAN Data register 0  
		i++;
		CAN_DATA3 = CAN_TX_BUFF_TEMP[i];
		i++;			
													
	    CAN_vWriteCANAddress(CAN_MODATAL0);	  				// address MO0 Data register
	    CAN_vWriteEN(ALL_DATA_VALID);	
	
		CAN_DATA0 = CAN_TX_BUFF_TEMP[i];  	// load to CAN Data register 0 
		i++; 
		CAN_DATA1 =	CAN_TX_BUFF_TEMP[i];
		i++;
		CAN_DATA2 = CAN_TX_BUFF_TEMP[i];  	// load to CAN Data register 0  
		i++;
		CAN_DATA3 = CAN_TX_BUFF_TEMP[i];
		i++;
	
		CAN_vWriteCANAddress(CAN_MODATAH0);	  				// address MO0 Data register
	    CAN_vWriteEN(ALL_DATA_VALID);
											   
	    CAN_vTransmit(0);	
		b_Waiting_CAN_Send_Interupt_Flag = 1;
		T0_5MS_count_Waiting_CAN_Send_INTR_Flag = 0;
	
		while(b_CAN_tran_complete == 0)
		{
		    T0_INT_SCAN();
		    if(T0_5MS_count_Waiting_CAN_Send_INTR_Flag > 2)
			{	   
			    Cancel_CAN_vTransmit(0);
			    Recover_CAN_BUS();
			    CAN_vInit();
				b_CAN_tran_complete = 1;
				b_CAN_Send_Fail_Flag = 1;	
				j = frame_number;	
				
				
			//	can_tx_func_fifo(CAN_TX_TimeOut);	
			}	    
		}
			b_CAN_tran_complete	 = 0;
			b_Waiting_CAN_Send_Interupt_Flag = 0;
	}
}


void Recover_CAN_BUS(void)
{
    CAN_vWriteCANAddress(CAN_NCR0); // Addressing CAN_NCR0
    CAN_DATA0 = 0x41;            // load NODE 0 control register[7-0]
    CAN_vWriteEN(D0_VALID);

	CAN_vWriteCANAddress(CAN_NECNT0);
	CAN_DATA0 = 0x00;
	CAN_DATA1 = 0x00;
	CAN_DATA2 = 0x60;
	CAN_DATA3 = 0x00;  
	CAN_vWriteEN(ALL_DATA_VALID);

	CAN_vWriteCANAddress(CAN_NCR0); // Addressing CAN_NCR0
    CAN_vReadEN();               // Read Mode is Enabled
    CAN_DATA0  &= ~0x41;         // reset INIT and CCE
    CAN_vWriteEN(D0_VALID); 

}



void Cancel_CAN_vTransmit(ubyte ubObjNr)
{
    CAN_pushAMRegs();    //   PUSH the CAN Access Mediator Register

    CAN_vWriteCANAddress(CAN_MOCTR(ubObjNr));  //Addressing CAN_MOCTR register
    CAN_vWriteCANData(0x00000720);      // set TXRQ,TXEN0,TXEN1,MSGVAL

    CAN_popAMRegs();    //   POP the CAN Access Mediator Register

}



void can_tx_status_scan_function(void)
{
    
    if((0 != TX_FIFO_COUNTER) && (!b_CAN_traning))
	{
	    can_tx_status =  TX_FIFO_FUNC[0];
//		TX_FIFO_COUNTER--;
//		FIFO_displace();
		clear_can_tx_buff_fun();
		b_CAN_traning = 1;
		switch(can_tx_status)
		{
		    case ACT:
				    send_Frame_data_for_can(ACT, Version_and_Sequence, 16);
					can_send_data(CAN_TX_BUFF,16);    		    
			    break;

			case Dont_Have_BootLoader:
				    send_Frame_data_for_can(Dont_Have_BootLoader, error_data, 0);
					can_send_data(CAN_TX_BUFF,0);
			    break;
			case Turn_To_BootLoader_APP:
				    send_Frame_data_for_can(Turn_To_BootLoader_APP, error_data, 0);
					can_send_data(CAN_TX_BUFF,0);
					b_Turn_To_BootLoader_Flag = 1;
						    		    
			    break;
			case Turn_LED_Status:
			    
					error_data[0] = ub_LED_Status;
				    send_Frame_data_for_can(Turn_LED_Status, error_data, 1);
					//can_tx_status_traning();
					can_send_data(CAN_TX_BUFF,1);
						    		    
			    break;
			case LOAD_SUCCESS:
			    
				
				    send_Frame_data_for_can(LOAD_SUCCESS, error_data, 0);
					//can_tx_status_traning();
					can_send_data(CAN_TX_BUFF,0);
						    		    
			    break;
			case LOAD_FAIL:
			    
				
				    send_Frame_data_for_can(LOAD_FAIL, error_data, 0);
					//can_tx_status_traning();
					can_send_data(CAN_TX_BUFF,0);
						    		    
			    break;
			case WORKER_QUIT_TURE:
			    
				
				    send_Frame_data_for_can(WORKER_QUIT_TURE, error_data, 0);
					//can_tx_status_traning();
					can_send_data(CAN_TX_BUFF,0);
						    		    
			    break;
			case ASK:
			    
					//send_Frame_data_for_can(ANS, IDCARD_data, 10);
				    send_Frame_data_for_can(ANS, full_data, 1);
					//can_tx_status_traning();
					can_send_data(CAN_TX_BUFF,1);
						    		    
			    break;

			case IN_OUT_STATION_STATUS:
			    
					//send_Frame_data_for_can(ANS, IDCARD_data, 10);
				    send_Frame_data_for_can(IN_OUT_STATION_STATUS, full_data, 1);
					//can_tx_status_traning();
					can_send_data(CAN_TX_BUFF,1);
						    		    
			    break;
			case EEROR:
			
				    
				    send_Frame_data_for_can(EEROR, error_data, 1);
					//can_tx_status_traning();
					can_send_data(CAN_TX_BUFF,1);
					error_data[0] = 0;
				
			    break;
			case YJ_ID_send:
			    
				    
				    send_Frame_data_for_can(YJ_ID_send, IDCARD_data, 10);
					//can_tx_status_traning();
					can_send_data(CAN_TX_BUFF,10);
				
			    break;
			case YJ_ID_With_LaserNumber_send:
			    
				    
				    send_Frame_data_for_can(YJ_ID_With_LaserNumber_send, IDCARD_data, (10 + ub_Send_LaserNumber_Count));

					can_send_data(CAN_TX_BUFF,(10 + ub_Send_LaserNumber_Count));
				
			    break;
			case YJ_ID:
			   
				    
				    send_Frame_data_for_can(YJ_ID, IDCARD_data, 10);
					//can_tx_status_traning();
					can_send_data(CAN_TX_BUFF,10);
				
			    break;
			case LCD_KEY_TO_PC:
			   
				    
				   
					//can_tx_status_traning();
					can_send_data(RS485_LK_buff,(ub_lcd_key_send_pc_number-7));
				
			    break;
	

	
			default:
			    
				//	can_tx_status = 0;
				
					b_CAN_waiting_interrupt = 0;
					can_traning_frame_number = 1;
					clear_can_tx_buff_fun();
				 
			    
			    break;
		
		}
		if(!b_CAN_Send_Fail_Flag)
		{

		    TX_FIFO_COUNTER--;
		    FIFO_displace();		
		}
		b_CAN_Send_Fail_Flag = 0;
		b_CAN_traning = 0;
	}
    

}


bool compare_command(ubyte tx_function_for_compare)
{
    ubyte i;

	for(i = 0; i < 4; i++)
	{
	  if(TX_FIFO_FUNC[i]  == tx_function_for_compare)
	  {	     
		 return 0;
	  }	
	}	
	return 1;

}



void can_tx_func_fifo(ubyte tx_function)
{
    if(compare_command(tx_function))
	{
		if(TX_FIFO_COUNTER < 4)
		{
		    TX_FIFO_FUNC[TX_FIFO_COUNTER] = tx_function;   
			TX_FIFO_COUNTER++; 
		}
		else
		{
		    TX_FIFO_FUNC[3] = tx_function;   
			TX_FIFO_COUNTER = 4;
		}
	}
	
}
 /*
void can_tran_complete_for_delay(void)
{
    if(b_CAN_tran_complete)
	{
	    b_CAN_tran_complete = 0;		
		b_CAN_waiting_interrupt = 0;
		T0_5MS_CAN_tran_complete_count = 0;
	}
} */

void FIFO_displace(void)
{
    ubyte i;
	for(i = 0; i < 3; i++)
	{
	    TX_FIFO_FUNC[0 + i] = TX_FIFO_FUNC[1 + i];
	}
	TX_FIFO_FUNC[3] = 0;
}

void Get_CAN_Data(void)
{
    ubyte ubTempMsgID = 0;
	ubyte ubTempVarObjHandler = 0;
	un_32bit ulBit_Pos_Mask;
	ubyte i;
	CAN_pushAMRegs();              // push the CAN Access Mediator Registers

    SFR_PAGE(_su0, SST0); 


    //   ---------------------------------------------------------------------
    //   Interrupts of CAN Msg Obj x 
    //   ---------------------------------------------------------------------

    CAN_vWriteCANAddress(CAN_MSIMASK);    // set message index mask register
    CAN_DATA0   =   0x06;        // set message index mask register
    CAN_DATA1   =   0x00;        // set message index mask register
    CAN_DATA2   =   0x00;        // set message index mask register
    CAN_DATA3   =   0x00;        // set message index mask register

    CAN_vWriteEN(ALL_DATA_VALID); // Write mode Enabled

    // USER CODE BEGIN (SRN1,1)

    // USER CODE END
    CAN_vWriteCANAddress(CAN_MSID0);   // message index register
    CAN_vReadEN();               // Read Mode is enabled

    ubTempMsgID = CAN_DATA0;

    if(ubTempMsgID != 0x20)
    {
      do
      {
      CAN_vWriteCANAddress(CAN_MOCTR(ubTempMsgID)); // Addressing CAN_MOCTRn
      CAN_vReadEN();               // Read Mode is enabled
      ubTempVarObjHandler = CAN_DATA0;

      ulBit_Pos_Mask.ulVal = ((unsigned long) 1 << ubTempMsgID);
      CAN_vWriteCANAddress(CAN_MSPND0); // Addressing CAN_MSPND0

      CAN_DATA0 = ~ulBit_Pos_Mask.ubDB[3]; // clear message pending register
      CAN_DATA1 = ~ulBit_Pos_Mask.ubDB[2]; // clear message pending register
      CAN_DATA2 = ~ulBit_Pos_Mask.ubDB[1]; // clear message pending register
      CAN_DATA3 = ~ulBit_Pos_Mask.ubDB[0]; // clear message pending register
      CAN_vWriteEN(ALL_DATA_VALID);  // Write mode Enabled



      // USER CODE BEGIN (SRN1_OBJ,1)
	  if( ubTempVarObjHandler & MOSTAT_RXPND)   // if RXPND is set
           {         
             if( ubTempVarObjHandler & MOSTAT_NEWDAT)   // if NEWDAT is set
             {	                				   
				   if(CAN_BYTE_DATA_COUNT > 25)
				   {
				       clear_can_rx_buff_fun();
				   }
				   CAN_vWriteCANAddress(CAN_MODATAL(ubTempMsgID));
				  // CAN_vWriteCANAddress(CAN_MODATAL1);	 		// Show received ADC value on port 3 LED's
	               CAN_vReadEN();
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA0;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA1;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA2;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA3;
				   CAN_BYTE_DATA_COUNT++;
				   
                   CAN_vWriteCANAddress(CAN_MODATAH(ubTempMsgID));
				  // CAN_vWriteCANAddress(CAN_MODATAH1);	 		// Show received ADC value on port 3 LED's
	               CAN_vReadEN();
				   
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA0;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA1;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA2;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA3;
				   CAN_BYTE_DATA_COUNT++;
				   
				   
				  
				   if(CAN_RX_BUFF[0] != Fram_Head)
				   {
					   clear_can_rx_buff_fun();	
									   
				   }
				   else
				   {
				       b_CAN_franme_start = 1;
				       if(CAN_BYTE_DATA_COUNT < 8)
					   {		
						   clear_can_rx_buff_fun();				   
					   }
					   else
					   {
						   for(i = 0; i < 8; i++)
						   {
						       if(CAN_RX_BUFF[CAN_BYTE_DATA_COUNT - i - 1] == Fram_End) 
							   {
							       b_CAN_franme_start = 0;
							       b_CAN_franme_stop = 1;
								   ub_send_lcd_key_data_number = (CAN_BYTE_DATA_COUNT - i);
								   CAN_BYTE_DATA_COUNT = 0;								  
							   }   
						   }
					   }
				   }

          
              }

          
          // Reset RXPND, NEWDAT, MSGLST (if set)
          
            CAN_vWriteCANAddress(CAN_MOCTR(ubTempMsgID)); // Addressing CAN_MOCTRn
          
            CAN_DATA0 = (ubTempVarObjHandler & MOSTAT_RST_MNR); // load CAN Data Register 0
            CAN_DATA1 = 0x00; // load CAN Data Register 1
            CAN_DATA2 = 0x00; // load CAN Data Register 2
            CAN_DATA3 = 0x00; // load CAN Data Register 3
            CAN_vWriteEN(ALL_DATA_VALID);   // Writemode is Enabled
           }

      // USER CODE END

      CAN_vWriteCANAddress(CAN_MSIMASK);    // set message index mask register
      CAN_DATA0  =   0x06;       // set message index mask register
      CAN_DATA1  =   0x00;       // set message index mask register
      CAN_DATA2  =   0x00;       // set message index mask register
      CAN_DATA3  =   0x00;       // set message index mask register

      CAN_vWriteEN(ALL_DATA_VALID); // Write mode Enabled

      // USER CODE BEGIN (SRN1,5)

      // USER CODE END

      CAN_vWriteCANAddress(CAN_MSID0);   // message index register
      CAN_vReadEN();               // Read Mode is enabled
      ubTempMsgID = CAN_DATA0;

      }while (ubTempMsgID != 0x20); // end while

    }  // end if


	SFR_PAGE(_su0, RST0);          // restore the old SCU page

    CAN_popAMRegs();  

}
 /*
void RE_circulation_FIFO(ubyte repend_function)
{
    ubyte i;
	for(i = 0; i < 3; i++)
	{
	    TX_FIFO_FUNC[3 - i] = TX_FIFO_FUNC[2 - i];
	}
	TX_FIFO_FUNC[0] = repend_function;
	TX_FIFO_COUNTER++;
} 	  */