#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>


typedef struct arg_struct {
    char *string;
    char *substring;
} ARGS;


void* naive_search(void *arguments)
{
    ARGS *args = arguments;
    char *string = args->string;
    char *substring = args->substring;

    size_t m = strlen(substring);
    size_t n = strlen(string);

    int *result = malloc(sizeof(int));
    *result = -1;

    if (m > n) {
        return result;
    }

    size_t i, j;

    for (i = 0, j = 0; i < n; i++)
    {
        while (i < n && j != m && ((char*)string)[i] == ((char*)substring)[j])
        {
            ++i;
            ++j;
        }
        if (j == m)
        {
            *result = i - m;
            j = 0;
        }
    }
    return result;
}


int main(int argc, char **argv)
{
    if (argc != 4) 
    {
        printf("./run SOURCE_FILE PATTERN THREADS\n");
        return 0;
    }

    int source_fd = open(argv[1], O_RDONLY);
    char *pattern = argv[2];
    const int THREAD_MAX = atoi(argv[3]);
    
    if (source_fd == -1)
    {
        perror("Source file open error\n");
        return 1;
    }
    
    off_t fsize;
    fsize = lseek(source_fd, 0, SEEK_END);
    lseek(source_fd, 0, SEEK_SET);

    ssize_t bytes_read;


    // read part of text as a string
    // search though it in many threads
    


    // char chunks[THREAD_MAX][CHUNK_SIZE];

    // for (int i = 0; i < THREAD_MAX; i++)
    // {
    //     bytes_read = read(source_fd, &chunks[i], CHUNK_SIZE);
    //     printf("%d\n", bytes_read);
    // }

    // for (int i = 0; i < THREAD_MAX; i++)
    // {
    //     for (int j = 0; j < CHUNK_SIZE; j++) {
    //         printf("%c", chunks[i][j]);
    //     }printf("\n");
    // }

    
    // for (int i = 0; i < THREAD_MAX; i++)
    // {
    //     ARGS args = { chunks[i], pattern };
    
    //     if (pthread_create(th + i, NULL, &naive_search, &args) != 0)
    //     {
    //         perror("Creating thread error\n");
    //         return i;
    //     }
    //     printf("thread %d has started\n", th[i]);
    // }
    
    // for (int i = 0; i < THREAD_MAX; i++) 
    // {
    //     int *result;
        
    //     if (pthread_join(th[i], (void**) &result) != 0)
    //     {
    //         return 2 * i;
    //     }
    //     printf("result = %d\n", *result);
        
    //     printf("thread %d  has finished\n", th[i]);
    // }

    return 0;
}
