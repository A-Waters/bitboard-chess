#ifndef _CHESS_ENGINE_ATTACKS_H
#define _CHESS_ENGINE_ATTACKS_H

#include "constants.h"
#include "bitboard_ops.h"
#include "globals.h"


//generate pawn attacks
U64 mask_pawn_attacks(int side_to_move, int square);

U64 mask_knight_attacks(int square);

U64 mask_king_attacks(int square);

U64 mask_bishop_attacks(int square);

U64 mask_rook_attacks(int square);

// generate bishop attacks on the fly
U64 bishop_attacks_on_the_fly(int square, U64 blocks);

// generate bishop attacks on the fly
U64 rook_attacks_on_the_fly(int square, U64 blocks);

// set occupancies
U64 set_occupancy(int index, int bits_in_mask, U64 attack_mask);

U64 get_bishop_attacks(int square, U64 occupancy);

U64 get_rook_attacks(int square, U64 occupancy);


#endif