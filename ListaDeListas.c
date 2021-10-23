#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Programa para almacenar los estados de la república junto con sus municipios*/

typedef struct nodoMun{
    char nomMun[25];
    float egMun;
    float pobMun;
    float dpMun;
    struct nodoMun *sigMun;
} *MUN;

typedef struct nodoEdo{
    char nomEdo[25];
    float egEdo;
    float pobEdo;
    float dpEdo;
    MUN cabMun;
    struct nodoEdo *sigEdo;
} *EDO;

/*Función para la inicializadión de estados*/
void iniEdos(EDO *lstEdo){
    *lstEdo=NULL;
}

/*Función para crear nodo municipio*/
int creaNodoMun(MUN *nvoMun, char *nom, float eg, float pMun){
    /*Asignar 0 a dp o calcularlo con base en eg y pob*/
    int res=0;

    *nvoMun=(MUN)malloc(sizeof(struct nodoMun));
    if(*nvoMun){
        strcpy((*nvoMun)->nomMun, nom);
        (*nvoMun)->egMun=eg;
        (*nvoMun)->pobMun=pMun;
        (*nvoMun)->dpMun=0;
        (*nvoMun)->sigMun=NULL;
        res=1;
    }

    return(res);
}

/*Función para crear nodo estado*/
int creaEdo(EDO *nvoEdo, char *nom){
    /*Vamos a dejar pendientes eg, pob, dp. Ya que estos van a depender de sus municipios*/
    int res=0;

    (*nvoEdo)=(EDO)malloc(sizeof(struct nodoEdo));
    if(*nvoEdo){
        strcpy((*nvoEdo)->nomEdo, nom);
        (*nvoEdo)->egEdo = (*nvoEdo)->pobEdo = (*nvoEdo)->dpEdo = 0;
        (*nvoEdo)->cabMun=NULL; /*Inicializando la cabecera de municipios*/
        (*nvoEdo)->sigEdo=NULL;
        /*No los podemos juntar ya que los tipos que manejan son diferentes*/
        res=1;
    }

    return(res);
}

/*Inserción de estado*/
int insEdo(EDO *lstEdo, char *nom){
    int res=0;
    EDO nuevo, ant, aux;

    aux=*lstEdo;
    while(aux && strcmp(nom, aux->nomEdo)>0){
        /*Nos devuelve 1 si  la cadena 'nom' es mayor que 'aux->nomEdo'*/
        ant=aux;
        aux=aux->sigEdo;
    }
    if(!aux || strcmp(nom, aux->nomEdo)<0){ /*Va a ingresar el dato*/
        res=creaNodoEdo(&nuevo, nom);
        if(res){
            nuevo->sigEdo=aux;
            if(*lstEdo == aux) /*Es el primer elemento de la lista*/
                *lstEdo=nuevo;
            else
                ant->sigEdo=nuevo;
        }
    }
    return(res);
}

/*Insersion de estado RECURSIVA*/
int insEdoRec(EDO *lstEdo, char *nom){
    int res;
    EDO nuevo;

    if(!*lstEdo || strcmp(nom, (*lstEdo)->nomEdo)<0){ /*Para insertarlo a la izq del elemento de la lista*/
        res=creaNodoEdo(&nuevo, nom);
        if(res){
            nuevo->sigEdo=*lstEdo;
            *lstEdo=nuevo; /*La recursividad y el parametro por referencia permiten el cambio al anterior*/
        }
    }
    else
        if(strcmp(nom, (*lstEdo)->nomEdo)==0) /*Son iguales los nombres*/
            res=0;
        else
            res=insEdoRec(&(*lstEdo)->sigEdo, nom);

    return(res);
}

/*Insersión de municipio UNA SOLA FUNCION*/
int insMun(EDO lstEdo, char *nEdo, char *nMun, float eg, float pob){
    int res=0;
    MUN nuevo, aux, ant;

    while(lstEdo && strcmp(nEdo, lstEdo->nomEdo)>0) /*Decimos que hay más elementos hacia la derecha*/
        lstEdo->sigEdo;
    if(lstEdo && strcmp(nEdo, lstEdo->nomEdo)==0){
        aux=lstEdo->cabMun;
        while(aux && strcmp(nMun, aux->nomMun)>0){
            ant=aux;
            aux=aux->sigMun;
        }
        if(!aux || strcmp(nMun, aux->nomMun)<0){
            res=creaNodoMun(&nuevo, nMun, eg, pob);
            if(res){
                nuevo->sigMun=aux;
                if(aux == lstEdo->cabMun) /*Es el primero?*/
                    lstEdo->cabMun=nuevo;
                else
                    ant->sigMun=nuevo;
            }
        }
    }

    return(res);
}

/*-------------FUNCION PERSONAL----------------*/
/*Insersión de municipio DOS FUNCIONES*/
/*Utilizando una funcion insMun y una funcion insMunAux con insMunAux ITERATIVO*/
int insMun2(EDO lstEdo, char *nEdo, char *nMun, float eg, float pob){
    int res=0;

    while(lstEdo && strcmp(nEdo, lstEdo->nomEdo)>0)
        lstEdo=lstEdo->sigEdo;
    if(lstEdo && strcmp(nEdo, lstEdo->nomEdo)==0)
        res=insMunAux2(&lstEdo->cabMun, nMun, eg, pob);

    return(res);
}
int insMunAux2(MUN *lstMun, char *nMun, float eg, float pob){
    int res;
    MUN nuevo, aux, ant;

    aux=*lstMun;
    while (aux && strcmp(nMun, aux->nomMun)>0){
        ant=aux;
        aux=aux->sigMun;
    }
    if(!aux || strcmp(nMun, aux->nomMun)<0){/*Si es igual, entonces no lo inserta a la lista*/
        res=creaNodoMun(&nuevo, nMun, eg, pob);
        if(res){
            nuevo->sigMun=aux;
            if(aux == *lstMun)
                *lstMun=nuevo;
            else
                ant->sigMun=nuevo;
        }
    }
    
    return(res);
}

/*-------------FUNCION PERSONAL----------------*/
/*Insersión de municipio DOS FUNCIONES*/
/*Utilizando una funcion insMun y una funcion insMunAux con insMunAux RECURSIVO*/
int insMun3(EDO lstEdo, char *nEdo, char *nMun, float eg, float pob){
    int res=0;

    if(lstEdo && strcmp(nEdo, lstEdo->nomEdo)>0)
        res=insMun3(lstEdo->sigEdo, nEdo, nMun, eg, pob);
    else
        if(lstEdo && strcmp(nEdo, lstEdo->nomEdo)==0);
            res=insMunAux3(&lstEdo->cabMun, nMun, eg, pob);
    
    return(res);
}
int insMunAux3(MUN *lstMun, char *nMun, float eg, float pob){
    int res;
    MUN nuevo;

    if(!*lstMun || strcmp(nMun, (*lstMun)->nomMun)<0){
        res=creaNodoMun(&nuevo, nMun, eg, pob);
        if(res){
            /*No importa cual fue el caso, si la inserción se hizo al inicio o no, las acciones a realizar son las mismas*/
            nuevo->sigMun=*lstMun;
            *lstMun=nuevo;
        }
    }
    else
        if(strcmp(nMun, (*lstMun)->nomMun)==0)
            res=0; /*No se pueden repetir los nombres de los municipios*/
        else
            res=insMunAux3(&(*lstMun)->sigMun, nMun, eg, pob);

    return(res);
}

/*Funcion para capturar Estados*/
void capturaEdos(EDO *lstEdo){
    int res;
    char resp, nom[25];

    do{
        printf("Dame el nombre del estado: ");
        gets(nom);
        res=insEdo(lstEdo, nom);
        if(res){
            printf("Otro?(s/n) ");
            scanf("%c", &resp);
        }
        /*Dependiendo de lo que se quiera:
         -Se puede liberar la lista. Si es que no se pudo introducir completa (Habría que agregar un else 
          y avisar si se pudo meter la lista completa).
         -Se puede dejar incompleta la*/
    }while(res && resp=='s');
}

/*-------------FUNCION PERSONAL----------------*/
/*Funcion para capturar Municipios*/
void capturaMuns(EDO lstEdo){
    int res;
    float eg, pob;
    char resp, nEdo[25], nMun[25];

    do{
        printf("A que estado pertenece: ");
        gets(nEdo);
        printf("Nombre del municipio: ");
        gets(nMun);
        printf("Extensión geográfica: ");
        scanf("%f", &eg);
        printf("Población: ");
        scanf("%f", &pob);
        res=insMun(lstEdo, nEdo, nMun, eg, pob);
        if(res){
            printf("Otro?(s/n) ");
            scanf("%c", &resp);
        }
    }while(res && resp=='s');
}

/*Test de comentario*/