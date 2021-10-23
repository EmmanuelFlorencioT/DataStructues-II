#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int info;
    struct nodo *liga;
} *TQUEUE;

void iniQueue(TQUEUE *front, TQUEUE *final);
int creaNodo(TQUEUE *nvo, int dato);
int enQueue(TQUEUE *front, TQUEUE *final, int dato);
int deQueue(TQUEUE *front, TQUEUE *final, int *dato);
void capturaQueue(TQUEUE *front, TQUEUE *final);
void muestraQueue(TQUEUE *front, TQUEUE *final);

int main(){
    TQUEUE frnt, fin;

    iniQueue(&frnt, &fin);
    capturaQueue(&frnt, &fin);
    muestraQueue(&frnt, &fin);
}

void iniQueue(TQUEUE *front, TQUEUE *final){
    *front=*final=NULL;
}

int creaNodo(TQUEUE *nvo, int dato){
    int res=0;

    *nvo=(TQUEUE)malloc(sizeof(struct nodo));
    if(*nvo){
        res=1;
        (*nvo)->info=dato;
        (*nvo)->liga=NULL;
    }
    return(res);
}

int enQueue(TQUEUE *front, TQUEUE *final, int dato){
    int res;
    TQUEUE nuevo;

    res=creaNodo(&nuevo, dato);
    if(res){
        if(!*front)
            *front=nuevo;
        else
            (*final)->liga=nuevo;
        *final=nuevo;
    }

    return(res);
}

int deQueue(TQUEUE *front, TQUEUE *final, int *dato){
    int res=0;
    TQUEUE aux;

    if(*front){
        if(*front == *final){
            *dato=(*front)->info;
            free(*front);
            *front=*final=NULL;
            res=1;
        }
        else{
            *dato=(*front)->info;
            aux=*front;
            *front=(*front)->liga;
            free(aux);
            res=1;
        }
    }

    return(res);
}

void capturaQueue(TQUEUE *front, TQUEUE *final){
    int res, data;
    char resp;

    do{
        printf("Intrduce un dato: ");
        scanf("%d", &data);
        res=enQueue(front, final, data);
        if(res){
            printf("Dato ingresado\n");
            fflush(stdin);
            printf("Desea ingresar otro?(s/n) ");
            scanf("%c", &resp);
        }
        else
            printf("Dato no ingresado, intente mas tarde\n");
    }while(res && resp=='s');
}

void muestraQueue(TQUEUE *front, TQUEUE *final){
    int data;

    while(deQueue(front, final, &data)==1)
        printf("Dato: %d\n", data);
}