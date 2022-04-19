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
void mostrarTareas(tarea **listaTareas, int cantTareas, tarea **tareasRealizadas);


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
        printf("Tarea numero %d\n",(*(listaTareas+i))->TareaID);
        puts("-----------Descripcion-----------");
        puts((*(listaTareas+i))->Descripcion);
        puts("-----------Duracion-----------");
        printf("-----------%d-----------\n",(*(listaTareas+i))->Duracion);
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

//Tareas Realizadas
    puts("-------------TAREAS REALIZADAS-------------");
    for (int i = 0; i < cantTareas; i++)
    {
        if (*(tareasRealizadas + i) != NULL)
        {
            printf("Tarea numero %d\n",(*(tareasRealizadas+i))->TareaID);
            puts("-----------Descripcion-----------");
            puts((*(tareasRealizadas+i))->Descripcion);
            puts("-----------Duracion-----------");
            printf("-----------%d-----------\n",(*(tareasRealizadas+i))->Duracion);
        }
    }

    puts("-------------TAREAS SIN REALIZAR-------------");
    for (int i = 0; i < cantTareas; i++)
    {
        if (*(listaTareas + i) != NULL)
        {
            printf("Tarea numero %d\n",(*(listaTareas+i))->TareaID);
            puts("-----------Descripcion-----------");
            puts((*(listaTareas+i))->Descripcion);
            puts("-----------Duracion-----------");
            printf("-----------%d-----------\n",(*(listaTareas+i))->Duracion);
        }
    }
    
    
    
}
