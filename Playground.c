#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int nmax;
    int cv;
    int *vecVer;
    int **matRel;
} GRAFO_MR;

int iniGrafoMR(GRAFO_MR *g, int nm);
int insVerMR(GRAFO_MR *g, int v);
int insRelMR(GRAFO_MR g, int vo, int vd);
void muestraGrafo(GRAFO_MR g);
int elimRelMR(GRAFO_MR g, int vo, int vd);
int elimVerMR(GRAFO_MR *g, int v);

int main(){
    GRAFO_MR graf;

    iniGrafo(&graf, 5);
    insVerMR(&graf, 1);
    insVerMR(&graf, 2);
    insVerMR(&graf, 3);
    insRelMR(graf, 1, 2);
    insRelMR(graf, 1, 3);
    insRelMR(graf, 2, 1);
    muestraGrafo(graf);
    elimRelMR(graf, 1, 2);
    elimVerMR(&graf, 3);
}




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