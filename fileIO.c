#include "fileIO.h"

void parseFile(char *filename, PP p[], int count) //file I/O function 
{
    
    FILE *fp = NULL;
    int i = 0, pid = 0;
    char buf[MAX] = 0;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Invalid file\n");
    }
    else
    {
        char size[20];
        char line[120];
        char* token;
        while(!feof(fp))
        {
            //read all the processes from the file
            pid++;
            p[i].pid = pid;
            sscanf(token, "%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
            i++;
        }
        fclose(fp);
    }
}

int getCount(char *filename)
{
    int count = 0;
    FILE *fp;
    int i = 0, pid = 0;

    fp = fopen(filename, "r");
        if (fp == NULL)
        {
            printf("Error : file %s\n not found", filename);
        }

        else
        {
            while(!feof(fp))
            {
                pid = fgetc(fp);
                if(pid == '\n')
                {
                    count++;
                }
            }   
        }
    fclose(fp);
    return count;
}


