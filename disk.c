#include "oslabs.h"
#include <stdio.h>

int isNULLRCB(struct RCB request);

int isNULLRCB(struct RCB request) {

    if (request.request_id == 0 && request.arrival_timestamp == 0 && request.cylinder == 0 && request.address == 0 && request.process_id == 0) {
        return 1;
    }

    return 0;
}
struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp) {

    if(isNULLRCB(current_request)) {
        return new_request;
    } else {
        request_queue[*queue_cnt] = new_request;
        (*queue_cnt)++;
        return current_request;
    }
}
struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp) {

    if(isNULLRCB(current_request)) {
        return new_request;
    } else {
        request_queue[*queue_cnt] = new_request;
        (*queue_cnt)++;
        return current_request;
    }
}
struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp) {

    return current_request;
}
struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX],int *queue_cnt) {

    struct RCB NULLRCB, tmp;
    int i, shortest_arrival_time, shortest_arrival_location;

    if(*queue_cnt == 0) {
        NULLRCB.request_id = 0;
        NULLRCB.arrival_timestamp = 0;
        NULLRCB.cylinder = 0;
        NULLRCB.address = 0;
        NULLRCB.process_id = 0;

        return NULLRCB;
    }

    shortest_arrival_time = request_queue[0].arrival_timestamp;
    shortest_arrival_location = 0;
    for(i = 1; i < *queue_cnt; i++) {
        if(request_queue[i].arrival_timestamp < shortest_arrival_time) {
            shortest_arrival_time = request_queue[i].arrival_timestamp;
            shortest_arrival_location = i;
        }
    }

    (*queue_cnt)--;
    return request_queue[shortest_arrival_location];
}
struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX],int  *queue_cnt, int current_cylinder, int scan_direction) {

    return request_queue[0];
}
struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt,int current_cylinder) {

    struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt,int current_cylinder);
}
