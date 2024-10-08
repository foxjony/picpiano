#define MAX_SAMPLES     4

/*******************************************************************************
 *   
 *     Array of four samples. Each sample represented by one period
 *     of sinus (64 points per sample)
 *   
 *******************************************************************************/

const signed char SAMPLES[MAX_SAMPLES][64] = {
    {
       0,   20,   41,   60,   78,   93,  106,  116,  123,  127,  127,  123,  117,  109,   98,   85, 
      72,   57,   43,   28,   14,    3,   -5,  -14,  -20,  -24,  -26,  -25,  -23,  -18,  -12,   -6, 
       0,    6,   12,   18,   22,   25,   26,   25,   20,   14,    6,   -2,  -14,  -28,  -42,  -57, 
     -72,  -86,  -99, -109, -118, -124, -128, -128, -124, -117, -108,  -95,  -79,  -62,  -42,  -21
    },

    {
       0,   55,  100,  118,  127,  127,  127,  127,  127,  127,  127,  127,  127,  127,  127,  100, 
      63,   27,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   -8,  -27,  -19, 
       0,   18,   27,    9,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  -26, 
     -63, -100, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -119, -101,  -57
    },

    {
      63,   64,   57,   42,   24,    5,  -10,  -21,  -21,  -10,    7,   31,   58,   84,  107,  121, 
     127,  121,  107,   85,   58,   31,    8,  -10,  -21,  -21,  -10,    5,   24,   42,   57,   64, 
      63,   52,   32,    6,  -27,  -62,  -93, -116, -128, -126, -114,  -94,  -69,  -42,  -20,   -4, 
       0,   -4,  -18,  -41,  -68,  -93, -114, -126, -128, -117,  -94,  -65,  -29,    4,   31,   51
    },
    
    {
       0,   38,   73,  101,  120,  127,  125,  114,  100,   82,   66,   54,   46,   44,   44,   45, 
      46,   46,   41,   32,   18,    4,  -16,  -37,  -52,  -56,  -54,  -40,  -23,   -7,    1,    2, 
       0,  -14,  -40,  -68,  -97, -116, -128, -123, -101,  -71,  -28,    6,   29,   48,   57,   57, 
      48,   30,    8,  -23,  -64,  -94, -113, -118, -111,  -94,  -73,  -49,  -28,  -11,   -2,    0
    }
    

};

