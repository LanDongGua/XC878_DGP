//****************************************************************************
// @Module        UART1 (Serial Interface)
// @Filename      UART1.C
// @Project       161018.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC878CM-16FF
//
// @Compiler      Keil
//
// @Codegenerator 2.2
//
// @Description:  This file contains functions that use the UART1 module.
//
//----------------------------------------------------------------------------
// @Date          2016-11-23 15:47:21
//
//****************************************************************************

// USER CODE BEGIN (UART1_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (UART1_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (UART1_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (UART1_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (UART1_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (UART1_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (UART1_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (UART1_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (UART1_General,9)

// USER CODE END


//****************************************************************************
// @Function      void UART1_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the UART1 function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
//                
//                The following SFR fields will be initialized:
//                - register SCON
//                - bits SMOD and EX2
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

// USER CODE BEGIN (UART1_Init,1)

// USER CODE END

void UART1_vInit(void)
{
  // USER CODE BEGIN (UART1_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  UART1 settings
  ///  -----------------------------------------------------------------------
  ///  Pin TXD1_1 (P3.1) is selected for transmission
  ///  Pin RXD1_1 (P3.2) is selected for reception
  ///  Receiver enabled
  ///  UART1 interrupt is enabled
  ///  UART1 Transmit interrupt is enabled
  ///  UART1 Receive interrupt is enabled
  ///  Ignore Normal divider overflow interrupt
  ///  Mode 3: 9-bit data, 1 start bit, 1 stop bit, variable baud rate
  ///  BRG is selected for baudrate generation


  SFR_PAGE(_pp2, noSST);         // switch to page 2 without saving
  P3_ALTSEL0   |=  (ubyte)0x02;  // configure alternate function register 0
  P3_ALTSEL1   |=  (ubyte)0x02;  // configure alternate function register 1
  SFR_PAGE(_pp0, noSST);         // switch to page 0 without saving
  P3_DIR       |=  (ubyte)0x02;  // set output direction


  SFR_PAGE(_su3, noSST);         // switch to page 3 without saving
  MODPISEL1    |=  (ubyte)0x08;  // configure peripheral input select register
  SFR_PAGE(_su0, noSST);         // switch to page 0 without saving


  SET_RMAP();                   

  UART1_BCON    =  0x00;         // reset baudrate timer/reload register
  UART1_SCON    =  0xD0;         // load serial channel control register

  ///  -----------------------------------------------------------------------
  ///  Baudrate generator settings
  ///  -----------------------------------------------------------------------
  ///  input clock = fPCLK
  ///  Fractional divider is disabled
  ///  baudrate = 19.2308 kbaud

  UART1_BG      =  0x4D;         // load baudrate timer/reload register
  UART1_BCON   |=  0x01;         // load baud rate control register


  RESET_RMAP();                 


  // USER CODE BEGIN (UART1_Init,3)

  // USER CODE END

  ///  UART1 Interrupt enable bit is set in SHINT_vInit() function

} //  End of function UART1_vInit


// USER CODE BEGIN (UART1_General,10)

// USER CODE END

