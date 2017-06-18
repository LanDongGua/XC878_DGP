#include "MAIN.H" 


/****  十六0-9，A-F。转ASC码   ********/

ubyte Hex_TurnTO_ASC(ubyte hex_data)
{
    ubyte ASC_data;

	if(9 >= hex_data)								//小于等于9属于数字字符
	{
	    ASC_data = (hex_data + 0x30);
	}
	else if((hex_data > 9)&&(hex_data <= 0x0F)) 
	{
	    ASC_data = (hex_data + 0x37);			  //大于九是字母字符。这里只对半个字节的数据做转换。
	}
	else
	{
	    ASC_data = 0x30;	    
	}
	
	return ASC_data;
}

/****  ASC码0-9，A-F。转十六进制   ********/

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

/***************检查BCC是否正确，Len是DADA的长度*****************************/
/*
bool check_BCC(ubyte Len)
{
       ubyte check_BCC_data,  BCC1, BCC2, BCC;

	//过长保护
	if(byte_count < 7)
	{
	    return 0;
	}
	
	BCC1    =    ASC_TurnTO_Hex(buff[byte_count-3]);   //提取出BCC1，2并转成16进制数据，合并车BCC
	BCC2    =    ASC_TurnTO_Hex(buff[byte_count-2]);
	BCC     =	 (BCC1<<4)|BCC2;

	//BCC 
	check_BCC_data    =    createBCC(Len);	  //按数据生成BCC码。

	if(BCC    ==    check_BCC_data)		//生成的BCC码和接受到的BCC码一致，返回1.
	{
	    return 1;
	}
	else
	{
	    return 0;
	}
}
	  */

/***************检查BCC是否正确，Len是DADA的长度*****************************/
 
bool check_BCC_1(ubyte Len)
{
       ubyte check_BCC_data,  BCC1, BCC2, BCC;
	   
	//过长保护
	if(byte_count_1 < 7)
	{
	    return 0;
	}
	
	BCC1    =    ASC_TurnTO_Hex(send_data[byte_count_1-3]);   //提取出BCC1，2并转成16进制数据，合并车BCC
	BCC2    =    ASC_TurnTO_Hex(send_data[byte_count_1-2]);
	BCC     =	 (BCC1<<4)|BCC2;
	check_BCC_data    =    createBCC_1(Len);	  //按数据生成BCC码。

	if(BCC    ==    check_BCC_data)		//生成的BCC码和接受到的BCC码一致，返回1.
	{
	    return 1;
	}
	else
	{
	    return 0;
	}
} 

/**********   获取BCC码  
输入参数为：DATA数据的长度
上位机通信使用
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
	
	for(i = 1; i < (Len + 4); i++)	  //DATA的长度加上前面的4个字节，头，类型，地址，FC类型。
	{
	    BCC_data    ^=    buff[i];	    	    
	}

	return BCC_data;
}		 

  */


/**********   获取BCC码  
输入参数为：DATA数据的长度
读卡器使用
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
	
	for(i = 1; i < (Len + 4); i++)	  //DATA的长度加上前面的4个字节，头，类型，地址，FC类型。
	{
	    BCC_data    ^=    send_data[i];	    	    
	}

	return BCC_data;
}


/****   组装发送包 ***********
输入参数为：命令类型，DATA数据所在的数组，DATA数据的长度
与上位机通信使用
 *********/		 /*
void send_Frame_data(ubyte FC_data, ubyte send_data[], ubyte Len)
{
	ubyte i,BCC_DATA,  BCC1_DATA,  BCC2_DATA;
	  
	//过长保护
	if(Len > 19)
	{
	    Len = 19;
	}
	
       buff[0]  =    Fram_Head;    //包头
	buff[1]  =    DEV_TYPE;     //类型
	buff[2]  =    DEV_ADDR;   //地址
	buff[3]  =    FC_data;      //命令

	//内容
	for(i = 0; i < Len; i++)
	{	    	    
	    buff[i+4]  =  send_data[i]; 		
	}

	BCC_DATA = 	createBCC(Len);	   //为要发送的数据产生BCC吗，再转成2个字节的字符型BCC1，BCC2
	
	//BCC转换
	BCC1_DATA = Hex_TurnTO_ASC((BCC_DATA&0xF0)>>4);

	buff[Len + 4] = BCC1_DATA;

	BCC2_DATA = Hex_TurnTO_ASC(BCC_DATA&0x0F);
	buff[Len + 5] = BCC2_DATA;
	buff[Len + 6] = Fram_End;	   //数据结束符
}
 		*/
/************  发送命令  
输入参数为：DATA数据的长度
偶校验。
与上位机通信使用
 ****************/	  /*

void send_command(ubyte send_buff[], ubyte Len)
{
	ubyte i, data_send;

	//过长保护
	if(Len > 19)
	{
	    Len = 19;
	}
	
	for(i = 0; i < (Len + 7); i++)
	{
		Enable_Txd();
		
		//Delay18b20(400); //485芯片的发送接收切换需要延时。
		
		data_send = send_buff[i];
		
		ACC = data_send;
		
		TB8 = P;				//偶校验。发送TB8；
		SBUF = ACC;

		//等待发送中断,发完硬件置位
		while(0 == TI);
	}
}
	 */



/************  发送命令  
输入参数为：DATA数据的长度
偶校验。
与读卡器通信使用
 ****************/
 /*
void send_command_1(ubyte send_buff[], ubyte Len)
{
	ubyte i, data_send;

	//进入该寄存器配置页码
	_push_(SYSCON0);               // push the current RMAP
	SET_RMAP();                    // sets RMAP

	//过长保护
	if(Len > 9)
	{
		Len = 9;
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
	*/