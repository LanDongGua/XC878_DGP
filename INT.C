//****************************************************************************
// @Module        Interrupt Unit
// @Filename      INT.C
// @Project       161018.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC878CM-16FF
//
// @Compiler      Keil
//
// @Codegenerator 2.2
//
// @Description:  This file contains functions that use the IR module.
//
//----------------------------------------------------------------------------
// @Date          2016-11-23 15:47:20
//
//****************************************************************************

// USER CODE BEGIN (IR_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (IR_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (IR_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (IR_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (IR_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (IR_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (IR_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (IR_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (IR_General,9)

// USER CODE END


//****************************************************************************
// @Function      void INT_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the IR function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
//                
//                The project settings regarding the external interrupts are 
//                taken over into the corresponding special function 
//                registers IENx (interrupt enabling), TCON and EXICONx 
//                (trigger selection)(x=0 or 1). The global enable Bit EA is 
//                not changed. The initialization of the interrupt priorities 
//                is located in function MAIN_vInit.
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

// USER CODE BEGIN (IR_Init,1)

// USER CODE END

void INT_vInit(void)
{
  // USER CODE BEGIN (IR_Init,2)

  // USER CODE END

  //   ------ Port initialization for Interrupt module-----
  ///  External interrupt 0 Not used.
  ///  External interrupt 1 Not used.
  ///  External interrupt 2 Not used.
  ///  External interrupt 3 Not used.
  ///  External interrupt 4 Not used.
  ///  External interrupt 5 Not used.
  ///  External interrupt 6 Not used.

  //   ---------- Non Maskable Interrupt configuration ----------
  ///   NMIWDT disabled
  ///   NMIPLL disabled
  ///   NMIVDDP disabled
  ///   NMIECC disabled

  NMICON        =  0x00;         //  NMI Control Register 

  ///  External interrupt 0 disabled.

  ///  External interrupt 1 disabled.

  ///  External interrupt 2 disabled.

  ///  External interrupt 3 disabled.

  ///  External interrupt 4 disabled.

  ///  External interrupt 5 disabled.

  ///  External interrupt 6 disabled.


  IEN0         |=  0x02;         //  interrupt enable  register 0

  IEN1         |=  0x00;         //  interrupt enable register 1


  // USER CODE BEGIN (IR_Init,3)

  // USER CODE END

} //  End of function INT_vInit


// USER CODE BEGIN (IR_General,10)

// USER CODE END

