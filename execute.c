#include "MAIN.H" 


//ɨ��ִ�ж�������
void execute_scan(void)
{
    if(T0_5MS_count_same_ID_re_read > 600)
	{
	    b_same_ID_re_read_flag = 0;
		b_send_ID_enable   =   0;
		T0_5MS_count_same_ID_re_read    =    0;

	}
	//��վ���������ʶ
	if(input_yj_flag)
	{
		//��վ��ʱ����100ms��λ����,5msΪ����߶ȡ�
		//����1S��ʱ��10 *20 = 200.   200*5 = 1000ms
		if((in_out_time[0] * 20) <= T0_5MS_count_input)
		{
			//��վ����
			INPUT_YJ_ENABLE    =    1;

			//����ʱ�������վ����
			if(((in_time_last*20) + (in_out_time[0]*20)) <= T0_5MS_count_input)
			{	  
				T0_5MS_count_input =    0;
				input_yj_flag      =    0;
				
				INPUT_YJ_ENABLE    =    0;
			}		     
		}
	}

	if(b_input_yj_flag_2)
	{
		//��վ��ʱ����100ms��λ����,5msΪ����߶ȡ�
		//����1S��ʱ��10 *20 = 200.   200*5 = 1000ms
		if((in_out_time[0] * 20) <= uw_T0_5MS_count_input_2)
		{
			//��վ����
			INPUT_YJ_ENABLE    =    1;

			//����ʱ�������վ����
			if(((in_time_last*20) + (in_out_time[0]*20)) <= uw_T0_5MS_count_input_2)
			{	  
				uw_T0_5MS_count_input_2 =    0;
				b_input_yj_flag_2      =    0;
				
				INPUT_YJ_ENABLE    =    0;
			}		     
		}
	}

	if(b_input_yj_flag_3)
	{
		//��վ��ʱ����100ms��λ����,5msΪ����߶ȡ�
		//����1S��ʱ��10 *20 = 200.   200*5 = 1000ms
		if((in_out_time[0] * 20) <= uw_T0_5MS_count_input_3)
		{
			//��վ����
			INPUT_YJ_ENABLE    =    1;

			//����ʱ�������վ����
			if(((in_time_last*20) + (in_out_time[0]*20)) <= uw_T0_5MS_count_input_3)
			{	  
				uw_T0_5MS_count_input_3 =    0;
				b_input_yj_flag_3      =    0;
				
				INPUT_YJ_ENABLE    =    0;
			}		     
		}
	}

	//��վ��ʱ��ԭ�����վ
	if(output_yj_flag)
	{
		if((in_out_time[1] * 20) <= T0_5MS_count_output)
		{
			OUTPUT_YJ_ENABLE    =    1;
			
			if(((out_time_last*20) + (in_out_time[1]*20)) <= T0_5MS_count_output)
			{		
				output_yj_flag      =    0;
				T0_5MS_count_output =    0;
			//	b_send_ID_enable    =    0;
				
				OUTPUT_YJ_ENABLE    =    0;
			}

		}
	}

	if(b_PutDownYjFlag)
	{
	    if(T0_5MS_count_PutDownYjDelay >= (ubPutDownYjDelay * 20))
		{
		    DONE_YJ_ENABLE = 1;
			if(((ubPutDownYjDelay * 20) + 200) <= T0_5MS_count_PutDownYjDelay)
			{
			    b_PutDownYjFlag = 0;
				DONE_YJ_ENABLE = 0;
				T0_5MS_count_PutDownYjDelay = 0;

			}
		}
	    
	}




	  if(!In_station_flag)
	  {
	      in_full = 1;
	  }
	  if(in_full)
	  {
	      if(In_station_flag)
		  {
		      in_full  =  0;
			  T0_5MS_count_infull = 0;
			  if((0x10 & (full_data[0])) != 0)
			  {
			      full_data[0]    &=    0xEF;
				 // can_tx_status    =     IN_STATION_STATUS;
				 
	
	

				 // if(have_id_data&&ID_read_enable)	 //�п������ݵ�ʱ�򡣲���ʹ�ܵ����¼ܶ����������һ�û����5�Σ����¼ܿ��Żظ�������
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
	
				  else //if((0 != full_data[0])&&load_success)	 �ظ�����״̬��
				  {
				      can_tx_func_fifo(IN_OUT_STATION_STATUS);
	
				  }
			  }

			  
		  }
		  
	    
	  }
	  if(400 <= T0_5MS_count_infull)
	  {
	      in_full    =    0;
	      T0_5MS_count_infull    =    0;
		  if((0x10 & (full_data[0])) == 0)
		  {
		      full_data[0]    |=    0x10;
			 // can_tx_status    =     IN_STATION_STATUS;
			


			  // if(have_id_data&&ID_read_enable)	 //�п������ݵ�ʱ�򡣲���ʹ�ܵ����¼ܶ����������һ�û����5�Σ����¼ܿ��Żظ�������
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

			  else //if((0 != full_data[0])&&load_success)	 �ظ�����״̬��
			  {
			      can_tx_func_fifo(IN_OUT_STATION_STATUS);

			  }
		  }
		  
		  

		  //full_data[0]    |=    0x01;
	      
	  }


	  //��ɰ�ťɨ��
	  if((!scan_complete)&&(T0_5MS_count_complete_scan >= 3)&&(!MOTO_ENABLE)&&(!b_COMPLETE_KEY_LOCK_STATUS))
	  {
	      T0_5MS_count_complete_scan = 0;  
	      if(!b_IDNumber_With_LaserNumber_flag)
		  {
			  b_COMPLETE_DONE_flag    =    1; 			  
		  }
		  else
		  {
		      if(b_Have_Got_LaserNumber_Flag)
			  {
			      b_COMPLETE_DONE_flag    =    1; 	
			  }
		  }
	            
	  }
	  //���һ��ֹͣ��Ӧ������΢����ɨ��
	  if((!scan_stop_moto_1)&&(T0_5MS_count_scan_stop_moto_1 >= 2))
	  {
	      b_stop_moto_1_flag = 1;
		  T0_5MS_count_scan_stop_moto_1 = 0;
	  }
	  if((b_stop_moto_1_flag)&&(scan_stop_moto_1))
	  {
		  MOTO_ENABLE       =    0;
		  P4_4              =    0;
		 // b_moto_be_completed_flag  =  0;

		  T0_5MS_count_scan_stop_moto_1 = 0;
		  b_stop_moto_1_flag    =    0;
		 // T0_5MS_count_stop_moto_delay_1 = 0;
	  }

	  //�������ֹͣ��Ӧ������΢����ɨ��
	  if((!scan_stop_moto_2)&&(T0_5MS_count_scan_stop_moto_2 >= 2))
	  {
	      b_stop_moto_2_flag = 1;
		  T0_5MS_count_scan_stop_moto_2 = 0;
	  }
	  if((b_stop_moto_2_flag)&&(scan_stop_moto_2))
	  {
			P3_5              =    0;
			T0_5MS_count_scan_stop_moto_2 = 0;
			b_stop_moto_2_flag    =    0;
			//T0_5MS_count_stop_moto_delay_2 = 0;
	  }

	/*  if(!Out_station_flag)
	  {
	      out_full = 1;
	  }
	  if(out_full)
	  {
	      if(Out_station_flag)
		  {
		      out_full  =  0;
			  T0_5MS_count_outfull  =  0;
			  full_data[0]    &=    0xFE;
			  //full_data[0]    &=    0xEF;

			  EXICON0     &=    0x7F;
			//  IEN1         |=  0x08; 
			  
		  }
		  
	    
	  }
	  if(400 <= T0_5MS_count_outfull)
	  {
	      out_full    =    0;
	      T0_5MS_count_outfull    =    0;
		  full_data[0]    &=    0xFE;
		  full_data[0]    |=    0x01;

		  //full_data[0]    |=    0x10;
		  EXICON0         |=    0x80;
		 // IEN1         &=  0xF7; 
		  if(Out_station_flag)
		  {
		      EXICON0     &=    0x7F;
			 // IEN1         |=  0x08; 
			  		  
		  }
	      
	  }		*/

}