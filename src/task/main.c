#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>


// TODO: refactor struct
typedef struct
{
    size_t len;
    char *data;
} CHUNK;


// TODO: make (void*)(void *arg)
void* find_match(void* string, void* substring)
{
    size_t m = strlen(substring);
    size_t n = strlen(string);
    int *result = malloc(sizeof(int));
    *result = -1;
    for (size_t i = 0, j = 0; i < n; ++i)
    {
        while (i < n && j != m && string[i] == substring[j])
        {
            ++i;
            ++j;
        }
        if (j == m)
        {
            *result = i - m;
            break;
        }
    }
    return result;
}

// Вариант 18:
// Найти образец в строке наивным алгоритмом
int main(int argc, char **argv)
{   
    if (argc != 3) 
    {
        char arguments_example[] = "./run SOURCE_FILE THREADS\n";
        write(STDOUT_FILENO, arguments_example, sizeof(arguments_example));
        return 0;
    }

    int source_fd = open(argv[1], O_RDONLY);
    const int THREADS = atoi(argv[2]);
    pthread_t th[THREADS];
    
    if (source_fd == -1)
    {
        perror("Source file open error\n");
        return 1;
    }

    // TODO: calculate best CHUNK_SIZE
    // FILE / THREADS = CHUNK_SIZE
    // FILE = CHNUNK_SIZE * THREADS

    const size_t CHUNK_SIZE = 10000;
    ssize_t bytes_read;
    char *chunk;

        
        


    while ((bytes_read = read(source_fd, chunk, CHUNK_SIZE)) > 0)
    {
        for (int i = 0; i < THREADS; i++)
        {
            if (pthread_create(th + i, NULL, &find_match, NULL) != 0)
            {
                perror("creating thread error\n");
                return i;
            }
        }
    }

    return 0;
}