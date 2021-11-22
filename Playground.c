#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodoVJ{
    char cveNum[10];
    char nomVJ[25];
    float precio;
    int cantEx;
    struct nodoVJ *sigVJ;
} *VJ;

typedef struct nodoSucu{
    char cveCad[15];
    char nomSucu[25];
    VJ cabVJ;
    struct nodoSucu *sigSuc;
} *SUC;

typedef struct nodoPais{
    char cveNumP[10];
    char nomPais[25];
    SUC cabSucu;
    struct nodoPais *sigPais;
} *PAIS;

/*Prob 2*/
void muestraCli(CLI cabC){
    if(cabC){
        printf("Clave Cliente: %s\t", cabC->claveCli);
        printf("Nombre Cliente: %s\t", cabC->nomCli);
        printf("Monto total: %.2f\t", cabC->total);
        printf("\n");
        muestraCli(cabC->sigCli);
    }
}

void muestraVen(VEND cabV){
    if(cabV){
        printf("Clave Vendedor: %s\t", cabV->claveVend);
        printf("Nombre Vendedor: %s\t", cabV->nomVend);
        printf("\nClientes:\n");
        muestraCli(cabV->cabCli);
        printf("\n");
        muestraVen(cabV->sigVend);
    }
}

void muestraSuc(SUC cabS){
    if(cabS){
        printf("Clave Sucursal: %s\t", cabS->claveSuc);
        printf("Nombre Sucursal: %s\t", cabS->nomSuc);
        printf("\nVendedores:\n");
        muestraVen(cabS->cabVend);
        printf("\n");
        muestraSuc(cabS->sigSuc);
    }
}

/*Prob 3*/
void calcTotVtaXSuc(SUC cabSu){
    float total;
    VEND auxVen;
    VTA auxVta;

    while(cabSu){
        total=0;
        auxVen=cabSuc->cabVend;
        while(auxVen){
            auxVta=auxVen->cabVta;
            while(auxVta){
                total+=auxVta->montoVta;
                auxVta=auxVta->sigVta;
            }
            auxVen=auxVen->sigVend;
        }
        cabSu->totalSuc=total;
        cabSu=cabSu->sigSuc;
    }
}

/*Prob 4*/
int calcVerRelConTodos(GRAFO_MR g){
    int contAct, contRes=0, i, j;

    for(i=0;i<g.cv;i++){
        contAct=0;
        for(j=0;j<g.cv;j++)
            if(i!=j) /*Aseguro que las relaciones no sean con uno mismo*/
                contAct+=*(*(g.matRel+i)+j);
        if(contAct==(g.cv-1))
            contRes++;
    }
    return(contRes); /*Conteo para el Resultado*/
}
