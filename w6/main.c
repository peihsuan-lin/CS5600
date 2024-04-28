/*
main.c / Multiprocessing in C
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Feb 20, 2024
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include "queue.h"
#include <string.h>
#define BATCH_SIZE 100
#define TOTAL_WORDS 10000
#define TOTAL_BATCHES (TOTAL_WORDS/BATCH_SIZE)
#define ENCRYPION_SIZE 5
queue_t word_queue;
pthread_mutex_t mutex;

/*
 * Takes a thread to encrypt a batch of 100 words
 */
void *process_thread(void *arg) {
    char *batch_words[BATCH_SIZE];
    for (int i = 0; i < BATCH_SIZE; i++) {
        pthread_mutex_lock(&mutex);
        char *word = popQ(&word_queue);

        if (word == NULL) break;
        batch_words[i] = word;
        pthread_mutex_unlock(&mutex);
    }

    // Implement IPC - Message Passing with pipes
    int fd[2]; // file descriptors, fd[0] read, fd[1] write
    pipe(fd);
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        // child process, for reading words from std and execute cipher to process
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        char out_file[100];

        // named output file by batch_id
        sprintf(out_file, "./results/batch_result_%d.txt", *(int *) arg);
        freopen(out_file, "w", stdout);
        execlp("./cipher", "./cipher", (char*)NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else {
        close(fd[0]);
        // parent process, for writing words into input
        for (int i = 0; i < BATCH_SIZE; i++) {
            if (batch_words[i] == NULL) break;
            int bytes_written = write(fd[1], batch_words[i], strlen(batch_words[i]));
            if (bytes_written < 0) {
                perror("Error writing to pipe");
            }
            int newline_written = write(fd[1], "\n", 1);
            if (newline_written < 0) {
                perror("Error writing newline to pipe");
            }
            write(fd[1], batch_words[i], strlen(batch_words[i]));
            write(fd[1], "\n", 1);
        }
        close(fd[1]);
        wait(NULL);
    }
    free(arg);
    return 0;
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    // read from output.txt and store the words in a queue
    initQueue(&word_queue);
    FILE *file;
    file = fopen("output.txt", "r");
    if (file == NULL)
    {
        printf("Unable to open file");
        return 1;
    }
    char word[13];
    while (fscanf(file, "%12s", word) == 1)
    {
        add2q(&word_queue, word);
    }
    fclose(file);

    pthread_t threads[TOTAL_BATCHES];
    for (int i = 0; i < TOTAL_BATCHES; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, process_thread, (void *)id);
    }
    for (int i = 0; i < TOTAL_BATCHES; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}



