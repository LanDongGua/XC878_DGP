//****************************************************************************
// @Module        Watch Dog Timer
// @Filename      WDT.C
// @Project       161018.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC878CM-16FF
//
// @Compiler      Keil
//
// @Codegenerator 2.2
//
// @Description:  This file contains functions that use the WDT module.
//
//----------------------------------------------------------------------------
// @Date          2016-11-23 15:47:21
//
//****************************************************************************

// USER CODE BEGIN (WDT_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (WDT_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (WDT_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (WDT_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (WDT_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (WDT_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (WDT_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (WDT_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (WDT_General,9)

// USER CODE END


//****************************************************************************
// @Function      void WDT_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the 'Watch Dog 
//                Timer' function library. It is assumed that the SFRs used 
//                by this library are in their reset state. 
//                
//                The watchdog timer is used.
//                The following SFR fields will be initialized:
//                WDTREL - WDT reload value
//                WDTIN  - WDT input frequency selection
//                Then the watchdog timer will be refreshed.
//                Note: The user has to take care that RMAP bit in SYSCON0 is 
//                to be set while using the registers of Watch dog timer.
//                Registers are WDTCON,WDTWINB,WDTREL,WDTH,WDTL
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

// USER CODE BEGIN (WDT_Init,1)

// USER CODE END

void WDT_vInit(void)
{
  // USER CODE BEGIN (WDT_Init,2)

  // USER CODE END

  ///  the watchdog timer is used and it is enabled in INIT function,user has 
  ///  to take care of WDT refresh
  ///  the RMAP bit of SYSCON0 is set
  ///  the input frequency is fSYS/128
  ///  the watchdog timer reload value is 0x24
  ///  the watchdog timeout period is 300 ms

  SFR_PAGE(_su1, noSST);         // switch to page1 without saving

  MAIN_vUnlockProtecReg();       // open access to protected register
  SFR_PAGE(_su0, noSST);         // switch to page0 with out saving

  SET_RMAP(); 
  WDTREL = 0x24;      //Watch dog timer reload register
  WDTCON |= 0x04;     //   set   WDTEN
  WDTCON |= 0x03;                // set WDTRS,set WDTIN
  RESET_RMAP(); 
  SFR_PAGE(_su1, noSST);         // switch to page1 without saving

  MAIN_vlockProtecReg();         // close access to protected register
  SFR_PAGE(_su0, noSST);         // switch to page0 with out saving

  // USER CODE BEGIN (WDT_Init,3)

  // USER CODE END



} //  End of function WDT_vInit


// USER CODE BEGIN (WDT_General,10)

// USER CODE END

