#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../colaEstatica/colaE.h"

#define ERROR_ARCH 0
#define TAM_PRODS 10

typedef struct
{
    int NRO_PED;
    int NRO_ART;
    int CANT_PED;
    float PRECIO_UNI;
}tPedido;


int crearArchivoPedido(char *ruta);
int procesarPedidos(char *ruta);


#endif // FUNCIONES_H_INCLUDED
