#include "oslabs.h"
#include <stdio.h>


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

    struct PCB NULLPCB, tmp;
    int i, highest_priority, highest_location;

    if(*queue_cnt == 0) {
        NULLPCB.process_id = 0;
        NULLPCB.arrival_timestamp = 0;
        NULLPCB.total_bursttime = 0;
        NULLPCB.execution_starttime = 0;
        NULLPCB.execution_endtime = 0;
        NULLPCB.remaining_bursttime = 0;
        NULLPCB.process_priority = 0;

        return NULLPCB;
    }

    highest_priority = ready_queue[0].process_priority;
    highest_location = 0;
    for(i = 1; i < *queue_cnt; i++) {
        if(!(highest_priority < ready_queue[i].process_priority)) {
            highest_priority = ready_queue[i].process_priority;
            highest_location = i;
        }
    }

    tmp = ready_queue[highest_location];
    for(i = highest_location; i < *queue_cnt-1; i++) {
        ready_queue[i] = ready_queue[i+1];
    }
    *queue_cnt-=1;

    tmp.execution_starttime = timestamp;
    tmp.execution_endtime = timestamp + tmp.remaining_bursttime;
    return tmp;
}
struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp) {

    struct PCB NULLPCB, tmp;
    int i, smallest_burst, smallest_burst_location;

    if(*queue_cnt == 0) {
        NULLPCB.process_id = 0;
        NULLPCB.arrival_timestamp = 0;
        NULLPCB.total_bursttime = 0;
        NULLPCB.execution_starttime = 0;
        NULLPCB.execution_endtime = 0;
        NULLPCB.remaining_bursttime = 0;
        NULLPCB.process_priority = 0;

        return NULLPCB;
    }

    smallest_burst = ready_queue[0].remaining_bursttime;
    smallest_burst_location = 0;
    for(i = 1; i < *queue_cnt; i++) {
        if(!(smallest_burst < ready_queue[i].remaining_bursttime)) {
            smallest_burst = ready_queue[i].remaining_bursttime;
            smallest_burst_location = i;
        }
    }

    tmp = ready_queue[smallest_burst_location];
    for(i = smallest_burst_location; i < *queue_cnt-1; i++) {
        ready_queue[i] = ready_queue[i+1];
    }
    *queue_cnt-=1;

    tmp.execution_starttime = timestamp;
    tmp.execution_endtime = timestamp + tmp.remaining_bursttime;
    return tmp;
}
struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int time_stamp, int time_quantum) {

    struct PCB NULLPCB, tmp;
    int i, arrival_time, arrival_time_location;

    if(*queue_cnt == 0) {
        NULLPCB.process_id = 0;
        NULLPCB.arrival_timestamp = 0;
        NULLPCB.total_bursttime = 0;
        NULLPCB.execution_starttime = 0;
        NULLPCB.execution_endtime = 0;
        NULLPCB.remaining_bursttime = 0;
        NULLPCB.process_priority = 0;

        return NULLPCB;
    }

    arrival_time = ready_queue[0].arrival_timestamp;
    arrival_time_location = 0;
    for(i = 1; i < *queue_cnt; i++) {
        if(!(arrival_time < ready_queue[i].arrival_timestamp)) {
            arrival_time = ready_queue[i].arrival_timestamp;
            arrival_time_location = i;
        }
    }

    tmp = ready_queue[arrival_time_location];
    for(i = arrival_time_location; i < *queue_cnt-1; i++) {
        ready_queue[i] = ready_queue[i+1];
    }
    *queue_cnt-=1;

    tmp.execution_starttime = timestamp;
    if(tmp.remaining_bursttime < time_quantum) {
        tmp.execution_endtime = timestamp + tmp.remaining_bursttime;
    } else {
        tmp.execution_endtime = timestamp + time_quantum;
    }

    return tmp;
}
