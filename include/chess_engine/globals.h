#ifndef _CHESS_ENGINE_GLOBALS_H
#define _CHESS_ENGINE_GLOBALS_H

#include "constants.h"



typedef struct {
    // pawn attack tables [side][square]
    U64 pawn_attacks[2][64];

    // knight attacks [square]
    U64 knight_attacks[64]; 

    // king attacks table [square]
    U64 king_attacks[64]; 

    // bishop attack table [square][occupancies]
    U64 bishop_attacks[64][512];

    // rook attack table [square][occupancies]
    U64 rook_attacks[64][4096];
} attacks;

extern attacks current_attacks;

typedef struct {
    // bishop attack mask
    U64 bishop_mask [64];

    // rook attack mask
    U64 rook_mask [64];
} masks;


extern masks attack_mask;







#endif