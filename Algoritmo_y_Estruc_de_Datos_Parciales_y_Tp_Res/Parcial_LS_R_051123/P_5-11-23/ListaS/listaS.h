#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(x,y) ((x)<(y) ? (x) : (y))

typedef struct sNodo
{
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tListaS;

void crear_lista(tListaS *pl);
int lista_vacia(tListaS *pl);
int poner_en_orden_lista(tListaS *pl,const void *dato,unsigned tamDato,int (*cmp)(const void *,const void *),void (*agrupar)( void *,const void *));
int sacar_primero_lista(tListaS *pl,void *dato,unsigned tamDato);






#endif // LISTAS_H_INCLUDED
