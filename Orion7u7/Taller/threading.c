#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct data
{
    int a, b;
    char fd;
};

FILE *archivo(char fd)
{
    FILE *fp = fopen(fd, "rt");
    if (fp == NULL)
    {
        printf("No se pudo leer el archivo");
    }
    return fp;
}

void function(void *data)
{
    struct data *t_data = (struct data *)data;
    FILE *fp = archivo();
    long i;
    int a = (*t_data).a;
    int b = (*t_data).b;
    int suma;
    int valor = 0;

    while (!feof(fp))
    {
        fscanf(fp, "%d", &valor);
        suma = suma + valor;
    }
    printf("Suma %d", suma);
    fclose(fp);
}
pthread_t threads[100];
// ./program aaaa     bbb     ccc
//   argv[0] argv[1]  argv[2] argv[3]
int main(int argc, char **argv)
{
    struct data array[5];
    int i;
    int num_hilos = atoi(argv[1]);
    char text = scanf("%s", &argv[2]);
    int num_datos = atoi(argv[3]);

    for (i = 0; i < num_hilos; i++)
    {
        array[i].b = i + 1;
        pthread_create(&threads[i], NULL, (void *)&function, (void *)&array[i]);
    }
    for (i = 0; i < num_hilos; i++)
    {
        pthread_join(threads[i], NULL);
    }
}
