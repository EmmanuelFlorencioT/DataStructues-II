#include<stdio.h>
#include<stdlib.h>

/*Estructura que maneja una lista*/
typedef struct nodo{
    int info;
    struct nodo *liga;
} *LISTA;



/*Función para inicializar una lista*/
void iniLista(LISTA *cab){
    *cab=NULL;
}

/*Funcion para crear nodo*/
int creaNodo(LISTA *nvo, int dato){
    int res=0;

    *nvo=(LISTA)malloc(sizeof(struct nodo));
    if(*nvo){
        res=1;
        (*nvo)->info=dato;
        (*nvo)->liga=NULL;
    }
    return(res);
}

/*Función para hacer una inserción*/
int insIni(LISTA *cab, int dato){
    int res;
    LISTA nuevo; /*Es el apuntador a nodo que crea el nodo*/

    res=creaNodo(&nuevo, dato);
    if(res){
        nuevo->liga=*cab;
        *cab=nuevo; /*Inevitablemente hay que hacer que la cabecera apunte a donde apunta nuevo*/
    }
    return(res);
}

/*Funcion para capturar datos en una lista*/
int capturaDatos(LISTA *cab){
    int res, dato;
    char resp;

    do{
        printf("Introduce el dato: ");
        scanf("%d", &dato);
        res=insIni(cab, dato); /* Se abrevió '&*cab' */
        if(res){
            printf("Dato ingresado\n");
            printf("Desea ingresar otro?(s/n) ");
            fflush(stdin);
            scanf("%c", &resp);
        }
    } while(res && resp=='s');
    return(res);
}

/*Función para insertar los datos de un arreglo en una lista (vacía)*/
int arrToList(int arr[], int n, LISTA *cab){
    int res=1, i;

    for(i=0;i<n && res;i++)
        res=insIni(cab, arr[i]);

    return(res); /* res=1 si se pudo ingresar TODO el arreglo a la lista*/
}

/*Funcion para hacer el RECORRDIO ==> Acceso a los datos.  De una lista*/
void recorre(LISTA cab){
    while(cab){ /* cab!=NULL */
        /*Aquí es donde se pone el que hacer con los datos*/
        cab = cab->liga;
    }
}

/*Debido a que while y for son exactamente iguales...
  Aquí está la misma funcion con for...*/

void recorre(LISTA cab){
    /* En el primer apartado como cab ya tiene guardado el valor inicial
      no hay necesidad de inicializarlo */
    /* En el siguiente apartado, la condición para continuar con el ciclo
      es que 'cab!=NULL' pero abreviado a 'cab' */
    for( ; cab ; cab=cab->liga)
        /*Aquí se se ponen las instrucciones de que hacer con los datos*/
        printf("%d\t", cab->info);
}

/*Función para hacer una inserción al final*/
int insFinal(LISTA *cab, int dato){
    int res;
    LISTA nvo, aux;

    res=creaNodo(&nvo, dato);
    if(res) /*Adentro de este if, hay un if completo (if con else), no necesita llaves*/
        if(!*cab)
            *cab=nvo;
        else{
            aux=*cab;
            while(aux->liga)
                aux=aux->liga;
            aux->liga=nvo;
        }
    return(res);
}

/*Función para hacer una inserción al final RECURSIVA*/
int insFinalRec(LISTA *cab, int dato){
    int res;

    if(!*cab)
        res=creaNodo(cab, dato); /*El nodo se crea y se asigna directamente a la cabecera*/
    else
        if(!(*cab)->liga)
            res=creaNodo(&(*cab)->liga, dato);
        else
            res=insFinal(&(*cab)->liga, dato);

    return(res);
}
/*Función para hacer una inserción al final RECURSIVA OPTIMIZADO*/
int insFinalRecOpt(LISTA *cab, int dato){
    int res;

    if(!*cab)
        res=creaNodo(cab, dato);
    else
        res=insFinalRecOpt(&(*cab)->liga, dato);

    return(res);
}

/*Función para insertar un dato a la izquierda de otro dato referencia de la lista*/
int insRefIzq(LISTA *cab, int dato, int ref){
    int res=0;
    LISTA nvo, aux, ant;

    aux=*cab;
    while(aux && ref!=aux->info){ /*Ciclo de búsqueda*/
        ant=aux;
        aux=aux->liga;
    }
    if(aux){ /*Si 'aux' apunta a algo quiere decir que si lo encontró*/
        res=creaNodo(&nvo, dato);
        if(res){
            nvo->liga=aux;
            if(*cab == aux)
                *cab=nvo;
            else
                ant->liga=nvo;
        }
    }

    return(res);
}

/*Función para eliminar el primer dato de una lista*/
int eliminaIni(LISTA *cab){
    int res=0;
    LISTA aux;

    if(*cab){
        aux=*cab;
        *cab=aux->liga;
        free(aux);
        res=1;
    }

    return(res);
}

/*Función para eliminar el primer nodo de una lista pero recuperando su valor*/
int eliminaIniRecup(LISTA *cab, int *dato){
    int res=0;
    LISTA aux;

    if(*cab){
        aux=*cab;
        *dato=aux->info;
        *cab=aux->liga;
        free(aux);
        res=1;
    }

    return(res);
}

/*Función para eliminar el nodo del final de una lista RECURSIVA*/
int elimFinRec(LISTA *cab){
    int res;

    if(!*cab)
        res=0;
    else
        if(!(*cab)->liga){
            free(*cab);
            *cab=NULL;
            res=1;
        }
        else
            res=elimFinRec(&(*cab)->liga);

    return(res);
}

/*----------------------FUNCIÓN PERSONAL--------------------*/
/*Función para eliminar el nodo del final de una lista*/
int elimFin(LISTA *cab){
    int res;
    LISTA aux, ant;

    if(*cab)
        if(!(*cab)->liga){
            free(*cab);
            *cab=NULL;
            res=1;
        }
        else{
            aux=*cab;
            while((*cab)->liga){
                ant=aux;
                aux=aux->liga;
            }
            free(aux);
            ant->liga=NULL;
            res=1;
        }
    else
        res=0;
}

/*----------------------FUNCIÓN PERSONAL--------------------*/
/*Función para eliminar un dato por referencia de una lista*/
int elimRef(LISTA *cab, int ref){
    int res=0;
    LISTA aux, ant;

    if(*cab){
        aux=*cab;
        while(aux && aux->info != ref){
            ant=aux;
            aux=aux->liga;
        }
        if(aux){
            if(aux == *cab){ /*Fue el primer elemento?*/
                if(aux->liga) /*No es el único elemento de la lista*/
                    *cab=aux->liga;
                else /*Cerrar la lista vacía*/
                    *cab=NULL;
            }
            else{
                if(aux->liga) /*No es el último elemento de la lista*/
                    ant->liga=aux->liga;
                else /*La coincidencia vino en el último elemento de la lista*/
                    ant->liga=NULL; /*Cerramos la lista*/ 
            }
            free(aux);
            res=1;
        } /*Si este if no se cumple, res=0;*/
    } /*Si este if no se cumple, res=0;*/

    return(res);
}

/*----------------------FUNCIÓN PERSONAL--------------------*/
/*Función para eliminar un dato por referencia de una lista RECURSIVA*/
int elimRefRec(LISTA *cab, int ref){
    int res;
    LISTA aux;

    if(!*cab)
        res=0;
    else
        if(ref == (*cab)->info)
            if(!(*cab)->liga){
                free(*cab);
                *cab=NULL;
                res=1;
            }
            else{
                aux=*cab;
                *cab=(*cab)->liga;
                free(aux);
                res=1;
            }
        else
            res=elimRefRec(&(*cab)->liga, ref);

    return(res);
}
