#ifndef BANCO_H_INCLUDED
#define BANCO_H_INCLUDED

#include <stdio.h>
#include "../include/cola_dinamica.h"

#define ARCH_ERROR -2
#define TODO_OK 1
#define SIN_MEM -3


#define PATH_REALIZADOS "../Archivos/pedidos_realizados.txt"
#define PATH_FALTANTES "../Archivos/pedidos_faltantes.txt"

typedef struct{
    char descripcion[20];
    unsigned stock;
    float precio;
}t_producto_stock;

typedef struct{
    unsigned cod_ped;
    unsigned cod_prod;
    unsigned cant;
}t_pedido;

int procesar_pedidos(const char * path_prods, const char * path_pedidos);
int procesar_pedidos_res(const char * path_prods, const char * path_pedidos);

///mias

void agregarPedidoEnCola(tCola* pc, t_pedido* ped, int* estadoPed, FILE* pfProd);
void procesarPedidosRealizados(tCola* pc, FILE* pfProd, FILE* pfPedRea, int* codPrevio);

void procesarPedidosFaltantes(tCola* pc, FILE* pfProd, FILE* pfFalta, int* codPrevio);

void obtener_producto(t_producto_stock *prod,int pos,FILE *pfProd);
void actualizarStock(t_pedido* ped, t_producto_stock* prod, FILE* pfProd);

void trozarLF(t_pedido *ped,char *linea);

#endif // BANCO_H_INCLUDED
