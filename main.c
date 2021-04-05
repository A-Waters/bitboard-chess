#include "init.h"





int main() {

    init_all();

    U64 occupancy = 0ULL;
    set_bit(occupancy, c5);

    print_bitboard(occupancy);

    print_bitboard(get_bishop_attacks(d4, occupancy));

    return 0;
}