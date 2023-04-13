#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef Tarea;

void iniciarArre(Tarea** A, int k);
void liberarArre(Tarea** A, int k);
void descripcion(char *k);
void cargarTareas(Tarea **A, int k);
void controlarTareas(Tarea **A, Tarea **B, int k);
void mostrarTarea(Tarea* T);
void mostrarArreglo(Tarea** A, int k);

int main()
{
    int cantTareas;
    srand(time(NULL));
    printf("Ingrese cantidad de tareas: ");
    scanf("%d",&cantTareas);

    Tarea **tareasPendientes = (Tarea **) malloc(sizeof(Tarea*)*cantTareas);
    iniciarArre(tareasPendientes, cantTareas);
    cargarTareas(tareasPendientes, cantTareas);

    Tarea **tareasRealizadas = (Tarea **) malloc(sizeof(Tarea*)*cantTareas);
    iniciarArre(tareasRealizadas, cantTareas);

    return 0;
}

void iniciarArre(Tarea** A, int k)
{
    for (int i = 0; i < k; i++){
        A[i] = NULL;
    }   
}

void liberarArre(Tarea** A, int k)
{
    for (int i = 0; i < k; i++){
        free(A[i]);
    }
    free(A);   
}

void descripcion(char *k)
{
    char buff[500];
    printf("\nIngrese descripcion: ");
    gets(buff);
    k = malloc(sizeof(char)*((strlen(buff))+1));
    strcpy(k,buff);
}

void cargarTareas(Tarea **A, int k)
{
    for (int i = 0; i < k; i++){
        A[i] = malloc(sizeof(Tarea));
        A[i]->TareaID = i;
        descripcion(A[i]->Descripcion);
        A[i]->Duracion = rand() % 91 + 10;
    }    
}

void controlarTareas(Tarea **A, Tarea **B, int k)
{
    int resp, p=0;
    for (int i = 0; i < k; i++){
        mostrarTarea(A[i]);
        printf("Hizo la tarea?(SI=1/NO=0)");
        scanf("%d", &resp);
        if(resp==1){
            B[p] = A[i];
            A[i] = NULL;
            p++;
        }
    }
    
}

void mostrarTarea(Tarea* T)
{
    printf("\nID TAREA: %d\n", T->TareaID);
    puts("DESCRIPCION:");
    puts(T->Descripcion);
    printf("DURACION: %d\n", T->TareaID);
}

void mostrarArreglo(Tarea** A, int k)
{
    for (int i = 0; i < k; i++){
        if(A[i]!=NULL){
            mostrarTarea(A[i]);
        }
    }
}