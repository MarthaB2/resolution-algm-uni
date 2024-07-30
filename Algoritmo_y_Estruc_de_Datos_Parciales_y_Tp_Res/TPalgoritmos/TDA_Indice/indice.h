#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../TDA_Arbol/arbol.h"
#include "../tpPrueba/macros.h"

typedef struct
{
    size_t tamClave;
    int (*cmp)(const void*, const void*);
    t_arbol a;
}t_indice;


void ind_crear (t_indice* ind, size_t tam_clave, int (*cmp)(const void*, const void*));
/* inicializa
 la estructura a �ndice vac�o y almacena en la estructura de �ndice el tama�o de la clave gen�rica a
 utilizar y la funci�n de comparaci�n.*/
int ind_insertar (t_indice* ind, void *clave, unsigned nro_reg);/* inserta en orden el registro
 reg_ind seg�n la clave. (1)*/
int ind_eliminar (t_indice* ind, void *clave, unsigned *nro_reg);/* elimina la entrada del �ndice
 correspondiente a la clave y devuelve en nro_reg el n�mero de registro asociado. (1)*/
int ind_buscar (const t_indice* ind, void *clave, unsigned *nro_reg);/*: Busca la clave recibida por
 par�metro y devuelve en nro_reg el n�mero de registro asociado. (1)*/
int ind_cargar (t_indice* ind, const char* path);/*: Carga el �ndice a partir de un archivo binario
 ordenado (t�picamente de extensi�n �.idx�), donde cada registro del archivo tiene la estructura
 definida, clave-nro_reg. (1)*/
int ind_grabar (const t_indice* ind, const char* path);/*: Graba un archivo binario ordenado
 (t�picamente de extensi�n �.idx�) con el contenido del �ndice con la estructura clave-nro_reg. (1)*/
void ind_vaciar (t_indice* ind); //: deja el �ndice en su estado de vac�o.

int ind_recorrer (const t_indice* ind, void (*accion)(const void *, unsigned, void *), void* param);
/* Recorre el �ndice en orden y llama a acci�n para cada registro del mismo. (1)
 (1)
 : Devuelve 1 (uno) si la operaci�n fue exitosa y 0 (cero) en caso contrario */

#endif // INDICE_H_INCLUDED
