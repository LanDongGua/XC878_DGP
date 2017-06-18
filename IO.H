//****************************************************************************
// @Module        GPIO
// @Filename      IO.H
// @Project       161018.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC878CM-16FF
//
// @Compiler      Keil
//
// @Codegenerator 2.2
//
// @Description:  This file contains all function prototypes and macros for 
//                the IO module.
//
//----------------------------------------------------------------------------
// @Date          2016-11-23 15:47:20
//
//****************************************************************************

// USER CODE BEGIN (IO_Header,1)

// USER CODE END



#ifndef _IO_H_
#define _IO_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (IO_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (IO_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (IO_Header,4)

// USER CODE END

//   Port 0

sbit P0_0       = 0x80;    
sbit P0_1       = 0x81;    
sbit P0_2       = 0x82;    
sbit P0_3       = 0x83;    
sbit P0_4       = 0x84;    
sbit P0_5       = 0x85;    
sbit P0_6       = 0x86;    
sbit P0_7       = 0x87;    

//   Port 1

sbit P1_0       = 0x90;    
sbit P1_1       = 0x91;    
sbit P1_2       = 0x92;    
sbit P1_3       = 0x93;    
sbit P1_4       = 0x94;    
sbit P1_5       = 0x95;    
sbit P1_6       = 0x96;    
sbit P1_7       = 0x97;    

//   Port 3

sbit P3_0       = 0xB0;    
sbit P3_1       = 0xB1;    
sbit P3_2       = 0xB2;    
sbit P3_3       = 0xB3;    
sbit P3_4       = 0xB4;    
sbit P3_5       = 0xB5;    
sbit P3_6       = 0xB6;    
sbit P3_7       = 0xB7;    

//   Port 4

sbit P4_0       = 0xC8;    
sbit P4_1       = 0xC9;    
sbit P4_2       = 0xCA;    
sbit P4_3       = 0xCB;    
sbit P4_4       = 0xCC;    
sbit P4_5       = 0xCD;    
sbit P4_6       = 0xCE;    
sbit P4_7       = 0xCF;    

//   Port 5

//   This port is not bit-addressable.


//----------------------------------------------------------------------------
// Defines for the parameter PinName
//----------------------------------------------------------------------------

#define READ_P0_0  P0_0
#define READ_P0_1  P0_1
#define READ_P0_2  P0_2
#define READ_P0_3  P0_3
#define READ_P0_4  P0_4
#define READ_P0_5  P0_5
#define READ_P0_6  P0_6
#define READ_P0_7  P0_7


#define READ_P1_0  P1_0
#define READ_P1_1  P1_1
#define READ_P1_2  P1_2
#define READ_P1_3  P1_3
#define READ_P1_4  P1_4
#define READ_P1_5  P1_5
#define READ_P1_6  P1_6
#define READ_P1_7  P1_7




#define READ_P3_0  P3_0
#define READ_P3_1  P3_1
#define READ_P3_2  P3_2
#define READ_P3_3  P3_3
#define READ_P3_4  P3_4
#define READ_P3_5  P3_5
#define READ_P3_6  P3_6
#define READ_P3_7  P3_7


#define READ_P4_0  P4_0
#define READ_P4_1  P4_1
#define READ_P4_2  P4_2
#define READ_P4_3  P4_3
#define READ_P4_4  P4_4
#define READ_P4_5  P4_5
#define READ_P4_6  P4_6
#define READ_P4_7  P4_7



#define READ_P5_0  (bit)(P5_DATA & 0x01)
#define READ_P5_1  (bit)(P5_DATA & 0x02)
#define READ_P5_2  (bit)(P5_DATA & 0x04)
#define READ_P5_3  (bit)(P5_DATA & 0x08)
#define READ_P5_4  (bit)(P5_DATA & 0x10)
#define READ_P5_5  (bit)(P5_DATA & 0x20)
#define READ_P5_6  (bit)(P5_DATA & 0x40)
#define READ_P5_7  (bit)(P5_DATA & 0x80)


#define SET_P0_0  P0_0= 1
#define SET_P0_1  P0_1= 1
#define SET_P0_2  P0_2= 1
#define SET_P0_3  P0_3= 1
#define SET_P0_4  P0_4= 1
#define SET_P0_5  P0_5= 1
#define SET_P0_6  P0_6= 1
#define SET_P0_7  P0_7= 1


#define SET_P1_0  P1_0= 1
#define SET_P1_1  P1_1= 1
#define SET_P1_2  P1_2= 1
#define SET_P1_3  P1_3= 1
#define SET_P1_4  P1_4= 1
#define SET_P1_5  P1_5= 1
#define SET_P1_6  P1_6= 1
#define SET_P1_7  P1_7= 1




#define SET_P3_0  P3_0= 1
#define SET_P3_1  P3_1= 1
#define SET_P3_2  P3_2= 1
#define SET_P3_3  P3_3= 1
#define SET_P3_4  P3_4= 1
#define SET_P3_5  P3_5= 1
#define SET_P3_6  P3_6= 1
#define SET_P3_7  P3_7= 1


#define SET_P4_0  P4_0= 1
#define SET_P4_1  P4_1= 1
#define SET_P4_2  P4_2= 1
#define SET_P4_3  P4_3= 1
#define SET_P4_4  P4_4= 1
#define SET_P4_5  P4_5= 1
#define SET_P4_6  P4_6= 1
#define SET_P4_7  P4_7= 1



#define SET_P5_0  P5_DATA |=0x01
#define SET_P5_1  P5_DATA |=0x02
#define SET_P5_2  P5_DATA |=0x04
#define SET_P5_3  P5_DATA |=0x08
#define SET_P5_4  P5_DATA |=0x10
#define SET_P5_5  P5_DATA |=0x20
#define SET_P5_6  P5_DATA |=0x40
#define SET_P5_7  P5_DATA |=0x80


#define RESET_P0_0  P0_0 = 0
#define RESET_P0_1  P0_1 = 0
#define RESET_P0_2  P0_2 = 0
#define RESET_P0_3  P0_3 = 0
#define RESET_P0_4  P0_4 = 0
#define RESET_P0_5  P0_5 = 0
#define RESET_P0_6  P0_6 = 0
#define RESET_P0_7  P0_7 = 0


#define RESET_P1_0  P1_0 = 0
#define RESET_P1_1  P1_1 = 0
#define RESET_P1_2  P1_2 = 0
#define RESET_P1_3  P1_3 = 0
#define RESET_P1_4  P1_4 = 0
#define RESET_P1_5  P1_5 = 0
#define RESET_P1_6  P1_6 = 0
#define RESET_P1_7  P1_7 = 0




#define RESET_P3_0  P3_0 = 0
#define RESET_P3_1  P3_1 = 0
#define RESET_P3_2  P3_2 = 0
#define RESET_P3_3  P3_3 = 0
#define RESET_P3_4  P3_4 = 0
#define RESET_P3_5  P3_5 = 0
#define RESET_P3_6  P3_6 = 0
#define RESET_P3_7  P3_7 = 0


#define RESET_P4_0  P4_0 = 0
#define RESET_P4_1  P4_1 = 0
#define RESET_P4_2  P4_2 = 0
#define RESET_P4_3  P4_3 = 0
#define RESET_P4_4  P4_4 = 0
#define RESET_P4_5  P4_5 = 0
#define RESET_P4_6  P4_6 = 0
#define RESET_P4_7  P4_7 = 0



#define RESET_P5_0  P5_DATA &=~0x01
#define RESET_P5_1  P5_DATA &=~0x02
#define RESET_P5_2  P5_DATA &=~0x04
#define RESET_P5_3  P5_DATA &=~0x08
#define RESET_P5_4  P5_DATA &=~0x10
#define RESET_P5_5  P5_DATA &=~0x20
#define RESET_P5_6  P5_DATA &=~0x40
#define RESET_P5_7  P5_DATA &=~0x80


#define TOGGLE_P0_0  P0_0 ^= 1
#define TOGGLE_P0_1  P0_1 ^= 1
#define TOGGLE_P0_2  P0_2 ^= 1
#define TOGGLE_P0_3  P0_3 ^= 1
#define TOGGLE_P0_4  P0_4 ^= 1
#define TOGGLE_P0_5  P0_5 ^= 1
#define TOGGLE_P0_6  P0_6 ^= 1
#define TOGGLE_P0_7  P0_7 ^= 1


#define TOGGLE_P1_0  P1_0 ^= 1
#define TOGGLE_P1_1  P1_1 ^= 1
#define TOGGLE_P1_2  P1_2 ^= 1
#define TOGGLE_P1_3  P1_3 ^= 1
#define TOGGLE_P1_4  P1_4 ^= 1
#define TOGGLE_P1_5  P1_5 ^= 1
#define TOGGLE_P1_6  P1_6 ^= 1
#define TOGGLE_P1_7  P1_7 ^= 1




#define TOGGLE_P3_0  P3_0 ^= 1
#define TOGGLE_P3_1  P3_1 ^= 1
#define TOGGLE_P3_2  P3_2 ^= 1
#define TOGGLE_P3_3  P3_3 ^= 1
#define TOGGLE_P3_4  P3_4 ^= 1
#define TOGGLE_P3_5  P3_5 ^= 1
#define TOGGLE_P3_6  P3_6 ^= 1
#define TOGGLE_P3_7  P3_7 ^= 1


#define TOGGLE_P4_0  P4_0 ^= 1
#define TOGGLE_P4_1  P4_1 ^= 1
#define TOGGLE_P4_2  P4_2 ^= 1
#define TOGGLE_P4_3  P4_3 ^= 1
#define TOGGLE_P4_4  P4_4 ^= 1
#define TOGGLE_P4_5  P4_5 ^= 1
#define TOGGLE_P4_6  P4_6 ^= 1
#define TOGGLE_P4_7  P4_7 ^= 1



#define TOGGLE_P5_0  P5_DATA ^=0x01
#define TOGGLE_P5_1  P5_DATA ^=0x02
#define TOGGLE_P5_2  P5_DATA ^=0x04
#define TOGGLE_P5_3  P5_DATA ^=0x08
#define TOGGLE_P5_4  P5_DATA ^=0x10
#define TOGGLE_P5_5  P5_DATA ^=0x20
#define TOGGLE_P5_6  P5_DATA ^=0x40
#define TOGGLE_P5_7  P5_DATA ^=0x80


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (IO_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void IO_vInit(void);


// USER CODE BEGIN (IO_Header,8)

// USER CODE END


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

// USER CODE BEGIN (IO_Header,9)

// USER CODE END


#endif  // ifndef _IO_H_
