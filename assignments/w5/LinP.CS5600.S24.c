/*
LinP.CS5600.S24.c / Create Threads
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Feb 12, 2024
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int arr[10];

void *worker(void *data) {
  char *name = (char *)data;
  pthread_t id = pthread_self();

  for (int i = 0; i < 120; i++) {
    usleep(50000);
    printf("Hi from thread name = %s, with thread id = %lu\n", name,
           (unsigned long)id);
  }
  printf("Thread %s done!\n", name);
  return NULL;
}

void *worker_reader(void *data) {
  char *name = (char *)data;
  pthread_t id = pthread_self();
  for (int i = 0; i < 10; i++) {
    // usleep(50000);
    printf("thread %s, with thread id = %lu, reading data = %d\n", name,
           (unsigned long)id, arr[i]);
  }
  printf("Thread %s done!\n", name);
  return NULL;
}

void *worker_writer(void *data) {
  char *name = (char *)data;
  pthread_t id = pthread_self();
  int val = 0;
  for (int i = 0; i < 10; i++) {
    arr[i] = val++;
    // usleep(50000);
    printf("thread %s, with thread id = %lu, writing data = %d\n", name,
           (unsigned long)id, arr[i]);
  }
  printf("Thread %s done!\n", name);
  return NULL;
}

int main(void) {
  pthread_t th1, th2;
  pthread_create(&th1, NULL, worker, "X");
  pthread_create(&th1, NULL, worker, "Y");
  sleep(1);
  printf("cancelling thread id= %lu\n", (unsigned long)th2);
  pthread_cancel(th2);
  usleep(100000);
  printf("cancelling thread id= %lu\n", (unsigned long)th1);
  pthread_cancel(th1);
  printf("exiting from main program, id: %lu\n", (unsigned long)pthread_self());

  pthread_t reader_thread, writer_thread;
  pthread_create(&reader_thread, NULL, worker_reader, "reader");
  pthread_create(&writer_thread, NULL, worker_writer, "writer");
  sleep(1);
  printf("cancelling thread id= %lu\n", (unsigned long)reader_thread);
  pthread_cancel(reader_thread);
  usleep(100000);
  printf("cancelling thread id= %lu\n", (unsigned long)reader_thread);
  pthread_cancel(reader_thread);
  printf("exiting from main program, id: %lu\n", (unsigned long)pthread_self());

  return 0;
}

/*
3. Yes, by creating a global array, arr[10], different threads can read and
write to the same array as the program runs.
4. When I include usleep(50000), I get consistency. This means if I do the write
operation first, the read operation waits until it's done. But, when I remove
usleep(50000), the program gives inconsistency results. This happens because the
program is not using locks to protect the global array from being accessed by
different threads at the same time. Without locks, one thread can interrupt
another thread before it's finished. The way to fix this is by using mutexes.
Mutexes will make sure that only one thread can access the array at a time,
preventing these interruptions.
*/
