#include "oslabs.h"


each process has a table of PTEs
each process has a pool frames
each page is a PTE entry in table

int process_page_access_fifo(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp) {

    int i, smallest_arrival, smallest_arrival_location;

    if(page_table[page_number].is_valid == 1) {
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count +=1;

        return page_table[page_number].frame_number;
    } else {
        if(*frame_cnt != 0) {
            (*frame_cnt)--;
            page_table[page_number].is_valid = 1;
            page_table[page_number].frame_number = frame_pool[*frame_cnt];
            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;

            return page_table[page_number].frame_number;
        } else {
            smallest_arrival = current_timestamp;
            for(i = 0; i < *table_cnt; i++) {
                if((page_table[i].is_valid == 1) && (page_table[i].arrival_timestamp < smallest_arrival)) {
                    smallest_arrival_location = i;
                    smallest_arrival = page_table[i].arrival_timestamp;
                }
            }

            page_table[smallest_arrival_location].is_valid = 0;
            page_table[page_number].frame_number = page_table[smallest_arrival_location].frame_number;
            page_table[smallest_arrival_location].frame_number = -1;
            page_table[smallest_arrival_location].arrival_timestamp = 0;
            page_table[smallest_arrival_location].last_access_timestamp = 0;
            page_table[smallest_arrival_location].reference_count = 0;
            page_table[page_number].is_valid = 1;
            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;

            return page_table[page_number].frame_number;
        }
    }
}
