#include <chess_engine/bitboard_ops.h>

#include <stdio.h>

// print bitboard 
void print_bitboard(U64 bitboard)
{
    printf("\n");

    //loop over board rank
    for(int rank = 0; rank < 8; rank++)
    {
        //loop over board files
        for(int file = 0; file < 8; file++)
        {
            //get square index
            int square = rank* 8 + file;

            //print ranks
            if (!file)
                printf("  %d ", 8 - rank);


            //print bitrandom_state (1 or 0)
            printf(" %d", get_bit(bitboard, square) ? 1 : 0);
        }
        printf("\n");
    }

    //print files
    printf("\n     a b c d e f g h \n \n");

    //print unsigned values
    printf("     Bitboard: %llud \n \n", bitboard);
    

}

//count bits in bitboard
int count_bits (U64 bitboard){
    //bit counter
    int count = 0;

    //consecutively reset least significant 1st bit
    while(bitboard > 0)
    {
        count++;

        //reset least significant 1st bit

        bitboard &= ( bitboard -1 );
    }

    //return bit count
    return count;
} 

// get least sig 1st bit index
int get_ls1b_index(U64 bitboard)
{
    // make sure bit board is not empty
    if (bitboard)
    {
        return(count_bits((bitboard & -bitboard) -1));
    }
    else
        return -1;

}

