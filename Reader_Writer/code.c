#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t db;                // Controls access to the shared database
pthread_mutex_t mutex;   // Protects read_count

int read_count = 0;      // Number of active readers

void* reader(void* arg) {
    int id = *(int*)arg;

    while (1) {
        pthread_mutex_lock(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&db);  // First reader locks the database
        }
        pthread_mutex_unlock(&mutex);

        printf("🟢 Reader %d is READING the flight data...\n", id);
        sleep(1);  // simulate reading
        printf("🔵 Reader %d finished READING.\n", id);

        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&db);  // Last reader releases the database
        }
        pthread_mutex_unlock(&mutex);

        sleep(2); // Wait before next read
    }
}

void* writer(void* arg) {
    int id = *(int*)arg;

    while (1) {
        printf("🟠 Writer %d is WAITING to access flight database...\n", id);
        sem_wait(&db);  // Wait for exclusive access
        printf("🔴 Writer %d is UPDATING flight data (booking/canceling)...\n", id);
        sleep(2);       // simulate writing
        printf("🟣 Writer %d finished UPDATING.\n", id);
        sem_post(&db);  // Release the database

        sleep(3); // Wait before next write
    }
}

int main() {
    pthread_t rtid[5], wtid[2];
    int r_id[5], w_id[2];

    sem_init(&db, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 5; i++) {
        r_id[i] = i + 1;
        pthread_create(&rtid[i], NULL, reader, &r_id[i]);
    }

    for (int i = 0; i < 2; i++) {
        w_id[i] = i + 1;
        pthread_create(&wtid[i], NULL, writer, &w_id[i]);
    }

    for (int i = 0; i < 5; i++)
        pthread_join(rtid[i], NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(wtid[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&db);

    return 0;
}
