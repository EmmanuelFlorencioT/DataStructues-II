/*Programa para manejar un apuntador que apunte a un apuntador a entero*/

#include<stdio.h>
#include<stdlib.h>

/*Declaración del apuntador*/
    int **ptrPtrInt;
    //(*ptrPtrInt), representa un apuntador
    //(int *), representa un apuntador a entero

/*Función para asignar memoria*/
int asignaMem(int ***ptrPtrInt)
{
    int resp=0;

    *ptrPtrInt=(int **) malloc(sizeof(int *));
    if(*ptrPtrInt != NULL)
    {
        **ptrPtrInt=(int *) malloc(sizeof(int));
        if(**ptrPtrInt != NULL)
            resp=1;
        else
            free(*ptrPtrInt);
    }
    return(resp);
}

/*Función para asignar dato*/
void asignaDato(int **ptrPtrInt, int dato)
{
    **ptrPtrInt=dato;
}

/*Función para mostrar el dato*/
void muestraDato(int **ptrPtrInt)
{
    printf("El dato es: %d", **ptrPtrInt);
}

/*Función para caputrar el dato*/
void capturaDato(int **ptrPtrInt)
{
    printf("Dame el dato: ");
    scanf("%d", *ptrPtrInt);
}

/*Función para liberar memoria*/
void liberaMem(int **ptrPtrInt)
{
    free(*ptrPtrInt);
    free(ptrPtrInt);
}
