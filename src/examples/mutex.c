#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char **argv)
{
    pthread_t p1, p2;
    if (pthread_create(&p1, NULL, &routine, NULL) != 0)
    {
        perror("Creating thread error\n");
        return 1;
    }
    if (pthread_create(&p2, NULL, &routine, NULL) != 0)
    {
        perror("Creating thread error\n");
        return 2;
    }

    if (pthread_join(p1, NULL) != 0)    
    {
        perror("Join thread error");
        return 3;
    }
    if (pthread_join(p2, NULL) != 0)
    {
        perror("Join thread error\n");
        return 4;
    }

    printf("%d\n", mails);
    
    return 0;
}