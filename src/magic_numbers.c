#include <chess_engine/magic_numbers.h>

#include <string.h>
#include <stdio.h>
#include <unistd.h>





unsigned int random_state = 1804289383;

magic_nums magic_numbers = {

    // random state
    1804289383,

    //rook numbers
    {
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
    },

    // bishop numbers
    {
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
    }

};

U64 generate_magic_number()
{
    return generate_random_U64_number() & generate_random_U64_number() & generate_random_U64_number();
}


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
