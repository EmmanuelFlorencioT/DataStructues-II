/*
    Objetivo:
    Nombre:
    Fecha:
    Nota(s):
*/

#include <stdio.h>
#include <stdlib.h>

int asignaMem(int **ptrInt);
void asignaDato(int *ptrInt, int dato);
void muestraDato(int *ptrInt);
void capturaDato(int *ptrInt);
void avanzaUno(int *ptrInt);
void retrocedeUno(int *ptrInt);
void liberaMem(int *ptrInt);

int main()
{
    int res;
    int *ptrEntero;

    res=asignaMem(&ptrEntero);
    if(res==1) /*Si hay memoria*/
    {
        asignaDato(ptrEntero, 100);
        muestraDato(ptrEntero);
        capturaDato(ptrEntero);
        muestraDato(ptrEntero);
        avanzaUno(ptrEntero);
        muestraDato(ptrEntero);
        retrocedeUno(ptrEntero);
        muestraDato(ptrEntero);
        liberaMem(ptrEntero);
    }
    else
        printf("No hubo memoria disponible\n");
}

/*Funci�n para asignar memoria al apuntador*/
int asignaMem(int **ptrInt)
{
    int resp=0;

    *ptrInt=(int *) malloc(sizeof(int));
    if(*ptrInt != NULL)
        resp=1;

    return(resp);
}

/*Funci�n para asignar un dato al apuntador*/
void asignaDato(int *ptrInt, int dato)
{
    /*Como se trata de un apuntador, le debo agregar el '*' para
      hacer referancia al dato del apuntador*/

    *ptrInt=dato;

    /* ptrInt ==> direcci�n
      *ptrInt ==> datos dentro de la direcci�n  */
}

/*Funci�n para moestrar el dato*/
void muestraDato(int *ptrInt)
{
    printf("El dato es: %d\n", *ptrInt);
}

/*Funci�n para capturar un dato para el apuntador*/
void capturaDato(int *ptrInt)
{
    printf("Dame el dato: ");
    scanf("%d", ptrInt);  //es lo mismo que scanf("%d", &*ptrInt)
}

/*Funci�n para incrementar en 1 el dato del apuntador*/
void avanzaUno(int *ptrInt)
{
    (*ptrInt)++;
}

/*Funci�n para dismunuir en 1 el dato del apuntador*/
void retrocedeUno(int *ptrInt)
{
    (*ptrInt)--;
}

/*Funci�n para liberar la memoria del apuntador*/
void liberaMem(int *ptrInt)
{
    free(ptrInt);
}
