//****************************************************************************
// @Module        MultiCAN Controller 
// @Filename      CAN.H
// @Project       161018.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC878CM-16FF
//
// @Compiler      Keil
//
// @Codegenerator 2.2
//
// @Description:  This file contains all function prototypes and macros for 
//                the CAN module.
//
//----------------------------------------------------------------------------
// @Date          2016-11-23 15:47:21
//
//****************************************************************************

// USER CODE BEGIN (CAN_Header,1)

// USER CODE END



#ifndef _CAN_H_
#define _CAN_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (CAN_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CAN_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (CAN_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************


//****************************************************************************
// @Declaration of SFRs
//****************************************************************************


#define CAN_LIST0        0x0040 
#define CAN_LIST1        0x0041 
#define CAN_LIST2        0x0042 
#define CAN_LIST3        0x0043 
#define CAN_LIST4        0x0044 
#define CAN_LIST5        0x0045 
#define CAN_LIST6        0x0046 
#define CAN_LIST7        0x0047 
#define CAN_MCR        0x0072 
#define CAN_MITR        0x0073 
#define CAN_MOAMR0        0x0403 
#define CAN_MOAMR1        0x040b 
#define CAN_MOAMR10        0x0453 
#define CAN_MOAMR11        0x045B 
#define CAN_MOAMR12        0x0463 
#define CAN_MOAMR13        0x046B 
#define CAN_MOAMR14        0x0473 
#define CAN_MOAMR15        0x047B 
#define CAN_MOAMR16        0x0483 
#define CAN_MOAMR17        0x048B 
#define CAN_MOAMR18        0x0493 
#define CAN_MOAMR19        0x049B 
#define CAN_MOAMR2        0x0413 
#define CAN_MOAMR20        0x04A3 
#define CAN_MOAMR21        0x04AB 
#define CAN_MOAMR22        0x04B3 
#define CAN_MOAMR23        0x04BB 
#define CAN_MOAMR24        0x04C3 
#define CAN_MOAMR25        0x04CB 
#define CAN_MOAMR26        0x04D3 
#define CAN_MOAMR27        0x04DB 
#define CAN_MOAMR28        0x04E3 
#define CAN_MOAMR29        0x04EB 
#define CAN_MOAMR3        0x041B 
#define CAN_MOAMR30        0x04F3 
#define CAN_MOAMR31        0x04FB 
#define CAN_MOAMR4        0x0423 
#define CAN_MOAMR5        0x042B 
#define CAN_MOAMR6        0x0433 
#define CAN_MOAMR7        0x043B 
#define CAN_MOAMR8        0x0443 
#define CAN_MOAMR9        0x044B 
#define CAN_MOAR0        0x0406 
#define CAN_MOAR1        0x040e 
#define CAN_MOAR10        0x0456 
#define CAN_MOAR11        0x045E 
#define CAN_MOAR12        0x0466 
#define CAN_MOAR13        0x046E 
#define CAN_MOAR14        0x0476 
#define CAN_MOAR15        0x047E 
#define CAN_MOAR16        0x0486 
#define CAN_MOAR17        0x048E 
#define CAN_MOAR18        0x0496 
#define CAN_MOAR19        0x049E 
#define CAN_MOAR2        0x0416 
#define CAN_MOAR20        0x04A6 
#define CAN_MOAR21        0x04AE 
#define CAN_MOAR22        0x04B6 
#define CAN_MOAR23        0x04BE 
#define CAN_MOAR24        0x04C6 
#define CAN_MOAR25        0x04CE 
#define CAN_MOAR26        0x04D6 
#define CAN_MOAR27        0x04DE 
#define CAN_MOAR28        0x04E6 
#define CAN_MOAR29        0x04EE 
#define CAN_MOAR3        0x041E 
#define CAN_MOAR30        0x04F6 
#define CAN_MOAR31        0x04FE 
#define CAN_MOAR4        0x0426 
#define CAN_MOAR5        0x042E 
#define CAN_MOAR6        0x0436 
#define CAN_MOAR7        0x043E 
#define CAN_MOAR8        0x0446 
#define CAN_MOAR9        0x044E 
#define CAN_MOCTR0        0x0407 
#define CAN_MOCTR1        0x040f 
#define CAN_MOCTR10        0x0457 
#define CAN_MOCTR11        0x045F 
#define CAN_MOCTR12        0x0467 
#define CAN_MOCTR13        0x046F 
#define CAN_MOCTR14        0x0477 
#define CAN_MOCTR15        0x047F 
#define CAN_MOCTR16        0x0487 
#define CAN_MOCTR17        0x048F 
#define CAN_MOCTR18        0x0497 
#define CAN_MOCTR19        0x049F 
#define CAN_MOCTR2        0x0417 
#define CAN_MOCTR20        0x04A7 
#define CAN_MOCTR21        0x04AF 
#define CAN_MOCTR22        0x04B7 
#define CAN_MOCTR23        0x04BF 
#define CAN_MOCTR24        0x04C7 
#define CAN_MOCTR25        0x04CF 
#define CAN_MOCTR26        0x04D7 
#define CAN_MOCTR27        0x04DF 
#define CAN_MOCTR28        0x04E7 
#define CAN_MOCTR29        0x04EF 
#define CAN_MOCTR3        0x041F 
#define CAN_MOCTR30        0x04F7 
#define CAN_MOCTR31        0x04FF 
#define CAN_MOCTR4        0x0427 
#define CAN_MOCTR5        0x042F 
#define CAN_MOCTR6        0x0437 
#define CAN_MOCTR7        0x043F 
#define CAN_MOCTR8        0x0447 
#define CAN_MOCTR9        0x044F 
#define CAN_MODATAH0        0x0405 
#define CAN_MODATAH1        0x040d 
#define CAN_MODATAH10        0x0455 
#define CAN_MODATAH11        0x045D 
#define CAN_MODATAH12        0x0465 
#define CAN_MODATAH13        0x046D 
#define CAN_MODATAH14        0x0475 
#define CAN_MODATAH15        0x047D 
#define CAN_MODATAH16        0x0485 
#define CAN_MODATAH17        0x048D 
#define CAN_MODATAH18        0x0495 
#define CAN_MODATAH19        0x049D 
#define CAN_MODATAH2        0x0415 
#define CAN_MODATAH20        0x04A5 
#define CAN_MODATAH21        0x04AD 
#define CAN_MODATAH22        0x04B5 
#define CAN_MODATAH23        0x04BD 
#define CAN_MODATAH24        0x04C5 
#define CAN_MODATAH25        0x04CD 
#define CAN_MODATAH26        0x04D5 
#define CAN_MODATAH27        0x04DD 
#define CAN_MODATAH28        0x04E5 
#define CAN_MODATAH29        0x04ED 
#define CAN_MODATAH3        0x041D 
#define CAN_MODATAH30        0x04F5 
#define CAN_MODATAH31        0x04FD 
#define CAN_MODATAH4        0x0425 
#define CAN_MODATAH5        0x042D 
#define CAN_MODATAH6        0x0435 
#define CAN_MODATAH7        0x043D 
#define CAN_MODATAH8        0x0445 
#define CAN_MODATAH9        0x044D 
#define CAN_MODATAL0        0x0404 
#define CAN_MODATAL1        0x040c 
#define CAN_MODATAL10        0x0454 
#define CAN_MODATAL11        0x045C 
#define CAN_MODATAL12        0x0464 
#define CAN_MODATAL13        0x046C 
#define CAN_MODATAL14        0x0474 
#define CAN_MODATAL15        0x047C 
#define CAN_MODATAL16        0x0484 
#define CAN_MODATAL17        0x048C 
#define CAN_MODATAL18        0x0494 
#define CAN_MODATAL19        0x049C 
#define CAN_MODATAL2        0x0414 
#define CAN_MODATAL20        0x04A4 
#define CAN_MODATAL21        0x04AC 
#define CAN_MODATAL22        0x04B4 
#define CAN_MODATAL23        0x04BC 
#define CAN_MODATAL24        0x04C4 
#define CAN_MODATAL25        0x04CC 
#define CAN_MODATAL26        0x04D4 
#define CAN_MODATAL27        0x04DC 
#define CAN_MODATAL28        0x04E4 
#define CAN_MODATAL29        0x04EC 
#define CAN_MODATAL3        0x041C 
#define CAN_MODATAL30        0x04F4 
#define CAN_MODATAL31        0x04FC 
#define CAN_MODATAL4        0x0424 
#define CAN_MODATAL5        0x042C 
#define CAN_MODATAL6        0x0434 
#define CAN_MODATAL7        0x043C 
#define CAN_MODATAL8        0x0444 
#define CAN_MODATAL9        0x044C 
#define CAN_MOFCR0        0x0400 
#define CAN_MOFCR1        0x0408 
#define CAN_MOFCR10        0x0450 
#define CAN_MOFCR11        0x0458 
#define CAN_MOFCR12        0x0460 
#define CAN_MOFCR13        0x0468 
#define CAN_MOFCR14        0x0470 
#define CAN_MOFCR15        0x0478 
#define CAN_MOFCR16        0x0480 
#define CAN_MOFCR17        0x0488 
#define CAN_MOFCR18        0x0490 
#define CAN_MOFCR19        0x0498 
#define CAN_MOFCR2        0x0410 
#define CAN_MOFCR20        0x04A0 
#define CAN_MOFCR21        0x04A8 
#define CAN_MOFCR22        0x04B0 
#define CAN_MOFCR23        0x04B8 
#define CAN_MOFCR24        0x04C0 
#define CAN_MOFCR25        0x04C8 
#define CAN_MOFCR26        0x04D0 
#define CAN_MOFCR27        0x04D8 
#define CAN_MOFCR28        0x04E0 
#define CAN_MOFCR29        0x04E8 
#define CAN_MOFCR3        0x0418 
#define CAN_MOFCR30        0x04F0 
#define CAN_MOFCR31        0x04F8 
#define CAN_MOFCR4        0x0420 
#define CAN_MOFCR5        0x0428 
#define CAN_MOFCR6        0x0430 
#define CAN_MOFCR7        0x0438 
#define CAN_MOFCR8        0x0440 
#define CAN_MOFCR9        0x0448 
#define CAN_MOFGPR0        0x0401 
#define CAN_MOFGPR1        0x0409 
#define CAN_MOFGPR10        0x0451 
#define CAN_MOFGPR11        0x0459 
#define CAN_MOFGPR12        0x0461 
#define CAN_MOFGPR13        0x0469 
#define CAN_MOFGPR14        0x0471 
#define CAN_MOFGPR15        0x0479 
#define CAN_MOFGPR16        0x0481 
#define CAN_MOFGPR17        0x0489 
#define CAN_MOFGPR18        0x0491 
#define CAN_MOFGPR19        0x0499 
#define CAN_MOFGPR2        0x0411 
#define CAN_MOFGPR20        0x04A1 
#define CAN_MOFGPR21        0x04A9 
#define CAN_MOFGPR22        0x04B1 
#define CAN_MOFGPR23        0x04B9 
#define CAN_MOFGPR24        0x04C1 
#define CAN_MOFGPR25        0x04C9 
#define CAN_MOFGPR26        0x04D1 
#define CAN_MOFGPR27        0x04D9 
#define CAN_MOFGPR28        0x04E1 
#define CAN_MOFGPR29        0x04E9 
#define CAN_MOFGPR3        0x0419 
#define CAN_MOFGPR30        0x04F1 
#define CAN_MOFGPR31        0x04F9 
#define CAN_MOFGPR4        0x0421 
#define CAN_MOFGPR5        0x0429 
#define CAN_MOFGPR6        0x0431 
#define CAN_MOFGPR7        0x0439 
#define CAN_MOFGPR8        0x0441 
#define CAN_MOFGPR9        0x0449 
#define CAN_MOIPR0        0x0402 
#define CAN_MOIPR1        0x040a 
#define CAN_MOIPR10        0x0452 
#define CAN_MOIPR11        0x045A 
#define CAN_MOIPR12        0x0462 
#define CAN_MOIPR13        0x046A 
#define CAN_MOIPR14        0x0472 
#define CAN_MOIPR15        0x047A 
#define CAN_MOIPR16        0x0482 
#define CAN_MOIPR17        0x048A 
#define CAN_MOIPR18        0x0492 
#define CAN_MOIPR19        0x049A 
#define CAN_MOIPR2        0x0412 
#define CAN_MOIPR20        0x04A2 
#define CAN_MOIPR21        0x04AA 
#define CAN_MOIPR22        0x04B2 
#define CAN_MOIPR23        0x04BA 
#define CAN_MOIPR24        0x04C2 
#define CAN_MOIPR25        0x04CA 
#define CAN_MOIPR26        0x04D2 
#define CAN_MOIPR27        0x04DA 
#define CAN_MOIPR28        0x04E2 
#define CAN_MOIPR29        0x04EA 
#define CAN_MOIPR3        0x041a 
#define CAN_MOIPR30        0x04F2 
#define CAN_MOIPR31        0x04FA 
#define CAN_MOIPR4        0x0422 
#define CAN_MOIPR5        0x042a 
#define CAN_MOIPR6        0x0432 
#define CAN_MOIPR7        0x043A 
#define CAN_MOIPR8        0x0442 
#define CAN_MOIPR9        0x044A 
#define CAN_MSID0        0x0050 
#define CAN_MSID1        0x0051 
#define CAN_MSIMASK        0x0070 
#define CAN_MSPND0        0x0048 
#define CAN_MSPND1        0x0049 
#define CAN_NBTR0        0x0084 
#define CAN_NBTR1        0x00C4 
#define CAN_NCR0        0x0080 
#define CAN_NCR1        0x00C0 
#define CAN_NECNT0        0x0085 
#define CAN_NECNT1        0x00C5 
#define CAN_NFCR0        0x0086 
#define CAN_NFCR1        0x00C6 
#define CAN_NIPR0        0x0082 
#define CAN_NIPR1        0x00C2 
#define CAN_NPCR0        0x0083 
#define CAN_NPCR1        0x00C3 
#define CAN_NSR0        0x0081 
#define CAN_NSR1        0x00C1 
#define CAN_PANCTR        0x0071 
 
 
 //------------------------------------------------------------
 //-- CAN Message Object x ------------------------------------
 //------------------------------------------------------------
 //------------------------------------------------------------
 // Note: DAvE Ignores Lower Address Lines A[1:0]
 //
 // MO = Message Ojbect; n = 31-0
 // MO base = 400H + n * 20H
 //
 //  Message Object 0 Address Map...
 //   __________
 //  |MOCTRn    |  -> 0x0407
 //  |----------|
 //  |MOARn     |  -> 0x0406
 //  |----------|
 //  |MODATAHn  |  -> 0x0405
 //  |----------|
 //  |MODATALn  |  -> 0x0404
 //  |----------|
 //  |MOAMRn    |  -> 0x0403
 //  |----------|
 //  |MOOIPRn   |  -> 0x0402
 //  |----------|
 //  |MOFGPRn   |  -> 0x0401
 //  |----------|
 //  |MOFCRn    |  -> 0x0400
 //  |__________|
 //
 //------------------------------------------------------------
 //------------------------------------------------------------
 //-- CAN Message Object x ------------------------------------
 //------------------------------------------------------------
 #define MO_BASE 0x0400
 
 //------------------------------------------------------------
 //-- CAN Message Object 0-31 ------------------------------------
 //------------------------------------------------------------
 
 // Message Object Nr Function Control Register
 #define CAN_MOFCR(Nr) (MO_BASE + (Nr * 8))
 
 // Message Object Nr FIFO/Gateway Pointer Register
 #define CAN_MOFGPR(Nr) (MO_BASE + 01 + (Nr * 8))
 
 // Message Object Nr Interrupt Pointer Register
 #define CAN_MOIPR(Nr) (MO_BASE + 02 + (Nr * 8))
 
 // Message Object Nr Acceptance Mask Register
 #define CAN_MOAMR(Nr) (MO_BASE + 03 + (Nr * 8))
 
 // Message Object Nr Data Register Low
 #define CAN_MODATAL(Nr) (MO_BASE + 04 + (Nr * 8))
 
 // Message Object Nr Data Register High
 #define CAN_MODATAH(Nr) (MO_BASE + 05 + (Nr * 8))
 
 // Message Object Nr Arbitration Register
 #define CAN_MOAR(Nr) (MO_BASE + 06 + (Nr * 8))
 
 // Message Object Nr Control Register
 #define CAN_MOCTR(Nr) (MO_BASE + 07 + (Nr * 8))

 //------------------------------------------------------------
 //-- CAN Node Registers 0-1 ----------------------------------
 //------------------------------------------------------------
 
 // Node x Error Counter Register
 #define CAN_NECNT(Nr) (CAN_NECNT0 + (Nr * 0x40))

 //****************************************************************************
 // @Defines
 //****************************************************************************

 // Panel Busy Flag
#define CAN_PANCTR_BUSY          0x01

// Message Object Status Register
#define MOSTAT_RXPND     0x01
#define MOSTAT_TXPND     0x02
#define MOSTAT_NEWDAT    0x08
#define MOSTAT_MSGLST    0x10
#define MOSTAT_RST_MNR   0x19
                  
 // MultiCAN Access Mediator Registers

 // ADCON Read is enabled
#define ADCON_R 0x00

 // ADCON Write is enabled
#define ADCON_W 0x01

 // Data Transmission Busy
#define CAN_ADCON_BSY 0x02

 // Auto increment the current address(+1)
#define ADR_INC 0x04

 // Auto increment the current address(+8)
#define ADR_INC8 0x0C

 // Auto decrement the current address(-1)
#define ADR_DEC 0x08

 // CAN Data 0 Valid
#define D0_VALID 0x10

 // CAN Data 1 Valid
#define D1_VALID 0x20

 // CAN Data 2 Valid
#define D2_VALID 0x40

 // CAN Data 3 Valid
#define D3_VALID 0x80

 // CAN Data 0-3 Valid
#define ALL_DATA_VALID 0xF0


 ///  -------------------------------------------------------------------------
 ///  @Definition of a union for the CAN data structure
 ///  -------------------------------------------------------------------------

 // The following data type used for converting 32-bit data to Four 8-bit data types
 // and vica-versa. This is used for accessing MultiCAN Kernel to Access Mediator
 // Registers. The data type has the following fields:
 //
 //       31       24  23       16  15       8  7         0
 //      |------------------------------------------------|
 //      |      DB0   |     DB1    |    DB2   |    DB3    |
 //      |------------------------------------------------|
 //      |                                                |
 //      | <------------------ ulVal -------------------> |
 //

typedef union ulValue {
    ulong ulVal;        // 32-bit Data Type
    ubyte ubDB[4];      // Four 8-bit Data Type
} un_32bit;


 // The following data type used for converting 16-bit data to Two 8-bit data types
 // and vica-versa. The data type has the following fields:
 //
 //       15       8 7          0
 //      |----------------------|
 //      |    DB0   |    DB1    |
 //      |----------------------|
 //      |                      |
 //      | <----- uwVal ------> |
 //

typedef union uwValue {
    uword uwVal;        // 16-bit Data Type
    ubyte ubDB[2];      // Two 8-bit Data Type
} un_16bit;

 ///  -------------------------------------------------------------------------
 ///  @Definition of a structure for the CAN data
 ///  -------------------------------------------------------------------------

 // The following data type serves as a software message object. Each access to
 // a hardware message object has to be made by forward a pointer to a software
 // message object (MCAN_SWObj). The data type has the following fields:
 //
 // ubMOdlc:
 // this byte has the same structure as the message configuration register of a
 // MOFCRn message object. It contains the ' Data Lenght Code (DLC)'
 //
 //         7     6     5      4    3     2     1     0
 //      |------------------------------------------------|
 //      |           0            |         DLC           |
 //      |------------------------------------------------|
 //
 // ubMOcfg:
 // this byte contains the 'Extended Identifier (IDE)', the 'Message Direction (DIR)',
 // the 'Node Select (NODE)' And the 'Remote Monitoring Mode (RMM)'
 //
 //
 //         7     6     5      4    3     2     1     0
 //      |------------------------------------------------|
 //      |                       | DIR | XTD | NODE | RMM |
 //      |------------------------------------------------|
 //
 // ulID:
 // this field is four bytes long and contains either the 11-bit identifier
 // or the 29-bit identifier
 //
 // ulMask:
 // this field is four bytes long and contains either the 11-bit mask
 // or the 29-bit mask
 //
 // ulDATAL:
 // contains the lowest 4 bytes of message object
 //
 // ulDATAH:
 // contains the upper 4 bytes of message object
 //
 // uwCounter:
 // this field is two bytes long and contains the counter value
 //

typedef struct
{
     ubyte ubMOdlc;       // message object function control register[31-24]
     ubyte ubMOcfg;       // message object configuration
     un_32bit ulID;       // standard (11-bit)/extended (29-bit) identifier
     un_32bit ulMask;     // standard (11-bit)/extended (29-bit) mask
     un_32bit ulDATAL;    // 32-bit data Lower bytes
     un_32bit ulDATAH;    // 32-bit data Higher bytes
     un_16bit uwCounter;  // frame counter(MOIPRn[31-16]
}stCAN_SWObj;


// USER CODE BEGIN (CAN_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void CAN_vInit(void);
void CAN_vTransmit(ubyte ubObjNr);
void CAN_vWriteAMData(ulong ulValue);
void CAN_vSetListCommand(ulong ulVal);


// USER CODE BEGIN (CAN_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         CAN_vReadEN() 
//
//----------------------------------------------------------------------------
// @Description   This macro enables Read mode (CAN Address/Data Control 
//                Register).
//                
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

#define CAN_vReadEN() CAN_ADCON = 0x00; while(CAN_ADCON & CAN_ADCON_BSY)

//****************************************************************************
// @Macro         CAN_vWriteEN(ubyte ubDCtrl) 
//
//----------------------------------------------------------------------------
// @Description   This macro enables Write mode (CAN Address/Data Control 
//                Register).
//                
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubDCtrl: 
//                Data Control Flags
//
//----------------------------------------------------------------------------
// @Date          2016-11-23
//
//****************************************************************************

#define CAN_vWriteEN(ubDCtrl) CAN_ADCON = ((ubDCtrl) | ADCON_W); while(CAN_ADCON & CAN_ADCON_BSY)

//****************************************************************************
// @Macro         CAN_vWriteCANAddress(uword uwAdr) 
//
//----------------------------------------------------------------------------
// @Description   This macro writes 16-bit CAN address to CAN Address 
//                Register Low and High respectively. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    uwAdr: 
//                16-bit Address
//
//----------------------------------------------------------------------------
// @Date          2016-11-23
//
//****************************************************************************

#define CAN_vWriteCANAddress(uwAdr) CAN_ADLH = uwAdr

//****************************************************************************
// @Macro         CAN_vWriteCANData(ulong ulValue) 
//
//----------------------------------------------------------------------------
// @Description   This macro writes 32-bit Data to CAN Data Register's 
//                0-3respectively. 
//                Note:
//                Write Process :
//                ->Write the address of the MultiCAN kernel register to the 
//                CAN_ADL and CAN_ADH registers.
//                use macro : CAN_vWriteCANAddress. 
//                ->Write the data to the 
//                CAN_DATA0/CAN_DATA1/CAN_DATA2/CAN_DATA3 registers.
//                ->Write the register CAN_ADCON, including setting the valid 
//                bit of the data registers and setting register bit RWEN to 
//                1.
//                ->The valid data will be written to the MultiCAN kernel 
//                only once. Register bit BSY will become 1.
//                ->When Register bit BSY becomes 0, the transmission is 
//                finished.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ulValue: 
//                32-bit Data
//
//----------------------------------------------------------------------------
// @Date          2016-11-23
//
//****************************************************************************

#define CAN_vWriteCANData(ulValue) CAN_DATA01 = (ulValue & 0xFFFF); \
   CAN_DATA23 = (ulValue >> 16) & 0xFFFF; \
   CAN_vWriteEN(ALL_DATA_VALID)

//****************************************************************************
// @Macro         CAN_pushAMRegs/_popAMRegs() 
//
//----------------------------------------------------------------------------
// @Description   The macro CAN_pushAMRegs() PUSH the CAN Access Mediator 
//                Registers.
//                The macro CAN_popAMRegs() POP the CAN Access Mediator 
//                Registers.
//                Note:
//                This macro is used in CAN ISR/Function's to protect Access 
//                Mediator Register
//                MultiCAN Access Mediator Registers:
//                    ADL, ADH, DATA0, DATA1, DATA2, DATA3. 
//                
//                The _push_/_pop_ routine inserts a PUSH/POP instruction 
//                into the program saving the contents of the Special 
//                Function Register(sfr) on the Stack.
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

#define CAN_pushAMRegs() while(CAN_ADCON & CAN_ADCON_BSY); \
        _push_(CAN_ADL);   _push_(CAN_ADH); \
        _push_(CAN_DATA0); _push_(CAN_DATA1); \
        _push_(CAN_DATA2); _push_(CAN_DATA3)

#define CAN_popAMRegs() _pop_(CAN_DATA3); _pop_(CAN_DATA2); \
        _pop_(CAN_DATA1); _pop_(CAN_DATA0); \
        _pop_(CAN_ADH);   _pop_(CAN_ADL)

//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

//   Shared interrupt vector definitions are defined in SHARED_INT.H


// USER CODE BEGIN (CAN_Header,9)

// USER CODE END


#endif  // ifndef _CAN_H_
