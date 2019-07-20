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
            (*queue_cnt)++;

            return current_process;
        } else {
            new_process.execution_starttime = timestamp;
            new_process.execution_endtime = timestamp + new_process.total_bursttime;
            new_process.remaining_bursttime = new_process.total_bursttime;
            current_process.execution_endtime = 0;
            ready_queue[*queue_cnt] = current_process;
            (*queue_cnt)++;

            return new_process;
        }
    }

    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = timestamp + new_process.total_bursttime;
    new_process.remaining_bursttime = new_process.total_bursttime;

    return new_process;
}
struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum) {

    if(!isNULLPCB(current_process)) {
        new_process.execution_starttime = 0;
        new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;
        ready_queue[*queue_cnt] = new_process;
        (*queue_cnt)++;

        return current_process;
    }

    new_process.execution_starttime = timestamp;

    if(new_process.total_bursttime < time_quantum) {
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
    } else {
        new_process.execution_endtime = timestamp + time_quantum;
    }

    new_process.remaining_bursttime = new_process.total_bursttime;

    return new_process;
}
struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp) {

    if(!isNULLPCB(current_process)) {
        if(!(new_process.total_bursttime < current_process.remaining_bursttime)) {
            new_process.execution_starttime = 0;
            new_process.execution_endtime = 0;
            new_process.remaining_bursttime = new_process.total_bursttime;
            ready_queue[*queue_cnt] = new_process;
            (*queue_cnt)++;

            return current_process;
        } else {
            new_process.execution_starttime = time_stamp;
            new_process.execution_endtime = time_stamp + new_process.total_bursttime;
            new_process.remaining_bursttime = new_process.total_bursttime;
            current_process.execution_starttime = 0;
            current_process.execution_endtime = 0;
            ready_queue[*queue_cnt] = current_process;
            (*queue_cnt)++;

            return new_process;
        }
    }

    new_process.execution_starttime = time_stamp;
    new_process.execution_endtime = time_stamp + new_process.total_bursttime;
    new_process.remaining_bursttime = new_process.total_bursttime;

    return new_process;
}
struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp) {

    struct PCB NULLPCB;
    int i, max;

    if(*queue_cnt = 0) {
        NULLPCB.process_id = 0;
        NULLPCB.arrival_timestamp = 0;
        NULLPCB.total_bursttime = 0;
        NULLPCB.execution_starttime = 0;
        NULLPCB.execution_endtime = 0;
        NULLPCB.remaining_bursttime = 0;
        NULLPCB.process_priority = 0;

        return NULLPCB;
    }

    max = 0;
    for(i = 0; i < *queue_cnt; i++) {
        if(ready_queue[max].process_priority < ready_queue[i].process_priority) {
            max = i;
        }
    }

    for(i = max; i < *queue_cnt-1; i++) {
        ready_queue[i] = ready_queue[i+1];
    }

    //*queue_cnt+=1;
    ready_queue[max].execution_starttime = timestamp;
    ready_queue[max].execution_endtime = timestamp + ready_queue[max].remaining_bursttime;
    return ready_queue[max];
}
struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp) {

    return ready_queue[0];
}
struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int time_stamp, int time_quantum) {

    return ready_queue[0];
}
