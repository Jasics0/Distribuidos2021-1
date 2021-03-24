#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_t threads[3];
pthread_mutex_t sem;
char c = '2';

void f()
{
    while (1)
    {
        if (c == '3')
        {
            pthread_mutex_lock(&sem);
            c = '1';
            printf("%c", c);
            pthread_mutex_unlock(&sem);
        }
    }
}

void f2()
{
    while (1)
    {
        if (c == '1')
        {
            pthread_mutex_lock(&sem);
            c = '2';
            printf("%c", c);
            pthread_mutex_unlock(&sem);
        }
    }
}

void f3()
{
    while (1)
    {
        if (c == '2')
        {
            pthread_mutex_lock(&sem);
            c = '3';
            printf("%c", c);
            pthread_mutex_unlock(&sem);
        }
    }
}

int main(int argc, char const *argv[])
{
    pthread_create(&threads[2], NULL, (void *)&f3, NULL);
    pthread_create(&threads[0], NULL, (void *)&f, NULL);
    pthread_create(&threads[1], NULL, (void *)&f2, NULL);

    while (1)
        ;
}
