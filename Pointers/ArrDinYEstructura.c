typedef struct{
    char nom[25];
    int edad;
    float estatura, peso;
}PER;

/*Función para asignar memoria al arreglo dinámico de estructra*/
int asignaMem(PER **ptrArrPer, int n){
    int resp=0;

    *ptrArrPer=(PER *)malloc(sizeof(PER)*n);
    if(*ptrArrPer)
        resp=1;

    return(resp);
}

/*Función para mostrar los datos del arreglo de estructura*/
void capturaArrPer(PER *ptrArrPer, int n){
    int i;

    for(i=0;i<n;i++){
        printf("Persona %d\n", i+1);
        printf("Introduce el nombre: ");
        gets((ptrArrPer+i)->nom);
        printf("Intrduce la edad: ");
        scanf("%d", &(ptrArrPer+i)->edad);
        printf("Intrduce la estatura: ");
        scanf("%f", &(ptrArrPer+1)->estatura);
        printf("Intrduce el peso: ");
        scanf("%f", &(ptrArrPer+i)->peso);
    }
}

void muestraArrPer(PER *ptrArrPer, int n){
    int i;

    for(i=0;i<n;i++){
        printf("No. %d\n", i+1);
        printf("Nombre: %s\n", (ptrArrPer+i)->nom);
        printf("Edad: %d\n", (ptrArrPer+i)->edad);
        printf("Estatura: %d\n", (ptrArrPer+i)->estatura);
        printf("Peso: %d\n\n", (ptrArrPer+i)->peso);
    }
}

float promEdad(PER *ptrArrPer, int n){
    int i, ac=0;
    float prom;

    for(i=i;i<n;i++)
        ac+=(ptrArrPer+i)->edad;
          /*Cast*/
    prom=(float)ac/n;

    return(prom);
}

void personaMasAlta(PER *ptrArrPer, int n, *char nomMasAlta, float *masAlta){
    int i;

    strcpy(nomMasAlta, (ptrArrPer+0)->nom);
    *masAlta=ptrArrPer->estatura; /*Da lo mismo quitarle el '+0'*/
    for(i=0;i<n;i++)
    if((ptrArrPer+i)->estatura > *masAlta){
        strcpy(nomMasAlta, (ptrArrPer+i)->nom);
        *masAlta=(ptrArrPer+i)->estatura;
    }
}

/*Suponiendo que la estructura tiene un campo de IMC, calcular el IMC para cada persona*/
void calculaIMC(PER *ptrArrPer, int n){
    int i;

    for(i=0;i<n;i++)
        (ptrArrPer+i)->imc=(ptrArrPer+i)->peso / ((ptrArrPer+i)->peso * (ptrArrPer+i)->estatura);
}

/*Función para liberar memoria*/
void liberaMem(PER *ptrArrPer){
    free(ptrArrPer);
}
