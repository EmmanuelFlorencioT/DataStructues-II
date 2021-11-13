#include<stdio.h>
#include<stdlib.h>

typedef struct nodoRel{
    int vecRel; /*Vector que se relaciona*/
    struct nodoRel *sigRel;
} *REL;

typedef struct{
    int ver;
    REL cabRel;
} VER;

typedef struct{
    int nmax; /*Numero maximo de vertices*/
    int cv; /*Contador de vertices*/
    VER *vecVer; /*Vector de vertices*/
} GRAFO_VR;


/*Inicializacion*/
int iniGrafoVR(GRAFO_VR *g, int nm){
    int res=0;

    g->vecVer=(VER *)malloc(sizeof(VER)*nm);
    if(g->vecVer){
        g->nmax=nm;
        g->cv=0;
        res=1;
    }
    return(res);
}

/*Insercion de vetice*/
int insVerGrafoVR(GRAFO_VR *g, int v){
    int res=0;

    if(g->cv < g->nmax){
        (*(g->vecVer+g->cv)).ver=v;
        (g->vecVer+g->cv)->cabRel=NULL;
        g->cv++;
        res=1;
    }
    return(res);
}

/*Insercion de relacion*/
int insRelGrafoVR(GRAFO_VR g, int vo, int vd){
    int res=0, i;

    for(i=0;i<g.cv && vd!=(g.vecVer+i)->ver;i++);
    if(i<g.cv){
        for(i=0;i<g.cv && vo!=(g.vecVer+i)->ver;i++);
        if(i<g.cv)
            res=insRelGrafoVRaux(&(g.vecVer+i)->cabRel, vd);
    }
    return(res);
}
/*Funcion auxiliar para Insertar Relacion*/
int insRelGrafoVRaux(REL *lstRel, int v){
    int res=0;
    REL nueva, aux, ant;

    aux=*lstRel;
    while(aux && v>aux->vecRel){
        ant=aux;
        aux=aux->sigRel;
    }
    if(!aux || v<aux->vecRel){
        res=creaNodo(&nueva, v);
        if(res){
            nueva->sigRel=aux;
            if(*lstRel == aux)
                *lstRel=nueva;
            else
                ant->sigRel=nueva;
        }
    }
    return(res);
}
/*Funcion auxiliar para Insertar Relacion*/
int creaNodo(REL *nvo, int v){
    int res=0;

    *nvo=(REL)malloc(sizeof(struct nodoRel));
    if(*nvo){
        (*nvo)->vecRel=v;
        (*nvo)->sigRel=NULL;
        res=1;
    }
    return(res);
}

/*Recorridos dentro del grafo*/
/*Muestra el grafo*/
void muestraVR(GRAFO_VR g){
    int i;
    REL aux;

    for(i=0;i<g.cv;i++){
        printf("Vertice %d:\n", (g.vecVer+i)->ver);
        aux=(g.vecVer+i)->cabRel;
        while(aux){
            printf("%d\t", aux->vecRel);
            aux=aux->sigRel;
        }
        printf("\n");
    }
}

/*Muestra vertices con su numero de relaciones*/
void muestraNoRelsVR(GRAFO_VR g){
    int i, contRels;
    REL aux;

    for(i=0;i<g.cv;i++){
        contRels=0;
        aux=(g.vecVer+i)->cabRel;
        while(aux){
            contRels++;
            aux=aux->sigRel;
        }
        printf("Vertice %d tiene %d", (g.vecVer+i)->ver, contRels);
    }
}

/*Encuentra el vertice mas relacionado*/
void muestraNoRelsVR(GRAFO_VR g, int *idVerMasRel){
    int i, contRels, may=0;
    REL aux;

    for(i=0;i<g.cv;i++){
        contRels=0;
        aux=(g.vecVer+i)->cabRel;
        while(aux){
            contRels++;
            aux=aux->sigRel;
        }
        if(contRels>may){
            may=contRels;
            *idVerMasRel=(g.vecVer+i)->ver;
        }
    }
}

/*Funciones para eliminar una relacion*/
int elimRelVR(GRAFO_VR g, int vo, int vd){
    int res=0, i;

    for(i=0;i<g.cv && vo!=(g.vecVer+i)->ver;i++);
    if(i<g.cv)
        res=elimRelVRaux(&(g.vecVer+i)->cabRel, vd);

    return(res);
}
/*-------FUNCION PERSONAL----------*/
int elimRelVRaux(REL *lr, int vd){
    int res=0;
    REL aux, ant;

    aux=*lr;
    while(aux && vd>aux->vecRel){
        ant=aux;
        aux=aux->sigRel;
    }
    if(aux && vd==aux->vecRel){
        if(aux == *lr)
            *lr=aux->sigRel;
        else
            ant->sigRel=aux->sigRel;
        free(aux);
        res=1;
    }
    return(res);
}

/*-------FUNCION PERSONAL----------*/
/*Funcion para elimiar todos las relaciones de un vertice*/
void elimRelsVerVR()
