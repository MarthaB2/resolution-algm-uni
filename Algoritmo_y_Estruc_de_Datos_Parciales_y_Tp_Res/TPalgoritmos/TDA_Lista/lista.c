#include "lista.h"

#define SIN_MEM -2
#define LISTA_VACIA 0
#define TODO_OK 1

void crearlista(tLista* pl)
{
    *pl = NULL;
}

int insertarTopN(tLista* pl,const void* info, size_t tam, int n, int(* cmp)(const void*, const void*))
{
    int cant=0, comp=0;

    while(*pl && (comp = cmp((*pl)->info,info))<=0) // 135
    {
        pl = &(*pl)->sig;
        cant++;
    }

    if(cant==n && !*pl )
        return 0;

    tNodo* nue = malloc(sizeof(tNodo));

    if(!nue || (nue->info = malloc(tam) )==NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, info, tam);
    nue->tam = tam;
    nue->sig = *pl;

    *pl = nue;

    while((*pl)->sig) // 235
    {
        pl = &(*pl)->sig;
        cant++;
    }
    if(*pl && cant==n)
    {

        free((*pl)->info);
        free(*pl);
        *pl=NULL;

    }


    return 1;
}


int sacarDeInicioLista(tLista* pl, void* info, size_t tam)
{
    if(!*pl)
        return LISTA_VACIA;

    tNodo* nae = *pl;

    memcpy(info, nae->info, MIN(tam, nae->tam));

    *pl = nae->sig;

    free(nae->info);
    free(nae);

    return TODO_OK;
}

int listaVacia(const tLista* pl)
{
    return !*pl;
}

void vaciarLista(tLista* pl)
{
    while(*pl)
    {
        tNodo* nae = *pl;
        *pl = nae->sig;
        free(nae->info);
        free(nae);
    }
}

int sacarFinalLista(tLista* pl, void* info, size_t tam)
{
    if(!(*pl))
        return LISTA_VACIA;

    while((*pl)->sig)
        pl= &(*pl)->sig;

    tNodo* nae = *pl;
    *pl = nae->sig;

    memcpy(info, nae->info, MIN(tam, nae->tam));

    free(nae->info);
    free(nae);

    return TODO_OK;
}
