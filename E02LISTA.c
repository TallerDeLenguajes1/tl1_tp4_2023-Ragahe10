#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
};

typedef struct Nodo* Lista;

Lista crearLista();
struct Nodo* crearNodo(int id);
void cargarTareas(Lista* L);
void mostrarTarea(Tarea* T);
void mostrarTareas(Lista L);
void descripcion(char **k);
void liberarLista(Lista *L);
int longitud (Lista L);
Lista quitarNodo(Lista *L);
Lista controlarTareas(Lista L1, Lista *L2);
Lista buscarTareaPorPalabra(Lista Lp, Lista Lr);
Lista busquedaTareaPorID(Lista Lp, Lista Lr);

int main ()
{
    srand(time(NULL));
    Lista TPendientes, TRealizadas, nod;
    TPendientes = crearLista();
    TRealizadas = crearLista();
    cargarTareas(&TPendientes);
    mostrarTareas(TPendientes);
    
    TPendientes = controlarTareas(TPendientes, &TRealizadas);
    puts("-----TAREAS PENDIENTES------");
    mostrarTareas(TPendientes);
    puts("-----TAREAS REALIZADAS------");
    mostrarTareas(TRealizadas);
   
    nod = busquedaTareaPorID(TPendientes,TRealizadas);
    mostrarTarea(&nod->T);
    nod = buscarTareaPorPalabra(TPendientes,TRealizadas);
    mostrarTarea(&nod->T);

    liberarLista(&TPendientes);
    liberarLista(&TRealizadas);
    return 0;
}

Lista crearLista()
{
    return NULL;
}

struct Nodo* crearNodo(int id)
{
    struct Nodo* nodo = malloc(sizeof(struct Nodo));
    printf("-----TAREA %d------", id);
    nodo->T.TareaID = id;
    nodo->T.Duracion = 10 + rand()%91;
    descripcion(&nodo->T.Descripcion);

    return nodo;
}

void cargarTareas(Lista* L)
{
    int resp, id = 1;
    struct Nodo* nodo;
    printf("\nDesea cargar tarea? (Si:1/No:0)");
    scanf("%d", &resp);
    fflush(stdin);
    while(resp == 1){
        nodo = crearNodo(id);
        nodo->Siguiente = *L;
        *L = nodo;
        id++;
        printf("\n Desea cargar otra tarea? (Si:1/No:0)");
        scanf("%d", &resp);
        fflush(stdin);
    }
}

void mostrarTarea(Tarea* T)
{
    if(T!=NULL){
        printf("\nID TAREA: %d\n", T->TareaID);
        puts("DESCRIPCION:");
        puts(T->Descripcion);
        printf("DURACION: %d\n", T->Duracion);
    }else{
        puts("La tarea no existe");
    }
}

void mostrarTareas(Lista L)
{
    while (L != NULL){
       mostrarTarea(&L->T);
       L = L->Siguiente;
    }
}

void descripcion(char **k)
{
    char buff[500];
    printf("\nIngrese descripcion: ");
    gets(buff);
    *k = malloc(sizeof(char)*((strlen(buff))+1));
    strcpy(*k,buff);
}

void liberarLista(Lista *L)
{
    struct Nodo *nod;
    while ((*L) != NULL){
        nod = (*L);
        (*L) = (*L)->Siguiente;
        free(nod->T.Descripcion);
        free(nod);
    }
}

Lista quitarNodo(Lista *L)
{
    struct Nodo * nodo = NULL;
    if((*L) != NULL){
        nodo = (*L);
        (*L) = (*L)->Siguiente;
    }
    return nodo;
}

int longitud (Lista L)
{
    int cant=0;
    while(L != NULL){
        L = L->Siguiente;  
        cant++;
    }
    return cant;
}
Lista controlarTareas(Lista L1, Lista *L2)
{
    Lista aux, LP;
    int resp;
    LP = crearLista();
    puts("--------CONTROLAR TAREAS--------");
    while (L1 != NULL){
        mostrarTarea(&(L1->T));
        printf("\nRealizo la tarea? (Si:1/No:0)");
        scanf("%d", &resp);
        fflush(stdin);
        if (resp == 0){
            aux = quitarNodo(&L1);
            aux->Siguiente = LP;
            LP = aux;
        }else{
            aux = quitarNodo(&L1);
            aux->Siguiente = (*L2);
            (*L2) = aux;
        }
    }
    return (LP);
}

Lista buscarTareaPorPalabra(Lista Lp, Lista Lr)
{
    char P[100];
    printf("\nIngrese DESCRIPCION de la tarea a buscar: ");
    gets(P);

    while (Lp){
        if(strstr(Lp->T.Descripcion, P)!=NULL){
            puts("Esta en PENNDIENTES");
            return(Lp);
        }
            Lp = Lp->Siguiente;
    }
    while (Lr){
        if(strstr(Lr->T.Descripcion, P)!=NULL){
            puts("Esta en REALIZADAS");
            return(Lr);
        }
            Lr = Lr->Siguiente;
    }
    return NULL;
}

Lista busquedaTareaPorID(Lista Lp, Lista Lr)
{
    int id;
    printf("\nIngrese el ID de la tarea a buscar");
    scanf("%d", &id);
    fflush(stdin);
    while (Lp){
        if(Lp->T.TareaID == id){
            puts("Esta en PENDIENTES");
            return(Lp);
        }
        Lp = Lp->Siguiente;
    }
    while (Lr){
        if(Lr->T.TareaID == id){
            puts("Esta en REALIZADAS");
            return(Lr);
        }
        Lr=Lr->Siguiente;
    }   
    return NULL;
}