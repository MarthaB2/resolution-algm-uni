#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include "../ListaS/listaS.h"
#include "utilitarias.h"

#define TODO_BIEN 1
#define ERROr_ARCH 0


typedef struct
{
    int d;
    int m;
    int a;
}tFecha;


typedef struct
{
    char patente[8];
    int nrocCuenta;
    char titular[26];
    int dni;
    tFecha vto;
    float importe;
}tImpVenc;


int crearArchivoImpuestoVencidos(char *ruta);

void obtenerDeudas(tListaS *pl, FILE *pfIV, int (*cmp)(const void *,const void *));

int cmp_dni(const void *na,const void *nb);
int cmp_dni_y_patente(const void *na,const void *nb);
void agruparDeuda(void *destinoN, const void *origenN);

void grabar_dni(tImpVenc *imp,FILE *pfD);
void grabar_dni_y_patente(tImpVenc *imp,FILE *pfD);
int mostrarInformeDeudas(tListaS *pl,char *ruta,void (*grabar)(tImpVenc *imp,FILE *pfD));

int procesarDeudas(char *ruta,void (*grabar)(tImpVenc *imp,FILE *pfD), int (*cmp)(const void *,const void *));


#endif // FUNCIONES_H_INCLUDED
