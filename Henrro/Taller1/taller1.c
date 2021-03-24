#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// ./program aaaa     bbb     ccc
//   argv[0] argv[1]  argv[2] argv[3]
FILE *datos;
pthread_t threads[100];
double total = 0;

struct data
{
    long a, b;
};

void sumarNumeros(void *data)
{
    struct data *t_data = (struct data *)data;
    long a = (*t_data).a;
    long b = (*t_data).b;
    long i = 0;
    long dato = 0;
    long suma = 0;
    for (int i = a; i < b; i++)
    {
        fscanf(datos, "%ld", &dato);
        suma = suma + dato;
        printf("La suma es: %ld\n", suma);
    }
    total += suma;
    printf("El total es: %f\n", total);
}

// void traerNumeros(char *arg, int *a){
//     int c;
//     char *file = arg;
//     FILE *archivo;
//     archivo = fopen(file, "r");
//     char cadena[20];
//     int i = 0;
//     int j = 0;
//     while (1)
//     {
//         cadena[i]= fgetc(archivo);
//         i++;
//         if (cadena[i] == ' ')
//         {
//             a[j] = *(int *)&cadena;
//             printf("%d\n", a[j]);
//             i = 0;
//         }
//         if (feof(archivo))
//         {
//             break;
//         }
//         //printf("%c", cadena[i]);
//     }
// }

int main(int argc, char **argv)
{
    datos = fopen(argv[2], "r");
    int numhilos = atoi(argv[1]);
    int numdatos = atoi(argv[3]);
    int n = numdatos / numhilos;
    struct data *numeros = (struct data *)calloc(n, sizeof(struct data));
    //int numbers[201] = {};
    //traerNumeros(argv[2], numbers);
    for (int i = 0; i < numhilos; i++)
    {
        numeros[i].a = (i * n);
        numeros[i].b = ((i + 1) * n);
        if (i == numhilos - 1 && numdatos % numhilos != 0)
        {
            int x = numdatos - (n * numhilos);
            numeros[i].b = numeros[i].b + x;
        }
        pthread_create(&threads[i], NULL, (void *)&sumarNumeros, (void *)&numeros[i]);
        pthread_join(threads[i], NULL);
    }
    double prom = total / numdatos;
    printf("\nNumero de hilos: %d\n", numhilos);
    printf("\nNumero de datos: %d\n", numdatos);
    printf("\nNumero de datos por cada hilo: %d\n", n);
    printf("\nEl promedio de la suma de los datos es: %f\n", prom);
    fclose(datos);
}