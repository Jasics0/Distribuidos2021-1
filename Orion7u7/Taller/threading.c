#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct data
{
    int a, b;
};

float sumaTotal=0;

FILE *archivo()
{
    
    FILE *fp = fopen("sample.txt", "rt");
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
    int valor = 0;

    while (!feof(fp))
    {
        i++;
        fscanf(fp, "%d", &valor);
        if (i > a && i <= b)
        {
            sumaTotal = sumaTotal + valor;
        }
        if (i == b)
        {
            fclose(fp);
            break;
        }
    }
    
}

pthread_t threads[100];
// ./program aaaa     bbb     ccc
//   argv[0] argv[1]  argv[2] argv[3]
int main(int argc, char **argv)
{
    struct data array[100];
    int i;
    int num_hilos = atoi(argv[1]);
    int num_datos = atoi(argv[2]);
    int var = num_datos/num_hilos;
    for (i = 0; i < num_hilos; i++)
    {
        array[i].a =i*var ;
        array[i].b=(i+1)*var;
        pthread_create(&threads[i], NULL, (void *)&function, (void *)&array[i]);
    }
    for (i = 0; i < num_hilos; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("LA suma es: %f\n",sumaTotal);
    printf("El promedio es: %f\n",sumaTotal/num_datos);
}
