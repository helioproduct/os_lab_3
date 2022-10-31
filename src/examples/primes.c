#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void *routine(void *arg)
{
    int index = *(int*)arg;
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += primes[i + index];
    }
    *(int*)arg = sum;
    return arg;
}

int main(void)
{
    pthread_t th[2];
    int i;

    for (i = 0; i < 2; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i * 5;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
        {
            perror("error creating thread!\n");
        }
    }

    int global_sum = 0;
    for (i = 0; i < 2; i++)
    {
        int *r;
        if (pthread_join(th[i], (void**)&r) != 0)
        {
            perror("Failed to join thread\n");            
        }
        global_sum += *r;
    }

    printf("%d\n", global_sum);

    return 0;
}