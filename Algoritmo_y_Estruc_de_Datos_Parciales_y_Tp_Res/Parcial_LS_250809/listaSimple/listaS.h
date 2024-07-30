#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MINIMO(x,y) ((x)<(y) ? (x) : (y))

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tLista;


void crear_lista(tLista *pl);
int insertar_en_orden(tLista *pl, void *d, unsigned tamD, int (*cmp)(const void *,const void *), void (*acumular)( void *, const void *));
bool buscar_en_orden(tLista *pl, void *d, unsigned tamD, int (*cmp)(const void *,const void *));
int lista_vacia(const tLista *pl);
int lista_llena(const tLista *pl, unsigned tamD);
int sacar_inicio_lista(tLista *pl, void *d, unsigned tamD);

#endif // LISTAS_H_INCLUDED
