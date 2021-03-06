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

/*Funcion para calcular el numero de nodos internos de un AB*/
/*El problema de hacerlo con recursividad es que no sabria distinguir
  entre la raiz del arbol y los nodos internos.
  Entonces se recurre a una operacion aritmetica -> internos=peso(a)-hojas(a)-1
    La op aritmetica no se cumple cuando el peso del arbol es menor que 3 
    por lo que se le asigna directamente 0*/
int interAB(AB a){
    int inter, p=calcPesoAB(a);

    if(p<3)
        inter=0;
    else
        inter=p-cuentaHojasAB(a)-1;
    return(inter);
}

/*Funcion que determina si un dato esta dentro del AB*/
int busqAB(AB a, int dato){
    int res;

    if(!a)
        res=0;
    else
        if(a->info==dato)
            res=1;
        else
            res=busqAB(a->izq, dato) || busqAB(a->der, dato);
            /*El OR nos asegura que si lo encuentra, entonces 
              ya no lo va a intentar por el otro lado 
              (por la evaulacion de circuito corto) de la computadora*/
    return(res);
}

/*Funcion que determina si un dato esta dentro del ABO (Ordenado)*/
int busqABO(AB a, int dato){
    int res;

    if(!a)
        res=0;
    else
        if(a->info==dato)
            res=1;
        else
            if(dato < a->info)
                res=busqABO(a->izq, dato);
            else
                res=busqABO(a->der, dato);
    return(res);
}

/*Funcion para hacer eliminaciones en arboles binarios*/
/*  Caso1:El dato a eliminar se encuentra en un nodo hoja, solo se elimina
    Caso2:El dato a eliminar se encuentra en un nodo con 1 sucesor, este sucesor toma su lugar
    Caso3:El dato a eliminar tiene 2 sucesores, entonces:
        3.1) Se sustituye por el dato más hacia la derecha del subarbol izquierdo
        3.2) Se sustituye por el dato más hacia la izquierda del subarbol derecho*/
int elimABO(AB *a, int dato){
    int res;
    AB aux, ant;

    if(!a)
        res=0;
    else
        if(dato == (*a)->info){
            aux=*a;
            /*Casos*/
            if(!(*a)->izq && !(*a)->der)
                *a=NULL;
            else
                if(!(*a)->izq) /*Podemos concluir que entonces si tiene nodo a la derecha*/
                    *a=(*a)->der;
                else
                    if(!(*a)->der) /*Podemos concluir que tiene solamente nodo a la izquierda*/
                        *a=(*a)->izq;
                    else{ /*Podemos concluir que tiene ambos nodos*/
                      /*Se aplica el criterio del subarbol IZQ*/
                        aux=(*a)->izq;
                        while(aux->der){ /*Debemos recorrer el auxiliar hasta el nodo de mas a la derecha*/
                            ant=aux;
                            aux=aux->der;
                        }
                        (*a)->info=aux->info; /*Se hace la eliminacion del dato por sobreescritura*/
                        if(aux == (*a)->izq) /*Se revisa si aux no se movio con el ciclo*/
                            (*a)->izq=aux->izq;
                        else
                            ant->der=aux->izq;
                    }
            free(aux);
            res=1;
        }
        else
            if(dato < (*a)->info)
                res=elimABO(&(*a)->izq, dato);
            else
                res=elimABO(&(*a)->der, dato);
}

/*Funcion para hacer eliminaciones en un arbol binario ordenado Optimizado*/
int elimABO_optim(AB *a, int dato){
    int res;
    AB aux, ant;

    if(!a)
        res=0;
    else
        if(dato == (*a)->info){
            aux=*a;
            /*Casos*/
            if(!(*a)->izq)
                *a=(*a)->der; /*No importa si la derecha es NULL*/
            else
                if(!(*a)->der)
                    *a=(*a)->izq; /*No importa si la izquierda es NULL*/
                else{
                  /*Se aplica el criterio del subarbol IZQ*/
                    aux=(*a)->izq;
                    while(aux->der){ /*Debemos recorrer el auxiliar hasta el nodo de mas a la derecha*/
                        ant=aux;
                        aux=aux->der;
                    }
                    (*a)->info=aux->info; /*Se hace la eliminacion del dato por sobreescritura*/
                    if(aux == (*a)->izq) /*Se revisa si aux no se movio con el ciclo*/
                        (*a)->izq=aux->izq;
                    else
                        ant->der=aux->izq;
                }
            free(aux);
            res=1;
        }
        else
            if(dato < (*a)->info)
                res=elimABO_optim(&(*a)->izq, dato);
            else
                res=elimABO_optim(&(*a)->der, dato);
}