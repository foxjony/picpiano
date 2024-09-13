#include <pic.h>
#include <osa.h>


#include <const.h>



//******************************************************************************
//  
//      Global variables
// 
//******************************************************************************

bank1   signed char Sample[64];         // Sample data

        TSound      S[MAX_CHANNELS];    // Sound control variables


bank1   OST_MSG_CB  msg_KBD;            // Message control block for data exchange
                                        // between Task_Keyboard and Task_Sound

//******************************************************************************
//  
//      Function prototypes
// 
//******************************************************************************

void Init (void);
void Task_Button (void);
void Task_Keyboard (void);
void Task_Sound (void);


#include "freqs.c"          // Frequency constants
#include "sinus.c"          // Several different samples
#include "interrupt.c"      // Interrupt code: sinthesizer
#include "button.c"         // Sample switch button
#include "keyboard.c"       // Sensor keyboard reading
#include "sound.c"          // Sound control variables forming


//******************************************************************************
//  
//      MAIN
// 
//******************************************************************************


void main (void)
{
    //------------------------------------------------------------------------------
    //  Init PIC periphery
    //------------------------------------------------------------------------------
    
    Init();

    //------------------------------------------------------------------------------
    //  OSA initialisation
    //------------------------------------------------------------------------------
    
    OS_Init();

    //------------------------------------------------------------------------------
    //  Create all task with identical priority
    //------------------------------------------------------------------------------
    
    OS_Task_Create(0, Task_Sound);
    OS_Task_Create(0, Task_Button);
    OS_Task_Create(0, Task_Keyboard);

    //------------------------------------------------------------------------------
    //  Enable interrupts and run system
    //------------------------------------------------------------------------------
    
    OS_EI();
    OS_Run();
}











/********************************************************************************
 *                                                                              *
 *  Function:       Init                                                        *
 *                                                                              *
 *------------------------------------------------------------------------------* 
 * 
 *  description:    Init PIC periphery:
 *                  - I/O PORTS
 *                  - ADC
 *                  - timers
 *                  - interrupts
 *
 *  parameters:     void
 *
 *  on return:      void
 *
 ********************************************************************************/

void Init (void)
{
    //------------------------------------------------------------------------------
    //  I/O ports configuration
    //------------------------------------------------------------------------------

    PORTA = PORTA_CONST;
    PORTB = PORTB_CONST;

    TRISA = TRISA_CONST;
    TRISB = TRISB_CONST;

    #if defined(PORTC_CONST)
        PORTC = PORTC_CONST;
        TRISC = TRISC_CONST;
    #endif


    #if defined(PORTD_CONST)
        PORTD = PORTD_CONST;
        TRISD = TRISD_CONST;
    #endif

    #if defined(PORTE_CONST)
        PORTE = PORTE_CONST;
        TRISE = TRISE_CONST;
    #endif

    //------------------------------------------------------------------------------
    //  ADC module
    //------------------------------------------------------------------------------

    ADCON0 = 0;
    ADCON1 = 0;

    #if defined(_16F88) || defined(_16F690)
    ADCS2 = 0;
    #endif
    ADCS1 = 1;
    ADCS0 = 1;
    ADFM  = 0;                      // Left justify

    ANSEL  = ANSEL_CONST;

    #if defined(ANSELH_CONST)
    ANSELH = ANSELH_CONST;   
    #endif

    ADON = 1;                       // ADC ON = 1

    //------------------------------------------------------------------------------
    //  Init timers and PWM mode
    //------------------------------------------------------------------------------
    
    OPTION = 0x80;

    T2CON = 0x1C;       // prs = 1; post = 4. TMR2IF period = TMR2 period * 4 = 400 us
    PR2 = 64-1;         // TMR2 period = (PR2+1) * prs * post * Tcyc = 64 * 1 * 4 * 0.2 = 50 us
                        // PWM freq = 1 / ((PR2+1) * prs * Tcyc) = 78 KHz

    CCP1CON = 0x0C;     // PWM-mode
    CCPR1L = 0;

    //------------------------------------------------------------------------------
    //  Configure interrupts
    //------------------------------------------------------------------------------
    
    INTCON = 0;
    PEIE = 1;
    TMR2IE = 1;

}


//******************************************************************************
// 
//      THE END
// 
//******************************************************************************

