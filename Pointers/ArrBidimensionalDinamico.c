/*Función para asignar memoria*/
int asignaMem(int ***ptrArrBi, int nRen, int nCol){
    int res=0, i;

    *ptrArrBi=(int **)malloc(sizeof(int *)*nRen);
    if(*ptrArrBi){
        res=1;
        for(i=0;i<nRen && res;i++){  /*res --> (res!=0)*/
            *(*ptrArrBi+i)=(int *)malloc(sizeof(int)*nCol);
            if(!*(*ptrArrBi+i)){   /*Se checa si NO se consiguió memoria*/
                res=0;
            /*Aqui en while vamos desfazados en cuanto al bloque que debemos liberar por eso --i*/
                while(--i >= 0)
                    free(*(*ptrArrBi+i));
                free(*ptrArrBi);
            }
        }
    }
    return(res);
}

void capturaArrBi(int **ptrArrBi, int nR, int nC){
    int i, j;

    for(i=0;i<nR;i++)
        for(j=0;j<nC;j++){
            printf("Introduce el dato [%d, %d]: ", i, j);
            scanf("%d", (*(ptrArrBi+i)+j));
        }
}

void muestraArrBi(int **ptrArrBi, int nR, int nC){
    int i, j;

    for(i=0;i<nR;i++)
        for(j=0;j<nC;j++)
            printf("El dato [%d, %d] es: &d\n", i, j, *(*(ptrArrBi+i)+j));
}

void liberaMem(int **ptrArrBi, int nRen){
    int i;
    for(i=0;i<nRen;i++)
        free(*(ptrArrBi+i));
    free(ptrArrBi);
}