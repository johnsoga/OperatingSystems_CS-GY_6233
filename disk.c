#include "oslabs.h"

int isNULLRCB(struct RCB request);

int isNULLRCB(struct RCB request) {

    if (request.request_id == 0 && request.arrival_timestamp == 0 && request.cylinder == 0 && request.address == 0 && request.process_id == 0) {
        return 1;
    }

    return 0;
}
struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp) {

    if(!isNULLRCB(current_request)) {
        return new_request;
    } else {
        request_queue[*queue_cnt] = new_request;
        (*queue_cnt)++;
        return current_request;
    }
}
