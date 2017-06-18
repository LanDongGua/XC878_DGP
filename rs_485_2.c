#include "MAIN.H" 


void scan_rs_485_2(void)
{
    ubyte temp_lcd_key_addr[2];
    if((!b_rs_485_2_traning) && (0 != ub_rs_485_2_TX_FIFO_COUNTER))
	{
	    Enable_Txd_1();
		Delay_function(100);
	    ub_rs485_2_TX_status = ub_rs485_2_TX_FIFO_FUNC[0];  
		ub_rs_485_2_TX_FIFO_COUNTER--; 
		rs_485_2_FIFO_displace(); 
		 
		switch(ub_rs485_2_TX_status)
		{
		    case READ_ID_READER:
			    byte_count_1 = 0;					       					       
	            FRAME_end_1   = 0;
                FRAME_start_1 = 0;
			    send_IdReader_Frame('2', 'F', full_data, 0);
				send_command_rs485_2(send_data,0);
				b_rs_485_2_traning = 1;
			     
			    break;
			case HELLO:
			    byte_count_rs485_lk = 0;
	            FRAME_start_rs485_lk = 0;
			    FRAME_end_rs485_lk   = 0;
				send_Frame_data_rs485_lk(HELLO, 0x13, 0, error_data, 0);
				send_command_rs485_2(RS485_LK_buff,0);
				b_rs_485_2_traning = 1;
			    break;
			

			case ASK:
			    byte_count_rs485_lk = 0;
	            FRAME_start_rs485_lk = 0;
			    FRAME_end_rs485_lk   = 0;
				send_Frame_data_rs485_lk(ASK, 0x13, DEV_ADDR, error_data, 0);
				send_command_rs485_2(RS485_LK_buff,0);
				b_rs_485_2_traning = 1;
			    break;
			case SET_ADDRESS:
			    byte_count_rs485_lk = 0;
	            FRAME_start_rs485_lk = 0;
			    FRAME_end_rs485_lk   = 0;
				temp_lcd_key_addr[0] = DEV_ADDR;
				temp_lcd_key_addr[0] = (temp_lcd_key_addr[0] & 0xF0);
				temp_lcd_key_addr[0] >>= 4;
				temp_lcd_key_addr[0] = 	Hex_TurnTO_ASC(temp_lcd_key_addr[0]);
				temp_lcd_key_addr[1] = DEV_ADDR;
				temp_lcd_key_addr[1] = (temp_lcd_key_addr[1] & 0x0F);
				temp_lcd_key_addr[1] = 	Hex_TurnTO_ASC(temp_lcd_key_addr[1]);
				send_Frame_data_rs485_lk(SET_ADDRESS, 0x13, 0, temp_lcd_key_addr, 2);
				send_command_rs485_2(RS485_LK_buff,2);
				b_rs_485_2_traning = 1;
			    break;
			   

			case PC_TO_LCD_KEY:
			    byte_count_rs485_lk = 0;
	            FRAME_start_rs485_lk = 0;
			    FRAME_end_rs485_lk   = 0;
			
				
				send_command_rs485_2(LCD_KEY_DATA,(ub_send_lcd_key_data_number - 7));
			//	b_rs_485_2_traning = 1;
			    break;	  

	
			default:
			   /* ub_rs485_2_TX_status = 0;
				byte_count_rs485_lk = 0;
	            FRAME_start_rs485_lk = 0;
			    FRAME_end_rs485_lk   = 0; */
				byte_count_1 = 0;					       					       
	            FRAME_end_1   = 0;
                FRAME_start_1 = 0;
				b_rs_485_2_traning = 0;
				ub_T0_5MS_count_re_485_2_wait_recieve = 0;
			    break;
		}
		Enable_Rxd_1();
	}
}

void rs_485_2_tx_status(void)
{
    if(b_rs_485_2_traning && (ub_T0_5MS_count_re_485_2_wait_recieve >= 8))
	{
	    b_rs_485_2_traning = 0;
		ub_T0_5MS_count_re_485_2_wait_recieve = 0;		    
	}
}

bool compare_command_rs_485_2(ubyte tx_function_for_compare)
{
    ubyte i;

	for(i = 0; i < 4; i++)
	{
	  if(ub_rs485_2_TX_FIFO_FUNC[i]  == tx_function_for_compare)
	  {	     
		 return 0;
	  }	
	}	
	return 1;

}

void rs_485_2_tx_func_fifo(ubyte tx_function)
{
    if(tx_function != PC_TO_LCD_KEY)
	{
	    if(compare_command_rs_485_2(tx_function))
		{
		    if(ub_rs_485_2_TX_FIFO_COUNTER < 4)
			{
			    ub_rs485_2_TX_FIFO_FUNC[ub_rs_485_2_TX_FIFO_COUNTER] =  tx_function;  
				ub_rs_485_2_TX_FIFO_COUNTER++; 
			}
		}
	}
	else
	{
		if(ub_rs_485_2_TX_FIFO_COUNTER < 4)
		{
		    ub_rs485_2_TX_FIFO_FUNC[ub_rs_485_2_TX_FIFO_COUNTER] =  tx_function;  
			ub_rs_485_2_TX_FIFO_COUNTER++; 
		}
	    
		else
		{
		    ub_rs485_2_TX_FIFO_FUNC[3] = tx_function;   
			ub_rs_485_2_TX_FIFO_COUNTER = 4;
		}
	}

    
	
}



void rs_485_2_FIFO_displace(void)
{
    ubyte i;
	for(i = 0; i < 3; i++)
	{
	    ub_rs485_2_TX_FIFO_FUNC[0 + i] = ub_rs485_2_TX_FIFO_FUNC[1 + i];
	}
	ub_rs485_2_TX_FIFO_FUNC[3] = 0;
}




void send_command_rs485_2(ubyte send_buff[], ubyte Len)
{
	ubyte i, data_send;

	//进入该寄存器配置页码
	_push_(SYSCON0);               // push the current RMAP
	SET_RMAP();                    // sets RMAP

	//过长保护
	if(Len > 19)
	{
		Len = 19;
	}
	
	for(i = 0; i < (Len + 7); i++)
	{	    
		data_send = send_buff[i];
		
		ACC = data_send;
		
		TB8_1 = P;				//偶校验。发送TB8；
		
		UART1_SBUF = ACC;
		
		while(0 == TI_1);
	}

	//退出该寄存器配置页码
	RESET_RMAP();                  // resets RMAP
        _pop_(SYSCON0);                // restore the old RMAP
}