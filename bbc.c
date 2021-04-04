#include <stdio.h>
#include <string.h>
#include <unistd.h>






/*========================*\

    Environment Ease

\*========================*/





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

//sides to move 
enum {rook, bishop};


const char *square_to_coordinates [] = 
{
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
};


U64 rook_magic_numbers [64] = {
    0x780a080080080056ULL, 
    0x40a00200840082ULL, 
    0x40180210122000c2ULL, 
    0xa010020200820040ULL, 
    0x4901000460040004ULL, 
    0x10a412020a04008ULL, 
    0x1019044410582210ULL, 
    0x8024012001002108ULL, 
    0xa08830040080400ULL, 
    0x4003108c18304c34ULL, 
    0x30200101200401cULL, 
    0x800420008018010ULL, 
    0x240060104a802240ULL, 
    0x6403020042c0200ULL, 
    0x2084100281084ULL, 
    0x5200a10004100804ULL, 
    0x110004200404283ULL, 
    0x28040081d00800c8ULL, 
    0x801042040301002ULL, 
    0x2101110020a20100ULL, 
    0x402010801a183ULL, 
    0x3006c0400040200ULL, 
    0x80088ad6a9002022ULL, 
    0x4700060104640080ULL, 
    0x8040802008001ULL, 
    0x82211002421c5000ULL, 
    0x800084003200412cULL, 
    0x4820081005020200ULL, 
    0x102a0c208180202ULL, 
    0x8000440403006402ULL, 
    0x800040100218020ULL, 
    0xd100021804020c10ULL, 
    0x4002251400810284ULL, 
    0x4032720081081000ULL, 
    0x8440431021202ULL, 
    0x100a0024080800ULL, 
    0x8014448220084098ULL, 
    0x110042020100d0ULL, 
    0x2288008090600ULL, 
    0x8484085001400820ULL, 
    0x6100308011002190ULL, 
    0x11000a020238484ULL, 
    0x200110520004062ULL, 
    0x44020904a004028ULL, 
    0x2002304119002200ULL, 
    0x100940005042100ULL, 
    0x800910022002002ULL, 
    0x710084009402104ULL, 
    0x10862048c00040ULL, 
    0x2810004120080010ULL, 
    0x1000204230024409ULL, 
    0x2200888682020080ULL, 
    0x10040800040821ULL, 
    0x6801050804000204ULL, 
    0x8043010202000200ULL, 
    0x42121200a08400c0ULL, 
    0x260001a020810abULL, 
    0xd001003004008041ULL, 
    0x1420030188841021ULL, 
    0x202088080410212ULL, 
    0x100280400841ULL, 
    0x8204624221421102ULL, 
    0x280200021109ULL, 
    0x90004020804c001ULL,
};


U64 bishop_magic_numbers [64] = {
    0x102021102004101ULL, 
    0x88854801004108ULL, 
    0x8480080220000ULL, 
    0x42640020020000ULL, 
    0x501027400032400ULL, 
    0xc4102052c8004ULL, 
    0x9040818220218008ULL, 
    0x410604410345ULL, 
    0x12040411044050ULL, 
    0x18430018204420aULL, 
    0x8100084122453020ULL, 
    0x4042200809218ULL, 
    0x4000cc50c822209ULL, 
    0x91c38a0084ULL, 
    0x2808004841509000ULL, 
    0x1050418041280e00ULL, 
    0x104000e08112102ULL, 
    0x2202006804009141ULL, 
    0x8028b00819620081ULL, 
    0x801000088530200ULL, 
    0x10210101022000ULL, 
    0x410101102601ULL, 
    0x480150860e0a5410ULL, 
    0x811a2081024cULL, 
    0xc10a24411880480ULL, 
    0x130414000825c10cULL, 
    0x10a0408020019ULL, 
    0x1460858284086038ULL, 
    0x5004000200c20ULL, 
    0x34004005500080ULL, 
    0x20080040044c2400ULL, 
    0x25a04c03008084ULL, 
    0x4204045100080203ULL, 
    0x880200e10420ULL, 
    0x2022002404050020ULL, 
    0x88900404080c102ULL, 
    0x8004020024020021ULL, 
    0x24100a0090104414ULL, 
    0x100a120040080ULL, 
    0x24089022920090ULL, 
    0x2240a08104102ULL, 
    0x20c08848202a200ULL, 
    0x94010018020a0404ULL, 
    0x20828002a08ULL, 
    0x803441012000845ULL, 
    0x8030894101082028ULL, 
    0x202210090021aULL, 
    0x110412200450041ULL, 
    0x811a80aa04100240ULL, 
    0x20220804040002ULL, 
    0x2c420201048000ULL, 
    0xa00020020910240ULL, 
    0x9800006802504004ULL, 
    0xa8120c019800ULL, 
    0x20041201005030ULL, 
    0x4011302200484400ULL, 
    0x45820304010400ULL, 
    0x22080a0944ULL, 
    0x500021020968c00ULL, 
    0x800000000311880ULL, 
    0x20a0204100201c6ULL, 
    0x40000412084090ULL, 
    0x98081001021228ULL, 
    0xa01b810184090d44ULL,
};




/*========================*\

      Bit Manipulation

\*========================*/

#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (1ull << square) : 0)

//count bits in bitboard
static inline int count_bits (U64 bitboard){
    //bit counter
    int count = 0;

    //consecutively reset least significant 1st bit
    while(bitboard > 0)
    {
        count++;

        //reset least significant 1st bit

        bitboard &= ( bitboard -1 );
    }

    //return bit count
    return count;
} 

// get least sig 1st bit index
static inline int get_ls1b_index(U64 bitboard)
{
    // make sure bit board is not empty
    if (bitboard)
    {
        return(count_bits((bitboard & -bitboard) -1));
    }
    else
        return -1;

}


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


            //print bitrandom_state (1 or 0)
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

      Random Number Gen

\*========================*/




unsigned int random_state = 1804289383;

unsigned int get_random_U32_number() 
{
    unsigned int num = random_state;

    // xor shift algorithm
    num ^= num << 13;
    num ^= num >> 17;
    num ^= num << 5;

    random_state = num;

    return num;

}

U64 generate_random_U64_number()
{
// define 4 random numbers
    U64 n1, n2, n3, n4;
    
    // init random numbers slicing 16 bits from MS1B side
    n1 = (U64)(get_random_U32_number()) & 0xFFFF;
    n2 = (U64)(get_random_U32_number()) & 0xFFFF;
    n3 = (U64)(get_random_U32_number()) & 0xFFFF;
    n4 = (U64)(get_random_U32_number()) & 0xFFFF;
    
    // return random number
    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);

}

U64 generate_magic_number()
{
    return generate_random_U64_number() & generate_random_U64_number() & generate_random_U64_number();
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


// bishop relevant occupancy bit count for every square on board
const int bishop_relevant_bits [64] = 
{
    6,  5,  5,  5,  5,  5,  5,  6, 
    5,  5,  5,  5,  5,  5,  5,  5, 
    5,  5,  7,  7,  7,  7,  5,  5, 
    5,  5,  7,  9,  9,  7,  5,  5, 
    5,  5,  7,  9,  9,  7,  5,  5, 
    5,  5,  7,  7,  7,  7,  5,  5, 
    5,  5,  5,  5,  5,  5,  5,  5, 
    6,  5,  5,  5,  5,  5,  5,  6,
};

// rook relevant occupancy bit count for every square on board
const int rook_relevant_bits [64] = 
{
    12,  11,  11,  11,  11,  11,  11,  12, 
    11,  10,  10,  10,  10,  10,  10,  11, 
    11,  10,  10,  10,  10,  10,  10,  11, 
    11,  10,  10,  10,  10,  10,  10,  11, 
    11,  10,  10,  10,  10,  10,  10,  11, 
    11,  10,  10,  10,  10,  10,  10,  11, 
    11,  10,  10,  10,  10,  10,  10,  11, 
    12,  11,  11,  11,  11,  11,  11,  12,
};



// pawn attack tables [side][square]
U64 pawn_attacks[2][64];

// knight attacks [square]
U64 knight_attacks[64]; 

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


U64 mask_bishop_attacks(int square)
{
    //result attack bitboard
    U64 attacks = 0ULL;

    // piece bitboard
    U64 bitboard = 0ULL;

    //init ranks, and files
    int r, f;

    //init target rank and file
    int tr = square / 8;
    int tf = square % 8;

    // dont go to the end of the board
    // mask relevant bits
    for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--) attacks |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++) attacks |= (1ULL << (r * 8 + f));

    for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++) attacks |= (1ULL << (r * 8 + f));
    for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--) attacks |= (1ULL << (r * 8 + f));
    //return
    return attacks;

}


U64 mask_rook_attacks(int square)
{
    //result attack bitboard
    U64 attacks = 0ULL;

    // piece bitboard
    U64 bitboard = 0ULL;

    //init ranks, and files
    int r, f;

    //init target rank and file
    int tr = square / 8;
    int tf = square % 8;

    // dont go to the end of the board
    // mask relevant bits
    for (f = tf + 1; f <= 6; f++) attacks |= (1ULL << (tr * 8 + f));
    for (f = tf - 1; f >= 1; f--) attacks |= (1ULL << (tr * 8 + f));
    
    for (r = tr + 1; r <= 6; r++) attacks |= (1ULL << (r * 8 + tf));
    for (r = tr - 1; r >= 1; r--) attacks |= (1ULL << (r * 8 + tf));
   
    //return
    return attacks;

}

// generate bishop attacks on the fly
U64 bishop_attacks_on_the_fly(int square, U64 blocks)
{
    //result attack bitboard
    U64 attacks = 0ULL;

    // piece bitboard
    U64 bitboard = 0ULL;

    //init ranks, and files
    int r, f;

    //init target rank and file
    int tr = square / 8;
    int tf = square % 8;

    //go to the end of the board
    //generate bishop attacks
    for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) 
    {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f) && blocks)) break;
    }
    
    for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++)  
    {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f) && blocks)) break;
    }

    for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++)  
    {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f) && blocks)) break;
    }

    for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--)  
    {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f) && blocks)) break;
    }

    //return
    return attacks;

}


// generate bishop attacks on the fly
U64 rook_attacks_on_the_fly(int square, U64 blocks)
{
    //result attack bitboard
    U64 attacks = 0ULL;

    // piece bitboard
    U64 bitboard = 0ULL;

    //init ranks, and files
    int r, f;

    //init target rank and file
    int tr = square / 8;
    int tf = square % 8;

    // go to the end of the board
    for (f = tf + 1; f <= 7; f++) 
    {
        attacks |= (1ULL << (tr * 8 + f));
        if ((1ULL << (tr * 8 + f)) && blocks) break;
    }

    for (f = tf - 1; f >= 0; f--)  
    {
        attacks |= (1ULL << (tr * 8 + f));
        if ((1ULL << (tr * 8 + f)) && blocks) break;
    }
    
    for (r = tr + 1; r <= 7; r++)
    {
        attacks |= (1ULL << (r * 8 + tf));
        if ((1ULL << (r * 8 + tf)) && blocks) break;
    }

    for (r = tr - 1; r >= 0; r--)     
    {
        attacks |= (1ULL << (r * 8 + tf));
        if ((1ULL << (r * 8 + tf)) && blocks) break;
    }
   
    //return
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





// set occupancies
U64 set_occupancy(int index, int bits_in_mask, U64 attack_mask)
{
    // occupancy map
    U64 occupancy = 0ULL;

    // loop over range of bits within mask
    for(int count = 0; count < bits_in_mask; count++) 
    {
        //get ls1b index of attack mask
        int square = get_ls1b_index(attack_mask);

        // pop ls1b in attack map
        pop_bit(attack_mask, square);

        // make sure occupancy is on board
        if (index & (1 << count))
            // populate occupancy map
            occupancy |= (1ULL << square);

    }

    return occupancy;
}



/*========================*\

      Magic Number Gen

\*========================*/


U64 find_magic_number(int square, int relevant_bits, int bishop)
{
    // init occupancies
    U64 occupancies[4096];
    
    // init attack tables
    U64 attacks[4096];
    
    // init used attacks
    U64 used_attacks[4096];
    
    // init attack mask for a current piece
    U64 attack_mask = bishop ? mask_bishop_attacks(square) : mask_rook_attacks(square);
    
    // init occupancy indicies
    int occupancy_indicies = 1 << relevant_bits;
    
    // loop over occupancy indicies
    for (int index = 0; index < occupancy_indicies; index++)
    {
        // init occupancies
        occupancies[index] = set_occupancy(index, relevant_bits, attack_mask);
        
        // init attacks
        attacks[index] = bishop ? bishop_attacks_on_the_fly(square, occupancies[index]) :
                                    rook_attacks_on_the_fly(square, occupancies[index]);
    }
    
    // test magic numbers loop
    for (int random_count = 0; random_count < 100000000; random_count++)
    {
        // generate magic number candidate
        U64 magic_number = generate_magic_number();



        // skip inappropriate magic numbers
        if (count_bits((attack_mask * magic_number) & 0xFF00000000000000ULL) < 6) continue;
        
        // init used attacks
        memset(used_attacks, 0ULL, sizeof(used_attacks));
        
        // init index & fail flag
        int index, fail;
        
        // test magic index loop
        for (index = 0, fail = 0; !fail && index < occupancy_indicies; index++)
        {
            // init magic index
            int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));
            
            // if magic index works
            if (used_attacks[magic_index] == 0ULL)
                // init used attacks
                used_attacks[magic_index] = attacks[index];
            
            // otherwise
            else if (used_attacks[magic_index] != attacks[index])
                // magic index doesn't work
                fail = 1;
        }
        

        // if magic number works
        if (!fail){
            // return it
            return magic_number;
            sleep(5);
        }
    }
    
    // if magic number doesn't work

    printf("  Magic number fails! %d \n");
    sleep(5);
    return 0ULL;
}


// init magic numbers 
void init_magic_numbers()
{
    // loop over squares

    for(int square = 0; square < 64; square++)
    {
        rook_magic_numbers[square] = find_magic_number(square, rook_relevant_bits[square], rook);
    }

    for(int square = 0; square < 64; square++)
    {
        bishop_magic_numbers[square] = find_magic_number(square, bishop_relevant_bits[square], bishop);
    }
}



void init_all(){
    init_leaper_attacks();
    //init_magic_numbers();
}


int main() {

    init_all();




    return 0;
}