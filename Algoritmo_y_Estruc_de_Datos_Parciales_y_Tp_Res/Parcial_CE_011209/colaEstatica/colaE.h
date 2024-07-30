#ifndef COLAE_H_INCLUDED
#define COLAE_H_INCLUDED

#include <string.h>

#define TAM 300
#define SIN_MEM -1
#define TODO_BIEN 1

#define MINIMO(x,y) (x)<(y) ? (x) : (y)

typedef struct
{
    char vec[TAM];
    unsigned pri,ult,tamDisp;
}tCola;


void crear_cola(tCola *pc);
int poner_en_cola(tCola *pc, const void *d, unsigned tamD);
int sacar_de_cola(tCola *pc, void *d, unsigned tamD);
int cola_vacia(const tCola *pc);
int cola_llena(const tCola *pc, unsigned tamD);
void vaciar_cola( tCola *pc);


#endif // COLAE_H_INCLUDED
