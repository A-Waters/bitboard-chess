#ifndef _CHESS_ENGINE_RANDOM_NUM_H
#define _CHESS_ENGINE_RANDOM_NUM_H


#ifndef _CHESS_ENGINE_CONSTANTS_H
    #include "constants.h"
#endif


#ifndef _CHESS_ENGINE_GLOBALS_H
    #include "globals.h"
#endif

/*========================*\

      Random Number Gen

\*========================*/



unsigned int get_random_U32_number() 
{
    unsigned int num = random_state;

    // xor shift algorithm
    num ^= num << 13;
    num ^= num >> 17;
    num ^= num << 5;

    random_state = num;

    return num;

}

U64 generate_random_U64_number()
{
// define 4 random numbers
    U64 n1, n2, n3, n4;
    
    // init random numbers slicing 16 bits from MS1B side
    n1 = (U64)(get_random_U32_number()) & 0xFFFF;
    n2 = (U64)(get_random_U32_number()) & 0xFFFF;
    n3 = (U64)(get_random_U32_number()) & 0xFFFF;
    n4 = (U64)(get_random_U32_number()) & 0xFFFF;
    
    // return random number
    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);

}


#endif