#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodoRel{
    struct nodoVer *rel; /*Direccion del pointer al nodo relacionado*/
    struct nodoRel *sigRel;
} *LST_REL;

typedef struct nodoVer{
    int ver;
    LST_REL cabRel;
    struct nodoVer *sigVer;
} *GRAFO_EN;

/*Inicializacion*/
void iniGrafoEN(GRAFO_EN *g){
    *g=NULL;
}

/*Crea el nodo de un Vertice*/
int creaNodoVer(GRAFO_EN *nvo, int v){
    int res=0;

    *nvo=(GRAFO_EN)malloc(sizeof(struct nodoVer));
    if(*nvo){
        (*nvo)->ver=v;
        (*nvo)->cabRel=NULL;
        (*nvo)->sigVer=NULL;
        res=1;
    }
    return(res);
}

/*----------Funcion Personal-----------*/
/*Inserta Vertice en el grafo de manera ordenada y sin repetir ITERATIVA*/
int insVerEN(GRAFO_EN *g, int v){
    int res=0;
    GRAFO_EN nvoVer, aux, ant;

    aux=*g;
    while(aux && v>aux->ver){
        ant=aux;
        aux=aux->sigVer;
    }
    if(!aux || v<aux->ver){
        res=creaNodoVer(&nvoVer, v);
        if(res){
            nvoVer->sigVer=aux;
            if(aux == *g)
                *g=nvoVer;
            else
                ant->sigVer=nvoVer;
        }
    }
    return(res);
}

/*Inserta Vertice en el grafo de manera ordenada y sin repetir RECURSIVA*/
int insVerENrec(GRAFO_EN *g, int v){
    int res;
    GRAFO_EN nvoVer;

    if(!*g || v<(*g)->ver){
        res=creaNodoVer(&nvoVer, v);
        if(res){
            nvoVer->sigVer=*g;
            *g=nvoVer; /*Al retornar el parametro por referencia, se hace el cambio y el anterior apuntará a nvoVer*/
        }
    }
    else
        if(v == (*g)->ver)
            res=0;
        else
            res=insVerENrec(&(*g)->sigVer, v);
    return(res);
}

/*Funcion para capturar los vertices del grafo*/
void capturaVerEN(GRAFO_EN *g){
    int v;
    char resp;

    do{
        printf("Valor del vertice: ");
        scanf("%d", &v);
        if(insVerENrec(g, v))
            printf("Vertice capturado\n");
        else
            printf("Intento fallido\n");
        printf("Otro?(s/n) ");
        fflush(stdin);
        scanf("%c", &resp);
    }while(tolower(resp)=='s');
}

/*Crea el nodo Relacion*/
int creaNodoRel(LST_REL *nvo, GRAFO_EN r){
    int res=0;

    (*nvo)=(LST_REL)malloc(sizeof(struct nodoRel));
    if(*nvo){
        (*nvo)->rel=r;
        (*nvo)->sigRel=NULL;
        res=1;
    }
    return(res);
}

/*Funcion AUXiliar para instertar una relacion(en la lista de relaciones del vertice)
  de forma ordenada, sin repeticion*/
int insRel(LST_REL *rels, GRAFO_EN rela){
    int res;
    LST_REL nvaRel;

    if(!*rels || rela<(*rels)->rel){ /*Se estan comparando las direcciones de memoria*/
        res=creaNodoRel(&nvaRel, rela);
        if(res){
            nvaRel->sigRel=*rels;
            *rels=nvaRel; /*Al retornar el parametro por referencia, se hace el cambio y el anterior apuntará a nvaRel*/
        }
    }
    else
        if(rela == (*rels)->rel)
            res=0; /*No se aceptan repetidos*/
        else
            res=insRel(&(*rels)->sigRel, rela);
    return(res);
}
/*Funcion que llama de insRel que inserta la relacion en la lista de relaciones correcta*/
int insRelEN(GRAFO_EN g, int vo, int vd){
    int res=0;
    GRAFO_EN auxB; /*Auxiliar para la Busqueda*/

    /*Primero se busca la existencia del vertice destino*/
    for(auxB=g; auxB && vd>auxB->ver; auxB=auxB->sigVer);
    if(auxB && vd==auxB->ver){
        for(; g && vo>g->ver; g=g->sigVer);
        if(g && vo==g->ver)
            res=insRel(&g->cabRel, auxB);
    }
    return(res);
}

/*Funcion de captura de relaciones del grafo*/
void capturaRelEN(GRAFO_EN g){
    int vo, vd;
    char resp;

    do{
        printf("Vertice origen: ");
        scanf("&d", &vo);
        printf("Vertice destino: ");
        scanf("&d", &vd);
        if(insRelEN(g, vo, vd))
            printf("Relacion agregada\n");
        else
            printf("Intento fallido\n");
        printf("Otro?(s/n) ");
        fflush(stdin);
        scanf("%c", &resp);
    }while(tolower(resp)=='s');
}

/*Funcion para Mostrar el grado RECORRIDO*/
void muestraGrafoEN(GRAFO_EN g){
    LST_REL aux;

    for(; g; g=g->sigVer){
        printf("%d: ", g->ver);
        for(aux=g->cabRel; aux; aux=aux->sigRel)
            printf("%5d", aux->rel->ver);
        printf("\n");
    }
}

/*Funcion que muestra los vertices con la cantidad de relaciones que tiene*/
void muestraVerNoRels(GRAFO_EN g){
    int cont;
    LST_REL aux;

    for(; g; g=g->sigVer){
        cont=0;
        for(aux=g->cabRel; aux; aux=aux->sigRel)
            cont++;
        printf("%d: %d relaciones ", g->ver, cont);
    }
}

/*Funcion que retorna el vertice con mas relaciones*/
int buscaVerMasRelEN(GRAFO_EN g){
    int cont, may=0, vecMay;
    LST_REL aux;

    while(g){
        cont=0;
        aux=g->cabRel;
        while(aux){
            cont++;
            aux=aux->sigRel;
        }
        if(cont>may){
            vecMay=g->ver;
            may=cont;
        }
        g=g->sigVer;
    }
    return(vecMay);
}

/*Funcion AUXiliar para eliminar una relacion de la lista de relaciones del vertice origen*/
int eliminaRel(LST_REL *rels, GRAFO_EN r){
    int res;
    LST_REL auxRel;

    if(!*rels || r<(*rels)->rel)
        res=0;
    else
        if(r==(*rels)->rel){
            auxRel=*rels;
            *rels=auxRel->sigRel;
            free(auxRel);
            res=1;
        }
        else
            res=eliminaRel(&(*rels)->sigRel, r);
    return(res);
}
/*Funcion para eliminar una relacion en el grafo, llamando a eliminaRel(preEscrita)*/
int eliminaRelEN(GRAFO_EN g, int vo, int vd){
    int res=0;
    GRAFO_EN auxB; /*auxiliar de Búsqueda*/

    /*Busqueda el vertice de destino o vertice final*/
    for(auxB=g; auxB && vd>auxB->ver; auxB=auxB->sigVer);
    if(auxB && vd==auxB->ver){
        for(; g && vo>g->ver; g=g->sigVer);
        if(g && vo==g->ver)
            res=eliminaRel(&g->cabRel, auxB);
    }
    return(res);
}

int eliminaVerEN(GRAFO_EN *g, int v){
    int res;
    GRAFO_EN auxB, auxVerAnt;
    LST_REL auxRel, aux;

    for(auxB=*g; auxB && v>auxB->ver; auxVerAnt=auxB, auxB=auxB->sigVer);
    if(auxB && v==auxB->ver){
        /*Se Elimina su lista de relaciones*/
        auxRel=auxB->cabRel;
        while(auxRel){
            /*Se va a ir eliminando el primer elemento de la lista
              y los demas nodos se irán recorriendo*/
            aux=auxRel;
            auxRel=aux->sigRel;
            free(aux);
        }
        /*Se elimina el vertice*/
        if(auxB==*g)
            *g=auxB->sigVer;
        else
            auxVerAnt->sigVer=auxB->sigVer;
        free(auxB);

        /*Se eliminan las relaciones de los otros vertices con el eliminado*/
        for(auxVerAnt=*g; auxVerAnt; auxVerAnt=auxVerAnt->sigVer)
            eliminaRel(&auxVerAnt->cabRel, auxB);
        res=1;
    }
    return(res);
}