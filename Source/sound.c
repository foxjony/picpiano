/********************************************************************************
 *                                                                              *
 *  TASK:           Task_Sound                                                  * 
 *                                                                              *
 *------------------------------------------------------------------------------*
 *
 *  description:    Forming sound control variables according to keyboard state.
 *
 ********************************************************************************/

void Task_Sound (void)
{
    OST_MSG         msg;            // Variable to receive message
    unsigned char   Data[KBD_SIZE]; // Array where keyboard state will be copied to
    unsigned char   cMask;          // Two temparary variables to address bits in
    unsigned char   cPos;           // array.
    
    unsigned char   cFreeSounds;    // How many free channels we have.
    unsigned char   i, j;           // Temp variables
    
    //------------------------------------------------------------------------------
    
    for (;;)
    {
        //------------------------------------------------------------------------------
        //   Wait for changing of keybaord state. Copy keyboard state into Data
        //   array
        //------------------------------------------------------------------------------
        
        OS_Msg_Wait(msg_KBD, msg);  
        
        for (i = 0; i < KBD_SIZE; i++) Data[i] = ((char*)msg)[i];

        //------------------------------------------------------------------------------
        //  If key is played now, then it will be deleted from list of pressed
        //  keys. At the same time we will count number of free sound channels.
        //------------------------------------------------------------------------------

        cFreeSounds = 0;

        for (i = 0; i < MAX_CHANNELS; i++)      // Check all channels
        {
            if (S[i].key == 0)                  // If current channel is quiet then
            {                                   // increase number of free channels.
                cFreeSounds++;    
                continue;
            }

            j = S[i].key - 1;                   // Forming bit address according to 
            cMask = 1 << (j & 7);               // current sound channel
            cPos = j >> 3;

            if (Data[cPos] & cMask)             // If key is still pressed then delete it
                Data[cPos] &= ~cMask;           // from list of pressed keys
            else                        
            {    
                cFreeSounds++;                  // Else stop channel's sound and increase
                S[i].key = 0;                   // free channels counter
            }
        }
        
        //------------------------------------------------------------------------------
        //  Now variable cFreeSounds contain number of free channels. They can be
        //  used to play sounds for just pressed keys.
        //------------------------------------------------------------------------------
        
        cMask = 0x01;   // Start searching just pressed keys
        cPos = 0;
        j = 0;          // Keys counter
        i = 0;          // Channels counter

        while ((j < KBD_KEYS) && cFreeSounds)
        {
            if (Data[cPos] & cMask)     // Is key pressed?
            {                           // Yes.
                while (S[i].key) i++;   // Search for free channel

                                        // Forming sound control variable:
                S[i].F = Freq[j];       //      Frequency
                S[i].f = 0;             //      Phase
                S[i].key = j + 1;       //      Store current key
                cFreeSounds--;          //      Decrease number of free channels
            }

            j++;                        // Get next key
            cMask <<= 1;
            if (!cMask)
            {
                cMask = 0x01;
                cPos++;
            }
        }
    }   //  for(;;)
}


