#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS 4

pthread_mutex_t mutex;

void *routine(void *args)
{
    if (pthread_mutex_trylock(&mutex) == 0) 
    {
        printf("Got lock\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    } 
    else 
    {
        printf("Didn't get lock\n");
    }
    return NULL;
}

int main(void)
{   
    pthread_t th[THREADS];

    for (int i = 0; i < THREADS; i++)
    {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
        {
            perror("error creating thread\n");
        }
    }

    for (int i = 0; i < THREADS; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("error joining thread\n");
        }
    }

    return 0;
}