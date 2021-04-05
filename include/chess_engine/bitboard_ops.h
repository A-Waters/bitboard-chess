#ifndef _CHESS_ENGINE_BITBOARD_OPS_H
#define _CHESS_ENGINE_BITBOARD_OPS_H

#include "constants.h"

#define get_bit(bitboard, square) ((bitboard) & (1ULL << square))
#define set_bit(bitboard, square) ((bitboard) |= (1ULL << square))
#define pop_bit(bitboard, square) ((bitboard) &= ~(1ull << square))

// print bitboard 
void print_bitboard(U64 bitboard);

//count bits in bitboard
int count_bits (U64 bitboard);

// get least sig 1st bit index
int get_ls1b_index(U64 bitboard);


#endif