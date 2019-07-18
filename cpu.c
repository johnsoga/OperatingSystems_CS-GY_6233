#include "oslabs.h"

int isNULLPCB(struct PCB process);

int isNULLPCB(struct PCB process) {

    if (process.process_id == 0 && process.arrival_timestamp == 0 && process.total_bursttime == 0 && process.execution_starttime == 0 && process.execution_endtime == 0 && process.remaining_bursttime == 0 && process.process_priority == 0) {
        return 1;
    }

    return 0;
}
struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp) {

    if(!isNULLPCB(current_process)) {
        if(new_process.process_priority >= current_process.process_priority) {
            new_process.execution_starttime = 0;
            new_process.execution_endtime = 0;
            new_process.remaining_bursttime = new_process.total_bursttime;
            ready_queue[*queue_cnt] = new_process;

            return current_process;
        } else {

            new_process.execution_starttime = timestamp;
            new_process.execution_endtime = timestamp + current_process.total_bursttime;
            new_process.remaining_bursttime = current_process.total_bursttime;
            current_process.execution_endtime = 0;

            ready_queue[*queue_cnt] = current_process;

            return new_process;
        }
    }

    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = timestamp + current_process.total_bursttime;
    new_process.remaining_bursttime = current_process.total_bursttime;

    return new_process;
}
