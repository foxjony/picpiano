#ifndef _CONST_H
#define _CONST_H



//------------------------------------------------------------------------------
#if     defined(_16F887) || defined(_16F886)
//------------------------------------------------------------------------------

    __CONFIG(HS & WDTDIS & PWRTEN & MCLRDIS & LVPDIS & UNPROTECT & BORDIS & IESODIS & FCMDIS & DEBUGDIS);

//------------------------------------------------------------------------------
#elif   defined(_16F690)
//------------------------------------------------------------------------------

    __CONFIG (HS & WDTDIS & PWRTEN & MCLRDIS & UNPROTECT & BORDIS & IESODIS & FCMDIS);

//------------------------------------------------------------------------------
#elif   defined(_16F88)
//------------------------------------------------------------------------------

    __CONFIG (HS & WDTDIS & PWRTEN & MCLRDIS & LVPDIS & UNPROTECT & BORDIS & DEBUGDIS & CCPRB3);
    __CONFIG (FCMDIS & IESODIS);

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

//******************************************************************************
//  
//      Constants
// 
//******************************************************************************

#define MAX_CHANNELS    8       // How many sound channels we use

#define KBD_ROWS        6       // Number of keyboard control lines (digital)
#define KBD_COLUMNS     6       // Number of keyboard columns (analog inputs)

#define KBD_KEYS        (KBD_ROWS * KBD_COLUMNS)    // Number of keys
#define KBD_SIZE        ((KBD_KEYS + 7) >> 3)       // Size of array to store keyboard state

#define ms              / 10    // Constant to simplify delay values



//******************************************************************************
// 
//      Data types
// 
//******************************************************************************

typedef struct          // Type for analog input (see array COLUMNS below)
{                       // 
    char  cADCChannel;  // Analog channel
    char *pPort;        // Pointer to PORT register
    char *pTris;        // Pointer to TRIS register
    char  cMask;        // Bit mask for PORT and TRIS
} TColumn;

//------------------------------------------------------------------------------

typedef struct          // Type for digital control output (see array ROWS below)
{                       // 
    char *pPort;        // Pointer to PORT register
    char  cMask;        // Bit mask for PORT
} TRow;


//------------------------------------------------------------------------------

typedef struct          // Type for sound control variables
{
    unsigned int F;     // Frequency
    unsigned int f;     // Phase
    unsigned char key;  // Played key
} TSound;



//******************************************************************************
//  
//      I/O PORTS
// 
//******************************************************************************



//------------------------------------------------------------------------------
#if     defined(_16F886)
//------------------------------------------------------------------------------

    #define PORTA_CONST     0x00
    #define TRISA_CONST     0x00
    
    #define PORTB_CONST     0x00
    #define TRISB_CONST     0x00

    #define PORTC_CONST     0x00
    #define TRISC_CONST     0x00

    #define PORTE_CONST     0x00
    #define TRISE_CONST     0x08

    #define pin_BUTTON      RE3

    #define ANSEL_CONST     0x00
    #define ANSELH_CONST    0x1F

    #define CCP_bit1        DC1B1
    #define CCP_bit0        DC1B0

    const TColumn  COLUMNS[KBD_COLUMNS] = 
    {
        {  13,  (char*)&PORTB, (char*)&TRISB, 1 << 5},
        {  11,  (char*)&PORTB, (char*)&TRISB, 1 << 4},
        {   9,  (char*)&PORTB, (char*)&TRISB, 1 << 3},
        {   8,  (char*)&PORTB, (char*)&TRISB, 1 << 2},
        {  10,  (char*)&PORTB, (char*)&TRISB, 1 << 1},
        {  12,  (char*)&PORTB, (char*)&TRISB, 1 << 0}
    };

    const TRow     ROWS[KBD_ROWS] = 
    {
        {   (char*)&PORTA,  1 << 0  },
        {   (char*)&PORTA,  1 << 1  },
        {   (char*)&PORTA,  1 << 2  },
        {   (char*)&PORTA,  1 << 3  },
        {   (char*)&PORTA,  1 << 5  },
        {   (char*)&PORTC,  1 << 0  },
    };

//------------------------------------------------------------------------------
#elif   defined(_16F887)
//------------------------------------------------------------------------------

    #define PORTA_CONST     0x00
    #define TRISA_CONST     0x00
    
    #define PORTB_CONST     0x00
    #define TRISB_CONST     0x01

    #define PORTC_CONST     0x00
    #define TRISC_CONST     0x00

    #define PORTD_CONST     0x00
    #define TRISD_CONST     0x00

    #define PORTE_CONST     0x00
    #define TRISE_CONST     0x00

    #define pin_BUTTON      RB0

    #define ANSEL_CONST     0x7E
    #define ANSELH_CONST    0x00

    #define CCP_bit1        DC1B1
    #define CCP_bit0        DC1B0

    const TColumn  COLUMNS[KBD_COLUMNS] = 
    {
        {   1,  (char*)&PORTA, (char*)&TRISA, 1 << 1},  // pin 20
        {   2,  (char*)&PORTA, (char*)&TRISA, 1 << 2},  // pin 21
        {   3,  (char*)&PORTA, (char*)&TRISA, 1 << 3},  // pin 22
        {   4,  (char*)&PORTA, (char*)&TRISA, 1 << 5},  // pin 24
        {   5,  (char*)&PORTE, (char*)&TRISE, 1 << 0},  // pin 25
        {   6,  (char*)&PORTE, (char*)&TRISE, 1 << 1}   // pin 26
    };

    const TRow     ROWS[KBD_ROWS] = 
    {
        {   (char*)&PORTD,  1 << 0  },  // pin 38
        {   (char*)&PORTD,  1 << 1  },  // pin 39
        {   (char*)&PORTD,  1 << 2  },  // pin 40
        {   (char*)&PORTD,  1 << 3  },  // pin 41
        {   (char*)&PORTD,  1 << 4  },  // pin 2
        {   (char*)&PORTD,  1 << 5  },  // pin 3
    };

//------------------------------------------------------------------------------
#elif     defined(_16F690)
//------------------------------------------------------------------------------

    #define PORTA_CONST     0x00
    #define TRISA_CONST     0x08
    
    #define PORTB_CONST     0x00
    #define TRISB_CONST     0x00

    #define PORTC_CONST     0x00
    #define TRISC_CONST     0x00

    #define pin_BUTTON      RA3

    #define ANSEL_CONST     0x74
    #define ANSELH_CONST    0x0C

    #define CCP_bit1        DC1B1
    #define CCP_bit0        DC1B0

    const TColumn  COLUMNS[KBD_COLUMNS] = 
    {
        {   2,  (char*)&PORTA, (char*)&TRISA, 1 << 2},  // pin 17
        {   4,  (char*)&PORTC, (char*)&TRISC, 1 << 0},  // pin 16
        {   5,  (char*)&PORTC, (char*)&TRISC, 1 << 1},  // pin 15
        {   6,  (char*)&PORTC, (char*)&TRISC, 1 << 2},  // pin 14
        {  10,  (char*)&PORTB, (char*)&TRISB, 1 << 4},  // pin 13
        {  11,  (char*)&PORTB, (char*)&TRISB, 1 << 5}   // pin 12
    };

    const TRow     ROWS[KBD_ROWS] = 
    {
        {   (char*)&PORTB,  1 << 6  },    // pin 11
        {   (char*)&PORTC,  1 << 4  },    // pin 6 
        {   (char*)&PORTC,  1 << 3  },    // pin 7
        {   (char*)&PORTC,  1 << 6  },    // pin 8
        {   (char*)&PORTC,  1 << 7  },    // pin 9
        {   (char*)&PORTB,  1 << 7  },    // pin 10
    };

//------------------------------------------------------------------------------
#elif   defined(_16F88)
//------------------------------------------------------------------------------

    #define PORTA_CONST     0x00
    #define TRISA_CONST     0x20
    
    #define PORTB_CONST     0x00
    #define TRISB_CONST     0x00
    
    #define pin_BUTTON      RA5

    #define T0IF    TMR0IF
    #define T0IE    TMR0IE

    #define ANSEL_CONST     0x5F

    #define CCP_bit1        CCP1X
    #define CCP_bit0        CCP1Y

    const TColumn  COLUMNS[KBD_COLUMNS] = 
    {
        {   6,  (char*)&PORTB, (char*)&TRISB, 1 << 7},  // pin 13
        {   0,  (char*)&PORTA, (char*)&TRISA, 1 << 0},  // pin 17
        {   1,  (char*)&PORTA, (char*)&TRISA, 1 << 1},  // pin 18
        {   2,  (char*)&PORTA, (char*)&TRISA, 1 << 2},  // pin 1
        {   3,  (char*)&PORTA, (char*)&TRISA, 1 << 3},  // pin 2
        {   4,  (char*)&PORTA, (char*)&TRISA, 1 << 4}   // pin 3
    };

    const TRow     ROWS[KBD_ROWS] = 
    {
        {   (char*)&PORTB,  1 << 0  },  // pin 6
        {   (char*)&PORTB,  1 << 1  },  // pin 7
        {   (char*)&PORTB,  1 << 2  },  // pin 8
        {   (char*)&PORTB,  1 << 4  },  // pin 10
        {   (char*)&PORTB,  1 << 5  },  // pin 11
        {   (char*)&PORTB,  1 << 6  },  // pin 12
    };

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------










#endif


