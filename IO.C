//****************************************************************************
// @Module        GPIO
// @Filename      IO.C
// @Project       161018.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC878CM-16FF
//
// @Compiler      Keil
//
// @Codegenerator 2.2
//
// @Description:  This file contains functions that use the IO module.
//
//----------------------------------------------------------------------------
// @Date          2016-11-23 15:47:20
//
//****************************************************************************

// USER CODE BEGIN (IO_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (IO_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (IO_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (IO_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (IO_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (IO_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (IO_General,9)

// USER CODE END


//****************************************************************************
// @Function      void IO_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the IO function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
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

// USER CODE BEGIN (IO_Init,1)

// USER CODE END

void IO_vInit(void)
{
  // USER CODE BEGIN (IO_Init,2)

  // USER CODE END


  ///  ***********************************************************************
  ///  Note : All peripheral related IO configurations are done in the 
  ///  respective peripheral modules (alternate functions selection)
  ///  
  ///  If no pins are selected DAvE assumes that registers are in default 
  ///  settings
  ///  ***********************************************************************

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P0:
  ///  -----------------------------------------------------------------------
  ///  P0.3:
  ///  - is used as general input
  ///  - pull-up device is assigned
  ///  P0.4:
  ///  - is used as general input
  ///  - pull-up device is assigned
  ///  P0.6:
  ///  - is used as general input
  ///  - pull-up device is assigned
  ///  P0.7:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned

  SFR_PAGE(_pp3, noSST);         // switch to page 3
  P0_DS         =  0x7F;         // load drive strength register
  SFR_PAGE(_pp1, noSST);         // switch to page 1
  P0_PUDEN      =  0xDC;         // load pullup/pulldown enable register

  SFR_PAGE(_pp0, noSST);         // switch to page 0
  P0_DIR        =  0x80;         // load direction register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P1:
  ///  -----------------------------------------------------------------------
  ///  P1.2:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned
  ///  P1.4:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned
  ///  P1.5:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned
  ///  P1.6:
  ///  - is used as alternate input for the MCAN Node 0 Receiver Input
  ///  - pull-up device is assigned
  ///  P1.7:
  ///  - is used as alternate output for the MCAN Node 0 Transmitter Output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - pull-up device is assigned

  SFR_PAGE(_pp3, noSST);         // switch to page 3
  P1_DS         =  0x4B;         // load drive strength register

  SFR_PAGE(_pp0, noSST);         // switch to page 0
  P1_DIR        =  0x34;         // load direction register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P3:
  ///  -----------------------------------------------------------------------
  ///  P3.0:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is high level
  ///  - pull device is disabled (tristate) 
  ///  P3.1:
  ///  - is used as alternate output for the UART1 Transmit Output
  ///  - push/pull output is selected
  ///  - Strong drive strength is selected for output driver
  ///  - pull device is disabled (tristate) 
  ///  P3.2:
  ///  - is used as alternate input for the UART1 Receive Input
  ///  - pull device is disabled (tristate) 
  ///  P3.4:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned
  ///  P3.5:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned
  ///  P3.7:
  ///  - is used as general input
  ///  - pull-up device is assigned

  SFR_PAGE(_pp3, noSST);         // switch to page 3
  P3_DS         =  0xCE;         // load drive strength register
  SFR_PAGE(_pp1, noSST);         // switch to page 1
  P3_PUDEN      =  0xB0;         // load pullup/pulldown enable register

  SFR_PAGE(_pp0, noSST);         // switch to page 0
  P3_DIR        =  0x31;         // load direction register
  P3_DATA       =  0x01;         // load data output register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P4:
  ///  -----------------------------------------------------------------------
  ///  P4.0:
  ///  - is used as general input
  ///  - pull-up device is assigned
  ///  P4.1:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned
  ///  P4.2:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned
  ///  P4.3:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned
  ///  P4.4:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned
  ///  P4.5:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned
  ///  P4.6:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned
  ///  P4.7:
  ///  - is used as general purpose output
  ///  - push/pull output is selected
  ///  - Weak drive strength is selected for output driver
  ///  - the pin status is low level
  ///  - pull-up device is assigned

  SFR_PAGE(_pp3, noSST);         // switch to page 3
  P4_DS         =  0x01;         // load drive strength register
  SFR_PAGE(_pp1, noSST);         // switch to page 1
  P4_PUDEN      =  0xFF;         // load pullup/pulldown enable register

  SFR_PAGE(_pp0, noSST);         // switch to page 0
  P4_DIR        =  0xFE;         // load direction register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P5:
  ///  -----------------------------------------------------------------------
  ///  - no pin of port P5 is used

  SFR_PAGE(_pp3, noSST);         // switch to page 3
  P5_DS         =  0xFF;         // load drive strength register

  SFR_PAGE(_pp0, noSST);         // switch to page 0

  // USER CODE BEGIN (IO_Init,3)

  // USER CODE END

} //  End of function IO_vInit




// USER CODE BEGIN (IO_General,10)

// USER CODE END

