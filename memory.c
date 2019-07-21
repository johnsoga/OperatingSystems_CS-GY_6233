#include "oslabs.h"

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {

    int i, bool_available_space, best_fit_size, first_guess;
    struct MEMORY_BLOCK NULLBLOCK, tmp;

    bool_available_space = 0;
    first_guess = 1;
    for(i = 0; i < *map_cnt; i++) {
        if((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            if(first_guess) {
                best_fit_size = i;
                first_guess = 0;
            }
            bool_available_space = 1;
            if(memory_map[i].segment_size < memory_map[best_fit_size].segment_size) {
                best_fit_size = i;
            }
        }
    }

    if(!bool_available_space) {
        NULLBLOCK.start_address = 0;
        NULLBLOCK.end_address = 0;
        NULLBLOCK.segment_size = 0;
        NULLBLOCK.process_id = 0;

        return NULLBLOCK;
    }

    if(memory_map[best_fit_size].segment_size == request_size) {
        return memory_map[best_fit_size];
    } else {
        tmp.segment_size = memory_map[best_fit_size].segment_size - request_size;
        tmp.process_id = 0;
        tmp.end_address = memory_map[best_fit_size].end_address;
        memory_map[best_fit_size].end_address = memory_map[best_fit_size].start_address + request_size-1;
        tmp.start_address = memory_map[best_fit_size].end_address + 1;
        memory_map[best_fit_size].segment_size = request_size;
        memory_map[best_fit_size].process_id = process_id;

        memory_map[*map_cnt] = tmp;
        (*map_cnt)++;

        return memory_map[best_fit_size];
    }
}
struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {

    int i, bool_available_space, first_fit_size;
    struct MEMORY_BLOCK NULLBLOCK, tmp;

    bool_available_space = 0;
    for(i = 0; i < *map_cnt; i++) {
        if((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            bool_available_space = 1;
            first_fit_size = i;
            break;
        }
    }

    if(!bool_available_space) {
        NULLBLOCK.start_address = 0;
        NULLBLOCK.end_address = 0;
        NULLBLOCK.segment_size = 0;
        NULLBLOCK.process_id = 0;

        return NULLBLOCK;
    }

    if(memory_map[first_fit_size].segment_size == request_size) {
        return memory_map[first_fit_size];
    } else {
        tmp.segment_size = memory_map[first_fit_size].segment_size - request_size;
        tmp.process_id = 0;
        tmp.end_address = memory_map[first_fit_size].end_address;
        memory_map[first_fit_size].end_address = memory_map[first_fit_size].start_address + request_size-1;
        tmp.start_address = memory_map[first_fit_size].end_address + 1;
        memory_map[first_fit_size].segment_size = request_size;
        memory_map[first_fit_size].process_id = process_id;

        memory_map[*map_cnt] = tmp;
        (*map_cnt)++;

        return memory_map[first_fit_size];

    }
}
struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK   memory_map[MAPMAX],int *map_cnt, int process_id, int last_address) {

    int i, bool_available_space, next_fit_size;
    struct MEMORY_BLOCK NULLBLOCK, tmp;

    bool_available_space = 0;
    for(i = last_address; i < *map_cnt; i++) {
        if((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) {
            bool_available_space = 1;
            next_fit_size = i;
            break;
        }
    }

    if(!bool_available_space) {
        NULLBLOCK.start_address = 0;
        NULLBLOCK.end_address = 0;
        NULLBLOCK.segment_size = 0;
        NULLBLOCK.process_id = 0;

        return NULLBLOCK;
    }

    if(memory_map[next_fit_size].segment_size == request_size) {
        return memory_map[next_fit_size];
    } else {
        tmp.segment_size = memory_map[next_fit_size].segment_size - request_size;
        tmp.process_id = 0;
        tmp.end_address = memory_map[next_fit_size].end_address;
        memory_map[next_fit_size].end_address = memory_map[next_fit_size].start_address + request_size-1;
        tmp.start_address = memory_map[next_fit_size].end_address + 1;
        memory_map[next_fit_size].segment_size = request_size;
        memory_map[next_fit_size].process_id = process_id;

        memory_map[*map_cnt] = tmp;
        (*map_cnt)++;

        return memory_map[next_fit_size];
    }
}
struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {

    struct MEMORY_BLOCK tmp;

    return tmp;
}
void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt) {

    return;
}
