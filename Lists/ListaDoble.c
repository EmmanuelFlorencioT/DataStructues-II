#include<stdio.h>
#include<stdlib.h>

typedef struct nodo2{
    struct nodo2 *ant;
    int info;
    struct nodo2 *sig;
} *LISTA2;

typedef struct{
    LISTA2 pri;
    LISTA2 ult;
} LST_DBL;

void iniLstDbl(LST_DBL *cabDbl){
    cabDbl->pri=cabDbl->ult=NULL;
}

int creaNodo2(LISTA2 *nvo, int dato){
    int res;

    *nvo=(LISTA2)malloc(sizeof(struct nodo2));
    if(*nvo){
        (*nvo)->info=dato;
        (*nvo)->ant=(*nvo)->sig=NULL;
        res=1;
    }

    return(res);
}

int insIniDbl(LST_DBL *cabDbl, int dato){
    int res;
    LISTA2 nuevo;

    res=creaNodo2(&nuevo, dato);
    if(res){
        nuevo->sig=cabDbl->pri;
        if(!cabDbl->pri) /*La lista esta vacía*/
            cabDbl->ult=nuevo;
        else
            cabDbl->pri->ant=nuevo;
        cabDbl->pri=nuevo;
    }

    return(res);
}

void recorre(LST_DBL *cabDbl, int dir){ /*dir=0 recorre de izq a der, dir=1 recorre de der a izq*/
    LISTA2 aux;

    if(!dir)
        aux=cabDbl->pri; /*Comenzamos por la izq para ir a la der*/
    else
        aux=cabDbl->ult; /*Comenzamos por la der para ir a la izq*/
    /*Se puede reemplazar este if-else por un "if abreviado" o "if de una linea":
      aux = (!dir)? cabDbl.pri : cabDbl.ult; */

    while(aux){
        printf("%d\t", aux->info);
        aux= (!dir)? aux->sig : aux->ant;
    }
}

/*Funcion para determinar si 2 listas dobles están recorriendolas en sentidos contrarios*/
int palindromos(LST_DBL cab1, LST_DBL cab2){
    int res=0;
    LISTA2 aux1=cab1.pri, aux2=cab2.ult;

    while(aux1 && aux2 && aux1->info==aux2->info){
        aux1=aux1->sig;
        aux2=aux2->ant;
    }
    if(!aux1 && !aux2) /*Si llego al final del recorrido, las listas son palindormos*/
        res=1;

    return(res);
}