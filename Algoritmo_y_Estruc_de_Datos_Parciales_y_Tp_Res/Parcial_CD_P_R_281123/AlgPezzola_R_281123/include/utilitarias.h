#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED
#include<ferreteria.h>
#include<stdio.h>
#define TAM_LINEA 50

void crear_archivo_productos_res(const char * path);
void crear_archivo_pedidos_res(const char * path);

void mostrar_archivo_productos_res(const char * path);
void mostrar_archivo_pedidos_res(const char * path);
void mostrar_archivo_texto_res(const char * path);

int leer_pedido_res(t_pedido * mov, FILE * arch_mov);
int leer_pedido(t_pedido * mov, FILE * arch_mov);

#endif // UTILITARIAS_H_INCLUDED
