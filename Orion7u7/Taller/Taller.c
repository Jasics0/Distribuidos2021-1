#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct data
{
    int a,b;
};

FILE *archivo(){
    FILE *fp=fopen("sample.txt","r");
    if(fp == NULL){
        printf("No se pudo leer el archivo");
    }
    return fp;
    
}
pthread_t threads [100];

int main(int argc,char **argv)
{
   struct data array[5];
   int i;
   int num=0;
   num=atoi(argv[1]);
   for (i=0;i<num;i++)
   {
       array[i].b=i+1;
       pthread_create(&threads[i],NULL,(void *)&function,(void *)&array[i]); 
   }
   for (i=0;i<num;i++)
   {
     pthread_join(threads[i],NULL); 
   }
}