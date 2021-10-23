#include<stdio.h>
#include<stdlib.h>

int asignaMem(int **ptrArr, int n);
void capturaArr(int *ptrArr, int n);
void muestraArr(int *ptrArr, int n);
int sumaArr(int *ptrArr, int n);
int encuentraMay(int *ptrArr, int n);
void liberaMem(int *ptrArr);


/*Función para asignarle memoria al arreglo dinámico*/
int asignaMem(int **ptrArr, int n){
    int resp=0;

    *ptrArr=(int *)malloc(sizeof(int)*n);
    if(*ptrArr != NULL)
        resp=1;

    return(resp);
}

/*Función para caputrar datos al arreglo*/
void capturaArr(int *ptrArr, int n){
    int i;

    for(i=0;i<n;i++){
        printf("Dame el dato %d: ", i+1);
        scanf("%d", (ptrArr+i));
    }
}

/*Función que muestra los datos dentro del arreglo*/
void muestraArr(int *ptrArr, int n){
    int i;

    for(i=0;i<n;i++)
        printf("Dato: %d\n", *(ptrArr+i));
}

/*Función que suma los datos del arreglo*/
int sumaArr(int *ptrArr, int n){
    int i, suma=0;

    for(i=0;i<n;i++)
        suma+=*(ptrArr+i);

    return(suma);
}

/*Función para encontrar el elemento mayor del arreglo*/
int encuentraMay(int *ptrArr, int n){
    int i, may = *ptrArr; /*Asignamos el primer dato*/

    for(i=1;i<n;i++)  /*El primer elemento ya se tom� en cuenta*/
        if(*(ptrArr+i)>may)
            may=*(ptrArr+i);

    return(may);
}

/*Función para liberar la memoria del arreglo*/
void liberaMem(int *ptrArr){
    free(ptrArr);
}
