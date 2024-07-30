#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../listaSimple/listaS.h"

#define TAM 11
#define TODO_BIEN 1
#define ERROR_ARCH 0
#define SIN_MEM -1
#define CANT_PED 10

typedef struct
{
    int nro_pedido;
    char nro_articulo[TAM];
    int cantidad_pedida;
    float precio_unitario;
}tPedido;

typedef struct
{
    int nro_pedido;
    float importe_total;
}tPedidoTotal;

int crearArchivoPedido(char *ruta);

int cmp_nroPedido(const void *a1,const void *b1);
void acumular_importe( void *a1, const void *b1);
void grabarArchivoTotales(FILE *pf,tPedidoTotal *pedT);
int procesarPedidos(char *ruta);


#endif // FUNCIONES_H_INCLUDED
