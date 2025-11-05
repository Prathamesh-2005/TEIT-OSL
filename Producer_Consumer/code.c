#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

void display_buffer() {
    printf("   Counter: [");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (buffer[i] == 0)
            printf(" _ ");
        else
            printf("%2d ", buffer[i]);
    }
    printf("]\n");
}

void* simpson(void* arg) {
    int pizza_num;
    for (int i = 1; i <= 20; i++) {
        pizza_num = i;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = pizza_num;
        printf("\nSimpson: Baked Pizza #%d (placed at position %d)\n", pizza_num, in);
        display_buffer();
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    printf("\nSimpson: Done baking all pizzas!\n");
    return NULL;
}

void* joey(void* arg) {
    int pizza_num;
    for (int i = 1; i <= 20; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        pizza_num = buffer[out];
        buffer[out] = 0;
        printf("\nJoey: Ate Pizza #%d (taken from position %d)\n", pizza_num, out);
        display_buffer();
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    printf("\nJoey: Done eating all pizzas!\n");
    return NULL;
}

int main() {
    pthread_t simpson_thread, joey_thread;

    for (int i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = 0;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    printf("=== Pizza Shop Problem ===\n");
    printf("Counter capacity: %d pizzas\n", BUFFER_SIZE);
    printf("Initial Counter: [ _  _  _  _  _ ]\n");
    printf("==============================\n");

    pthread_create(&simpson_thread, NULL, simpson, NULL);
    pthread_create(&joey_thread, NULL, joey, NULL);

    pthread_join(simpson_thread, NULL);
    pthread_join(joey_thread, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("\n=== Program Complete ===\n");
    return 0;
}
