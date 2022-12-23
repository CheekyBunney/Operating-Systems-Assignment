#ifndef _PPSCHEDULER_H
#define _PPSCHEDULER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;

    int isComplete;

    float avg_waiting_time;
    float avg_turnaround_time;
}PP;

void calcAvg(PP*, int count);
void output(PP*, int count);

#include "fileIO.h"
void parseFile(char*, PP*[], int);

#endif