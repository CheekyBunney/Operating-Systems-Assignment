#include "ppscheduler.h"
#include "fileIO.h"

void print_table(PP p[], int count);
void print_gantt_chart(PP p[], int count);

int main(int argc, char *argv[])
{
    PP* p;
    int count, i;
    if(argc != 2)
    {
        printf("Error: invalid input %d\n", argc);
        printf("try ./ppscheduler ppInput.txt\n");
    }
    else
    {
        count = getCount(argv[i]);
        p = (PP*)malloc(sizeof(PP) * count);
        parseFile(argv[1], p, count);
        calcAvg(p, count);
        output(p, count);
    }
    return 0;
}

void calcAvg(PP p[], int count) //function for all process time calculations 
{   
    int i, j;
    int current_time = 0;
    int completed = 0;
    int prev = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int burstTime[count]; 
    
    /*queue = (int*)malloc(sizeof(int)*count);*/

    while(completed != count) 
    {       
        int index = -1;
        int priority = -1;
        for (i = 0; i < count; i++)
        {
            if(p[i].arrival_time <= current_time && p[i].isComplete == 0) /*check for the process with the maximum priority time in the ready queue at current time*/
            {
                if(p[i].priority > priority) //the current process has a higher priority than the maximum priority process in the ready queue
                {
                    priority = p[i].priority;                        // set current process' priority as the new maximum priority
                    index = i;                                  // set the current process as the new highest priority process index
                }

                if(p[i].priority == priority) //the current process has the same priority as the maximum priority process in the ready queue
                {
                    if(p[i].arrival_time < p[index].arrival_time) //the current process has an earlier arrival time than the process
                    {                                             // with the earliest arrival time in the ready queue
                        priority = p[i].priority;                      
                        index = i;                                
                    }
                }
            }
        }

        if(index != -1)
        {
            if(p[index].burst_time == 0) //the current process has completed its burst time
            {
                p[index].start_time = current_time; //set the process' start time as the current time
            }

            p[index].burst_time--;
            current_time++;
            prev = current_time;

            if(p[index].burst_time == 0) //current process has complete its running time 
            {
                p[index].completion_time = current_time; //set the process' comepletion time as the current time
                p[index].turnaround_time = p[index].completion_time - p[i].arrival_time; // set process' turnaround time as its completion time subtracted by its arrival time
                p[index].waiting_time = p[index].turnaround_time - p[index].burst_time; //set process' waiting time as its turnaround time subtracted by its burst time

                total_turnaround_time += p[index].turnaround_time; //add current process' turnaround time to the total
                total_waiting_time += p[index].waiting_time; //add current process' waiting time to the total

                p[index].isComplete = 1; //set current process as completed
                completed++; //loop
            }
        }
        else
        {
            current_time++;
        }
    }
}

void burstTimeReset(PP p[], int count)
{

}

void arrivalTimeSort(PP p[], int count) //selection sort to sort arrival time 
{
    int pass = 0;
    int i;
    PP temp;
    int sorted = 0;
    do
    {
        sorted = 1;
        for(i = 0; i < (count - 1 - pass) - 1; i++)
        {

            if (p[i].priority > p[i + 1].priority)
            {
                temp = p[i];
                p[i] = p[i + 1];
                p[i + 1] = temp;
            }
        } 
        pass++;
    } while (!sorted == 1);
}

void output(PP p[], int count) //function for terminal output
{
    int i;
    float total_waiting_time, total_turnaround_time, avg_waiting_time, avg_turnaround_time;
     
     // prints table
    puts(""); // Empty line
    print_table(p, count);
    puts(""); // Empty Line
    printf("Total Waiting Time      : %-2d\n", total_waiting_time);
    printf("Average Waiting Time    : %-2.2lf\n", (double)avg_waiting_time / (double) count);
    printf("Total Turnaround Time   : %-2d\n", total_turnaround_time);
    printf("Average Turnaround Time : %-2.2lf\n", (double)avg_turnaround_time / (double) count);

     // prints Gantt chart
    puts(""); // Empty line
    puts("          GANTT CHART          ");
    puts("          ***********          ");
    print_gantt_chart(p, count);
    return 0;
}

void print_table(PP p[], int count) 
{
    int i;
    puts("+-----+--------------+------------+----------+------------+-----------------+-----------------+--------------+");
    puts("| PID | Arrival Time | Burst Time | Priority | Start Time | Completion Time | Turnaround Time | Waiting Time |");
    puts("+-----+--------------+------------+----------+------------+-----------------+-----------------+--------------+");

    for(i = 0; i < count; i++) 
    {
        printf("| %2d |     %2d      |    %2d     |   %2d    |    %2d     |       %2d       |       %2d       |      %2d     |\n"
               ,p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority, p[i].start_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
        printf("+-----+--------------+------------+----------+------------+-----------------+-----------------+--------------+");
    }

}

void print_gantt_chart(PP p[], int count)
{
    int i, j;
    // print top bar
    printf(" ");
    for(i = 0; i < count; i++) 
    {
        for(j = 0; j < p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // printing process id in the middle
    for(i = 0; i < count; i++) 
    {
        for(j = 0; j < p[i].burst_time - 1; j++) printf(" ");
        printf("P%d", p[i].pid);
        for(j = 0; j < p[i].burst_time - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // print bottom bar
    for(i = 0; i < count; i++) 
    {
        for(j = 0; j < p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    // printing the time line
    printf("0");
    for(i = 0; i < count; i++) 
    {
        for(j = 0; j < p[i].burst_time; j++) printf("  ");
        if(p[i].turnaround_time > 9) printf("\b"); // backspace : remove 1 space
        printf("%d", p[i].turnaround_time);

    }
    printf("\n");

} 