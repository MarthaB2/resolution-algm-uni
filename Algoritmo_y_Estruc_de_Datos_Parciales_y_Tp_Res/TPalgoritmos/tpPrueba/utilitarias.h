#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "socios.h"
#include "macros.h"




char menu(const char *msj, const char *opc);
void imprimirMensaje(int res);
int comparaFechas(const void *fechN1,const void *fechN2);
int mostrarTop10(T_Socio *vecS,int cant);


#endif // UTILITARIAS_H_INCLUDED
