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
Lista sacarNodo(Lista *L);
Lista controlarTareas(Lista L1, Lista *L2);
Lista buscarTareaPorPalabra(Lista Lp, Lista Lr);
Lista busquedaTareaPorID(Lista Lp, int id);
void eliminarTarea(struct Nodo* Nodo);
struct Nodo* quitarNodoPorID(Lista *L , int id);
void insertarNodo(Lista *L, struct Nodo* nodo);

int main ()
{
    srand(time(NULL));
    Lista TPendientes, TRealizadas, TProceso, nod;
    TPendientes = crearLista();
    TRealizadas = crearLista();
    TProceso = crearLista();
    cargarTareas(&TPendientes);
    // eliminarTarea(quitarNodoPorID(&TPendientes, 2));
    // mostrarTareas(TPendientes);
    
    // TPendientes = controlarTareas(TPendientes, &TRealizadas);
    // puts("-----TAREAS PENDIENTES------");
    // mostrarTareas(TPendientes);
    // puts("-----TAREAS REALIZADAS------");
    // mostrarTareas(TRealizadas);
   
    // nod = busquedaTareaPorID(TPendientes,TRealizadas);
    // mostrarTarea(&nod->T);
    // nod = buscarTareaPorPalabra(TPendientes,TRealizadas);
    // mostrarTarea(&nod->T);

    // Listar Tareas
    puts("-----TAREAS PENDIENTES-----");
    mostrarTareas(TPendientes);
    puts("-----TAREAS EN PROCESO-----");
    mostrarTareas(TProceso);
    puts("-----TAREAS REALIZADAS-----");
    mostrarTareas(TRealizadas);

    int resp, id, list;
    puts("Desea mover alguna tarea?");
    puts("0- No.");
    puts("1- Si.");
    printf("RESPUESTA: ");
    scanf("%d", &resp);
    fflush(stdin);
    while (resp == 1){
        printf("ID de la tarea a mover: ");
        scanf("%d", &id);
        if(busquedaTareaPorID(TPendientes, id)){
            list = 1;
        }else{
            if(busquedaTareaPorID(TProceso, id)){
                list = 2;
            }else{
                if (busquedaTareaPorID(TRealizadas, id)) {
                    list = 3;
                }else{
                    list = 0;
                }  
            }
        }
        switch (list){
            case 1:
                printf("A donde desea mover?\n");
                printf("- No mover (0)\n");
                printf("- Tareas en Proceso (1)\n");
                printf("- Tareas Realizadas (2)\n");
                scanf("%d", &resp);
                fflush(stdin);
                switch (resp){
                    case 1:
                        nod = quitarNodoPorID(&TPendientes,id);
                        insertarNodo(&TProceso, nod);
                        break;
                    case 2:
                        nod = quitarNodoPorID(&TPendientes,id);
                        insertarNodo(&TRealizadas, nod);
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                printf("A donde desea mover?\n");
                printf("- No mover (0)\n");
                printf("- Tareas Pendientes (1)\n");
                printf("- Tareas Realizadas (2)\n");
                scanf("%d", &resp);
                fflush(stdin);
                switch (resp){
                    case 1:
                        nod = quitarNodoPorID(&TProceso,id);
                        insertarNodo(&TPendientes, nod);
                        break;
                    case 2:
                        nod = quitarNodoPorID(&TProceso,id);
                        insertarNodo(&TRealizadas, nod);
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                printf("A donde desea mover?\n");
                printf("- No mover (0)\n");
                printf("- Tareas Pendientes (1)\n");
                printf("- Tareas en Proceso (2)\n");
                scanf("%d", &resp);
                fflush(stdin);
                switch (resp){
                    case 1:
                        nod = quitarNodoPorID(&TRealizadas,id);
                        insertarNodo(&TPendientes, nod);
                        break;
                    case 2:
                        nod = quitarNodoPorID(&TRealizadas,id);
                        insertarNodo(&TProceso, nod);
                        break;
                    default:
                        break;
                }
                break;
            default:
                puts("No existe la tarea");
                break;
        }
        puts("-----TAREAS PENDIENTES-----");
        mostrarTareas(TPendientes);
        puts("-----TAREAS EN PROCESO-----");
        mostrarTareas(TProceso);
        puts("-----TAREAS REALIZADAS-----");
        mostrarTareas(TRealizadas);
        puts("Desea mover otra tarea?");
        puts("0- No.");
        puts("1- Si.");
        printf("RESPUESTA: ");
        scanf("%d", &resp);
        fflush(stdin);
    }
    puts("-----TAREAS PENDIENTES-----");
    mostrarTareas(TPendientes);
    puts("-----TAREAS EN PROCESO-----");
    mostrarTareas(TProceso);
    puts("-----TAREAS REALIZADAS-----");
    mostrarTareas(TRealizadas);

    liberarLista(&TPendientes);
    liberarLista(&TRealizadas);
    liberarLista(&TProceso);
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
    nodo->Siguiente = NULL;

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
    int suma = 0;
    while (L != NULL){
       mostrarTarea(&L->T);
       suma = suma + L->T.Duracion;
       L = L->Siguiente;
    }
    if(L=NULL){
        puts("--NO HAY TAREAS--");
    }
    printf("\n--TIEMPO TOTAL: %d--\n", suma);
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

Lista sacarNodo(Lista *L)
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
        printf("\nA donde desea mover?");
        printf("\n- No mover (0)");
        printf("\n- A 'En Proceso' (1)");
        printf("\n- A 'Realizadas' (2)");
        scanf("%d", &resp);
        fflush(stdin);
        if (resp == 2){
            aux = sacarNodo(&L1);
            aux->Siguiente = LP;
            LP = aux;
        }else{
            aux = sacarNodo(&L1);
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

Lista busquedaTareaPorID(Lista Lp, int id)
{
    while (Lp){
        if(Lp->T.TareaID == id){
            return(Lp);
        }
        Lp = Lp->Siguiente;
    }   
    return NULL;
}

void eliminarTarea(struct Nodo* Nodo)
{
    free(Nodo->T.Descripcion);
    free(Nodo);
}

struct Nodo* quitarNodoPorID(Lista *L , int id)
{
    struct Nodo *aux, *auxAnterior;

    if(*L != NULL){
        if( (*L)->T.TareaID == id){ 
            aux = *L;
            *L = NULL;
            return aux;
        
        }else{
            auxAnterior = (*L);
            aux = (*L)->Siguiente;
            while(aux->Siguiente != NULL && aux->T.TareaID !=id){
                auxAnterior = aux;
                aux = aux->Siguiente;
            }
            if(aux->T.TareaID == id){
                auxAnterior->Siguiente = aux->Siguiente;
                return aux;
            }

        }
    }
    return NULL;
}

void insertarNodo(Lista *L, struct Nodo* nodo)
{
    nodo->Siguiente = (*L);
    (*L) = nodo;
}