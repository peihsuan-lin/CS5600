/*
 * pqueuepmain.c / Synchronization with Monitors
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Feb 25, 2024
 *
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 15
#define ITEMS_SIZE 30
int buffer[BUF_SIZE];
int num = 0;
int total_produced = 0; // items produced
int total_consumed = 0; // items consumed
pthread_mutex_t mut;
pthread_cond_t cond;

void *producer(void *param);

void *consumer(void *param);

int main(int argc, char *argv[]) {
    pthread_t t1, t2;
    if (pthread_mutex_init(&mut, NULL) != 0) {
        perror("pthread_mutex_init");
        exit(1);
    }
    if (pthread_cond_init(&cond, NULL) != 0) {
        perror("pthread_cond_init");
        exit(1);
    }
    if (pthread_create(&t1, NULL, producer, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }
    if (pthread_create(&t2, NULL, consumer, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }
    pthread_t t3, t4;
    if (pthread_create(&t3, NULL, consumer, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }
    if (pthread_create(&t4, NULL, consumer, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }

/* wait until 4 threads finished */
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    printf("WE ARE DONE\n");
}

void *producer(void *param) {
    while (1) {
        pthread_mutex_lock(&mut);
        // producer exits while 30 items produced
        if (total_produced >= ITEMS_SIZE) {
            pthread_mutex_unlock(&mut);
            pthread_exit(NULL);
        }
        while (num == BUF_SIZE)
            pthread_cond_wait(&cond, &mut);
        buffer[num++] = total_produced;
        printf("buffer size: %d, produced item %d\n", num, total_produced);
        total_produced++;
        pthread_mutex_unlock(&mut);
        pthread_cond_signal(&cond);
        sleep(1);
    }
}

void *consumer(void *param) {
    while (1) {
        pthread_mutex_lock(&mut);
        // consumer exits while 30 items consumed
        if (total_consumed >= ITEMS_SIZE) {
            pthread_mutex_unlock(&mut);
            pthread_exit(NULL);
        }
        while (num == 0)
            pthread_cond_wait(&cond, &mut);
        int item = buffer[0]; // consumed the first item in the buffer (FIFO)
        /*
         * Move all the remaining items forward. For higher efficiency, some other data
         * structure might be more appropriate.
         */
        for (int i = 1; i < num; i++) {
            buffer[i - 1] = buffer[i];
        }
        num--; // decrease buffer amount
        printf("buffer size: %d, consumed item %d\n", num, item);
        total_consumed++;
        pthread_mutex_unlock(&mut);
        pthread_cond_signal(&cond);
        sleep(5);
    }
}
