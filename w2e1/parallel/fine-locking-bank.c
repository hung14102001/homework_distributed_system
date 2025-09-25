#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10
#define NUM_TRANS   100000

// Global variables
int balance  = 0;
int credits  = 0;
int debits   = 0;

// Define 3 separate mutex locks
pthread_mutex_t b_lock;
pthread_mutex_t c_lock;
pthread_mutex_t d_lock;

void *bank_service(void *arg) {
    int i, v;
    for (i = 0; i < NUM_TRANS; i++) {
        v = rand() % 100;   // random transaction amount

        // Update balance with fine-grained lock
        pthread_mutex_lock(&b_lock);
        balance = balance + v;
        pthread_mutex_unlock(&b_lock);

        // Update credits
        pthread_mutex_lock(&c_lock);
        credits = credits + v;
        pthread_mutex_unlock(&c_lock);

        // Update debits
        pthread_mutex_lock(&d_lock);
        debits = debits + v;
        pthread_mutex_unlock(&d_lock);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int i;

    // Initialize the locks
    pthread_mutex_init(&b_lock, NULL);
    pthread_mutex_init(&c_lock, NULL);
    pthread_mutex_init(&d_lock, NULL);

    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, bank_service, NULL) != 0) {
            fprintf(stderr, "Error: pthread_create failed at i=%d\n", i);
            exit(1);
        }
    }

    // Wait for threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy locks
    pthread_mutex_destroy(&b_lock);
    pthread_mutex_destroy(&c_lock);
    pthread_mutex_destroy(&d_lock);

    // Print results
    printf("Balance: %d\n", balance);
    printf("Credits: %d\n", credits);
    printf("Debits:  %d\n", debits);

    return 0;
}
