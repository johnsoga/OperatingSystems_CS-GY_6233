#include "oslabs.h"

##true is 1, false is 0

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {

    int i, bool_available_space, best_fit_size, first_guess;
    struct MEMORY_BLOCK NULLBLOCK, tmp;

    bool_available_space = 0;
    first_guess = 1
    for(i = 0; i < *map_cnt; i++) {
        if((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            if(first_guess) {
                best_fit_size = i;
                first_guess = 0;
            }
            bool_available_space = 1;
            if(memory_map[i].segment_size < memory_map[best_fit_size]) {
                best_fit_size = i;
            }
        }
    }

    if(!bool_available_space) {
        NULLBLOCK = {0,0,0,0};
        return NULLBLOCK;
    }

    if(memory_map[best_fit_size].segment_size == request_size) {
        return memory_map[best_fit_size];
    } else {
        tmp = {0,0,0,0};
        tmp.segment_size = memory_map[best_fit_size].segment_size - request_size;
        tmp.process_id = 0;
        tmp.end_address = memory_map[best_fit_size].end_address;
        memory_map[best_fit_size].end_address = memory_map[best_fit_size].start_address + request_size;
        tmp.start_address = memory_map[best_fit_size].end_address + 1;
        memory_map[best_fit_size].segment_size = request_size;
        memory_map[best_fit_size].process_id = process_id;

        memory_map[*map_cnt] = tmp;
        (*map_cnt)++;

        return memory_map[best_fit_size];
    }
}
