/*Escribe un programa para manejar una estrcutra persona(PER)
  por medio de un apuntadro. Considere que la estructura está
  formada por los campos: nombre, edad, estatura y peso.*/

/*
    Objetivo: Apuntadores y Estructuras
    Autor: E. F. T.
    Fecha: 30.08.21
    Nota(s):
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char nom[25];
    int edad;
    float estatura, peso;
} PER;

int asignaMem(PER **ptrPer);
void asignaPer(PER *ptrPer, char n[], int ed, float est, float pe);
void muestraPer(PER *ptrPer);
void capturaPer(PER *ptrPer);
void cumple(PER *ptrPer);
void muestraMayorMenor(PER *ptrPer);
float calculaIMC(PER *ptrPer);
void muestraIMC(float imc);
void liberaMem(PER *ptrPer);

int main(){
    int res;
    float resIMC;
    PER *ptrPersona;

    res=asignaMem(&ptrPersona);
    if(res == 1){
        asignaPer(ptrPersona, "Juan Perez", 21, 1.73, 70.7);
        muestraPer(ptrPersona);
        capturaPer(ptrPersona);
        muestraPer(ptrPersona);
        cumple(ptrPersona);
        muestraPer(ptrPersona);
        muestraMayorMenor(ptrPersona);
        resIMC=calculaIMC(ptrPersona);
        muestraIMC(resIMC);
        liberaMem(ptrPersona);
    }
    else{
        printf("No hay memoria :c\n");
    }
}

/*Fucnión para asignar memoria*/
int asignaMem(PER **ptrPer){
    int resp=0;
    *ptrPer=(PER *)malloc(sizeof(PER));
    if(ptrPer != NULL)
        resp=1;
    return(resp);
}

/*Función para asignar datos a la estructura PER*/
void asignaPer(PER *ptrPer, char n[], int ed, float est, float pe){
    strcpy(ptrPer->nom, n);
    ptrPer->edad=ed;
    ptrPer->estatura=est;
    ptrPer->peso=pe;
}

/*Función para mostrar los datos de un estructura PER*/
void muestraPer(PER *ptrPer){
    printf("Nombre: %s, Edad: %d, Estarua: %.2f, Peso: %.2f\n", ptrPer->nom, ptrPer->edad, ptrPer->estatura, ptrPer->peso);
}

/*Función para caputrar los datos de una persona PER*/
void capturaPer(PER *ptrPer){
    printf("Nombre: ");
    gets(ptrPer->nom);
    printf("Edad: ");
    scanf("%d", &ptrPer->edad);
    printf("Estatura: ");
    scanf("%f", &ptrPer->estatura);
    printf("Peso: ");
    scanf("%f", &ptrPer->peso);
}

/*Función para cuando una persona cumple años*/
void cumple(PER *ptrPer){
    ptrPer->edad+=1;
}

/*Función para indicar mayor/menor de edad*/
void muestraMayorMenor(PER *ptrPer){
    if(ptrPer->edad > 17)
        printf("Eres mayor de edad\n");
    else
        printf("Eres menor de edad\n");
}

/*Función para calcular el IMC*/
float calculaIMC(PER *ptrPer){
    float imc;
    imc=ptrPer->peso/(ptrPer->estatura*ptrPer->estatura);
    return(imc);
}

/*Función para mostrar el IMC*/
void muestraIMC(float imc){
    printf("IMC: %.2f\n", imc);
}

/*Función para liberar memoria*/
void liberaMem(PER *ptrPer){
    free(ptrPer);
}
