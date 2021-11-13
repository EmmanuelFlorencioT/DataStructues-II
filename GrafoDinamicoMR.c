#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int nmax;
    int cv;
    int *vecVer;
    int **matRel;
} GRAFO_MR;

/*INICIALIZACION*/
int iniGrafoMR(GRAFO_MR *g, int nm){
    int res=0, ren;

    g->vecVer=(int *)malloc(sizeof(int)*nm);
    if(g->vecVer){
        g->matRel=(int **)malloc(sizeof(int *)*nm);
        if(g->matRel){
            res=1;
            for(ren=0;ren<nm && res;ren++){
                *(g->matRel+ren)=(int *)malloc(sizeof(int)*nm);
                if(!*(g->matRel+ren)){
                    res=0;
                    while(--ren >= 0)
                        free(*(g->matRel+ren));
                    free(g->matRel);
                    free(g->vecVer);
                }
            }
            if(res){
                g->nmax=nm;
                g->cv=0;
            }
        }
    }
    return(res);
}

/*INSERCION DE VERTICE*/
int insVerMR(GRAFO_MR *g, int v){
    int res=0, i;

    if(g->cv < g->nmax){
        *(g->vecVer+g->cv)=v;
        for(i=0;i<=g->cv;i++)
            *(*(g->matRel+g->cv)+i) = *(*(g->matRel+i)+g->cv) = 0;
        g->cv++;
        res=1;
    }
    return(res);
}

/*INSERCION DE RELACION*/
int insRelMR(GRAFO_MR g, int vo, int vd){
    int res=0, col, ren;

    /*Ciclo de búsqueda del vector origen*/
    for(ren=0; ren<g.cv && vo!=*(g.vecVer+ren);ren++);
    if(ren<g.cv){ /*Será true cuando encuentre el vector origen*/
        /*Ciclo de búsqueda del vector destino*/
        for(col=0;col<g.cv && vd!=*(g.vecVer+col);col++);
        if(col<g.cv)
            *(*(g.matRel+ren)+col)=res=1;
    }
    return(res);
}

/*ELIMINACION DE RELACION*/
int elimRelMR(GRAFO_MR g, int vo, int vd){
    int res=0, col, ren;

    for(ren=0; ren<g.cv && vo!=*(g.vecVer+ren);ren++);
    if(ren<g.cv){
        for(col=0;col<g.cv && vd!=*(g.vecVer+col);col++);
        if(col<g.cv){
            *(*(g.matRel+ren)+col)=0;
            res=1;
        }
    }
    return(res);
}

int elimVerMR(GRAFO_MR *g, int v){
    int res=0, pos, i;

    for(pos=0; pos<g->cv && v!=*(g->vecVer+pos);pos++);
    if(pos<g->cv){
        g->cv--;
        *(g->vecVer+pos)=*(g->vecVer+g->cv);
        for(i=0;i<=g->cv;i++){
            *(*(g->matRel+pos)+i)=*(*(g->matRel+g->cv)+i);
            *(*(g->matRel+i)+pos)=*(*(g->matRel+i)+g->cv);
        }
        res=1;
    }
    return(res);
}

/*Función de captura de vértices*/
void capturaVers(GRAFO_MR *g){
    int ver, res;
    char resp;

    do{
        printf("Ingrese el vertice: ");
        scanf("%d", &ver);
        res=insVerMR(g, ver);
        if(res){
            printf("Dato agregado\nOtro?(s/n)");
            fflush(stdin);
            scanf("%d", &resp);
        }
        else
            printf("Dato no agregado\n");
    }while(res && resp=='s');
}

/*Funcion de inserción de relaciones*/
void insRels(GRAFO_MR g){
    int res, verO, verD;
    char resp;

    do{
        printf("Vertice origen: ");
        scanf("%d", &verO);
        printf("Vertice destino: ");
        scanf("%d", &verD);
        res=insRelMR(g, verO, verD);
        if(res)
            printf("Vertices relacionados\n");
        else
            printf("Vertices no relacionados\n");
        printf("Dato agregado\nOtro?(s/n)");
        fflush(stdin);
        scanf("%d", &resp);
    }while(res && resp=='s');
}

/*RECORRIDO DEL GRAFO
    Mostrar la información del grafo de la manera:
    A=> B C
    B=> A D
    D=> B D F
*/
void muestraGrafo(GRAFO_MR g){
    int ren, col;

    for(ren=0;ren<g.cv;ren++){
        printf("%d=> ", *(g.vecVer+ren));
        for(col=0;col<g.cv;col++)
            if(*(*(g.matRel+ren)+col))
                printf("%d ", *(g.vecVer+ren));
            printf("\n");
    }
}

/*Funcion para mostrar cada vértice con el no. de relaciones*/
void muestraVerConNoRels(GRAFO_MR g){
    int ren, col, cont;
    
    for(ren=0;ren<g.cv;ren++){
        cont=0;
        for(col=0;col<g.cv; col++)
            cont+=*(*(g.matRel+ren)+col);
        printf("%d tiene %d relaciones\n", *(g.vecVer+ren), cont);
    }
}

/*Funcion para encontrar el vértice más relacionado*/
void muestraVerConNoRels(GRAFO_MR g, int *vMasRel){
    int ren, col, cont, may=0;
    
    for(ren=0;ren<g.cv;ren++){
        cont=0;
        for(col=0;col<g.cv; col++)
            cont+=*(*(g.matRel+ren)+col);
        if(cont>may){
            may=cont;
            *vMasRel=*(g.vecVer+ren);
        }
    }
}

/*Funcion para determinar si hay (1) o no hay (0) relacion entre 2 vértices dados*/
int hayRelMR(GRAFO_MR g, int vo, int vd){
    int res=0, ren, col;
    
    for(ren=0; ren<g.cv && vo!=*(g.vecVer+ren);ren++);
    if(ren<g.cv){
        for(col=0;col<g.cv && vd!=*(g.vecVer+col);col++);
            if(col<g.cv)
                res=*(*(g.matRel+ren)+col);
    }
    return(res);
}