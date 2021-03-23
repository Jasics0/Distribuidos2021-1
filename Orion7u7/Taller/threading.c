#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct data
{
    int a,b;
};

void function(void *data)
{
    struct data *t_data=(struct data *)data;
    long i;
    for (i=0;i<1e5;i++)
        printf("%d\n",t_data->b);
        //(*t_data).b
}
pthread_t threads[100];
// ./program aaaa     bbb     ccc
//   argv[0] argv[1]  argv[2] argv[3]   
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




