#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define size 5
int buffer[size];

int in=0;
int out=0;

pthread_mutex_t mutex;
sem_t full;
sem_t empty;

void display()
{
    printf(" Counter :[");
    for(int i=0;i<size;i++)
    {
        if(buffer[i]==0)
        {
            printf(" _ ");
        }
        else{
            printf("%2d ",buffer[i]);
        }
    }
    printf("]\n");
}

void* simpson(void* arg)
{
    int pizza;

    for(int i=1;i<=20;i++)
    {
        pizza=i;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in]=pizza;
        printf("\nSimpson: Baked Pizza #%d (placed at position %d)\n", pizza, in);
        display();
        in=(in+1)%size;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    printf("\nSimpson: Done baking all pizzas!\n");
    return NULL;
}

void* joey(void* arg)
{
    int pizza;

    for(int i=1;i<=20;i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        pizza=buffer[out];
        buffer[out]=0;
        printf("\njoey: ate Pizza #%d (placed at position %d)\n", pizza, out);
        display();
        out=(out+1)%size;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    printf("\nJoey: Done eating all pizzas!\n");
    return NULL;
}

int main()
{
    pthread_t simpson_thread,joey_thread;

    for(int i=0;i<size;i++)
    {
        buffer[i]=0;
    }
    pthread_mutex_init(&mutex,NULL);
    sem_init(&empty,0,size);
    sem_init(&full,0,0);

    printf("=== Pizza Shop Problem ===\n");
    printf("Counter capacity: %d pizzas\n", size);
    printf("Initial Counter: [ _  _  _  _  _ ]\n");
    printf("==============================\n");

    pthread_create(&simpson_thread,NULL,simpson,NULL);
    pthread_create(&joey_thread,NULL,joey,NULL);

    pthread_join(simpson_thread,NULL);
    pthread_join(joey_thread,NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    printf("\n=== Program Complete ===\n");
    return 0;
}