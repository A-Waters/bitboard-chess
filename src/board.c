#include <chess_engine/board.h>

#include <stdio.h>
#include <string.h>

board_rep board_text = 
{
    "PNBRQKpnbrqk",

    {"♟︎", "♞", "♝", "♜", "♚", "♛", "♙", "♘", "♗", "♖", "♔", "♕"},
    
    {
        ['P'] = P,
        ['N'] = N,
        ['B'] = B,
        ['R'] = R,
        ['Q'] = Q,
        ['K'] = K,
        ['p'] = p,
        ['n'] = n,
        ['b'] = b,
        ['r'] = r,
        ['q'] = q,
        ['k'] = k
    }
};


board chessboard = {
    {} , 
    {} ,
    white ,
    no_sq ,
    0 // all casteling

};

void print_board(){
    
    printf("\n\n");

    for (int rank = 0; rank < 8; rank++){
        for( int file = 0; file < 8; file++){
            int square = rank * 8 + file;

            if (!file)
                printf(" %d ", 8 - rank);

            int piece = -1;

            //loop over bitboards
            for(int piece_type = P; piece_type <= q; piece_type++)
            {
                if (get_bit(chessboard.bitboards[piece_type], square)){
                    piece = piece_type;
                }    
            }
            //print picture if not on windows
            #ifdef WIN64
                printf(" %c", (piece == -1) ? '.' : board_text.ascii_pieces[piece]);
            #else 
                printf(" %s", (piece == -1) ? "." : board_text.unicode_pieces[piece]);
            #endif

        }

        printf("\n");
    }


    //print files
    printf("\n    a b c d e f g h \n \n");

    //side to move 
    printf("    Side:     %s\n", (!chessboard.side && chessboard.side != -1) ? "White" : "Black");

    printf("    En Pas:      %s\n", (chessboard.en_passant != no_sq) ? square_to_coordinates[chessboard.en_passant] : "no" );

    printf("    Castle:    %c%c%c%c\n", (chessboard.castle & wk) ? 'K' : '-',
                                        (chessboard.castle & wq) ? 'Q' : '-',
                                        (chessboard.castle & bk) ? 'k' : '-',
                                        (chessboard.castle & wq) ? 'q' : '-'              
                                    );
}


// https://github.com/maksimKorzh/chess_programming/blob/master/src/bbc/parse_fen/bbc.c#L429
void FEN_parse(char * FEN)
{
    // reset board pos
    memset(chessboard.bitboards, 0ULL, sizeof(chessboard.bitboards));
    memset(chessboard.occupancy, 0ULL, sizeof(chessboard.occupancy));

    chessboard.side = white;
    chessboard.en_passant = no_sq;
    chessboard.castle = 0;


    for (int rank = 0; rank < 8; rank++)
    {
        for (int file = 0; file < 8; file++)
        {
            // init current square
            int square = rank * 8 + file;
            
            // match ascii pieces within FEN string
            if ((*FEN >= 'a' && *FEN <= 'z') || (*FEN >= 'A' && *FEN <= 'Z'))
            {
                // init piece type
                int piece = board_text.char_pieces[*FEN];
                
                // set piece on corresponding bitboard
                set_bit(chessboard.bitboards[piece], square);
                
                // increment pointer to FEN string
                *FEN++;
            }

            //empty square numbers
            // match empty square numbers within FEN string
            if (*FEN >= '0' && *FEN <= '9')
            {
                // init offset (convert char 0 to int 0)
                int offset = *FEN - '0';
                
                // define piece variable
                int piece = -1;
                
                // loop over all piece bitboards
                for (int piece_type = P; piece_type <= k; piece_type++)
                {
                    // if there is a piece on current square
                    if (get_bit(chessboard.bitboards[piece_type], square))
                        // get piece code
                        piece = piece_type;
                }
                
                // on empty current square
                if (piece == -1)
                    // decrement file
                    file--;
                
                // adjust file counter
                file += offset;
                
                // increment pointer to FEN string
                *FEN++;
            }
            
            // match rank separator
            if (*FEN == '/') 
                // increment pointer to FEN string
                *FEN++;
        }
        
    }
    FEN++;

    // side 
    (*FEN == 'w') ? (chessboard.side = white) : (chessboard.side = black);


    // get to castle   
    FEN += 2;
    
    // castleing rights
    while (*FEN != ' ')
    {
        switch (*FEN)
        {
        case 'K' : chessboard.castle |= wk; break;
        case 'Q' : chessboard.castle |= wq; break;
        case 'k' : chessboard.castle |= bk; break;
        case 'q' : chessboard.castle |= bq; break;
        case '-' : break;
        }
        *FEN++;
    }

    *FEN++;
    
    // no empassant square
    if (*FEN != '-') 
    {
        int file = FEN[0] - 'a';
        int rank = 8 - (FEN[1] - '0');

        chessboard.en_passant = rank * 8 + file;
    }

    else
        chessboard.en_passant = no_sq;

    
    // occupancies

    for (int piece = P; piece <= Q;piece++) {
        chessboard.occupancy[white] |= chessboard.bitboards[piece];
    } 

    for (int piece = p; piece <= q;piece++) {
        chessboard.occupancy[black] |= chessboard.bitboards[piece];
    } 

    chessboard.occupancy[both] |= chessboard.occupancy[white];
    chessboard.occupancy[both] |= chessboard.occupancy[black];
}