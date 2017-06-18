#include "MAIN.H"

//完成按钮扫描函数
void COMPLEGE_DONE_SCAN(void)
{
    ubyte i;
	//检测到完成按钮标记
    if((b_COMPLETE_DONE_flag)&&(scan_complete))
	{
	    b_COMPLETE_DONE_flag    =    0;
		T0_5MS_count_complete_scan  =  0;

	    if(have_id_data&&(push_count >= 2))
		{
		    
		    MOTO_ENABLE       =    0;
		    P3_5              =    0;
		    P4_4              =    0;
			if((0x01 & (full_data[0])) == 0)
		    {
		        full_data[0]     |=    0x01;

				  if(have_id_data)
				  {			     
				      if(!b_IDNumber_With_LaserNumber_flag)
					  {
						  can_tx_func_fifo(YJ_ID_send); 
					  }	
					  else
					  {
					      can_tx_func_fifo(YJ_ID_With_LaserNumber_send);
					  }    			     
	
				  }
	
				  else 
				  {
				      can_tx_func_fifo(IN_OUT_STATION_STATUS);
	
				  }
		    }
		    
		}
		else
		{
		    if(have_id_data)
			{
			    //如果有衣架,完成按钮++
			    push_count++;
			}
			else
			{
			//只要没有衣架,完成按钮就清0
			    push_count = 0;		
			}
			if((0x01 & (full_data[0])) != 0)
			{
			    full_data[0]    &=    0xFE;
				  if(have_id_data)
				  {			     
				      if(!b_IDNumber_With_LaserNumber_flag)
					  {
						  can_tx_func_fifo(YJ_ID_send); 
					  }	
					  else
					  {
					      can_tx_func_fifo(YJ_ID_With_LaserNumber_send);
					  }    			     
	
				  }
	
				  else 
				  {
				      can_tx_func_fifo(IN_OUT_STATION_STATUS);
	
				  }
			}
	
		    
		    b_PutDownYjFlag    =    1;  //下放衣架
		    MOTO_ENABLE       =    1;   //提升电机
		    P3_5              =    1;
		    P4_4              =    1;
			b_Have_Got_LaserNumber_Flag  = 0;
			Store_Laser_Number_ADDR_IN_XDATA = (THE_FIRST_ADDR_For_Store_LaserNumber_At_XDATA + (20 * ub_STORE_Count_LaserNumbers_In_XDATA_ADDR));
			*Store_Laser_Number_ADDR_IN_XDATA = Laser_Temp_DATA[0];
			Store_Laser_Number_ADDR_IN_XDATA++;
			for(i = 0; i < Laser_Temp_DATA[0]; i++)
			{
			    *Store_Laser_Number_ADDR_IN_XDATA = Laser_Temp_DATA[i + 1];   
				Store_Laser_Number_ADDR_IN_XDATA++; 
			}
			if(9 == ub_STORE_Count_LaserNumbers_In_XDATA_ADDR)
			{
			    ub_STORE_Count_LaserNumbers_In_XDATA_ADDR = 0;
			}
			else if(ub_STORE_Count_LaserNumbers_In_XDATA_ADDR <9)
			{
			    ub_STORE_Count_LaserNumbers_In_XDATA_ADDR++;
			}
			else
			{
			    b_IDNumber_With_LaserNumber_flag = 0;
			}
			
		}
	}
}	

//计时器扫描
void T0_INT_SCAN(void)
{
	//计时器中断标记
    if(b_T0_5MS_flag)
	{
	    b_T0_5MS_flag    =    0;
		if(b_CAN_franme_start)
		{
			if(T0_5MS_count1 > 250)
			{
			    T0_5MS_count1 = 0;
			}
			else
			{
			    T0_5MS_count1++;
			}
		}
		if(FRAME_start_1)
		{
			if(T0_5MS_IDread_frame_count > 250)
			{
			    T0_5MS_IDread_frame_count = 0;
			}
			else
			{
			    T0_5MS_IDread_frame_count++;
			}
		}

		if(FRAME_start_rs485_lk)
		{
		    if(T0_5MS_rs485_lk_frame_count > 250)
			{
			    T0_5MS_rs485_lk_frame_count = 0;
			}
			else
			{
			    T0_5MS_rs485_lk_frame_count++;
			}
		}
	
	
	

		 if(in_full)
		 {
		     if(T0_5MS_count_infull < 60000)
			 {
			 	 T0_5MS_count_infull++;
			 }
			 else
			 {
			     T0_5MS_count_infull = 0;
			 }
		 }

		 //衣架进站计数器
		 if(input_yj_flag)
		 {
		     if(T0_5MS_count_input < 60000)
			 {
			     T0_5MS_count_input++;
			 }
			 else
			 {
			     T0_5MS_count_input = 0;
			 }
		     
		 }


		 if(b_input_yj_flag_2)
		 {
		     if(uw_T0_5MS_count_input_2 < 60000)
			 {
			     uw_T0_5MS_count_input_2++;
			 }
			 else
			 {
			     uw_T0_5MS_count_input_2 = 0;
			 }
		     
		 }

		 if(b_input_yj_flag_3)
		 {
		     if(uw_T0_5MS_count_input_3 < 60000)
			 {
			     uw_T0_5MS_count_input_3++;
			 }
			 else
			 {
			     uw_T0_5MS_count_input_3 = 0;
			 }
		     
		 }

		//衣架出站计数器
		 if(output_yj_flag)
		 {
		     if(T0_5MS_count_output < 60000)
			 {
			     T0_5MS_count_output++;
			 }
			 else
			 {
			     T0_5MS_count_output = 0;
			 
			 }
		     
		 }

		 //扫描键盘信息。通过串口
		
		     if(T0_5MS_count_rs485_lk < 250)
			 {
			     T0_5MS_count_rs485_lk++;
			 }
			 else
			 {
			     T0_5MS_count_rs485_lk = 0;
			 }

		if(b_Waiting_CAN_Send_Interupt_Flag)
		{
			if(T0_5MS_count_Waiting_CAN_Send_INTR_Flag > 250)
			{
			    T0_5MS_count_Waiting_CAN_Send_INTR_Flag = 0;
			}
			else
			{
			    T0_5MS_count_Waiting_CAN_Send_INTR_Flag++;
			}
		}

		if(ub_T0_5MS_count_led < 200)
		 {
		     ub_T0_5MS_count_led++;
		 }
		 else
		 {
		     ub_T0_5MS_count_led = 0;
		 }
		     
		 

		 //衣架读卡器计时器，读卡频率
		 if(ID_read_enable)
		 {
		     if(T0_5MS_count_YJ_id < 250)
			 {
			     T0_5MS_count_YJ_id++;
			 }
			 else
			 {
			     T0_5MS_count_YJ_id = 0;
			 }
		     
		 }

		 if(!scan_complete)
		 {
		     if(T0_5MS_count_complete_scan < 250)
			 {
			     T0_5MS_count_complete_scan++;
			 }
			 else
			 {
			     T0_5MS_count_complete_scan = 0;
			 }
		 }
	/*	 else
		 {
		     T0_5MS_count_complete_scan = 0;
		 }	*/
		 
		 //电机一，停止感应器或者微动，扫描
		 if(!scan_stop_moto_1)
		 {
		     if(T0_5MS_count_scan_stop_moto_1 < 250)
			 {
			     T0_5MS_count_scan_stop_moto_1++;
			 }
			 else
			 {
			     T0_5MS_count_scan_stop_moto_1 = 0;
			 }
		 }
	/*	 else
		 {
		     T0_5MS_count_scan_stop_moto_1 = 0;
			 b_stop_moto_1_flag    =    0;
			 T0_5MS_count_stop_moto_delay_1 = 0;
		 } */
		 
		 

		 //电机二，停止感应器或者微动，扫描
		 if(!scan_stop_moto_2)
		 {
		     if(T0_5MS_count_scan_stop_moto_2 < 250)
			 {
			     T0_5MS_count_scan_stop_moto_2++;
			 }
			 else
			 {
			     T0_5MS_count_scan_stop_moto_2 = 0;
			 }
		 }
	/*	 else
		 {
		     T0_5MS_count_scan_stop_moto_2 = 0;
			 b_stop_moto_2_flag    =    0;
			 T0_5MS_count_stop_moto_delay_2 = 0;
		 }	 */
		 
	

		 
		 if(b_same_ID_re_read_flag)
		 {
		     if(T0_5MS_count_same_ID_re_read < 60000)
			 {
			     T0_5MS_count_same_ID_re_read++;
			 }
			 else
			 {
			     T0_5MS_count_same_ID_re_read = 0;
			 }
		 }
		 
		 if(b_rs_485_2_traning)
		 {
		     if(ub_T0_5MS_count_re_485_2_wait_recieve < 250)
			 {
			     ub_T0_5MS_count_re_485_2_wait_recieve++;
			 }
			 else
			 {
			     ub_T0_5MS_count_re_485_2_wait_recieve = 0;
			 }
		 }

		 	
		
	/*	 if(T0_5MS_count_KEY_SCAN < 250)
		 {
		     T0_5MS_count_KEY_SCAN++;
		 }
		 else
		 {
		     T0_5MS_count_KEY_SCAN = 0;
		 } */
		if(b_PutDownYjFlag)
			 {
			     if(T0_5MS_count_PutDownYjDelay < 60000)
				 {
				     T0_5MS_count_PutDownYjDelay++;
				 }
				 else
				 {
				     T0_5MS_count_PutDownYjDelay = 0;
				 }  
			 }
		   
		
	}
}







