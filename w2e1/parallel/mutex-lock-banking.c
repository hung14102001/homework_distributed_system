#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

int shared = 0;               // shared variable
pthread_mutex_t mutex;        // mutex lock

void * incrementer(void * args) {
    int i;
    for (i = 0; i < 100; i++) {
        // lock trước khi vào đoạn găng
        pthread_mutex_lock(&mutex);

        shared++; // increment (critical section)

        // unlock sau khi xong
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char * argv[]) {
    pthread_t * threads;
    int n, i;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Invalid number of threads\n");
        exit(1);
    }

    // convert argv[1] to a long
    if ((n = atol(argv[1])) == 0) {
        fprintf(stderr, "ERROR: Invalid number of threads\n");
        exit(1);
    }

    // khởi tạo mutex
    pthread_mutex_init(&mutex, NULL);

    // allocate array of pthread_t identifiers
    threads = calloc(n, sizeof(pthread_t));

    // create n threads
    for (i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, incrementer, NULL);
    }

    // join all threads
    for (i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    // print shared value and result
    printf("Shared: %d\n", shared);
    printf("Expect: %d\n", n * 100);

    // hủy mutex
    pthread_mutex_destroy(&mutex);

    free(threads);
    return 0;
}
