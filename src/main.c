#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS_AMOUNT 8

int mails = 0;
pthread_mutex_t mutex;

void* routine()
{
    for (int i = 0; i < 10000000; i++) 
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char **argv)
{
    pthread_t th[THREADS_AMOUNT];
    pthread_mutex_init(&mutex, NULL);   

    for (int i = 0; i < THREADS_AMOUNT; i++)
    {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0)
        {
            perror("creating thread error\n");
            return i;
        }
        printf("Thread %d has started\n",  i);
    }

    for (int i = 0; i < THREADS_AMOUNT; i++) 
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            return 2 * i;
        }
        printf("Thread %d has finished\n", i);
    }

    pthread_mutex_destroy(&mutex);
    printf("Number of mails = %d\n", mails);
    
    return 0;
}