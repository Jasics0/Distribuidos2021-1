#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct data
{
    int a;
    int b;
};

pthread_t *threads;
double suma_total = 0;
FILE *openFile()
{
    FILE *flujo = fopen("sample.txt", "rb");
    if (flujo == NULL)
    {
        perror("Hubo un error al abrir el archivo.");
    }
    return flujo;
}

void closeFile(FILE *flujo)
{
    fclose(flujo);
}

void sumarDatos(void *data)
{
    struct data *t_data = (struct data *)data;
    FILE *flujo = openFile();
    int a = (*t_data).a;
    int b = (*t_data).b;
    int i = 0;
    long dato = 0;
    double suma = 0;

    while (feof(flujo) == 0)
    {
        i++;
        fscanf(flujo, "%ld", &dato);
        if (i > a && i <= b)
        {
            suma = suma + dato;
        }
        if (i == b)
        {
            closeFile(flujo);
            suma_total += suma;
            break;
        }
    }
}

long contarDatos(FILE *flujo)
{
    long i = 0;
    long dato = 0;
    while (feof(flujo) == 0)
    {
        i++;
        fscanf(flujo, "%ld", &dato);
    }
    closeFile(flujo);
    return i;
}

// ./program aaaa     bbb     ccc
//   argv[0] argv[1]  argv[2] argv[3]
int main(int argc, char **argv)
{
    long num_datos = contarDatos(openFile());
    int num_hilos = atoi(argv[1]);
    int n = num_datos / num_hilos;
    struct data *posiciones = (struct data *)calloc(n, sizeof(struct data));
    threads = (pthread_t *)calloc(num_hilos, sizeof(pthread_t));
    printf("Número de hilos usados: %d\n", num_hilos);
    for (int i = 0; i < num_hilos; i++)
    {
        posiciones[i].a = (i * n);
        posiciones[i].b = ((i + 1) * n);
        pthread_create(&threads[i], NULL, (void *)&sumarDatos, (void *)&posiciones[i]);
    }

    for (int i = 0; i < num_hilos; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("La suma es: %lf\n", suma_total);
    double promedio = suma_total / num_datos;
    printf("El promedio es: %lf\n", promedio);
}
