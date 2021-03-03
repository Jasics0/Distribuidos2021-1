#include<stdio.h>

#include<string.h>

#include<pthread.h>

#include<stdlib.h>

#include<unistd.h>

pthread_t tid[2];

void* doSomeThing(void *arg)
{
unsigned long i = 0;

pthread_t id = pthread_self(); 

if(pthread_equal(id,tid[0]))

{
printf("\n Primer Hilo en ejecucion\n");
}

else

{ 
printf("\n Segundo hilo en ejecucion\n");
}



for(i=0; i<(0xFFFFFFFF);i++);

return NULL;

}


int main(void){

int i = 0;

int err;

while(i < 2){

err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
 if (err != 0)
  printf("\nError al iniciar el hilo :[%s]", strerror(err));

else
printf("\n Hilos Creados\n");

i++;
}
sleep(5);
 return 0;
 }
