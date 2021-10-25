#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int info;
    struct nodo *liga;
} *PILA;

void iniPila(PILA *top);
int creaNodo2(PILA *nvo, int dato);
int push(PILA *top, int dato);
int pop(PILA *top, int *dato);
void capturaPila(PILA *top);
void muestraPila(PILA *top);

int main(){
    PILA p;

    iniPila(&p);
    capturaPila(&p);
    muestraPila(&p);
}

void iniPila(PILA *top){
    *top=NULL;
}

int creaNodo(PILA *nvo, int dato){
    int res=0;

    *nvo=(PILA)malloc(sizeof(struct nodo));
    if(*nvo){
        res=1;
        (*nvo)->info=dato;
        (*nvo)->liga=NULL;
    }
    return(res);
}

int push(PILA *top, int dato){
    int res;
    PILA nuevo;

    res=creaNodo(&nuevo, dato);
    if(res){
        nuevo->liga=*top;
        *top=nuevo;
    }

    return(res);
}

int pop(PILA *top, int *dato){
    int res=0;
    PILA aux;

    if(*top){
        aux=*top;
        *dato=(*top)->info;
        *top=(*top)->liga;
        free(aux);
        res=1;
    }

    return(res);
}

void capturaPila(PILA *top){
    int res, data;
    char resp;

    do{
        printf("Introduce el dato: ");
        scanf("%d", &data);
        res=push(top, data);
        if(res){
            printf("Dato ingresado\n");
            fflush(stdin);
            printf("Desea apilar otro?(s/n) ");
            scanf("%c", &resp);
        }
        else
            printf("Dato no aplilado\n");
    }while(res && resp=='s');
}

void muestraPila(PILA *top){
    int res, data;

    while(pop(top, &data)==1)
            printf("Dato: %d\n", data);
}