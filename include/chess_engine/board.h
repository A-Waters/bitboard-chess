#ifndef _CHESS_ENGINE_BOARD_H
#define _CHESS_ENGINE_BOARD_H

#include "constants.h"
#include "bitboard_ops.h"
//castleing 

/*
    bin  dec
    
   0001    1  white king can castle to the king side
   0010    2  white king can castle to the queen side
   0100    4  black king can castle to the king side
   1000    8  black king can castle to the queen side

   examples

   1111       both sides an castle both directions
   1001       black king => queen side
              white king => king side
*/

enum { wk = 1, wq = 2, bk = 4, bq = 8 };
enum { P, N, B, R, K, Q, p, n, b, r, k, q};

typedef struct 
{
    char ascii_pieces[12];
    char *unicode_pieces[12];
    // convert ASCII character pieces to encoded constants
    int char_pieces[];

} board_rep;

extern board_rep board_text;


typedef struct 
{   
    // chess pieces for each side
    U64 bitboards[12];

    // occupancy boards
    U64 occupancy[3];

    int side;

    int en_passant;

    int castle;

}board;

extern board chessboard;

void print_board();

void FEN_parse(char * FEN);

#endif

