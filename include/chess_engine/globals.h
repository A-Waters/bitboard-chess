#ifndef _CHESS_ENGINE_GLOBALS_H
#define _CHESS_ENGINE_GLOBALS_H

#include "constants.h"

// pawn attack tables [side][square]
extern U64 pawn_attacks[2][64];

// knight attacks [square]
extern U64 knight_attacks[64]; 

// king attacks table [square]
extern U64 king_attacks[64]; 

// bishop attack mask
extern U64 bishop_mask [64];

// rook attack mask
extern U64 rook_mask [64];

// bishop attack table [square][occupancies]
extern U64 bishop_attacks[64][512];

// rook attack table [square][occupancies]
extern U64 rook_attacks[64][4096];

extern unsigned int random_state;

extern U64 rook_magic_numbers [64];

extern U64 bishop_magic_numbers [64];


#endif