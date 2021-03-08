#include <stdio.h>

#include <string.h>

#include <pthread.h>

#include <stdlib.h>

#include <unistd.h>
int shv = 0;
pthread_mutex_t sem;

void function1()
{
    while (1)
    {
        pthread_mutex_lock(&sem);
        shv++;
        shv++;
        pthread_mutex_unlock(&sem);
    }
}
void function2()
{
    while (1)
    {
        pthread_mutex_lock(&sem);
        shv--;
        shv--;
        pthread_mutex_unlock(&sem);
    }
}
void main(int arg, char **argv)
{
    pthread_t h1, h2;
    pthread_create(&h1, NULL, (void *)&function1, NULL);
    pthread_create(&h2, NULL, (void *)&function2, NULL);
    while (1)
    {
        pthread_mutex_lock(&sem);
        printf("%d\n", shv);
        pthread_mutex_unlock(&sem);
    }
}