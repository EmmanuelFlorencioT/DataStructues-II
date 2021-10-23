#include<stdio.h>
#include<stdlib.h>

int asignaMem(void **ptrGen);
void asignaDato(void *ptrGen, int dato);
void capturaDato(void *ptrGen);
void muestraDato(void *ptrGen);
void liberaMem(void *ptrGen);

int main(){
    void *ptrG;
    int disc=0;

    disc=asignaMem(&ptrG);
    if(disc){
        asignaDato(ptrG, 10);
        muestraDato(ptrG);
        capturaDato(ptrG);
        muestraDato(ptrG);
        liberaMem(ptrG);
    }
    else
        printf("No hay memoria disponible");
}

int asignaMem(void **ptrGen){
    int res=0;

    *ptrGen=malloc(sizeof(int));
    if(*ptrGen)
        res=1;

    return(res);
}

void asignaDato(void *ptrGen, int dato){
    *(int *)ptrGen = dato;
}

void capturaDato(void *ptrGen){
    printf("Introduce un numero: ");
    scanf("%d", (int *)ptrGen);
}

void muestraDato(void *ptrGen){
    printf("El dato es: %d\n", *(int *)ptrGen);
}

void liberaMem(void *ptrGen){
    free(ptrGen);
}