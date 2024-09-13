
char ReadRow (char row);


//******************************************************************************
//  
//      Keybard state.
// 
//******************************************************************************

struct
{
    unsigned char   Data[KBD_SIZE];         // Array of bits: =1 - key pressed
    unsigned char   cDataPos;               // Two variables to point current
    unsigned char   cDataMask;              // bit while keyboard scanning.
    unsigned char   Tresholds[KBD_COLUMNS]; // Array of reference values of
                                            // ADC to determinate that key is
                                            // pressed
} KBD;

/********************************************************************************
 *                                                                              *
 *  TASK: Task_Keyboard                                                         *
 *                                                                              *
 *------------------------------------------------------------------------------*
 *
 *  description:    Read keyboard state
 *
 ********************************************************************************/

void Task_Keyboard (void)
{
    static char n;
    static char s_cChanged;

    //------------------------------------------------------------------------------
    //  Make call of ReadRow to make sure that all analog input pins are
    //  configured as digital output (to discharge capasitors)
    //------------------------------------------------------------------------------
    
    ReadRow(0);

    //------------------------------------------------------------------------------
    //  First time all reference values are cleared (not set)
    //------------------------------------------------------------------------------
    
    for (n = 0; n < KBD_COLUMNS; n++) KBD.Tresholds[n] = 0;

    for (;;)
    {
        //------------------------------------------------------------------------------
        //  Set bit mask for first key
        //------------------------------------------------------------------------------
        
        KBD.cDataPos  = 0;                  // Byte number
        KBD.cDataMask = 0x01;               // Bit mask in byte
        s_cChanged = 0;                     // Boolean value: =1 - keys states
                                            // were changed

        for (n = 0; n < KBD_ROWS; n++)      // Loop by all rows
        {    
            s_cChanged |= ReadRow(n);       // Measuring of all sensors (key) in a 
                                            // row may take about 500 us. So
                                            // between row measures we switch
                                            // tasks.
            OS_Yield();
        }

        //------------------------------------------------------------------------------
        //  If keyboard state was changed, then send a message to Task_Sound
        //------------------------------------------------------------------------------
        
        if (s_cChanged) 
        {    
            OS_Msg_Send_Now(msg_KBD, (OST_MSG) KBD.Data);
        }

        OS_Delay(10 ms);
    }
}


/*******************************************************************************
 *                                                                              
 *  Function:       ReadRow                                                    
 *                                                                              
 *----------------------------------------------------------------------------- 
 *                                                                              
 *  description:    Read all keys in one row
 *                                                                              
 *  parameters:     char row - row position 0..KBD_ROWS-1                        
 *                                                                              
 *  on return:      char - =1 - there were changes in state of keys in row
 *                                                                              
 *******************************************************************************/

char ReadRow (char row)
{
    //------------------------------------------------------------------------------

    char        m, a, i, k;             // Additional variables
    char        col;                    // Current analog input (column)
    TColumn     Column;                 // Use a variable to redice code size and 
                                        // increaze speed.

    static char s_Changes[KBD_SIZE];    // For debounce: changes since last reading

    static bit  s_bChanged;             // ariable o be returned

    //------------------------------------------------------------------------------
    
    *ROWS[row].pPort |= ROWS[row].cMask;// Set row control output to "1"

    s_bChanged = 0;                     // First we suppose that there were not 
                                        // any changes in keyboard state

    //******************************************************************************
    //   Loop for all columns
    //******************************************************************************
    
    for (col = 0; col  < KBD_COLUMNS; col++)    
    {
        //------------------------------------------------------------------------------
        // Copy channel info into RAM variable to reduce code size
        //------------------------------------------------------------------------------
        
        Column.pPort       = COLUMNS[col].pPort;
        Column.pTris       = COLUMNS[col].pTris;
        Column.cMask       = COLUMNS[col].cMask;
        Column.cADCChannel = COLUMNS[col].cADCChannel;

        //------------------------------------------------------------------------------
        //  Select ADC channel
        //------------------------------------------------------------------------------
        
        CHS0 = 0;
        CHS1 = 0;
        CHS2 = 0;
        if (Column.cADCChannel & 0x01) CHS0 = 1;
        if (Column.cADCChannel & 0x02) CHS1 = 1;
        if (Column.cADCChannel & 0x04) CHS2 = 1;

        #if defined(_16F887) || defined(_16F886) || defined(_16F690)
        CHS3 = 0;
        if (Column.cADCChannel & 0x08) CHS3 = 1;
        #endif

        //------------------------------------------------------------------------------
        //  Start measuring
        //------------------------------------------------------------------------------

        GIE = 0;                        // Disabling interrupts while making delay
                                        // to charge capasitor
                                        
        *Column.pTris |=  Column.cMask; // Start capasitor sensor charging by 
                                        // set analog pin for input (high imp.)

        for (m = 0; m < 3; m++) NOP();  // CHARGING DELAY
                                        
        GODONE = 1;                     // Start AD conversion. 
        GIE = 1;                        // Now we can enable interrupts

        while (GODONE) continue;

        //------------------------------------------------------------------------------
        //  AD conversion is done. Now forming key states array.
        //------------------------------------------------------------------------------
        
        *Column.pTris &= ~Column.cMask;
        *Column.pPort &= ~Column.cMask; // Discharge capasitor by switching analog
                                        // input to output "0"
        a = ADRESH;

        //------------------------------------------------------------------------------
        //  Set reference for current channel if it not set yet
        //------------------------------------------------------------------------------
        
        m = KBD.Tresholds[col];         // Copy element of array in vaiable to 
                                        // reduce code size
        i = 0;
        if (a < m) i = KBD.cDataMask;   // Compare with reference value. If just read
                                        // value is less than reference, then
                                        // capasitor were charged to slow. It
                                        // means that key is pressed.

        if (!m)                         // If reference is not set (is zero) then
        {                               // set it as 88% of current ADRESH value
            m = a >> 3;
            KBD.Tresholds[col] = a - m;
        }

        //------------------------------------------------------------------------------
        //  Setting new keyboard state (with debounce)
        //------------------------------------------------------------------------------
        
        m  =  KBD.Data[KBD.cDataPos];   // To reduce code size we will work with
        k  =  s_Changes[KBD.cDataPos];  // copy of array's element

        //------------------------------------------------------------------------------
        if ((m ^ i) & KBD.cDataMask)
        {                               // Key state was changed:
            if (!(k & KBD.cDataMask))   //   Just now:
                k |=  KBD.cDataMask;    //     Set change token
                                        
            else                        //   Not just now:
            {
                m ^=  KBD.cDataMask;    //     Set new key state
                s_bChanged = 1;         //     Form variableto be returned
                k &= ~KBD.cDataMask;    //     Reset change token
            }
        //------------------------------------------------------------------------------
        } else {                        // Key state remain unchanged
            k &= ~KBD.cDataMask;        //   Reset change token
        }
        //------------------------------------------------------------------------------

        KBD.Data[KBD.cDataPos] = m;     // Restore array's elements from 
        s_Changes[KBD.cDataPos] = k;    // temp variables

        //------------------------------------------------------------------------------
        //   Set bit mask for next key
        //------------------------------------------------------------------------------
        
        KBD.cDataMask <<= 1;            
        if (!KBD.cDataMask)
        {
            KBD.cDataMask = 0x01;
            KBD.cDataPos++;
        }

    };

    *ROWS[row].pPort &= ~ROWS[row].cMask;   // Set row control output to "0"

    return s_bChanged;

}


