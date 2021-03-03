#include<stdio.h>

#include<string.h>

#include<pthread.h>

#include<stdlib.h>

#include<unistd.h>

pthread_t tid[10];

void* doSomeThing(void *arg)
{

pthread_t id = pthread_self(); 
for (int i = 0; i < 10; i++)
{
    if (pthread_equal(id,tid[i]))
    {
        printf("Hilo número %d : \n",i);
        int inicio=10000*i;
        for (int j = inicio; j <= (inicio+10000); j++)
        {
            printf("%d\n",(j));
        }
        break;
    }
    
}


return NULL;

}


int main(void){

int i = 0;

int err;

while(i < 10){

err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);

 if (err != 0)
  printf("\nError al iniciar el hilo :[%s]", strerror(err));

 i++;
 sleep(2);
}
 return 0;
 }
