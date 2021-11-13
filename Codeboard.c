/*
  INSTRUCCIONES
  1.- Escribir el código correspondiente a cada función.
  2.- ** Solo ** implementar las partes de código faltantes, ** no ** modificar el código ya escrito.
  3.-  No agregar mas funciones, solo son necesarias las incluidas.
  
  Nombre del alumno: "Emmanuel Florencio Trujillo"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estructura ingrediente */
typedef struct nodoIngre
{ 
  char nomIngre[25];
  struct nodoIngre *sigIngre;
} *LISTA_INGRE;

/* Estructura receta */
typedef struct nodoRece
{
  char nomRece[25];
  LISTA_INGRE cabIngre;
  struct nodoRece *sigRece;
} *LISTA_RECE;

/* Estructura tipo receta */
typedef struct nodoTipo
{
  char nomTipo[25];
  LISTA_RECE cabRece;
  struct nodoTipo *sigTipo;
} *RECETARIO;

/* Esta función inicializa el recetario */
void iniRecetario(RECETARIO *r);

/* Esta función creará un nodo ingrediente */
int creaNodoIngre(LISTA_INGRE *nuevo, char *ingre);

/* Esta función creará un nodo receta */
int creaNodoRece(LISTA_RECE *nuevo, char *rece);

/* Esta función creará un nodo tipo-receta */
int creaNodoTipo(RECETARIO *nuevo, char *tipo);

/* Esta función busca el tipo de receta donde según la receta se insertará el ingrediente */
int insIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre);

/* Esta función busca la receta donde insertará el ingrediente */
int insIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre);

/* Esta función inserta el ingrediente */
int insIngre(LISTA_INGRE *li, char *ingre);

/* Esta función busca el tipo de receta donde se inserta la receta */
int insReceta(RECETARIO r, char *tipo, char *rece);

/* Esta función inserta una receta */
int insRece(LISTA_RECE *lr, char *rece);

/* Esta función inserta un tipo de receta */
int insTipo(RECETARIO *r, char *tipo);

/* Esta Función captura los tipos de recetas, para insertarlos en el recetario */
void capturaTipos(RECETARIO *r);

/* Esta Función captura las recetas, para insertarlas en el recetario */
void capturaRecetas(RECETARIO r);

/* Esta Función captura los ingredientes, para insertarlos en el recetario */
void capturaIngredientes(RECETARIO r);

/* Esta función muestra toda la información del rcetario */
void muestraRecetario(RECETARIO r);

/* Esta función muestra las recetas de un tipo de receta */
void muestraRecetasTipo(RECETARIO r, char *tipo);

/* Esta función muestra los ingredientes de una receta */
void muestraIngredientesReceta(RECETARIO r, char *tipo, char *rece);

/* Esta función muestra el No. de receta que tiene cada tipo de receta */
void muestraNoReceXtipo(RECETARIO r);

/* Esta función muestra el No. de ingredientes de cadad receta */
void muestraNoIngreXrece(RECETARIO r);

/* Esta función calcula y retorna cuantos tipos de recta tiene un recetario */
int cuentaTipos(RECETARIO r);

/* Esta función busca el tipo de receta para contar cuantas recetas tiene
   se usa como base para la siguiente función 
  */
int cuentaRecetas(RECETARIO r, char *tipo);

/* Esta función cuenta el No. de recetas de un tipo previamente buscado */
int cuentaRece(LISTA_RECE lr);

/* Esta función busca el tipo de receta como base para la siguiente función */
int cuentaIngredientes(RECETARIO r, char *tipo, char *rece);

/* Esta función busca una receta para poder contar cuantas recetas tiene
   se usa como base para la siguiente función 
 */
int cuentaIngreBuscaRece(LISTA_RECE lr, char *rece);

/* Esta función cuenta el No. de ingredientes de una receta previamente buscada,
   que pertece a un tipo también previamente buscado.
 */
int cuentaIngre(LISTA_INGRE li);

/* Esta función encuentra el nombre del tipo de receta con mas recetas(TMR) */
void encuentraTMR(RECETARIO r, char *nomTMR);

/* Esta función encuentra el nombre de la receta con mas ingredientes (RMI) 
   así como también el tipo al que pertenece */
void encuentraRMI(RECETARIO r, char *tipoRMI, char *nomRMI);

/* Esta función cuenta el número de recetas que usan un ingrediente */
int cuentaReceIngre(RECETARIO r, char *ingre);

/* Esta función elimina un ingrediente, despues de haber encontrado su
   receta y tipo al que pertenece */
int eliminaIngre(LISTA_INGRE *li, char *ingre);

/* Esta función busca la receta para poder eliminar el ingrediente */
int eliminaReceIngre(LISTA_RECE lr, char *rece, char *ingre);

/* Esta función busca el tipo de receta, para ubicar la lista de recetas
   donde se ubica el ingrediente a eliminar 
 */
int eliminaIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre);

/* Esta función elimina todos los ingredientes de una receta */
void eliminaIngredientes(LISTA_INGRE *li);

/* Función para buscar una receta y poder eliminar sus ingredientes */
int eliminaIngresBuscaReceXreceta(LISTA_RECE *lr, char *rece);

/* Esta función elimina todas las recetas de un tipo, eliminando
   previamente todos los ingredientes  */
void eliminaRecetas(LISTA_RECE lr);

/* Esta función elimina un tipo de receta */
int eliminaTipo(RECETARIO *r, char *tipo);

/* Esta función elimina un recetario completo */
void eliminaRecetario(RECETARIO *r);

//#include "evalua/evaluar.h"

int main()
{
  /* Puede escribir a continuación el código necesario para probar sus funciones
     aunque no es necesario */ 
     
     
 /* NO BORRAR ESTA LINEA */
  //evaluar();    
}

/* Función para inicualizar la estructura principal */
void iniRecetario(RECETARIO *r)
{
   *r=NULL;
}

/* Función para crear un nodo ingrediente */
int creaNodoIngre(LISTA_INGRE *nuevo, char *ingre)
{
   int res=0;

   *nuevo=(LISTA_INGRE)malloc(sizeof(struct nodoIngre));
   if(*nuevo){
      strcpy((*nuevo)->nomIngre, ingre);
      (*nuevo)->sigIngre=NULL;
      res=1;
   }
   return(res);
}

/* Función para crear un nodo receta */
int creaNodoRece(LISTA_RECE *nuevo, char *rece)
{
   int res=0;

   *nuevo=(LISTA_RECE)malloc(sizeof(struct nodoRece));
   if(*nuevo){
      strcpy((*nuevo)->nomRece, rece);
      (*nuevo)->cabIngre=NULL;
      (*nuevo)->sigRece=NULL;
      res=1;
   }
   return(res);
}

/* Función para crear un nodo tipo */
int creaNodoTipo(RECETARIO *nuevo, char *tipo)
{
   int res=0;

   *nuevo=(RECETARIO)malloc(sizeof(struct nodoTipo));
   if(*nuevo){
      strcpy((*nuevo)->nomTipo, tipo);
      (*nuevo)->cabRece=NULL;
      (*nuevo)->sigTipo=NULL;
      res=1;
   }
   return(res);
}

/* Inserta ingrediente: Función para insertar el ingrediente */
int insIngre(LISTA_INGRE *li, char *ingre)
{
   int res;
   LISTA_INGRE aux, ant, nvo;

   aux=*li;
   while(aux && strcmp(ingre, aux->nomIngre)>0){
      ant=aux;
      aux=aux->sigIngre;
   }
   if(!aux || strcmp(ingre, aux->nomIngre)<0){
      res=creaNodoIngre(&nvo, ingre);
      if(res){
         nvo->sigIngre=aux;
         if(aux == *li)
            *li=nvo;
         else
            ant->sigIngre=nvo;
      }
   }
   return(res);
}

/* Inserta ingrediente: Función para buscar la receta */
int insIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre)
{
   int res=0;

   while(lr && strcmp(rece, lr->nomRece)>0)
      lr=lr->sigRece;
   if(lr && strcmp(rece, lr->nomRece)==0)
      res=insIngre(&(lr->cabIngre), ingre);

   return(res);
}

/* Inserta ingrediente: Función para buscar el tipo */
int insIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre)
{
   int res=0;

   while(r && strcmp(tipo, r->nomTipo)>0)
      r=r->sigTipo;
   if(r && strcmp(tipo, r->nomTipo)==0)
      res=insIngreBuscaRece(r->cabRece, rece, ingre);

   return(res);
}

/* Inserta receta: Función para insertar la receta */
int insRece(LISTA_RECE *lr, char *rece)
{
   int res=0;
   LISTA_RECE aux, ant, nvo;

   aux=*lr;
   while(aux && strcmp(rece, aux->nomRece)>0){
      ant=aux;
      aux=aux->sigRece;
   }
   if(!aux || strcmp(rece, aux->nomRece)<0){
      res=creaNodoRece(&nvo, rece);
      if(res){
         nvo->sigRece=aux;
         if(aux == *lr)
            *lr=nvo;
         else
            ant->sigRece=nvo;
      }
   }
   return(res);
}

/* Inserta receta: Función para buscar el tipo de la receta */
int insReceta(RECETARIO r, char *tipo, char *rece)
{
   int res=0;

   while(r && strcmp(tipo, r->nomTipo)>0)
      r=r->sigTipo;
   if(r && strcmp(tipo, r->nomTipo)==0)
      res=insRece(&r->cabRece, rece);

   return(res);
}

/*Función para insertar un tipo de receta */
int insTipo(RECETARIO *r, char *tipo)
{
   int res=0;
   RECETARIO aux, ant, nvo;

   aux=*r;
   while(aux && strcmp(tipo, aux->nomTipo)>0){
      ant=aux;
      aux=aux->sigTipo;
   }
   if(!aux || strcmp(tipo, aux->nomTipo)<0){
      res=creaNodoTipo(&nvo, tipo);
      if(res){
         nvo->sigTipo=aux;
         if(aux == *r)
            *r=nvo;
         else
            ant->sigTipo=nvo;
      }
   }
   return(res);
}

/* Función para capturar Tipos de recetas, inserlos en el recetario */
void capturaTipos(RECETARIO *r)
{
   int res;
   char resp, tipo[25];

   do{
      printf("Introduce el tipo de receta: ");
      gets(tipo);
      res=insTipo(r, tipo);
      if(res){
         printf("Tipo de receta agregado\n");
         printf("Otro?(s/n) ");
         fflush(stdin);
         scanf("%c", &resp);
      }
      else
         printf("No se agrego el tipo, intente mas tarde");
   }while(res && resp=='s');
}

/* Función para captura las recetas, insertarlas en recetario en el tipo al que pertenecen */
void capturaRecetas(RECETARIO r)
{
   int res;
   char resp, tipo[25], rece[25];

   do{
      printf("Introduce la receta: ");
      gets(rece);
      printf("Introduce el tipo de receta: ");
      gets(tipo);
      res=insReceta(r, tipo, rece);
      if(res){
         printf("Receta agregada a %s\n", tipo);
         printf("Desea agregar otra?(s/n) ");
         fflush(stdin);
         scanf("%c", &resp);
      }
      else
         printf("No se agrego la receta, intente mas tarde");
   }while(res && resp=='s');
}

/* Esta Función captura los ingredientes, para insertarlos en el recetario */
void capturaIngredientes(RECETARIO r)
{
   int res=0;
   char resp, tipo[25], rece[25], ingre[25];

   do{
      printf("Introduce el ingrediente: ");
      gets(ingre);
      printf("Introduce la receta: ");
      gets(rece);
      printf("Introduce el tipo de receta: ");
      gets(tipo);
      res=insIngrediente(r, tipo, rece, ingre);
      if(res){
         printf("Ingrediente agregado a %s, dentro de %s\n", rece, tipo);
         printf("Desea agregar otro?(s/n) ");
         fflush(stdin);
         scanf("%c", &resp);
      }
      else
         printf("No se puedo agregar el ingrediente, intente mas tarde");
   }while(res && resp=='s');
}

/* Función para mostrar el recetario completo */
void muestraRecetario(RECETARIO r)
{
   LISTA_RECE auxR;
   LISTA_INGRE auxI;

   printf("Recetario:\n\n");
   while(r){
      printf("Tipo: %s\n", r->nomTipo);
      auxR=r->cabRece;
      while(auxR){
         printf("\tNombre de la receta: %s\n", auxR->nomRece);
         auxI=auxR->cabIngre;
         printf("\tIngradientes:\n");
         while(auxI){
            printf("\t\t%s\n", auxI->nomIngre);
            auxI=auxI->sigIngre;
         }
         printf("\n");
         auxR=auxR->sigRece;
      }
      printf("\n\n");
      r->sigTipo;
   }
}

/* Función para contar el No. de tipos de recetas */
int cuentaTipos(RECETARIO r)
{
   int cont=0;
   
   while(r){
      cont++;
      r=r->sigTipo;
   }
   return(cont);
}

/* Cuenta Recetas: Función para contar las recetas */
int cuentaRece(LISTA_RECE lr)
{
   int cont=0;

   while(lr){
      cont++;
      lr=lr->sigRece;
   }
   return(cont);
}

/* Cuenta Recetas: Función para buscar el tipo de las recetas a contar*/
int cuentaRecetas(RECETARIO r, char *tipo)
{
   int cont;

   while(r && strcmp(tipo, r->nomTipo)>0)
      r->sigTipo;
   if(r && strcmp(tipo, r->nomTipo)==0)
      cont=cuentaRece(r->cabRece);

   return(cont);
}

/* Cuenta ingredientes:Función para buscar el tipo */
int cuentaIngredientes(RECETARIO r, char *tipo, char *rece)
{
   int cont;

   while(r && strcmp(tipo, r->nomTipo)>0)
      r->sigTipo;
   if(r && strcmp(tipo, r->nomTipo)==0)
      cont=cuentaIngreBuscaRece(r->cabRece, rece);
}

/* Cuenta ingredientes: Función para buscar la receta */
int cuentaIngreBuscaRece(LISTA_RECE lr, char *rece)
{
   int cont;

   while(lr && strcmp(rece, lr->nomRece)>0)
      lr=lr->sigRece;
   if(lr && strcmp(rece, lr->nomRece)==0)
      cont=cuentaIngre(lr->cabIngre);

   return(cont);
}

/* Función para contar los ingredientes */
int cuentaIngre(LISTA_INGRE li)
{
   int cont=0;

   while(li){
      cont++;
      li=li->sigIngre;
   }
   return(cont);
}

/* Función para contar y mostrar el No. de recetas en cada tipo */
void muestraNoRece(RECETARIO r)
{
   int cont;
   LISTA_RECE auxR;

   while(r){
      auxR=r->cabRece;
      cont=0;
      while(auxR){
         cont++;
         auxR=auxR->sigRece;
      }
      printf("De %s tiene %d recetas\n", r->nomTipo, cont);
      r=r->sigTipo;
   }
}

/* Función para contar y mostrar el No. de ingredientes por cada receta */
void muestraNoIngre(RECETARIO r)
{
   int cont;
   LISTA_RECE auxR;
   LISTA_INGRE auxI;

   while(r){
      auxR=r->cabRece;
      while(auxR){
         auxI=auxR->cabIngre;
         cont=0;
         while(auxI){
            cont++;
            auxI=auxI->sigIngre;
         }
         printf("La receta %s tiene %d ingredientes\n", auxR->nomRece, cont);
         auxR=auxR->sigRece;
      }
      r=r->sigTipo;
   }
}

/* Función para encontrar el nombre del Tipo de receta con Mas Recetas(TMR) */
void encuentraTMR(RECETARIO r, char *nomTMR)
{
   int cont, may=0;
   LISTA_RECE aux;

   while(r){
      aux=r->cabRece;
      cont=0;
      while(aux){
         cont++;
         aux=aux->sigRece;
      }
      if(cont>may){
         may=cont;
         strcpy(nomTMR, r->nomTipo);
      }
      r=r->sigTipo;
   }
}

/* Función para encontrar el nombre de la Receta con Mas Ingredientes(RMI) 
   así como también el tipo al que pertenece */
void encuentraRMI(RECETARIO r, char *tipoRMI, char *nomRMI)
{
   int cont, may=0;
   LISTA_RECE auxR;
   LISTA_INGRE auxI;

   while(r){
      auxR=r->cabRece;
      while(auxR){
         auxI=auxR->cabIngre;
         cont=0;
         while(auxI){
            cont++;
            auxI=auxI->sigIngre;
         }
         if(cont>may){
            strcpy(nomRMI, auxR->nomRece);
            strcpy(tipoRMI, r->nomTipo);
            may=cont;
         }
         auxR=auxR->sigRece;
      }
      r=r->sigTipo;
   }
}

/* Función para contar el número de recetas que usan un ingrediente */
int cuentaReceIngre(RECETARIO r, char *ingre)
{
   int cont=0;
   LISTA_RECE auxR;
   LISTA_INGRE auxI;

   while(r){
      auxR=r->cabRece;
      while(auxR){
         auxI=auxR->cabIngre;
         while(auxI){
            if(strcmp(ingre, auxI->nomIngre)==0)
               cont++;
            auxI=auxI->sigIngre;
         }
         auxR=auxR->sigRece;
      }
      r=r->sigTipo;
   }
   return(cont);
}

/* Función para elimina un ingrediente, despues de haber encontrado su receta
   y tipo al que pertenece */
int eliminaIngre(LISTA_INGRE *li, char *ingre)
{
   int res=0;
   LISTA_INGRE aux, ant=NULL;

   aux=*li;
   while(aux && strcmp(ingre, aux->nomIngre)>0){
      ant=aux;
      aux=aux->sigIngre;
   }
   if(aux && strcmp(ingre, aux->nomIngre)==0){
      if(ant)
         ant->sigIngre=aux->sigIngre;
      else
         *li=aux->sigIngre;
      free(aux);
      res=1;
   }
   return(res);
}

/* Función para buscar la receta a la que pertenece el ingrediente a eliminar*/
int eliminaIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre)
{
   int res=0;

   while(lr && strcmp(rece, lr->nomRece)>0)
      lr=lr->sigRece;
   if(lr && strcmp(rece, lr->nomRece)==0)
      res=eliminaIngre(&lr->cabIngre, ingre);

   return(res);
}

/* Esta función busca el tipo de receta, al que pertenece la receta del
   ingrediente a eliminar */
int eliminaIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre)
{
   int res=0;

   while(r && strcmp(tipo, r->nomTipo)>0)
      r=r->sigTipo;
   if(r && strcmp(tipo, r->nomTipo)==0)
      res=eliminaIngreBuscaRece(r->cabRece, rece, ingre);

   return(res);
}

/* Función para eliminar todos los ingredientes de una receta */
void eliminaIngredientes(LISTA_INGRE *li)
{
   if(*li){
      eliminaIngredientes(&(*li)->sigIngre);
      free(*li);
      *li=NULL;
   }
}

/* Función para buscar una receta y poder eliminar sus ingredientes */
int eliminaXreceta(LISTA_RECE *lr, char *rece)
{
   int res=0;
   LISTA_RECE aux;

   aux=*lr;
   while(aux && strcmp(rece, aux->nomRece)>0)
      aux=aux->sigRece;
   if(aux && strcmp(rece, aux->nomRece)==0){
      eliminaIngredientes(&((*lr)->cabIngre));
      res=1;
   }
   return(res);
}

/* Función para buscar tipo de la receta a eliminar */
int eliminaReceta(RECETARIO r, char *tipo, char *rece)
{
   int res;

   while(r && strcmp(tipo, r->nomTipo)>0)
      r=r->sigTipo;
   if(r && strcmp(tipo, r->nomTipo)==0)
      res=eliminaXreceta(&(r->cabRece), rece);

   return(res);
}

/* Funciòn para eliminar las todas las recetas de un tipo, eliminando
   previamente todos los ingredientes
   */
void eliminaRecetas(LISTA_RECE lr)
{
   if(lr){
      eliminaRecetas(lr->sigRece);
      eliminaIngredientes(&lr->cabIngre);
      free(lr);
   }
}

/* Función para eliminar un tipo de receta */
int eliminaTipo(RECETARIO *r, char *tipo)
{
   int res=0;
   RECETARIO aux, ant=NULL;

   aux=*r;
   while(aux && strcmp(tipo, aux->nomTipo)>0){
      ant=aux;
      aux=aux->sigTipo;
   }
   if(aux && strcmp(tipo, aux->nomTipo)==0){
      eliminaRecetas(aux->cabRece);
      if(aux == *r)
         *r=aux->sigTipo;
      else
         ant->sigTipo=aux->sigTipo;
      free(aux);
      res=1;
   }
}

/* Función para eliminar un recetario completo */
void eliminaRecetario(RECETARIO *r)
{
   if(*r){
      eliminaRecetario(&(*r)->sigTipo);
      eliminaRecetas((*r)->cabRece);
      free(*r);
      *r=NULL;
   }
}
