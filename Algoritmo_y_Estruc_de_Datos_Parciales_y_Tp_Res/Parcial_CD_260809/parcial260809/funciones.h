#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../colaDinamica/cola.h"

typedef struct
{
    char codigo_de_evento; // S solicitud o A asigancion
    long int identificacion; // nro de pasaporte, nro de pasaje
}tVuelo;

///version1
void ingresarDatos(tVuelo *vuelo);

void ingresarCodigodeEvento(tVuelo *vuelo);
void ingresarIdentificacion(tVuelo *vuelo);
int procesarVuelos(char *ruta,tCola *cola);

#endif // FUNCIONES_H_INCLUDED
