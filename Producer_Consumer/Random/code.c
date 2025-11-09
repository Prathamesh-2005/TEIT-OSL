#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>

sem_t full;
sem_t empty;
pthread_mutex_t mutex;

void* producer(void* arg)
{
    FILE* fp;
    while(1)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        int num=rand()%10;
        fp=fopen("data.txt","w");
        fprintf(fp,"%d",num);
        fclose(fp);
        printf("Producer Produced:%d\n",num);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
}

void* consumer(void* arg)
{
    FILE* fp;
    int num;
    while(1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        fp=fopen("data.txt","r");
        fscanf(fp,"%d",&num);
        fclose(fp);
        printf("Consumer Consumed:%d\n",num);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
}

int main()
{
    pthread_t prod,cons;

    sem_init(&empty,0,1);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&cons,NULL,consumer,NULL);
    pthread_join(prod,NULL);
    pthread_join(cons,NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}