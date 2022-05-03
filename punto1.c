#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion; //
int Duracion; // entre 10 – 100
}typedef tarea;

struct nodo
{
    tarea tarea;
    struct nodo *next;
}typedef nodo;

nodo *crearListaVacia();
nodo *crearNodo(int id);
void insertarNodo(nodo **lista, nodo *nodo);
tarea cargarTareas(int id);
nodo *copiarNodo(nodo **lista);
void borrarNodo(nodo **lista,int id);
void escribirLista(nodo *lista);
void escribirNodo(nodo *nodo);
void organizarTareas(nodo **listaSinRealizar, nodo **listaRealizada);
void *buscarPorID (nodo *listaRealizada, int id);
void *buscarPorPalabra(nodo *listaRealizada,char* palabraClave);


int main()
{
    srand(time(NULL));
    int cantTareas,id;
    char *palabraClave, *buff=(char *) malloc(30*sizeof(char));
    nodo *tareasRealizadas= crearListaVacia();
    nodo *tareasSinRealizar= crearListaVacia();
    nodo *aux;
    puts("Ingrese la cantidad de tareas");
    scanf("%d",&cantTareas);
    for (int i = 0; i < cantTareas; i++)
    {
        aux=crearNodo(i);
        insertarNodo(&tareasSinRealizar,aux);
    }
    organizarTareas(&tareasSinRealizar,&tareasRealizadas);
    puts("Ingrese la ID a buscar");
    scanf("%d",&id);
    buscarPorID(tareasSinRealizar,id);
    buscarPorID(tareasRealizadas,id);

    puts("Ingrese la palabra a buscar");
    fflush(stdin);
    gets(buff);
    palabraClave= (char *) malloc((strlen(buff)+1)*sizeof(char));
    strcpy(palabraClave,buff);
    free(buff);
    buscarPorPalabra(tareasSinRealizar,palabraClave);
    buscarPorPalabra(tareasRealizadas,palabraClave);

    free(palabraClave);
    free(tareasSinRealizar);
    free(tareasRealizadas);
    getchar();

    return 0;
}

nodo *crearListaVacia(){
    return NULL;
}

nodo *crearNodo(int id){
    nodo *nuevoNodo=(nodo *) malloc(sizeof(nodo));
    nuevoNodo->tarea=cargarTareas(id);
    nuevoNodo->next=NULL;
    return nuevoNodo;
}

void insertarNodo(nodo **lista, nodo *nodo){
    nodo->next= *lista;
    *lista=nodo;
}

nodo *copiarNodo(nodo **lista){
    nodo *aux = malloc(sizeof(nodo));
    aux->tarea.Descripcion=(char *)malloc(strlen((*lista)->tarea.Descripcion)+1*sizeof(char));
    strcpy(aux->tarea.Descripcion,(*lista)->tarea.Descripcion);
    aux->tarea.Duracion=(*lista)->tarea.Duracion;
    aux->tarea.TareaID=(*lista)->tarea.TareaID;
    aux->next=NULL;
    return aux;
}

void borrarNodo(nodo **lista,int id){
    nodo *aux=*lista;
    nodo *auxAnterior=*lista;
    while (aux && aux->tarea.TareaID!=id)
    {
            auxAnterior=aux;
            aux=aux->next;
    }
    if (aux != auxAnterior)
    {
        auxAnterior->next=aux->next;
        free(aux);
    }else
    {
         *lista=(*lista)->next;
        free(aux);
    }
}

tarea cargarTareas(int id){

    char *buff=malloc(1000*sizeof(char));
    tarea nuevaTarea;
    puts("Ingrese la descripcion de la tarea");
    fflush(stdin);
    gets(buff);
    nuevaTarea.Descripcion= (char *) malloc((strlen(buff)+1)*sizeof(char));
    strcpy(nuevaTarea.Descripcion,buff);
    nuevaTarea.Duracion= rand()%90 + 10;
    nuevaTarea.TareaID= id+1;
    free (buff);
    return nuevaTarea;
}

void organizarTareas(nodo **listaSinRealizar, nodo **listaRealizada){
    int completada;
    nodo *aux;
    nodo *listaAux=*listaSinRealizar;
    while (listaAux)
    {
        escribirNodo(listaAux);
        puts("Esta tarea esta completada? [0] No [1] Si");
        scanf("%d",&completada);
        if (completada > 0)
        {
            aux=copiarNodo(&listaAux);
            insertarNodo(listaRealizada,aux);
            listaAux=listaAux->next;
            borrarNodo(listaSinRealizar,aux->tarea.TareaID);
        }else
        {
            listaAux=listaAux->next;
        }
    }

    puts("----------Tareas Realizadas----------\n");
    escribirLista(*listaRealizada);

    puts("----------Tareas Pendientes----------\n");
    escribirLista(*listaSinRealizar);
}

void escribirLista(nodo *lista){
    while (lista)
    {
        printf("----------Tarea numero %d----------\n",lista->tarea.TareaID);
        puts("\n-----------Descripcion-----------\n");
        puts(lista->tarea.Descripcion);
        printf("Duracion: %d\n",lista->tarea.Duracion);
        puts("-----------------------------------------");
        lista=lista->next;
    }    
}

void escribirNodo(nodo *nodo){
    if (nodo)
    {
        printf("----------Tarea numero %d----------\n",nodo->tarea.TareaID);
        puts("-----------Descripcion-----------\n");
        puts(nodo->tarea.Descripcion);
        printf("Duracion: %d\n",nodo->tarea.Duracion);
        puts("-----------------------------------------");
    }
}


void *buscarPorPalabra(nodo *lista,char* palabraClave){

    while(lista && strcmp(lista->tarea.Descripcion,palabraClave)!=0)
    {
        lista=lista->next;
    }
    if (lista)
    {
        puts("-----------Tarea Encontrada-----------");
        escribirNodo(lista);
    }
   
}

void *buscarPorID (nodo *lista, int id){
    while(lista && lista->tarea.TareaID!=id)
    {
        lista=lista->next;
    }
    if (lista)
    {
        puts("-----------Tarea Encontrada-----------");
        escribirNodo(lista);
    }
}