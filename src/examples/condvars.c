#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define THREADS 2


pthread_mutex_t fuel_mutex;
pthread_cond_t fuel_cond;
int fuel = 0;


void *fuel_filling(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&fuel_mutex);
        fuel += 15;
        printf("Filling fuel... %d\n", fuel);
        pthread_mutex_unlock(&fuel_mutex);
        pthread_cond_signal(&fuel_cond);
        sleep(1);
    }
}

void *car(void *arg)
{
    pthread_mutex_lock(&fuel_mutex);

    while (fuel < 40)
    {
        sleep(1);
        pthread_cond_wait(&fuel_cond, &fuel_mutex);
        printf("No fuel (%d)\n", fuel);
    }

    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&fuel_mutex);
}

int main(int argc, char **argv)
{
    pthread_t th[THREADS];

    pthread_mutex_init(&fuel_mutex, NULL);
    pthread_cond_init(&fuel_cond, NULL);
    
    for (int i = 0; i < THREADS; i++)
    {
        if (i == 1) 
        {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
            {
                perror("error creating thread\n");
                return i;
            }
        }
        else
        {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0) 
            {
                perror("error creating thread\n");
                return i;
            }
        }
    }

    for (int i = 0; i < THREADS; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("thread join error\n");
            return 2 * i;
        }
    }

    pthread_mutex_destroy(&fuel_mutex);
    pthread_cond_destroy(&fuel_cond);

    return 0;
}