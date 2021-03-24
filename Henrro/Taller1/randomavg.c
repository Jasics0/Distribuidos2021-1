#include <stdio.h>
#include <pthread.h>
struct data
{
    int a, b;
};
void function(void *data)
{
    struct data *t_data = (struct data *)data;
    while (1)
    {
        printf("%d\n", t_data->b);
    }
}
pthread_t threads[5];
int main(int argc, char const *argv[]) {
    struct data array[5];
    int i;
    for (i = 0; i < 2; i++)   {
        pthread_create(&threads[i], NULL,(void *)&function,(void *)&array[i]);

    }
    for (i = 0; i < 2; i++)   {
        pthread_join(threads[i],NULL);
    }

    return 0;
}
