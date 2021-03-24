#include <stdio.h>

#include <string.h>

#include <pthread.h>

#include <stdlib.h>

#include <unistd.h>
pthread_mutex_t sem;
int  semaforo=3;
void f()
{
    while (1)
    {
        if (semaforo==2)
        {
            pthread_mutex_lock(&sem);
            printf("1");
            semaforo--;
            pthread_mutex_unlock(&sem);
        }
    }
}
void f2()
{
    while (1)
    {
        if ( semaforo==1)
        {
            pthread_mutex_lock(&sem);
            printf("2");
            semaforo=3;
            pthread_mutex_unlock(&sem);
        }
    }
}
void f3()
{
    while (1)
    {
        if (semaforo==3)
        {
            pthread_mutex_lock(&sem);
            printf("3");
            semaforo--;
            pthread_mutex_unlock(&sem);
        }
    }
}

pthread_t hilo[3];

void main(int arg, char **argv)
{

    pthread_create(&hilo[0], NULL, (void *)&f3, NULL);
    pthread_create(&hilo[1], NULL, (void *)&f2, NULL);
    pthread_create(&hilo[2], NULL, (void *)&f, NULL);

    while (1)
    {
    }
}