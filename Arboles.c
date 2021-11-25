#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodoAB{
    struct nodoAB *izq;
    int info;
    struct nodoAB *der;
} *AB;

/*INICIALIZACION*/
void iniAB(AB *a){
    *a=NULL;
}

/*CREACION DE NODO*/
int creaNodoAB(AB *nvo, int dato){
    int res=0;

    *nvo=(AB)malloc(sizeof(struct nodoAB));
    if(*nvo){
        (*nvo)->info=dato;
        (*nvo)->der=(*nvo)->izq=NULL;
        res=1;
    }
    return(res);
}

/*INSERCION GUIADA*/
int insGuiadaAB(AB *a, int dato){
    int res;
    char resp;

    if(!*a)
        res=creaNodoAB(a, dato);
    else{
        printf("Direccion?(s/n) ");
        fflush(stdin);
        scanf("%d", &resp);
        if(resp=='i')
            res=insGuiadaAB(&(*a)->izq, dato);
        else
            res=insGuiadaAB(&(*a)->der, dato);
    }
    return(res);
}

/*INSERCION ORDENADA*/
/*Se van a insertar datos de acuerdo a un criterio:
  Si el dato es menor que el dato raíz, se inserta a la izq
  Si el dato es mayor que la raíz, se inserta a la der*/
int insOrdAB(AB *a, int dato){
    int res;

    if(!*a)
        res=creaNodoAB(a, dato);
    else
        if(dato<(*a)->info)
            res=insOrdAB(&(*a)->izq, dato);
        else
            if(dato>(*a)->info)
                res=insOrdAB(&(*a)->der, dato);
            else
                res=0;
    return(res);
}

/*RECORRIDO preOrden*/
void preOrden(AB a){
    if(a){
        printf("%d\t", a->info);
        preOrden(a->izq);
        preOrden(a->der);
    }
}

/*RECORRIDO enOrden*/
void enOrden(AB a){
    if(a){
        enOrden(a->izq);
        printf("%d\t", a->info);
        enOrden(a->der);
    }
}

/*RECORRIDO enOrden*/
void posOrden(AB a){
    if(a){
        posOrden(a->izq);
        posOrden(a->der);
        printf("%d\t", a->info);
    }
}

/*-----Funciones Recorrido--------*/
/*Funcion para calcular el peso (No. de nodos) de un arbol*/
int calcPesoAB(AB a){
    int res;

    if(!a)
        res=0;
    else
        res=1+calculaPesoAB(a->izq)+calculaPesoAB(a->der);
    return(res);
}

/*Calcular el peso de un arbol por medio de un parametro por referencia*/
void calcPesoABref(AB a, int *peso){
    int pIzq, pDer; /*Peso izquierdo, Peso Derecho*/

    if(!a)
        *peso=0;
    else{
        pesoAB(a->izq, &pIzq);
        pesoAB(a->der, &pDer);
        *peso=1+pIzq+pDer; /*Aquí se determina que es preOrden*/
    }
}

/*Funcion para calcular el "costo" de un arbol (La suma de los valores de todos los nodos del arbol)*/
float costoAB(AB a){
    float costo;

    if(!a)
        costo=0;
    else
        costo=a->info+costoAB(a->izq)+costoAB(a->der);
    return(costo);
}

/*Funcion para contar el numero de hojas de un AB*/
int cuentaHojasAB(AB a){
    int hojas;

    if(!a)
        hojas=0;
    else
        if(!a->izq && !a->der)
            hojas=1;
        else
            hojas=cuentaHojasAB(a->izq)+cuentaHojasAB(a->der);
    return(hojas);
}