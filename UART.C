//****************************************************************************
// @Module        UART (Serial Interface)
// @Filename      UART.C
// @Project       141209_for_can.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC878CM-16FF
//
// @Compiler      Keil
//
// @Codegenerator 2.2
//
// @Description:  This file contains functions that use the UART module.
//
//----------------------------------------------------------------------------
// @Date          2014-12-10 13:59:28
//
//****************************************************************************

// USER CODE BEGIN (UART_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (UART_General,2)
//ubyte    CRC;



// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (UART_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (UART_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (UART_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (UART_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (UART_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (UART_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (UART_General,9)

// USER CODE END


//****************************************************************************
// @Function      void UART_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the UART function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
//                
//                The following SFR fields will be initialized:
//                - register SCON
//                - bits SMOD and ES
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2014-12-10
//
//****************************************************************************

// USER CODE BEGIN (UART_Init,1)

// USER CODE END

void UART_vInit(void)
{
  // USER CODE BEGIN (UART_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  UART settings
  ///  -----------------------------------------------------------------------
  ///  Pin TXD_0 (P1.1) is selected for transmission
  ///  Pin RXD_0 (P1.0) is selected for reception
  ///  Receiver enabled
  ///  Mode 3: 9-bit data, 1 start bit, 1 stop bit, variable baud rate
  ///  BRG is selected for baudrate generation

  SFR_PAGE(_pp2, noSST);         // switch to page 2 without saving
  P1_ALTSEL0   &= ~(ubyte)0x02;  // configure alternate function register 0
  P1_ALTSEL1   |=  (ubyte)0x02;  // configure alternate function register 1
  SFR_PAGE(_pp0, noSST);         // switch to page 0 without saving
  P1_DIR       |=  (ubyte)0x02;  // set output direction


  MODPISEL     &= ~(ubyte)0x01;  // configure peripheral input select register
  BCON          =  0x00;         // reset baudrate timer/reload register
  SCON          =  0xD0;         // load serial channel control register

  ///  -----------------------------------------------------------------------
  ///  Baudrate generator settings
  ///  -----------------------------------------------------------------------
  ///  input clock = fPCLK
  ///  Fractional divider is disabled
  ///  baudrate = 38.4615 kbaud

  BG            =  0x26;         // load baudrate timer/reload register
  BCON         |=  0x01;         // load baud rate control register


  // USER CODE BEGIN (UART_Init,3)

  // USER CODE END

  ///  UART interrupt enabled
  ES = 1;

} //  End of function UART_vInit


//****************************************************************************
// @Function      void UART_viIsr(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the service routine for the UART interrupt. It is 
//                called after each transmission (flag TI set) or reception 
//                (flag RI set) of a data unit.
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2014-12-10
//
//****************************************************************************

//   You have two choices for interrupt type select in Project Settings Page 
//   under Global Settings Section.
//   If you select CHOICE 1 then ISR will be generated with push and pop.
//   If you select CHOICE 2 then ISR will be generated without push and pop.
//   Default choice is CHOICE 2.
//   Current selection is CHOICE 2 

// USER CODE BEGIN (UART_Isr,1)

// USER CODE END

void UART_viIsr(void) interrupt UARTINT
{

    // USER CODE BEGIN (UART_Isr,2)

    // USER CODE END
  SFR_PAGE(_su0, SST1);          // switch to page 0
  if (TI)
  {
    // USER CODE BEGIN (UART_Isr,3)

       TI = 0;

    // USER CODE END
  }
  if (RI)
  {
    // USER CODE BEGIN (UART_Isr,4)

       RI = 0;
	   /***********************
             if((SBUF ==  0xED)&&(0 == byte_count))
			 对串口数据进行判断，如果是为报头，并且，数据计数器为0.则，接收报头正确
			 置位，报头开始标记符 FRAME_start。


            ************************/

			if((SBUF ==  Fram_Head)&&(0 == byte_count)) //判断帧头，并标记帧开始。
		   {		      
			   FRAME_start = 1;		       
		   }


		   /***********************
             if(FRAME_start&&(SBUF ==  0xED)&&(0 != byte_count))
			 对串口数据进行判断，如果报头标记符已经置位，说明已经收到过报头。
			 这里再次出现报头，并且数据计数器不为0.说明之前的通信错误。
			 默认为接收到本次报头为真正的报头。置位报头标记符FRAME_start
			 并对数据计数器	byte_count，清零。
			 

            ************************/
	
		   if(FRAME_start&&(SBUF ==  Fram_Head)&&(0 != byte_count)) //判断帧头，并标记帧开始。
		   {
			   FRAME_start = 1;
			   byte_count  =0;		       
		   }


		   /***********************
             if(FRAME_start)
			 对接收到报头后的数据进行处理，并存储到buff【】里。并对每个数据进行判断报尾。
			 接收到报尾后，置位报尾标记符 FRAME_end。说明一帧数据完整接收到。
			 并对数据接收使能位	Receive_Enable，清零。不在允许在报文处理完之前的串口数据进入buff【】

            ************************/
	
	
	
		   if(FRAME_start)
		   {		       
			   if(byte_count < 26)
			   {
				   buff[byte_count]	  	   =    SBUF;			   
				   if(Fram_End == buff[byte_count])	//判断帧尾，并标记帧结束。
				   {
				       FRAME_end = 1;
					   FRAME_start = 0;  
				   }
				   byte_count++;
			   }
			   else
			   {
			       clear_communicate_flag();
			   }		       		      			   		      
		   }

    // USER CODE END
  }

    // USER CODE BEGIN (UART_Isr,5)

    // USER CODE END
  SFR_PAGE(_su0, RST1);          // restore the old page
} //  End of function UART_viIsr


// USER CODE BEGIN (UART_General,10)

// USER CODE END

