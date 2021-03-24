#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_t h1, h2;
pthread_mutex_t sem;
int c1=0;
void f1()
{
    int i=0;
    
    while (i<1000)
    {
        
        printf("1\n");
        c++;
        i++;
        
    }
    

}
 
void f2()
{
    int i=0;
    pthread_mutex_lock(&sem);
    while (i<2000)
    {
        printf("2");
        if(c1==100)
        {
            pthread_mutex_unlock(&sem);
        }
        i++;
        
    }
    

}
 
int main(int argc, char const *argv[])
{
    
    pthread_create(&h1, NULL, (void *)&f1, NULL);
    pthread_create(&h1, NULL, (void *)&f2, NULL);
    
    pthread_join(h1,NULL);
    pthread_join(h2,NULL);
}
