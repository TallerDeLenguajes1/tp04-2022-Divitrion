#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion; //
int Duracion; // entre 10 – 100
}typedef tarea;

void cargarTareas(tarea **listaTareas, int cantTareas);
void escribirTarea(tarea *lista);
void mostrarTareas(tarea **listaTareas, int cantTareas, tarea **tareasRealizadas);
tarea* BuscarTarea(tarea **listaRealizada, tarea **listaSinRealizar, int cantTareas);


int main()
{
    srand(time(NULL));
    int cantTareas;
    tarea **listaTareas, **tareasRealizadas;

    puts("Ingrese la cantidad de tareas");
    scanf("%d",&cantTareas);

    listaTareas= (tarea **) malloc(cantTareas*(sizeof(tarea *)));
    tareasRealizadas= (tarea **) malloc(cantTareas*(sizeof(tarea *)));
    
    cargarTareas(listaTareas,cantTareas);
    mostrarTareas(listaTareas,cantTareas,tareasRealizadas);
    escribirTarea(BuscarTarea(tareasRealizadas,listaTareas,cantTareas));

    getchar();

    return 0;
}

void cargarTareas(tarea **listaTareas, int cantTareas){

    char *buff=malloc(1000*sizeof(char));

    for (int i = 0; i < cantTareas; i++)
    {
        (*(listaTareas + i))= (tarea *) malloc(sizeof(tarea));
        (*(listaTareas+i))->TareaID = i+1;
        puts("Ingrese la descripcion de la tarea");
        fflush(stdin);
        gets(buff);
        (*(listaTareas+i))->Descripcion= (char *) malloc((strlen(buff)+1)*sizeof(char));
        strcpy((*(listaTareas+i))->Descripcion,buff);
        (*(listaTareas+i))->Duracion= rand()%90 + 10;
    }
    free (buff);
}

void mostrarTareas(tarea **listaTareas, int cantTareas, tarea **tareasRealizadas){

    int completada;
    for (int i = 0; i < cantTareas; i++)
    {
        escribirTarea(listaTareas[i]);
        puts("Esta tarea esta realizada? [1]Si, [0]No");
        scanf("%d",&completada);

        if (completada > 0)
        {
            (*(tareasRealizadas + i))= (tarea *) malloc(sizeof(tarea));
            (*(tareasRealizadas+i))->TareaID=(*(listaTareas+i))->TareaID;
            (*(tareasRealizadas+i))->Duracion=(*(listaTareas+i))->Duracion;
            (*(tareasRealizadas+i))->Descripcion= (char *) malloc(strlen((*(listaTareas+i))->Descripcion)+1*sizeof(char));
            strcpy((*(tareasRealizadas+i))->Descripcion,(*(listaTareas+i))->Descripcion);
            (*(listaTareas+i))=NULL;
        }else
        {
            (*(tareasRealizadas+i))= NULL;   
        }
        
    }
    puts("-------------TAREAS REALIZADAS-------------\n");
    for (int i = 0; i < cantTareas; i++)
    {
        escribirTarea(tareasRealizadas[i]);
    }

    puts("-------------TAREAS SIN REALIZAR-------------\n");
    for (int i = 0; i < cantTareas; i++)
    {
        escribirTarea(listaTareas[i]);
    }
}

void escribirTarea(tarea *lista){
    if (lista!=NULL)
    {
        printf("----------Tarea numero %d----------\n",lista->TareaID);
        puts("-----------Descripcion-----------\n");
        puts(lista->Descripcion);
        printf("Duracion: %d\n",lista->Duracion);
        puts("-----------------------------------------");
    }
}

tarea* BuscarTarea(tarea **listaRealizada, tarea **listaSinRealizar, int cantTareas)
{
    char *buff=(char *) malloc(100*sizeof(char));

    puts("Que palabra quiere buscar?");
    fflush(stdin);
    gets(buff);

    char *palabraClave = (char *) malloc((strlen(buff)+1)*sizeof(char));
    strcpy(palabraClave,buff);
    free(buff);
    for (int i = 0; i < cantTareas; i++)
    {
        if (listaSinRealizar[i] != NULL)
        {
            if (strcmp((*(listaSinRealizar + i))->Descripcion,palabraClave) == 0)
            {
                return((*(listaSinRealizar + i)));
            }
        }
        if (listaRealizada[i] != NULL)
        {
            if (strcmp((*(listaRealizada + i))->Descripcion,palabraClave) == 0)
            {
                return((*(listaRealizada + i)));
            }
        }
        
    }
    free(palabraClave);
}
