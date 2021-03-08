#include <stdio.h>
#include <pthread.h>
int shv = 0;

void function1() {
while (1)
{
    shv+=2;
}

}
void function2() {
    while (1)
    {
        shv-=2;
    }
    
}

void main(int arg, char **argv) {
    pthread_t h1, h2;
    pthread_create(&h1,NULL,(void *)&function1, NULL);
    pthread_create(&h2,NULL,(void *)&function1, NULL);
    while (1)
    {
        printf("%d\n", shv);
    }
    
}
