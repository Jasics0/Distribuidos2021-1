#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct data
{
    long a;
    long b;
};

pthread_t threads[100];
double suma_total = 0;
char *nombre;

FILE *openFile()
{
    FILE *flujo = fopen(nombre, "rb");
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
    long a = (*t_data).a;
    long b = (*t_data).b;
    long i = 0;
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

int main(int argc, char **argv)
{
    nombre = argv[2];
    long num_datos = contarDatos(openFile());
    int num_hilos = atoi(argv[1]);
    long n = num_datos / num_hilos;
    struct data *posiciones = (struct data *)calloc(num_hilos, sizeof(struct data));
    printf("Número de hilos usados: %d\n", num_hilos);
    for (int i = 0; i < num_hilos; i++)
    {
        posiciones[i].a = (i * n);
        posiciones[i].b = ((i + 1) * n);
        if (i == num_hilos - 1 && num_datos % num_hilos != 0)
        {
            int excedente = num_datos - (n * num_hilos);
            posiciones[i].b = posiciones[i].b + excedente;
        }
        pthread_create(&threads[i], NULL, (void *)&sumarDatos, (void *)&posiciones[i]);
        pthread_join(threads[i], NULL);
    }

    printf("La suma es: %lf\n", suma_total);
    double promedio = suma_total / num_datos;
    printf("El promedio es: %lf\n", promedio);
}
