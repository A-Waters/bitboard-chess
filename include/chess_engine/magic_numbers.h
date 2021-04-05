#ifndef _CHESS_ENGINE_MAGIC_NUM_H
#define _CHESS_ENGINE_MAGIC_NUM_H

#include "constants.h"
#include "attacks.h"
#include "random_num.h"

U64 generate_magic_number();

U64 find_magic_number(int square, int relevant_bits, int bishop);

#endif