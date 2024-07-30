#ifndef SOCIOS_H_INCLUDED
#define SOCIOS_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"



typedef struct{
    int dia,
        mes,
        anio;
}T_Fecha;

typedef struct{
 long dni;
 char apellido[61];
 char nombre[61];
 T_Fecha fechaNacimiento;
 char sexo;
 T_Fecha fechaAfiliacion;
 char categoria[11];
 T_Fecha fechaUltimaCuotaPaga;
 char estado;
 T_Fecha fechaBaja;
}T_Socio;


int crearArchivoTexto(char *ruta);
int archTxtaBin(const char *narcht, const char *narchb, size_t tamreg, int (*TxtaBin)(char *, void *));
int trozarSocioLV(char *linea, void *reg);
int mostrarSocios(char *ruta);

#endif // SOCIOS_H_INCLUDED
