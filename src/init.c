#include <chess_engine/init.h>

// init magic numbers 
void init_magic_numbers()
{
    // loop over squares

    for(int square = 0; square < 64; square++)
    {
        magic_numbers.rook_magic_numbers[square] = find_magic_number(square, rook_relevant_bits[square], rook);
    }

    for(int square = 0; square < 64; square++)
    {
        magic_numbers.bishop_magic_numbers[square] = find_magic_number(square, bishop_relevant_bits[square], bishop);
    }
}


void init_slider_attacks(int bishop)
{

    for (int square = 0; square < 64; square++)
    {
        attack_mask.bishop_mask[square] = mask_bishop_attacks(square);
        attack_mask.rook_mask[square] = mask_rook_attacks(square);


        // init current mask 
        U64 attack_mask_var = bishop ? attack_mask.bishop_mask[square] : attack_mask.rook_mask[square];

        int relevant_bits_count = count_bits(attack_mask_var);

        int occupancy_indicies = (1 << relevant_bits_count);



        // loop over occupancy_indicies

        for (int index = 0; index < occupancy_indicies; index++){

            if (bishop){
                U64 occupancy = set_occupancy(index, relevant_bits_count, attack_mask_var);

                int magic_index = (occupancy * magic_numbers.bishop_magic_numbers[square]) >> (64 - bishop_relevant_bits[square]);

                current_attacks.bishop_attacks[square][magic_index] = bishop_attacks_on_the_fly(square, occupancy);
            }

            else
            {
                U64 occupancy = set_occupancy(index, relevant_bits_count, attack_mask_var);

                int magic_index = (occupancy * magic_numbers.rook_magic_numbers[square]) >> (64 - rook_relevant_bits[square]);

                current_attacks.rook_attacks[square][magic_index] = rook_attacks_on_the_fly(square, occupancy);
            }

        }
        
    }



}


//init leaper pieces attacks
void init_leaper_attacks(){

    //loop over board

    for(int square = 0; square < 64; square++){
        //init pawn attacks 

        current_attacks.pawn_attacks[white][square] = mask_pawn_attacks(white, square);
        current_attacks.pawn_attacks[black][square] = mask_pawn_attacks(black, square);


        //init knight attacks 
        current_attacks.knight_attacks[square] = mask_knight_attacks(square);


        //init king attacks 
        current_attacks.king_attacks[square] = mask_king_attacks(square);

    }

}

void init_all(){
    init_leaper_attacks();
    //init_magic_numbers();
    init_slider_attacks(bishop);
    init_slider_attacks(rook);
}
