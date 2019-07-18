#include "oslabs.h"

int isNULLPCB(struct PCB process);

int isNULLPCB(struct PCB process) {

    if (process.process_id == 0 && process.arrival_timestamp == 0 && process.total_bursttime == 0 && process.execution_starttime == 0 && process.execution_endtime == 0 && process.remaining_bursttime == 0 && process.process_priority == 0) {
        return 1;
    }

    return 0;
}
struct PCB handle_process_arrival_pp(struct PCB readyQueue[], int queueCount, struct PCB currProcess, struct PCB nextProcess, int currTime) {

    if(!isNULLPCB(currProcess)) {
        if(nextProcess.process_priority >= currProcess.process_priority) {
            nextProcess.execution_starttime = 0;
            nextProcess.execution_endtime = 0;
            nextProcess.remaining_bursttime = nextProcess.total_bursttime;
            ready_queue[queue_cnt] = nextProcess;

            return currProcess;
        } else {

            nextProcess.execution_starttime = currTime;
            nextProcess.execution_endtime = currTime + currProcess.total_bursttime;
            nextProcess.remaining_bursttime = currProcess.total_bursttime;
            currProcess.execution_endtime = 0;

            ready_queue[queue_cnt] = currProcess;

            return nextProcess;
        }
    }

    nextProcess.execution_starttime = currTime;
    nextProcess.execution_endtime = currTime + currProcess.total_bursttime;
    nextProcess.remaining_bursttime = currProcess.total_bursttime;

    return nextProcess;
}
