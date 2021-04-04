#include <stdio.h>

//single bitboard
#define U64 unsigned long long

enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1,
};

//sides to move 
enum {white, black};


/* add f file
   "a8", "b8", "c8", "d8", "e8", "g8", "h8",
   "a7", "b7", "c7", "d7", "e7", "g7", "h7",
   "a6", "b6", "c6", "d6", "e6", "g6", "h6",
   "a5", "b5", "c5", "d5", "e5", "g5", "h5",
   "a4", "b4", "c4", "d4", "e4", "g4", "h4",
   "a3", "b3", "c3", "d3", "e3", "g3", "h3",
   "a2", "b2", "c2", "d2", "e2", "g2", "h2",
   "a1", "b1", "c1", "d1", "e1", "g1", "h1",
*/

/*========================*\

    Build Bit Boards

\*========================*/


/*========================*\

      Bit Manipulation

\*========================*/

#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (1ull << square) : 0)




/*========================*\

      Input & output

\*========================*/



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


            //print bitstate (1 or 0)
            printf(" %d", get_bit(bitboard, square) ? 1 : 0);
        }
        printf("\n");
    }

    //print files
    printf("\n     a b c d e f g h \n \n");

    //print unsigned values
    printf("     Bitboard: %llud \n \n", bitboard);
    

}


/*========================*\

          Attacks

\*========================*/

/*
    not a file const 

    8  0 1 1 1 1 1 1 1
    7  0 1 1 1 1 1 1 1
    6  0 1 1 1 1 1 1 1
    5  0 1 1 1 1 1 1 1
    4  0 1 1 1 1 1 1 1
    3  0 1 1 1 1 1 1 1
    2  0 1 1 1 1 1 1 1
    1  0 1 1 1 1 1 1 1

       a b c d e f g h 
 
       Bitboard: 18374403900871474942d 


    not h file const 

    8  1 1 1 1 1 1 1 0
    7  1 1 1 1 1 1 1 0
    6  1 1 1 1 1 1 1 0
    5  1 1 1 1 1 1 1 0
    4  1 1 1 1 1 1 1 0
    3  1 1 1 1 1 1 1 0
    2  1 1 1 1 1 1 1 0
    1  1 1 1 1 1 1 1 0

       a b c d e f g h 

       Bitboard: 9187201950435737471d 



    not hg file const 

    8  1 1 1 1 1 1 0 0
    7  1 1 1 1 1 1 0 0
    6  1 1 1 1 1 1 0 0
    5  1 1 1 1 1 1 0 0
    4  1 1 1 1 1 1 0 0
    3  1 1 1 1 1 1 0 0
    2  1 1 1 1 1 1 0 0
    1  1 1 1 1 1 1 0 0

       a b c d e f g h 

       Bitboard: 4557430888798830399d 


    not ab file const 

    8  0 0 1 1 1 1 1 1
    7  0 0 1 1 1 1 1 1
    6  0 0 1 1 1 1 1 1
    5  0 0 1 1 1 1 1 1
    4  0 0 1 1 1 1 1 1
    3  0 0 1 1 1 1 1 1
    2  0 0 1 1 1 1 1 1
    1  0 0 1 1 1 1 1 1

       a b c d e f g h 

       Bitboard: 18229723555195321596d
*/






// not A file const
const U64 not_a_file = 18374403900871474942ULL;

// not H file const
const U64 not_h_file = 9187201950435737471ULL;

// not HG file const
const U64 not_hg_file = 4557430888798830399ULL;

// not AB file const
const U64 not_ab_file = 18229723555195321596ULL;

// pawn attack tables [side][square]
U64 pawn_attacks[2][64];

// knight attacks [square]
U64 knight_attacks [64]; 

// king attacks table [square]
U64 king_attacks[64]; 



//generate pawn attacks
U64 mask_pawn_attacks(int side_to_move, int square){

    //result attack bitboard
    U64 attacks = 0ULL;

    // piece bitboard
    U64 bitboard = 0ULL;

    //set piece on board
    set_bit(bitboard, square);

    //white pawn
    if (!side_to_move)
    {
        if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    }

    //black pawns
    else 
    {
        if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
        if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
    }

    //return attack map
    return attacks;
}



U64 mask_knight_attacks(int square) {

    //result attack bitboard
    U64 attacks = 0ULL;

    // piece bitboard
    U64 bitboard = 0ULL;

    //set piece on board
    set_bit(bitboard, square);

    // generate knight attacks
    if ((bitboard >> 17) & not_h_file) attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & not_a_file) attacks |= (bitboard >> 15);
    if ((bitboard >> 10) & not_hg_file) attacks |= (bitboard >> 10);
    if ((bitboard >> 6) & not_ab_file) attacks |= (bitboard >> 6);


    if ((bitboard << 17) & not_a_file) attacks |= (bitboard << 17);
    if ((bitboard << 15) & not_h_file) attacks |= (bitboard << 15);
    if ((bitboard << 10) & not_ab_file) attacks |= (bitboard << 10);
    if ((bitboard << 6) & not_hg_file) attacks |= (bitboard << 6);



    //return attack map
    return attacks;
}


U64 mask_king_attacks(int square) {

    //result attack bitboard
    U64 attacks = 0ULL;

    // piece bitboard
    U64 bitboard = 0ULL;

    //set piece on board
    set_bit(bitboard, square);

    //generate king attack

    if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
    if ((bitboard >> 8)) attacks |= (bitboard >> 8);
    if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);

    if ((bitboard >> 1) & not_h_file) attacks |= (bitboard >> 1);
    if ((bitboard << 1) & not_a_file) attacks |= (bitboard << 1);

    if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
    if ((bitboard << 8)) attacks |= (bitboard << 8);
    if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);



    //return attack map
    return attacks;
}




//init leaper pieces attacks
void init_leaper_attacks(){

    //loop over board

    for(int square = 0; square < 64; square++){
        //init pawn attacks 

        pawn_attacks[white][square] = mask_pawn_attacks(white, square);
        pawn_attacks[black][square] = mask_pawn_attacks(black, square);


        //init knight attacks 
        knight_attacks[square] = mask_knight_attacks(square);


        //init king attacks 
        king_attacks[square] = mask_king_attacks(square);

    }

}






// main


int main() {


    //init leaper attacks 
    init_leaper_attacks();

    //loop over 64 board squares
    for(int square = 0; square < 64; square++)
        print_bitboard(king_attacks[square]);

    print_bitboard(mask_king_attacks(h4));



    return 0;
}