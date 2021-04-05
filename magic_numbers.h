#ifndef _CHESS_ENGINE_MAGIC_NUM_H
#define _CHESS_ENGINE_MAGIC_NUM_H

#ifndef _CHESS_ENGINE_CONSTANTS_H
    #include "constants.h"
#endif

#ifndef _CHESS_ENGINE_ATTACKS_H
    #include "attacks.h"
#endif

#ifndef _CHESS_ENGINE_RANDOM_NUM_H
    #include "random_num.h"
#endif


#include <string.h>
#include <stdio.h>
#include <unistd.h>

U64 generate_magic_number()
{
    return generate_random_U64_number() & generate_random_U64_number() & generate_random_U64_number();
}


U64 find_magic_number(int square, int relevant_bits, int bishop)
{
    // init occupancies
    U64 occupancies[4096];
    
    // init attack tables
    U64 attacks[4096];
    
    // init used attacks
    U64 used_attacks[4096];
    
    // init attack mask for a current piece
    U64 attack_mask = bishop ? mask_bishop_attacks(square) : mask_rook_attacks(square);
    
    // init occupancy indicies
    int occupancy_indicies = 1 << relevant_bits;
    
    // loop over occupancy indicies
    for (int index = 0; index < occupancy_indicies; index++)
    {
        // init occupancies
        occupancies[index] = set_occupancy(index, relevant_bits, attack_mask);
        
        // init attacks
        attacks[index] = bishop ? bishop_attacks_on_the_fly(square, occupancies[index]) :
                                    rook_attacks_on_the_fly(square, occupancies[index]);
    }
    
    // test magic numbers loop
    for (int random_count = 0; random_count < 100000000; random_count++)
    {
        // generate magic number candidate
        U64 magic_number = generate_magic_number();



        // skip inappropriate magic numbers
        if (count_bits((attack_mask * magic_number) & 0xFF00000000000000ULL) < 6) continue;
        
        // init used attacks
        memset(used_attacks, 0ULL, sizeof(used_attacks));
        
        // init index & fail flag
        int index, fail;
        
        // test magic index loop
        for (index = 0, fail = 0; !fail && index < occupancy_indicies; index++)
        {
            // init magic index
            int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));
            
            // if magic index works
            if (used_attacks[magic_index] == 0ULL)
                // init used attacks
                used_attacks[magic_index] = attacks[index];
            
            // otherwise
            else if (used_attacks[magic_index] != attacks[index])
                // magic index doesn't work
                fail = 1;
        }
        

        // if magic number works
        if (!fail){
            // return it
            return magic_number;
            sleep(5);
        }
    }
    
    // if magic number doesn't work

    printf("  Magic number fails! %d \n");
    sleep(5);
    return 0ULL;
}





#endif