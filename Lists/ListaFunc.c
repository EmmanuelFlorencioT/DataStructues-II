#include<stdio.h>

/*Estructura que maneja una lista*/
typedef struct nodo{
    int info;
    struct nodo *liga;
} *LISTA;

/*Función para contar el No. de datos(nodos) en una lista(el peso de la lista)*/
int cuentaLista(LISTA cab){
    int cont=0;
    while(cab){
        cont++;
        cab=cab->liga;
    }
    return(cont);
}

/*Función para calcular la suma de los datos en una lista(costo)*/
int sumaLista(LISTA cab){
    int suma=0;
    for( ;cab;cab=cab->liga)
        suma+=cab->info;
    return(suma);
}

/*Función RECURSIVA para calcular la suma de los datos de una lista*/
int sumaListaRec(LISTA cab){
    int suma;
    
    if(!cab)
        suma=0;
    else
        suma=cab->info+sumaListaRec(cab->liga);
    
    return(suma);
}

/*Función RECURSIVA para calcular el número de elementos en una lista*/
int cuentaListaRec(LISTA cab){
    int cont;
    if(!cab)
        cont=0;
    else
        cont=1+cuentaListaRec(cab->liga);
    return(cont);
}

/*Determinar si un dato pertenece o no a una lista (Búsqueda) RECURSIVO*/
int busqLstRec(LISTA cab, int busc){
    int res;

    if(!cab) /*Si la lista está vacía desde un principio 
                o si llegó al final de la lista*/
        res=0;
    else
        if(busc == cab->info)
            res=1;
        else
            res=busqLstRec(cab->liga, busc);

    return(res);
}

/*Encontrar el mayor dato en una lista RECURSIVO*/
int mayorLstRec(LISTA cab){
    int mayor;

    if(!cab)
        mayor=0;
    else{
        mayor=mayorLstRec(cab->liga);
        if(cab->info > mayor)
            mayor=cab->info;
    }

    return(mayor);
}

/*Mostrar los datos de una lista RECURSIVO*/
/*
void muestraLstRec(LISTA cab){
    if(!cab)
        continue; //No hay nada que hacer
    else{
        printf("%d\t", cab->info);
        muestraLstRec(cab->liga);
    }
}
*/
void muestraLstRec(LISTA cab){
    if(cab){
        printf("%d\t", cab->info);
        muestraLstRec(cab->liga);
        /*Si se intercambian el orden de las líneas, la lista se imprime al revés*/
    }
}

/*Función para incrementar los datos en h los datos de una lista*/
void incrementaRec(LISTA cab, int h){
    if(cab){
        cab->info += h;
        incrementaRec(cab->liga, h);
    }
}

