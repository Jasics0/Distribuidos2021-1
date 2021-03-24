#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
//Estructura compuesta de inicio y final
struct data
{
    int a, b;
};

float sumaTotal=0;
char *arch;
FILE *archivo()
{
    
    FILE *fp = fopen(arch, "rt");
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

    while (!feof(fp))
    {
        i++;
        fscanf(fp, "%ld", &valor);
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
    arch= argv[2];
    int num_datos = atoi(argv[3]);
    int var = num_datos/num_hilos;

    for (i = 0; i < num_hilos-1; i++)
    {
        array[i].a =i*var ;
        array[i].b=(i+1)*var;
        pthread_create(&threads[i], NULL, (void *)&function, (void *)&array[i]);
    }
    if (var*(num_hilos)<=num_datos)
    {   
        array[num_hilos-1].a =(num_hilos-1)*var ;
        array[num_hilos-1].b=num_datos;
        pthread_create(&threads[num_hilos-1], NULL, (void *)&function, (void *)&array[num_hilos-1]);
  
    }
    for (i = 0; i < num_hilos; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("LA suma es: %f\n",sumaTotal);
    printf("El promedio es: %f\n",sumaTotal/num_datos);
printf(" %i\n",var );
}