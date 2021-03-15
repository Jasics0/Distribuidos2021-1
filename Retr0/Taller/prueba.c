#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE * flujo = fopen("sample.txt","rb");
    if(flujo==NULL){
        perror("Hubo un error al abrir el archivo.");
        return 1;
    }

    char c;
    int num_datos=0;
    long dato=0;

    while(feof(flujo)==0){
        c=fgetc(flujo);
        if(c=='\n'){
            num_datos++;
        }
        fscanf(flujo,"%ld",&dato);
        printf("%ld\n",dato);
    }
    num_datos++;
    fclose(flujo);
    printf("\n\nTodo se ejecutó nice, y hubo %d datos\n",num_datos);
}