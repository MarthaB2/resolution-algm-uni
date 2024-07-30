#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


#include "socios.h"
#include "../TDA_Indice/indice.h"
#include "utilitarias.h"
#include "../TDA_Arbol/arbol.h"
#include "../TDA_Lista/lista.h"

#include "macros.h"






int cmp_dni(const void *na,const void *nb);
int cargarIndiceConArchBinNoOrdenadoPorInsercion(t_indice *ind, const char *path);
void mostrarDato(const void * info, unsigned tam, void * params);
void ingresarNuevoSocio(T_Socio *socio);
int alta(T_Socio *socio,FILE *maestro,t_indice *ind);
int ingresarModiSocio(T_Socio *socio,t_indice *ind, FILE *maestro);
void modificar(T_Socio *socio,FILE *maestro);
int ingresarSocioABajar(T_Socio *socio,t_indice *ind, FILE *maestro);
int listar(T_Socio *socio,t_indice *ind, FILE *maestro);
void mostrarMaestro(const void *info, unsigned tam, void *params);


#endif // FUNCIONES_H_INCLUDED
