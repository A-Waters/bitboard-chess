#ifndef _CHESS_ENGINE_INIT_H
#define _CHESS_ENGINE_INIT_H

#include "constants.h"
#include "globals.h"
#include "magic_numbers.h"


// init magic numbers 
void init_magic_numbers();

void init_slider_attacks(int bishop);

//init leaper pieces attacks
void init_leaper_attacks();

void init_all();

#endif