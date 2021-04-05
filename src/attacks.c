#include <chess_engine/attacks.h>

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
        if ((bitboard >> 7) & not_files.not_a_file) attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & not_files.not_h_file) attacks |= (bitboard >> 9);
    }

    //black pawns
    else 
    {
        if ((bitboard << 7) & not_files.not_h_file) attacks |= (bitboard << 7);
        if ((bitboard << 9) & not_files.not_a_file) attacks |= (bitboard << 9);
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
    if ((bitboard >> 17) & not_files.not_h_file) attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & not_files.not_a_file) attacks |= (bitboard >> 15);
    if ((bitboard >> 10) & not_files.not_hg_file) attacks |= (bitboard >> 10);
    if ((bitboard >> 6) & not_files.not_ab_file) attacks |= (bitboard >> 6);


    if ((bitboard << 17) & not_files.not_a_file) attacks |= (bitboard << 17);
    if ((bitboard << 15) & not_files.not_h_file) attacks |= (bitboard << 15);
    if ((bitboard << 10) & not_files.not_ab_file) attacks |= (bitboard << 10);
    if ((bitboard << 6) & not_files.not_hg_file) attacks |= (bitboard << 6);



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

    if ((bitboard >> 7) & not_files.not_a_file) attacks |= (bitboard >> 7);
    if ((bitboard >> 8)) attacks |= (bitboard >> 8);
    if ((bitboard >> 9) & not_files.not_h_file) attacks |= (bitboard >> 9);

    if ((bitboard >> 1) & not_files.not_h_file) attacks |= (bitboard >> 1);
    if ((bitboard << 1) & not_files.not_a_file) attacks |= (bitboard << 1);

    if ((bitboard << 7) & not_files.not_h_file) attacks |= (bitboard << 7);
    if ((bitboard << 8)) attacks |= (bitboard << 8);
    if ((bitboard << 9) & not_files.not_a_file) attacks |= (bitboard << 9);



    //return attack map
    return attacks;
}


U64 mask_bishop_attacks(int square)
{
    //result attack bitboard
    U64 attacks = 0ULL;

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
        if ((1ULL << (r * 8 + f) & blocks)) break;
    }
    
    for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++)  
    {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f) & blocks)) break;
    }

    for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++)  
    {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f) & blocks)) break;
    }

    for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--)  
    {
        attacks |= (1ULL << (r * 8 + f));
        if ((1ULL << (r * 8 + f) & blocks)) break;
    }

    //return
    return attacks;

}


// generate bishop attacks on the fly
U64 rook_attacks_on_the_fly(int square, U64 blocks)
{
    //result attack bitboard
    U64 attacks = 0ULL;


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




U64 get_bishop_attacks(int square, U64 occupancy)
{
    // get bishop attacks assuming current board occupancy 
    occupancy &= attack_mask.bishop_mask[square];
    occupancy *= magic_numbers.bishop_magic_numbers[square];

    occupancy >>= (64 - bishop_relevant_bits[square]);

    return current_attacks.bishop_attacks[square][occupancy];
}


U64 get_rook_attacks(int square, U64 occupancy)
{
    // get bishop attacks assuming current board occupancy 
    occupancy &= attack_mask.rook_mask[square];
    occupancy *= magic_numbers.rook_magic_numbers[square];

    occupancy >>= (64 - rook_relevant_bits[square]);

    return current_attacks.rook_attacks[square][occupancy];
}
