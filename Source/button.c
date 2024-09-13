void CopySample (char c);

/********************************************************************************
 *                                                                              *
 *  TASK: Task_Button                                                           *
 *                                                                              *
 *------------------------------------------------------------------------------*
 *
 *  description:    Select sample by pressing a button
 *
 *
 ********************************************************************************/

void Task_Button (void)
{
    static char s_cCurSample;   // Current sample

    s_cCurSample = 0;
    
    CopySample(s_cCurSample);
    for (;;)
    {
        //------------------------------------------------------------------------------
        //  Wait for key press (with debounce)
        //------------------------------------------------------------------------------
        
        do 
        {
            OS_Cond_Wait(!pin_BUTTON);
            OS_Delay(40 ms);
        } while (pin_BUTTON);

        //------------------------------------------------------------------------------
        //  Chenging sample, copy sample info into RAM
        //------------------------------------------------------------------------------
        
        s_cCurSample++;
        if (s_cCurSample >= MAX_SAMPLES) s_cCurSample = 0;
        CopySample(s_cCurSample);

        //------------------------------------------------------------------------------
        //  Wait for key release
        //------------------------------------------------------------------------------
        
        do 
        {
            OS_Cond_Wait(pin_BUTTON);
            OS_Delay(40 ms);
        } while (!pin_BUTTON);

        
    }
}

/********************************************************************************
 *
 *  Function:       CopySample
 *
 *------------------------------------------------------------------------------ 
 *
 *  description:    Copy sample data for sinthesizer from ROM into RAM
 *
 *  parameters:     char c - sample position in SAMPLE array
 *
 *  on return:      void
 *
 ********************************************************************************/

void CopySample (char c)
{
    char n;
    if (c >= MAX_SAMPLES) c = 0;
    for (n = 0; n < 64; n++) Sample[n] = SAMPLES[c][n];
}



