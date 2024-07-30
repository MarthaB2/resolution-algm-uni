#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#define MIN(x,y) (((x)<(y))? (x) : (y))

typedef struct sNodo
{
    void* info;
    size_t tam;
    struct sNodo* sig;

}tNodo;

typedef tNodo* tLista;

void crearlista(tLista* pl);
int insertarTopN(tLista* pl,const void* info, size_t tam, int n, int(*cmp)(const void*, const void*));
int sacarDeInicioLista(tLista* pl, void* info, size_t tam);
int listaVacia(const tLista* pl);
int sacarFinalLista(tLista* pl, void* info, size_t tam);

#endif // LISTA_H_INCLUDED
