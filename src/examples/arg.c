#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS 10

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void *routine(void *arg)
{
    sleep(1);
    int index = *(int*) arg;
    free(arg);
    printf("%d ", primes[index]);
}

int main(int argc, char **argv)
{
    pthread_t th[THREADS];
    for (int i = 0 ; i < THREADS; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
        {
            perror("thread create error\n");
            return i;
        }
    }
    
    for (int i = 0 ; i < THREADS; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("thread join error\n");
            return i;
        }
    }
    return 0;
}
