#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// ./program aaaa     bbb     ccc
//   argv[0] argv[1]  argv[2] argv[3]
pthread_t threads[100];

struct data
{
    int a, b;
};

void sumarNumeros(int n)
{

}

void traerNumeros(char *arg, int *a){
    int c;
    char *file = arg;
    FILE *archivo;
    archivo = fopen(file, "r");
    char cadena[20];
    int i = 0;
    int j = 0;
    while (1)
    {
        cadena[i]= fgetc(archivo);
        i++;
        if (cadena[i] == ' ')
        {
            a[j] = *(int *)&cadena;
            printf("%d\n", a[j]);
            i = 0;
        }
        if (feof(archivo))
        {
            break;
        }
        //printf("%c", cadena[i]);
    }
}

int main(int argc, char **argv)
{
    int numhilos = atoi(argv[1]);
    int numdatos = atoi(argv[3]);
    int n = numdatos/numhilos;
    int numbers[201] = {};
    traerNumeros(argv[2], numbers); 
    printf("\nNumero de hilos: %d\n", numhilos);
    printf("\nNumero de datos: %d\n", numdatos);
    printf("\nNumero de datos por cada hilo: %d\n", n);

}