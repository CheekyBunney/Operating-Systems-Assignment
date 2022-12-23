#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
// compiling: gcc task3_final1.c -lpthread
// run: ./a.out

char buffer1[10] =  "NULL"; // file input name
double buffer2[2];
int input_done = 0; // not having user input yet
int buffer2_done = 0; //buffer2 can be written
int quit = 0;
// thread condition variable(must be initialized)
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
// mutex
pthread_mutex_t lock =  PTHREAD_MUTEX_INITIALIZER;
void *pp()
{
    pthread_mutex_lock(&lock);
    if(input_done==0)
    {
        //printf("pp waiting signal from parent thread\n");
        pthread_cond_wait(&cond, &lock);
        //printf("pp receives signal from parent thread\n");
    }
    pthread_mutex_unlock(&lock);
    // deal with input

    
    if (strcmp(buffer1, "QUIT") == 0)
    {
        //printf("buffer1 == QUIT\n");
        printf("PP: terminate\n");
        quit += 1;
        pthread_exit(NULL);
    }
    else // not "QUIT"
    {
        /* pp calculation*/
        double aver_turnaround;
        double aver_waiting;

        /* YOUR CODE OF CALCULATION*/

        // assign results
        aver_turnaround = 0.5;
        aver_waiting = 0.5;
        
        /* write results to buffer2*/
        while (1)
        {
            if (buffer2_done == 0)
            {
                pthread_mutex_lock(&lock);
                buffer2[0]=aver_turnaround;
                buffer2[1]=aver_waiting;
                buffer2_done = 1; // means thread 1 writes to buffer2.

                pthread_cond_broadcast(&cond);
                pthread_mutex_unlock(&lock);
                break;
            }
        }
    }
    return NULL;
}
void *srtf()
{
    //printf("srtf created, input_done = %d\n", input_done);
    pthread_mutex_lock(&lock);
    if(input_done==0)
    {
        //printf("srtf waiting signal from parent thread\n");
        pthread_cond_wait(&cond, &lock);
        //printf("srtf receives signal from parent thread\n");
    }
    pthread_mutex_unlock(&lock);

    
    if (strcmp(buffer1, "QUIT") == 0)
    {
        //printf("buffer1 == QUIT\n");
        printf("SRTF: terminate\n");
        pthread_exit(NULL);
    }
    else // not "QUIT"
    {
        /* srtf calculation*/

        double aver_turnaround;
        double aver_waiting;

        /* YOUR CODE OF CALCULATION*/

        // assign results
        aver_turnaround = 2.5;
        aver_waiting = 2.5;

        
        /* write results to buffer2*/
        while (1)
        {
            if (buffer2_done == 0)
            {
                pthread_mutex_lock(&lock);
                buffer2[0]=aver_turnaround;
                buffer2[1]=aver_waiting;
                buffer2_done = 2; // means thread 2 writes to buffer2.
                //pthread_cond_signal(&cond);
                //sleep(1);
                pthread_cond_broadcast(&cond);
                pthread_mutex_unlock(&lock);
                break;
            }
        }

    }
    return NULL;
}

int main()
{

    while (1)
    {
        pthread_t ptid[2];
        int error[2];
        // mutex init
        if (pthread_mutex_init(&lock, NULL) != 0) 
        {
            printf("\n mutex initialization failed\n");
            return 1;
        }
        // create threads
        error[0] = pthread_create(&(ptid[0]), NULL, &pp, NULL);
        error[1] = pthread_create(&(ptid[1]), NULL, &srtf, NULL);
        // check if threads created successfully
        if (error[0] != 0)
            printf("\nThread failed to be created : [%s]", strerror(error[0]));
        if (error[1] != 0)
            printf("\nThread failed to be created : [%s]", strerror(error[1]));
        //========
        // The parent thread waits for an input from the user.
        //========
        printf("Enter input file name:");
        gets(buffer1);
        
        if(strcmp(buffer1, "QUIT")==0)
        {
            pthread_mutex_lock(&lock);
            pthread_cond_broadcast(&cond);//send signal to child threads
            pthread_mutex_unlock(&lock);
            pthread_join(ptid[0], NULL);
            pthread_join(ptid[1], NULL);
            return 0;
        }

        pthread_mutex_lock(&lock);
        input_done = 2; //ready for 2 threads.
        pthread_cond_broadcast(&cond); //send signal to child threads
        pthread_mutex_unlock(&lock);

        // waiting a thread writes results to buffer2
        int print_count = 0; // 0 pair of results has been printed. 
        while (print_count < 2) // ################## 2
        {
            if (buffer2_done == 0) ////
            {
                pthread_mutex_lock(&lock);
                pthread_cond_wait(&cond, &lock);

                // when get signal
                // check which thread send the signal. 
                if (buffer2_done == 1)
                {
                    printf("PP: the average turnaround time = %lf, the average waiting time = %lf\n", buffer2[0], buffer2[1]);
                    buffer2_done=0;
                    print_count+=1;
                }
                if (buffer2_done == 2)
                {
                    printf("SRTF: the average turnaround time = %lf, the average waiting time = %lf\n", buffer2[0], buffer2[1]);
                    buffer2_done=0;
                    print_count+=1;
                }
                pthread_mutex_unlock(&lock); 
            }
        }
        input_done = 0;
        pthread_join(ptid[0], NULL);
        pthread_join(ptid[1], NULL);
    }

        

    
    pthread_mutex_destroy(&lock);
    return 0;
}