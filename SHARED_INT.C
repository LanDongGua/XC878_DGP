//****************************************************************************
// @Module        Shared Interrupt Routines
// @Filename      SHARED_INT.C
// @Project       161018.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC878CM-16FF
//
// @Compiler      Keil
//
// @Codegenerator 2.2
//
// @Description   This file contains the Shared interrupt routines.
//
//----------------------------------------------------------------------------
// @Date          2016-11-23 15:47:20
//
//****************************************************************************

// USER CODE BEGIN (SHARED_INT_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "SHARED_INT.H"

// USER CODE BEGIN (SHARED_INT_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (SHARED_INT_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (SHARED_INT_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (SHARED_INT_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (SHARED_INT_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (SHARED_INT_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************


// USER CODE BEGIN (SHARED_INT_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (SHARED_INT_General,9)

// USER CODE END


//****************************************************************************
// @Function      void SHINT_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes the shared interrupts. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2016-11-23
//
//****************************************************************************

// USER CODE BEGIN (SHINT_Init,1)

// USER CODE END

void SHINT_vInit(void)
{
  // USER CODE BEGIN (SHINT_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the Shared  Interrupts:
  ///  -----------------------------------------------------------------------
  ///  - MultiCAN Node 0 Interrupt is Selected


  IEN0         |=  0x20;         // load interrupt enable register 0

  ///  - MultiCAN Node 1 Interrupt is Selected
  ///  - UART1 Interrupt is Selected


  IEN1         |=  0x05;         // load interrupt enable register 1


  // USER CODE BEGIN (SHINT_Init,3)

  // USER CODE END


} //  End of function SHINT_vInit


//****************************************************************************
// @Function      void SHINT_viXINTR5Isr(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the service routine for the shared interrupt node 
//                XINTR5. XINTR5 ISR Node is shared by Timer 2, UART 
//                Fractional Divider(BRG Interrupt),MultiCAN Node 0 and LIN. 
//                Depending on the selected module interrupt it is called.
//                T2 - Depending on the selected operating mode it is called 
//                when TF2 is set by an overflow or underflow of the timer 2 
//                register or when EXF2 is set by a negative transition on 
//                T2EX.
//                UART - It is called after the BRG timer overflows and sets 
//                the NDOV bit.
//                CAN -  It is called for the  Service Request Node 0 of the 
//                MultiCAN module.
//                Note: Comments related to MultiCAN module are only 
//                applicable to their availability
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   none
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2016-11-23
//
//****************************************************************************

//   You have two choices for interrupt type select in Project Settings Page 
//   under Global Settings Section.
//   If you select CHOICE 1 then ISR will be generated with push and pop.
//   If you select CHOICE 2 then ISR will be generated without push and pop.
//   Default choice is CHOICE 2.
//   Current selection is CHOICE 2 

// USER CODE BEGIN (SHINT_XINTR5Isr,1)

// USER CODE END

void SHINT_viXINTR5Isr(void) interrupt XINTR5INT
{


ubyte ubTempMsgID = 0;
ubyte ubTempVarObjHandler = 0;
un_32bit ulBit_Pos_Mask;

  // USER CODE BEGIN (SHINT_XINTR5Isr,2)

  // USER CODE END


  CAN_pushAMRegs();              // push the CAN Access Mediator Registers

  SFR_PAGE(_su0, SST2);          // switch to page 0

  //   MultiCAN Node 0 (SRN0) interrupt handling section...


  //   Check Interrupt Request Register 2 Interrupt Flag 0
  if (((IRCON2 & 0x01) != 0))
  {

    IRCON2 &= ~(ubyte)0x01; //   clear CANSRC0

    //   ---------------------------------------------------------------------
    //   Interrupts of CAN Msg Obj x 
    //   ---------------------------------------------------------------------

    CAN_vWriteCANAddress(CAN_MSIMASK);    // set message index mask register
    CAN_DATA0   =   0x01;        // set message index mask register
    CAN_DATA1   =   0x00;        // set message index mask register
    CAN_DATA2   =   0x00;        // set message index mask register
    CAN_DATA3   =   0x00;        // set message index mask register

    CAN_vWriteEN(ALL_DATA_VALID); // Write mode Enabled

    // USER CODE BEGIN (SRN0,1)

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

          ///  Note: Below commented code could be copied by the user to user 
          ///  defined section for Interrupt handling.

          ///  Handling of MO TXPND for transmit data/remote frames (Generic 
          ///  Code).
          ///  (ubTempVarObjHandle & MOSTAT_TXPND)

          // if( ubTempVarObjHandler & MOSTAT_TXPND)   // if TXPND is set
          // {
          //// The transmission of the last message object was successful.
          //// reset TXPND, NEWDAT
          //    CAN_vWriteCANAddress(CAN_MOCTR(ubTempMsgID)); // Addressing CAN_MOCTRn
          //
          //    CAN_DATA0 = (MOSTAT_TXPND + MOSTAT_NEWDAT); // load CAN Data Register 0
          //    CAN_DATA1 = 0x00; // load CAN Data Register 1
          //    CAN_DATA2 = 0x00; // load CAN Data Register 2
          //    CAN_DATA3 = 0x00; // load CAN Data Register 3
          //    CAN_vWriteEN(ALL_DATA_VALID); // Writemode is Enabled
          //
          // }  // End of TXPNDn

      // USER CODE BEGIN (SRN0_OBJ,2)

	   if( ubTempVarObjHandler & MOSTAT_TXPND)   // if TXPND is set
           {
          // The transmission of the last message object was successful.
		   
		   b_CAN_tran_complete = 1;
		  
          // reset TXPND, NEWDAT
              CAN_vWriteCANAddress(CAN_MOCTR(ubTempMsgID)); // Addressing CAN_MOCTRn
          
              CAN_DATA0 = (MOSTAT_TXPND + MOSTAT_NEWDAT); // load CAN Data Register 0
              CAN_DATA1 = 0x00; // load CAN Data Register 1
              CAN_DATA2 = 0x00; // load CAN Data Register 2
              CAN_DATA3 = 0x00; // load CAN Data Register 3
              CAN_vWriteEN(ALL_DATA_VALID); // Writemode is Enabled
          
           }
      // USER CODE END

      CAN_vWriteCANAddress(CAN_MSIMASK);    // set message index mask register
      CAN_DATA0  =   0x01;       // set message index mask register
      CAN_DATA1  =   0x00;       // set message index mask register
      CAN_DATA2  =   0x00;       // set message index mask register
      CAN_DATA3  =   0x00;       // set message index mask register

      CAN_vWriteEN(ALL_DATA_VALID); // Write mode Enabled

      // USER CODE BEGIN (SRN0,5)

      // USER CODE END

      CAN_vWriteCANAddress(CAN_MSID0);   // message index register
      CAN_vReadEN();               // Read Mode is enabled
      ubTempMsgID = CAN_DATA0;

      }while (ubTempMsgID != 0x20); // end while

    }  // end if

    // USER CODE BEGIN (SHINT_XINTR5Isr,7)
	

    // USER CODE END

  }


  // USER CODE BEGIN (SHINT_XINTR5Isr,8)

  // USER CODE END

  SFR_PAGE(_su0, RST2);          // restore the old SCU page

  CAN_popAMRegs();               // restore the CAN Access Mediator Registers


} //  End of function SHINT_viXINTR5Isr


//****************************************************************************
// @Function      void SHINT_viXINTR6Isr(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the service routine for the shared interrupt node 
//                XINTR6. XINTR6 ISR Node is shared by ADC[1:0] and MultiCAN 
//                Nodes 1 & 2. Depending on the selected module interrupt it 
//                is called. 
//                ADC -  It is activated by different interrupt sources 
//                (Channel Interrupts or Event Interrupts).The user obtains 
//                the conversion result by calling the function 
//                ADC_uwGetResultDataX(0,1,2,3).
//                CAN - It is called for the  Service Request Node 1 and 2 of 
//                the MultiCAN module.
//                Note: Comments related to MultiCAN module are applicable to 
//                the Devices support MultiCAN
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   none
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2016-11-23
//
//****************************************************************************

//   You have two choices for interrupt type select in Project Settings Page 
//   under Global Settings Section.
//   If you select CHOICE 1 then ISR will be generated with push and pop.
//   If you select CHOICE 2 then ISR will be generated without push and pop.
//   Default choice is CHOICE 2.
//   Current selection is CHOICE 2 

// USER CODE BEGIN (SHINT_XINTR6Isr,1)

// USER CODE END

void SHINT_viXINTR6Isr(void) interrupt XINTR6INT
{



 

  CAN_pushAMRegs();              // push the CAN Access Mediator Registers

  SFR_PAGE(_su0, SST0);          // switch to page 0
  
  IRCON1 &= ~(ubyte)0x20;
  b_Communicate_Error = 1;


  SFR_PAGE(_su0, RST0);          // restore the old SCU page

  CAN_popAMRegs();               // restore the CAN Access Mediator Registers
} //  End of function SHINT_viXINTR6Isr


//****************************************************************************
// @Function      void SHINT_viXINTR8Isr(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the service routine for the shared interrupt node 
//                XINTR8. XINTR8 ISR Node is shared by External Interrupt 
//                2,Timer 21,CORDIC,UART1,UART1 Fractional Divider(BRG 
//                Interrupt), and MDU[1:0]. Depending on the selected module 
//                interrupt it is called. 
//                EXT2 - It is called for the External interrupt 2. 
//                T21 - Depending on the selected operating mode it is called 
//                when TF2 is set by an overflow or underflow of the timer 21 
//                register or when EXF2 is set by a negative transition on 
//                T2EX.
//                UART1 - It is called after the BRG timer overflows and sets 
//                the NDOV bit.
//                It is called after each transmission (flag TI_1 set) or 
//                reception (flag RI_1 set) of a data unit.
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   none
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2016-11-23
//
//****************************************************************************

//   You have two choices for interrupt type select in Project Settings Page 
//   under Global Settings Section.
//   If you select CHOICE 1 then ISR will be generated with push and pop.
//   If you select CHOICE 2 then ISR will be generated without push and pop.
//   Default choice is CHOICE 2.
//   Current selection is CHOICE 2 

// USER CODE BEGIN (SHINT_XINTR8Isr,1)

// USER CODE END

void SHINT_viXINTR8Isr(void) interrupt XINTR8INT
{

  // USER CODE BEGIN (SHINT_XINTR8Isr,2)

  // USER CODE END

  EA = 0;                        // disable global interrupt
  _push_(SYSCON0);               // push the current RMAP

  SET_RMAP();                    // sets RMAP

  //   UART1 transmit interrupt handling section...

  if (TI_1)
  {
    //   UART1 transmit interrupt has occured

    // USER CODE BEGIN (SHINT_XINTR8Isr,6)

         UART1_SCON   &= ~(ubyte)0x02;  // Clear transmit interrupt flag

    // USER CODE END
  }

  //   UART1 receive interrupt handling section...

  if (RI_1)
  {
    //   UART1 recieve interrupt has occured

    // USER CODE BEGIN (SHINT_XINTR8Isr,7)
	//	 ubyte i;
         UART1_SCON   &= ~(ubyte)0x01;  // Clear receive interrupt flag
	   if((UART1_SBUF ==  Fram_Head_1)&&(0 == byte_count_1))
	   {
	      
		   FRAME_start_1 = 1;
	       
	   }

	   if((UART1_SBUF ==  Fram_Head) && (0 == byte_count_rs485_lk))
	   {
	       FRAME_start_rs485_lk = 1;
	   	  
	   }

	   if(FRAME_start_1)
	   {	       
		   if(byte_count_1 < 16)
		   {
			   send_data[byte_count_1]	  	   =    UART1_SBUF;
			   
			   if(Fram_End_1 == send_data[byte_count_1])
			   {			       
					   FRAME_end_1   = 1;
					   FRAME_start_1 = 0;				   				  		   
			   }
			   byte_count_1++;
		   }
		   else
		   {
		       byte_count_1 = 0;
			   FRAME_start_1 = 0;
			   FRAME_end_1   = 0;
		   }
	       	       		   		      
	   }

	   if(FRAME_start_rs485_lk)
	   {	       
		   if(byte_count_rs485_lk < 25)
		   {
			   RS485_LK_buff[byte_count_rs485_lk]	  	   =    UART1_SBUF;
			   
			   if(Fram_End == RS485_LK_buff[byte_count_rs485_lk])
			   {			       
					   FRAME_end_rs485_lk   = 1;
					   FRAME_start_rs485_lk = 0;				   				  		   
			   }
			   byte_count_rs485_lk++;
			   ub_lcd_key_send_pc_number = byte_count_rs485_lk;
		   }
		   else
		   {
		       byte_count_rs485_lk = 0;
			   FRAME_start_rs485_lk = 0;
			   FRAME_end_rs485_lk   = 0;
		   }
	       	       		   		      
	   }
    // USER CODE END
  }

  // USER CODE BEGIN (SHINT_XINTR8Isr,9)

  // USER CODE END


  RESET_RMAP();                  // resets RMAP
  _pop_(SYSCON0);                // restore the old RMAP
  EA = 1;                        // enable global interrupt

} //  End of function SHINT_viXINTR8Isr


// USER CODE BEGIN (SHARED_INT_General,10)

// USER CODE END


