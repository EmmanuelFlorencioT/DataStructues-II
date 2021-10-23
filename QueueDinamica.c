#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int info;
    struct nodo *liga;
} *TQUEUE;

typedef struct{
    TQUEUE front;
    TQUEUE final;
} QUEUE;

void iniQueue(QUEUE *q);
int creaNodo(TQUEUE *nvo, int dato);
int enQueue(QUEUE *q, int dato);
int deQueue(QUEUE *q, int *dato);
void capturaQueue(QUEUE *q);
void muestraQueue(QUEUE *q);

int main(){
    QUEUE fila;

    iniQueue(&fila);
    capturaQueue(&fila);
    muestraQueue(&fila);
}


void iniQueue(QUEUE *q){
    q->front=q->final=NULL;
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

int enQueue(QUEUE *q, int dato){
    int res;
    TQUEUE nuevo;

    res=creaNodo(&nuevo, dato);
    if(res){
        if(!q->front)
            q->front=nuevo;
        else
            q->final->liga=nuevo;
        q->final=nuevo;
    }

    return(res);
}

int deQueue(QUEUE *q, int *dato){
    int res=0;
    TQUEUE aux;

    if(q->front){
        if(q->front == q->final){
            *dato=q->front->info;
            free(q->front);
            q->front=q->final=NULL;
            res=1;
        }
        else{
            *dato=q->front->info;
            aux=q->front;
            q->front=q->front->liga;
            free(aux);
            res=1;
        }
    }

    return(res);
}

void capturaQueue(QUEUE *q){
    int res, data;
    char resp;

    do{
        printf("Intrduce un dato: ");
        scanf("%d", &data);
        res=enQueue(q, data);
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

void muestraQueue(QUEUE *q){
    int data;

    while(deQueue(q, &data)==1)
        printf("Dato: %d\n", data);
}