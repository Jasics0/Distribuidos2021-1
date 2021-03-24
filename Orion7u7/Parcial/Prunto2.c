//si pai
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t sem;
int c1 = 0;
void f()
{
    
    while (1)
    {
        if (c1 == 1)
        {
            pthread_mutex_lock(&sem);
            printf("1");
            c1++;
            pthread_mutex_unlock(&sem);
        }
    }
}

void f2()
{
    while (1)
    {
        if (c1 == 2)
        {
            pthread_mutex_lock(&sem);
            printf("2");
            c1 = 0;
            pthread_mutex_unlock(&sem);
        }
    }
}

void f3()
{
    while (1)
    {
        if (c1 == 0)
        {
            pthread_mutex_lock(&sem);
            printf("3");
            c1++;
            pthread_mutex_unlock(&sem);
        }
    }
}

int main(int argc, char const *argv[])
{
    pthread_t threads[3];
    pthread_create(&threads[0], NULL, (void *)&f3, NULL);
    pthread_create(&threads[1], NULL, (void *)&f, NULL);
    pthread_create(&threads[2], NULL, (void *)&f2, NULL);
    
    while(1);
}
