#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

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

typedef struct
{
    tNodo *pri;
    tNodo *ult;
}tCola;



void crear_cola(tCola *pc);
int poner_en_cola(tCola *pc, void *d, unsigned tamD);
int sacar_de_cola(tCola *pc, void *d, unsigned tamD);
int cola_vacia(const tCola *pc);
int cola_llena(const tCola *pc, unsigned tamD);
void vaciar_cola(tCola *pc);



#endif // COLA_H_INCLUDED
