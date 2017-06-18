#include "MAIN.H" 

void rs485_lk_scan(void)
{

	ubyte i;

	if(RS485_LK_Frequency <= T0_5MS_count_rs485_lk)
	{
	    T0_5MS_count_rs485_lk = 0;	
		if(b_have_LCD_KEY_DATA)
		{
		    b_check_have_lcd_key = 0;
		    full_data[0] &= 0xBF;
		}
		b_have_LCD_KEY_DATA = 1;
		if(!b_check_have_lcd_key)
		{
		    rs_485_2_tx_func_fifo(HELLO);	    
		}
		else
		{
			rs_485_2_tx_func_fifo(ASK);
		}
	    		
	}  

    

	
	if(FRAME_start_rs485_lk&&(!FRAME_end_rs485_lk)&&(16 <= T0_5MS_rs485_lk_frame_count))
    {
        T0_5MS_rs485_lk_frame_count  =    0;
		byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;

	  
	    return;
  //此函数为判断，收到帧头后，中间间隔10ms以上没有收到帧尾，说明通信错误。
    }
	if(!FRAME_end_rs485_lk)
    {
      return;
    }
	b_rs_485_2_traning = 0;
	ub_T0_5MS_count_re_485_2_wait_recieve = 0;
	
	FRAME_end_rs485_lk = 0;
	T0_5MS_rs485_lk_frame_count = 0;
//	T0_5MS_count_rs485_lk_b_flag_time = 0;

	if(26 < byte_count_rs485_lk)
    {
        byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;
		
	    return;
  
    }
	if(7 > byte_count_rs485_lk)
    {
        byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;
	  
	    return;  
    }
/*	if(!check_BCC_rs485_lk(byte_count_rs485_lk-7))
	{
	    byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;
	  
	    return;    
	
	}				 
	byte_count_rs485_lk = 0;
    FRAME_start_rs485_lk = 0;
    FRAME_end_rs485_lk   = 0;	*/

	if(RS485_LK_buff[1] != 0x13)
	{
	    byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;
		b_check_have_lcd_key = 0;
		full_data[0] &= 0xBF;
	  
	    return; 
	}

	
	if(RS485_LK_buff[2] != DEV_ADDR)
	{
	    byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;
		b_check_have_lcd_key = 0;
		full_data[0] &= 0xBF;
		rs_485_2_tx_func_fifo(SET_ADDRESS);	
	  
	    return; 
	}
	b_check_have_lcd_key = 1;
	full_data[0] |= 0x40;
	b_have_LCD_KEY_DATA = 0;
	if(!b_IDNumber_With_LaserNumber_flag)
	{
		if((RS485_LK_buff[3] != ANS) && (RS485_LK_buff[3] != ACT))
		{
		   
		    //b_have_LCD_KEY_DATA = 1;   
			can_tx_func_fifo(LCD_KEY_TO_PC);    		 
		}
	}
	else
	{
	    if((RS485_LK_buff[3] != ANS) && (RS485_LK_buff[3] != ACT) && (RS485_LK_buff[3] != LASER_NUMBER))
		{
			can_tx_func_fifo(LCD_KEY_TO_PC);    		 
		}
		if(RS485_LK_buff[3] == LASER_NUMBER)
		{	
		    for(i = 0; i < (ub_lcd_key_send_pc_number-7); i++)
			{
			    Laser_Temp_DATA[i + 1] =  RS485_LK_buff[4 + i];
			}
			b_Have_Got_LaserNumber_Flag = 1;
			ub_A_LaserNumber_Count = (ub_lcd_key_send_pc_number-7);	
			Laser_Temp_DATA[0] = ub_A_LaserNumber_Count;	    
	    }
	}
	
	
	
    

	
	


}
//	   异卡比较



ubyte createBCC_rs485_lk(ubyte Len)
{
       ubyte BCC_data = 0x55; 
	ubyte i;
	
	if(Len > 19)
	{
	    return BCC_data;
	}
	
	BCC_data = RS485_LK_buff[0];
	
	for(i = 1; i < (Len + 4); i++)	  //DATA的长度加上前面的4个字节，头，类型，地址，FC类型。
	{
	    BCC_data    ^=    RS485_LK_buff[i];	    	    
	}

	return BCC_data;
}

/****   组装发送包 ***********
输入参数为：命令类型，DATA数据所在的数组，DATA数据的长度
与上位机通信使用
 *********/
void send_Frame_data_rs485_lk(ubyte FC_data, ubyte DEV_TYPE_RS485_LK_SLAVE, ubyte DEV_ADDR_RS485_LK_SLAVE, ubyte send_data[], ubyte Len)
{
	ubyte i,BCC_DATA,  BCC1_DATA,  BCC2_DATA;
	  
	//过长保护
	if(Len > 19)
	{
	    Len = 19;
	}
	
    RS485_LK_buff[0]  =    Fram_Head;    //包头
	RS485_LK_buff[1]  =    DEV_TYPE_RS485_LK_SLAVE;     //类型
	RS485_LK_buff[2]  =    DEV_ADDR_RS485_LK_SLAVE;   //地址
	RS485_LK_buff[3]  =    FC_data;      //命令

	//内容
	for(i = 0; i < Len; i++)
	{	    	    
	    RS485_LK_buff[i+4]  =  send_data[i]; 		
	}

	BCC_DATA = 	createBCC_rs485_lk(Len);	   //为要发送的数据产生BCC吗，再转成2个字节的字符型BCC1，BCC2
	
	//BCC转换
	BCC1_DATA = Hex_TurnTO_ASC((BCC_DATA&0xF0)>>4);

	RS485_LK_buff[Len + 4] = BCC1_DATA;

	BCC2_DATA = Hex_TurnTO_ASC(BCC_DATA&0x0F);
	RS485_LK_buff[Len + 5] = BCC2_DATA;
	RS485_LK_buff[Len + 6] = Fram_End;	   //数据结束符
}





