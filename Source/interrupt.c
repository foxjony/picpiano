// This macro forms summ of all channel's signals 

#define SOUND(x)                                        \
    if (S[x].key) {                                     \
        temp_dac += Sample[*((char*)&S[x].f+1) & 0x3F]; \
        *((char*)&S[x].f+1) += *((char*)&S[x].F+1);     \
        *((char*)&S[x].f+0) += *((char*)&S[x].F+0);     \
        if (CARRY) *((char*)&S[x].f+1) += 1;            \
    } 



/*******************************************************************************
 *   
 *     This interrupt occures every 51.2 us (f = 19.5 KHz)
 *   
 *******************************************************************************/

void interrupt isr (void)
{
    static  unsigned    char    prs;        // OS_Timer's prescalser
            signed      int     temp_dac;   // Summa of all signals
            unsigned    char    m_cDAC;     // Value of DAC
    

    TMR2IF = 0;
    temp_dac = 0;

    //------------------------------------------------------------------------------
    //  Forming DAC value
    //------------------------------------------------------------------------------
    
    SOUND(0);
    SOUND(1);
    SOUND(2);
    SOUND(3);
    SOUND(4);
    SOUND(5);
    SOUND(6);
    SOUND(7);

    temp_dac >>= 3;     // Divide by number of channels (8)

    m_cDAC  = *((char*)&temp_dac+0) + 0x80; 
    m_cDAC >>= 2;

    //------------------------------------------------------------------------------
    //  Out currect DAC value through PWM
    //------------------------------------------------------------------------------
    
    CCP_bit1 = 0;
    CCP_bit0 = 0;
    if (temp_dac & 2) CCP_bit1 = 1;
    if (temp_dac & 1) CCP_bit0 = 1 ;
    CCPR1L = m_cDAC;
    
    //------------------------------------------------------------------------------
    //  Call system timer once per 200 periods (interval = 10 ms)
    //------------------------------------------------------------------------------
    
    if (!--prs)
    {
        OS_Timer();     // System timer
        prs = 200;
    }    
    
}

