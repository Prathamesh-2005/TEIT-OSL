#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

#define chairs 3
#define num_students 10

sem_t students;
sem_t ta;
pthread_mutex_t mutex;

int waiting=0;

void* student(void* arg)
{
    int id=*(int*)arg;
    while(1)
    {
        sleep(rand()%5);
        pthread_mutex_lock(&mutex);
        if(waiting<chairs)
        {
            waiting++;
            printf("student %d waiting. waiting count = %d\n",id,waiting);
            sem_post(&students);
            pthread_mutex_unlock(&mutex);
            sem_wait(&ta);
            printf("student %d is getting help.\n",id);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            printf("student %d found no chair, leaving.\n",id);
        }
    }
}

void* ta_thread(void* arg)
{
    while(1)
    {
        sem_wait(&students);
        pthread_mutex_lock(&mutex);
        waiting--;
        printf("TA helping a student. Waiting left = %d\n",waiting);
        pthread_mutex_unlock(&mutex);
        printf("TA is helping...\n");
        sleep(2);
        sem_post(&ta);
        printf("TA finished helping...\n");
    }
}

int main()
{
    srand(time(NULL));
    pthread_t ta_thread_id;
    pthread_t student_threads[num_students];
    int id[num_students];

    sem_init(&students,0,0);
    sem_init(&ta,0,0);
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&ta_thread_id,NULL,ta_thread,NULL);

    for(int i=0;i<num_students;i++)
    {
        id[i]=i+1;
        pthread_create(&student_threads[i],NULL,student,&id[i]);
    }

    pthread_join(ta_thread_id,NULL);
    for(int i=0;i<num_students;i++)
    {
        pthread_join(student_threads[i],NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&students);
    sem_destroy(&ta);
    return 0;
}
