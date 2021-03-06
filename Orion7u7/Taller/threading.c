#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct data
{
    int a, b;
};

float sumaTotal = 0;
char text;

FILE *archivo()
{

    FILE *fp = fopen(text,"r");
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
    long valor = 0;
    int suma;
    while (!feof(fp))
    {
        i++;
        fscanf(fp, "%ld", &valor);
        if (i > a && i <= b)
        {
            suma = suma + valor;
        }
        if (i == b)
        {
            fclose(fp);
            sumaTotal = sumaTotal + suma;
            break;
        }
    }
}

pthread_t threads[100];
// ./program aaaa     bbb     ccc
//   argv[0] argv[1]  argv[2] argv[3]
int main(int argc, char **argv)
{
    struct data array[5];
    int i;

    int num_hilos = atoi(argv[1]);
    text = scanf("%c",argv[2]);
    int num_datos = atoi(argv[3]);
    float var = num_datos / num_hilos;
    for (i = 0; i < num_hilos; i++)
    {
        array[i].a = i * var;
        array[i].b = (i + 1) * var;
        pthread_create(&threads[i], NULL, (void *)&function, (void *)&array[i]);
    }
    for (i = 0; i < num_hilos; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("LA suma es: %f\n", sumaTotal);
    printf("El promedio es: %f\n", sumaTotal / num_datos);
}
