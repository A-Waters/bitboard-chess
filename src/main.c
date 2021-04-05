#include <chess_engine/init.h>

#include <chess_engine/board.h>

int main() {

    init_all();

    FEN_parse(start_position);
    print_board();

    return 0;
}