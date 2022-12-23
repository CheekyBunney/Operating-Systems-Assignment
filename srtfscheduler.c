#include <stdio.h>
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
    int response_time;

}PP;

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
        loadPP(argv[1], process, count);
        sortPP(p, count);
        calcAvg(p, count);
        output(p, count);
    }
}

void calcAvg(PP p[], int count)
{
    int i;
    int currentTime = 0;
    int completed = 0;

    for (i = 0; i < count; i++)
    {
        if(process[i].arrival_time = 0)
        {

        }
    }
    
    process[0].avg_wait_time = total/count;

}

void output(PP p[], int count)
{
     // prints table
    puts(""); // Empty line
    print_table(p, count);
    puts(""); // Empty Line
    printf("Total Waiting Time      : %-2d\n", sum_waiting_time);
    printf("Average Waiting Time    : %-2.2lf\n", (double)sum_waiting_time / (double) n);
    printf("Total Turnaround Time   : %-2d\n", sum_turnaround_time);
    printf("Average Turnaround Time : %-2.2lf\n", (double)sum_turnaround_time / (double) n);

     // prints Gantt chart
    puts(""); // Empty line
    puts("          GANTT CHART          ");
    puts("          ***********          ");
    print_gantt_chart(p, count);
    return 0;
}

void parseFile(char *filename, Process p[])
{
    FILE *fp = NULL;
    Process *p = NULL;
    int i = 0;
    char buf[MAX_BUF_SIZE] = 0;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Invalid file\n");
    }
    else
    {
        while(!feof(fp))
        {
            //read all the processes from the file
            fgets(line, sizeof(line), fp);
            sscanf(line, "%d %d %d", &p->arrival_time, &p->burst_time, &p->priority);
            buf[0] = '\0';

        }
        fclose(fp);
    }
}

//bubble sort
void arrivalTimeSort(PP p[], int count)
{
    int i, pid;
    Process temp;
    int sorted;
    do
    {
        sorted = 1;
        for(i = 0; i < (count - 1 - pass) - 1); i++)
        {
            if (p[i].priority > p[i + 1].priority)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        } 
    } while ({/* condition */});
    
}



void print_table(PP p[], int n)
{
    int i;

    puts("+-----+------------+--------------+-----------------+");
    puts("| PID | Burst Time | Waiting Time | Turnaround Time |");
    puts("+-----+------------+--------------+-----------------+");

    for(i=0; i<n; i++) 
    {
        printf("| %2d  |     %2d     |      %2d      |        %2d       |\n"
               , p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time );
        puts("+-----+------------+--------------+-----------------+");
    }

}

void print_gantt_chart(PP p[], int n)
{
    int i, j;
    // print top bar
    printf(" ");
    for(i = 0; i < n; i++) 
    {
        for(j = 0; j < p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // printing process id in the middle
    for(i = 0; i < n; i++) 
    {
        for(j  =0; j < p[i].burst_time - 1; j++) printf(" ");
        printf("P%d", p[i].pid);
        for(j = 0; j < p[i].burst_time - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // print bottom bar
    for(i = 0; i < n; i++) 
    {
        for(j = 0; j < p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    // printing the time line
    printf("0");
    for(i = 0; i < n; i++) 
    {
        for(j = 0; j < p[i].burst_time; j++) printf("  ");
        if(p[i].turnaround_time > 9) printf("\b"); // backspace : remove 1 space
        printf("%d", p[i].turnaround_time);

    }
    printf("\n");

} 