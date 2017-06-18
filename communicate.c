#include "MAIN.H" 


/****  ʮ��0-9��A-F��תASC��   ********/

ubyte Hex_TurnTO_ASC(ubyte hex_data)
{
    ubyte ASC_data;

	if(9 >= hex_data)								//С�ڵ���9���������ַ�
	{
	    ASC_data = (hex_data + 0x30);
	}
	else if((hex_data > 9)&&(hex_data <= 0x0F)) 
	{
	    ASC_data = (hex_data + 0x37);			  //���ھ�����ĸ�ַ�������ֻ�԰���ֽڵ�������ת����
	}
	else
	{
	    ASC_data = 0x30;	    
	}
	
	return ASC_data;
}

/****  ASC��0-9��A-F��תʮ������   ********/

ubyte ASC_TurnTO_Hex(ubyte Asc_data)
{
    ubyte Hex_data;

	if((0x39 >= Asc_data)&&(Asc_data >= 0x30))
	{
	    Hex_data = (Asc_data - 0x30);
	}

	else if((Asc_data >= 0x41)&&(Asc_data <= 0x46)) 
	{
	    Hex_data = (Asc_data - 0x37);
	}
	else
	{
	    Hex_data = 0;    
	}
	
	return Hex_data;
}

/***************���BCC�Ƿ���ȷ��Len��DADA�ĳ���*****************************/
/*
bool check_BCC(ubyte Len)
{
       ubyte check_BCC_data,  BCC1, BCC2, BCC;

	//��������
	if(byte_count < 7)
	{
	    return 0;
	}
	
	BCC1    =    ASC_TurnTO_Hex(buff[byte_count-3]);   //��ȡ��BCC1��2��ת��16�������ݣ��ϲ���BCC
	BCC2    =    ASC_TurnTO_Hex(buff[byte_count-2]);
	BCC     =	 (BCC1<<4)|BCC2;

	//BCC 
	check_BCC_data    =    createBCC(Len);	  //����������BCC�롣

	if(BCC    ==    check_BCC_data)		//���ɵ�BCC��ͽ��ܵ���BCC��һ�£�����1.
	{
	    return 1;
	}
	else
	{
	    return 0;
	}
}
	  */

/***************���BCC�Ƿ���ȷ��Len��DADA�ĳ���*****************************/
 
bool check_BCC_1(ubyte Len)
{
       ubyte check_BCC_data,  BCC1, BCC2, BCC;
	   
	//��������
	if(byte_count_1 < 7)
	{
	    return 0;
	}
	
	BCC1    =    ASC_TurnTO_Hex(send_data[byte_count_1-3]);   //��ȡ��BCC1��2��ת��16�������ݣ��ϲ���BCC
	BCC2    =    ASC_TurnTO_Hex(send_data[byte_count_1-2]);
	BCC     =	 (BCC1<<4)|BCC2;
	check_BCC_data    =    createBCC_1(Len);	  //����������BCC�롣

	if(BCC    ==    check_BCC_data)		//���ɵ�BCC��ͽ��ܵ���BCC��һ�£�����1.
	{
	    return 1;
	}
	else
	{
	    return 0;
	}
} 

/**********   ��ȡBCC��  
�������Ϊ��DATA���ݵĳ���
��λ��ͨ��ʹ��
 ***********/
 /*
ubyte createBCC(ubyte Len)
{
       ubyte BCC_data = 0x55; 
	ubyte i;
	
	if(Len > 19)
	{
	    return BCC_data;
	}
	
	BCC_data = buff[0];
	
	for(i = 1; i < (Len + 4); i++)	  //DATA�ĳ��ȼ���ǰ���4���ֽڣ�ͷ�����ͣ���ַ��FC���͡�
	{
	    BCC_data    ^=    buff[i];	    	    
	}

	return BCC_data;
}		 

  */


/**********   ��ȡBCC��  
�������Ϊ��DATA���ݵĳ���
������ʹ��
 ***********/
 
ubyte createBCC_1(ubyte Len)
{
       ubyte BCC_data = 0x55; 
	ubyte i;
	   
	if(Len > 9)
	{
	    return BCC_data;
	}
	
	BCC_data = send_data[0];
	
	for(i = 1; i < (Len + 4); i++)	  //DATA�ĳ��ȼ���ǰ���4���ֽڣ�ͷ�����ͣ���ַ��FC���͡�
	{
	    BCC_data    ^=    send_data[i];	    	    
	}

	return BCC_data;
}


/****   ��װ���Ͱ� ***********
�������Ϊ���������ͣ�DATA�������ڵ����飬DATA���ݵĳ���
����λ��ͨ��ʹ��
 *********/		 /*
void send_Frame_data(ubyte FC_data, ubyte send_data[], ubyte Len)
{
	ubyte i,BCC_DATA,  BCC1_DATA,  BCC2_DATA;
	  
	//��������
	if(Len > 19)
	{
	    Len = 19;
	}
	
       buff[0]  =    Fram_Head;    //��ͷ
	buff[1]  =    DEV_TYPE;     //����
	buff[2]  =    DEV_ADDR;   //��ַ
	buff[3]  =    FC_data;      //����

	//����
	for(i = 0; i < Len; i++)
	{	    	    
	    buff[i+4]  =  send_data[i]; 		
	}

	BCC_DATA = 	createBCC(Len);	   //ΪҪ���͵����ݲ���BCC����ת��2���ֽڵ��ַ���BCC1��BCC2
	
	//BCCת��
	BCC1_DATA = Hex_TurnTO_ASC((BCC_DATA&0xF0)>>4);

	buff[Len + 4] = BCC1_DATA;

	BCC2_DATA = Hex_TurnTO_ASC(BCC_DATA&0x0F);
	buff[Len + 5] = BCC2_DATA;
	buff[Len + 6] = Fram_End;	   //���ݽ�����
}
 		*/
/************  ��������  
�������Ϊ��DATA���ݵĳ���
żУ�顣
����λ��ͨ��ʹ��
 ****************/	  /*

void send_command(ubyte send_buff[], ubyte Len)
{
	ubyte i, data_send;

	//��������
	if(Len > 19)
	{
	    Len = 19;
	}
	
	for(i = 0; i < (Len + 7); i++)
	{
		Enable_Txd();
		
		//Delay18b20(400); //485оƬ�ķ��ͽ����л���Ҫ��ʱ��
		
		data_send = send_buff[i];
		
		ACC = data_send;
		
		TB8 = P;				//żУ�顣����TB8��
		SBUF = ACC;

		//�ȴ������ж�,����Ӳ����λ
		while(0 == TI);
	}
}
	 */



/************  ��������  
�������Ϊ��DATA���ݵĳ���
żУ�顣
�������ͨ��ʹ��
 ****************/
 /*
void send_command_1(ubyte send_buff[], ubyte Len)
{
	ubyte i, data_send;

	//����üĴ�������ҳ��
	_push_(SYSCON0);               // push the current RMAP
	SET_RMAP();                    // sets RMAP

	//��������
	if(Len > 9)
	{
		Len = 9;
	}
	
	for(i = 0; i < (Len + 7); i++)
	{	    
		data_send = send_buff[i];
		
		ACC = data_send;
		
		TB8_1 = P;				//żУ�顣����TB8��
		
		UART1_SBUF = ACC;
		
		while(0 == TI_1);
	}

	//�˳��üĴ�������ҳ��
	RESET_RMAP();                  // resets RMAP
        _pop_(SYSCON0);                // restore the old RMAP
}
	*/