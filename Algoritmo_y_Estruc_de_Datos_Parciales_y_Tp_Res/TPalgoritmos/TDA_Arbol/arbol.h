#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tpPrueba/macros.h"


#define MIN(x,y) (((x)<(y))? (x) : (y))
#define MAX(x,y) (((x)>(y))? (x) : (y))


typedef struct s_nodoa
{
    void *info;
    size_t tam;
    struct s_nodoa *izq,*der; ////ind->clave->tam
}t_nodoa;

typedef t_nodoa *t_arbol;

void crearArbol(t_arbol* pa);

int insertarArbol(t_arbol *pa, const void *pd, size_t tam, int (*cmp)(const void *, const void *));

void recorrerEnOrdenSimpleArbol(const t_arbol * pa, void * params, void (*accion)(const void *, unsigned, void *));
void recorrerPreOrdenSimpleArbol(const t_arbol * pa, void * params, void (*accion)(void *, unsigned, void *));
void recorrerPosOrdenSimpleArbol(const t_arbol * pa, void * params, void (*accion)(void *, unsigned, void *));
void recorrerEnOrdenInversoRecArbol(const t_arbol * pa, void * params, void (*accion)(void *, unsigned, void *));

int eliminarDeArbol(t_arbol *pa,void *pd,size_t tam,int (*cmp)(const void *,const void *));
int eliminarElemArbol(t_arbol *pa, void *pd, size_t tam, int (*cmp)(const void*, const void *));
int eliminarRaiz(t_arbol *pa);


t_nodoa **buscarNodoArbol(const t_arbol *pa, const void * pd, int (*cmp)(const void*, const void *));
t_nodoa **buscarRecNodoArbol(const t_arbol *pa, const void *pd, int (*cmp)(const void*, const void *));
int buscarElemArbol(const t_arbol *pa, void *pd, size_t tam, int (*cmp)(const void *, const void *));

t_arbol *mayorNodoArbol(t_arbol *pa);
t_arbol *menorNodoArbol(t_arbol *pa);

int menorElemArbol(const t_arbol *pa, void *pd, size_t tam);
int mayorElemArbol(const t_arbol *pa, void *pd, size_t tam);

t_nodoa **mayorRecNodoArbol(const t_arbol *pa);
t_nodoa **menorRecNodoArbol(const t_arbol *p);

int alturaArbol(const t_arbol *pa);

int contar_nodos( const t_arbol *pa);
int cantNodosHastaNivelArbol(const t_arbol *pa, int n);


int esCompletoHastaNivelArbol(const t_arbol *pa, int n);
int esCompletoArbol(const t_arbol *pa);

int esBalanceadoArbol(const t_arbol *pa);

int esAVLArbol(const t_arbol *pa);

void vaciarArbol(t_arbol *pa);

int cargarArchivoBinOrdenadoArbol(t_arbol * pa, const char * path, size_t tamInfo);
int cargarDesdeDatosOrdenadosRec(t_arbol * pa, void * ds, unsigned (*leer)(void **, void *, unsigned, void * params), int li, int ls, void * params);
unsigned leerDesdeArchivoBin(void ** d, void * pf, unsigned pos, void * params);
int cargarArchivoBinOrdenadoAbiertoArbolBinBusq(t_arbol *pa, FILE * pf, size_t tamInfo);
int cargarDesdeDatosOrdenadosArbolBin(t_arbol * pa, void * ds, unsigned cantReg, unsigned (*leer)(void **, void *, unsigned, void *params),void * params);

int grabarEnArchivoOrdenadoArbolBin(const t_arbol* p, const char* path);
void grabarArchBin(const void *d, unsigned tamDato, void *pf);


#endif // ARBOL_H_INCLUDED
