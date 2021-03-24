#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
pthread_t threads[2];
pthread_mutex_t sem;

void function1()
{

    int i = 0;
    pthread_mutex_lock(&sem);
    while (i < 1000)
    {
        printf("1\n");
        if (i == 100)
        {
            pthread_mutex_unlock(&sem);
        }
    }
}

void function2()
{
    int i = 0;
    while (i < 2000)
    {
        printf("2\n");
    }
}

int main(int argc, char const *argv[])
{
    pthread_create(&threads[0], NULL, (void *)&function1, NULL);
    pthread_create(&threads[1], NULL, (void *)&function2, NULL);
    pthread_join(threads[0],threads[1]);
}