#include <stdio.h>
#include <stdlib.h>

struct data
{
    int a;
    int b;
};

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

double sumarDatos(int a, int b, FILE *flujo)
{
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
            return suma;
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

int main(char **argv)
{
    long num_datos = contarDatos(openFile());
    int num_hilos = 2;
    int n = num_datos / num_hilos;
    struct data *posiciones = (struct data *)calloc(n, sizeof(struct data));
    double suma = 0;
    for (int i = 0; i < num_hilos; i++)
    {
        posiciones[i].a = (i * n);
        posiciones[i].b = ((i + 1) * n);
        suma += sumarDatos(posiciones[i].a, posiciones[i].b, openFile());
    }
    printf("La suma es: %lf\n", suma);
    double promedio=suma/num_datos;
    printf("El promedio es: %lf\n",promedio);
}
