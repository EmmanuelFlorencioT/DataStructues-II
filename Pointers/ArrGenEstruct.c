/*
    Objetivo: Arreglo de estructuras genéricas
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct{
    /*Datos comunes*/
    char nom[25];
    char dom[25];
    char tel[18];
    /*Datos genéricos*/
    int tipo; /* <-- 1=Alumno,  2=Prof,  3=Empleado*/
    void *ptrGen;
} GEN;

typedef struct{
    float cal1, cal2, cal3;
    float prom;
} ALU;

typedef struct{
    float sueldo;
    int hTrab;
    char sec; /* <-- p=primaria,  s=secundaria,  b=bachillerato*/
} PROF;

typedef struct{
    float sBase;
    int dpto; /*1, 2, o 3*/
    float bono;
} EMPLE;

int pideN();
int asignaMem(GEN **ptr, int n);
void capturaTipos(GEN *ptr, int n);
void capturaDatos(GEN *ptr, int n);
void muestraDatos(GEN *ptr, int n);

void calculaProms(GEN *ptr, int n);

float calculaTotSueldoProf(GEN *ptr, int n);
void muestraTotalSueldo(float total);

void liberaMem(GEN *ptr, int n);

int main(){
    GEN *ptrEscuela;
    int res, nElem;
    float totSueldo;

    nElem=pideN();
    res=asignaMem(&ptrEscuela, nElem);
    if(res){
        capturaDatos(ptrEscuela, nElem);
        //muestraDatos(ptrEscuela, nElem);
        calculaProms(ptrEscuela, nElem);
        muestraDatos(ptrEscuela, nElem);
        totSueldo=calculaTotSueldoProf(ptrEscuela, nElem);
        muestraTotalSueldo(totSueldo);
        liberaMem(ptrEscuela, nElem);
    }
    else{
        printf("No hubo memoria\n");
    }
}

int pideN(){
    int n;

    printf("No. de elementos: ");
    scanf("%d", &n);
    return(n);
}

int asignaMem(GEN **ptr, int n){
    int i, resp=0;

    *ptr=(GEN *)malloc(sizeof(GEN)*n);
    if(*ptr){
        resp=1;
        /*Capturar todos los tipos de elemento, puede ser una función*/
        capturaTipos(*ptr, n);
        for(i=0;i<n && resp;i++){
            switch((*ptr+i)->tipo){
                case 1: /*Apuntador genérico para Alumno*/
                    (*ptr+i)->ptrGen=malloc(sizeof(ALU));
                    break;
                case 2: /*Apuntador genérico para Profesor*/
                    (*ptr+i)->ptrGen=malloc(sizeof(PROF));
                    break;
                case 3: /*Apuntador genérico para Empleado*/
                    (*ptr+i)->ptrGen=malloc(sizeof(EMPLE));
                    break;
            }
            if(!(*ptr+i)->ptrGen){ /*En caso de que NO apunte*/
                while(--i>=0)
                    free((*ptr+i)->ptrGen);
                free(*ptr);
                resp=0; /*Rompe el ciclo 'for' que consigue memoria*/
            }
        }
    }
    return(resp);
}

void capturaTipos(GEN *ptr, int n){
    int i;

    for(i=0;i<n;i++){
        printf("Tipo del dato no.%d: ", i+1);
        scanf("%d", &(ptr+i)->tipo);
    }
}

void capturaDatos(GEN *ptr, int n){
    int i;

    for(i=0;i<n;i++){
        /*Datos comunes*/
        printf("Elemento No.%d:\n", i+1);
        printf("Nombre: ");
        fflush(stdin);
        gets((ptr+i)->nom);
        printf("Domicilio: ");
        fflush(stdin);
        gets((ptr+i)->dom);
        printf("Telefono: ");
        fflush(stdin);
        gets((ptr+i)->tel);
        /*Datos No Comunes (Genéricos)*/
        switch((ptr+i)->tipo){
            case 1: /*Alumno*/
                printf("1era. Calif: ");
                scanf("%f", &((ALU *) (ptr+i)->ptrGen)->cal1);
                            /*Hacemos el cast para el ptrGen i-ésimo, de tal manera 
                              que accese al dato requerido de la estructura requerida*/
                printf("2da. Calif: ");
                scanf("%f", &((ALU *) (ptr+i)->ptrGen)->cal2);
                printf("3ra. Calif: ");
                scanf("%f", &((ALU *) (ptr+i)->ptrGen)->cal3);
                ((ALU *) (ptr+i)->ptrGen)->prom=0;
                break;
            case 2: /*Profesor*/
                printf("Sueldo por hora: ");
                scanf("%f", &((PROF *) (ptr+i)->ptrGen)->sueldo);
                printf("Horas trabajadas: ");
                scanf("%d", &((PROF *) (ptr+i)->ptrGen)->hTrab);
                printf("Seccion: ");
                fflush(stdin);
                scanf("%c", &((PROF *) (ptr+i)->ptrGen)->sec);
                break;
            case 3: /*Empleado*/
                printf("Sueldo base: ");
                scanf("%f", &((EMPLE *) (ptr+i)->ptrGen)->sBase);
                printf("Departamento (1, 2 o 3): ");
                scanf("%d", &((EMPLE *)(ptr+i)->ptrGen)->dpto);
                printf("Bono: ");
                scanf("%f", &((EMPLE *) (ptr+i)->ptrGen)->bono);
                break;
        }
    }
}

void muestraDatos(GEN *ptr, int n){
    int i;

    for(i=0;i<n;i++){
        /*Datos comunes*/
        printf("Elemento No. %d\n", i+1);
        printf("Nombre: %s\n", (ptr+i)->nom);
        printf("Domicilio: %s\n", (ptr+i)->dom);
        printf("Tel: %s\n", (ptr+i)->tel);
        /*Datos no comunes (genéricos)*/
        switch((ptr+i)->tipo){
            case 1:
                printf("Alumno:\n");
                printf("Calif 1: %.2f\n", ((ALU *)(ptr+i)->ptrGen)->cal1);
                printf("Calif 2: %.2f\n", ((ALU *)(ptr+i)->ptrGen)->cal2);
                printf("Calif 3: %.2f\n", ((ALU *)(ptr+i)->ptrGen)->cal3);
                printf("Promedio: %.2f\n", ((ALU *)(ptr+i)->ptrGen)->prom);
                break;
            case 2:
                printf("Profesor:\n");
                printf("Sueldo por hora: %.2f\n", ((PROF *)(ptr+i)->ptrGen)->sueldo);
                printf("No. de horas trabajadas: %d\n", ((PROF *)(ptr+i)->ptrGen)->hTrab);
                printf("Secci\xa2n: %c\n", ((PROF *)(ptr+i)->ptrGen)->sec);
                break;
            case 3:
                printf("Empleado:\n");
                printf("Sueldo base: %.2f\n", ((EMPLE *)(ptr+i)->ptrGen)->sBase);
                printf("Departamento: %d\n", ((EMPLE *)(ptr+i)->ptrGen)->dpto);
                printf("Valor del bono: %.2f\n", ((EMPLE *)(ptr+i)->ptrGen)->bono);
                break;
        }
    }
}

void calculaProms(GEN *ptr, int n){
    int i;

    for(i=0;i<n;i++)
        if((ptr+i)->tipo == 1) /*¿Alumno?*/
            ((ALU *)(ptr+i)->ptrGen)->prom=(((ALU *)(ptr+i)->ptrGen)->cal1+
                                            ((ALU *)(ptr+i)->ptrGen)->cal2+
                                            ((ALU *)(ptr+i)->ptrGen)->cal3)/3;
}

/*Función para calcular el total pagado por concepto de sueldo a profesores*/
float calculaTotSueldoProf(GEN *ptr, int n){
    int i;
    float total;

    for(i=0;i<n;i++)
        if((ptr+i)->tipo == 2)
            total+=((PROF *)(ptr+i)->ptrGen)->sueldo * ((PROF *)(ptr+i)->ptrGen)->hTrab;
    return(total);
}

void muestraTotalSueldo(float tot){
    printf("El sueldo total a profesores es %.2f\n", tot);
}

void liberaMem(GEN *ptr, int n){
    int i;
    for(i=0;i<n;i++)
        free((ptr+i)->ptrGen);
    
    free(ptr);
}