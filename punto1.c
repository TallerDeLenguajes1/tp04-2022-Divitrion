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
tarea* buscarTarea (tarea **listaRealizada,tarea **listaSinRealizar, int cantTareas,int id);


int main()
{
    srand(time(NULL));
    int cantTareas,id;
    tarea **listaTareas, **tareasRealizadas;

    puts("Ingrese la cantidad de tareas");
    scanf("%d",&cantTareas);

    listaTareas= (tarea **) malloc(cantTareas*(sizeof(tarea *)));
    tareasRealizadas= (tarea **) malloc(cantTareas*(sizeof(tarea *)));
    
    cargarTareas(listaTareas,cantTareas);
    mostrarTareas(listaTareas,cantTareas,tareasRealizadas);
    puts("Que id desea buscar");
    scanf("%d",&id);
    escribirTarea(buscarTarea(tareasRealizadas,listaTareas,cantTareas,id));

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
    system("cls");
    for (int i = 0; i < cantTareas; i++)
    {
        escribirTarea(*(listaTareas+i));
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
        escribirTarea(*((tareasRealizadas+i)));
    }
    

    puts("-------------TAREAS SIN REALIZAR-------------\n");
    for (int i = 0; i < cantTareas; i++)
    {
        escribirTarea(*((listaTareas+i)));
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

tarea* buscarTarea (tarea **listaRealizada,tarea **listaSinRealizar, int cantTareas,int id){

    if (listaRealizada!=NULL || listaSinRealizar!=NULL)
    {
        for (int i = 0; i < cantTareas; i++)
        {
            if ((*(listaRealizada+i))->TareaID=id)
            {
                return(*(listaRealizada+i));
            }
            if ((*(listaSinRealizar+i))->TareaID=id)
            {
               return(*(listaSinRealizar+i));
            }
            
        }
    }
}
