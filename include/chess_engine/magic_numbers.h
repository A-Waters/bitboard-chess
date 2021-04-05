#ifndef _CHESS_ENGINE_MAGIC_NUM_H
#define _CHESS_ENGINE_MAGIC_NUM_H

#include "constants.h"
#include "attacks.h"
#include "random_num.h"

typedef struct
{
    unsigned int random_state;
    U64 rook_magic_numbers [64];
    U64 bishop_magic_numbers [64];
} magic_nums;

extern magic_nums magic_numbers;


U64 generate_magic_number();

U64 find_magic_number(int square, int relevant_bits, int bishop);

#endif