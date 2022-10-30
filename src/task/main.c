#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>


typedef struct arguments 
{
    int source_fd;
    char *substring;    
    off_t offset;
    size_t chunk_size;
    size_t file_size;
} ARGS;


void *search_substring(void *arguments)
{
    ARGS *args = arguments;
    int *result = malloc(sizeof(int));
    *result = -1;

    char *chunk = (char*)malloc(args->chunk_size);
    size_t bytes_read;

    bytes_read = pread(args->source_fd, chunk, args->chunk_size, args->offset);
    
    // printf("%d ", args->chunk_size);


    size_t m = strlen(args->substring);
    if (m > args->file_size)
    {
        return result;
    }

    int i = 0, j = 0;
    while (i < args->chunk_size)
    {
        while (i < args->chunk_size && j < m && (chunk[i] == args->substring[j]))
        {
            ++i;
            ++j;
        }
        if (j == m)
        {
            *result = i - m;
            j = 0;
            // i--;
            printf("found substring at %d\n", args->offset + i + 1 - m);
        }
        if (0 < j && j < m) 
        {   
            // cannot increase chunk
            if (args->offset + args->chunk_size + (m - j) > args->file_size) 
            {
                return result;
            }

            args->chunk_size = args->chunk_size + (m - j);
            chunk = realloc(chunk, args->chunk_size);        

            bytes_read = pread(args->source_fd, chunk, args->chunk_size, args->offset);
            if (bytes_read != args->chunk_size)
            {
                perror("chunk increase error\n");
            }
        }
        if (j == 0) 
        {
            i++;
        }
    }
    free(chunk);
    return result;
}


int main(int argc, char **argv)
{
    if (argc != 4)
    {
        // printf("%d\n", argc);
        printf("USAGE: ./run SOURCE_FILE PATTERN THREADS\n");
        return 0;
    }

    // argv[1] = "source.txt";
    // argv[2] = "say";
    // argv[3] = "1";


    int source_fd = open(argv[1], O_RDONLY);
    char *substring = argv[2];
    const int THREAD_MAX = atoi(argv[3]);
    
    if (source_fd == -1)
    {
        perror("Source file open error\n");
        return 1;
    }
    
    // define size of source file
    off_t file_size = lseek(source_fd, 0, SEEK_END);    
    lseek(source_fd, 0, SEEK_SET);

    const size_t CHUNK_SIZE = ceil(file_size / (double) THREAD_MAX);

    // for (int i = 0; i < file_size / CHUNK_SIZE + 1; i++) 
    // {
    //     off_t offset = i * CHUNK_SIZE;
    //     ARGS *args = (ARGS*)malloc(sizeof(ARGS));
    
    //     args->source_fd = source_fd;
    //     args->substring = substring;
    //     args->offset = i * CHUNK_SIZE;
    //     args->chunk_size = CHUNK_SIZE;
    //     args->file_size = file_size;

    //     search_substring(args);
    // }

    pthread_t th[THREAD_MAX];
    for (int i = 0; i < THREAD_MAX; i++)
    {
        off_t offset = i * CHUNK_SIZE;
        ARGS *args = (ARGS*)malloc(sizeof(ARGS));
    
        args->source_fd = source_fd;
        args->substring = substring;
        args->offset = i * CHUNK_SIZE;
        args->chunk_size = CHUNK_SIZE;
        args->file_size = file_size;

        if (pthread_create(th + i, NULL, &search_substring, args) != 0)
        {
            perror("Creating thread error\n");
            return i;
        }
    }

    for (int i = 0; i < THREAD_MAX; i++) 
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            return 2 * i;
        }
    }

    return 0;
}