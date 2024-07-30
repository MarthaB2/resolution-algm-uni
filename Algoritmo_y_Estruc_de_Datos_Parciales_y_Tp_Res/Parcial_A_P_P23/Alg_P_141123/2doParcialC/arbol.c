#include <tipos.h>
#include <stdio.h>
#include <stdlib.h>
#include <arbol.h>




/*
tNodoArbol** buscarNodoArbol(tArbolBinBusq *p, void* d, int(*cmp)(const void*, const void*))
{
    if(!*p)
        return NULL;

    if(cmp(d, (*p)->info) < 0)
        return buscarNodoArbol(&(*p)->izq,d,cmp);

    if(cmp(d, (*p)->info) > 0)
        return buscarNodoArbol(&(*p)->der,d,cmp);

    return (tNodoArbol**)p;
}

int buscarElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam,int (*cmp)(const void *, const void *))
{
    p = buscarNodoArbol((tArbolBinBusq*)p,d,cmp);

    if(!p)
        return NO_EXISTE;

    memcpy(d,(*p)->info,MIN(tam, (*p)->tamInfo));

    return TODO_OK;
}

int eliminarElemArbolBinBusq(tArbolBinBusq *p, void *d, unsigned tam,int (*cmp)(const void *, const void *))
{
    p = buscarNodoArbol(p,d,cmp);

    if(!p)
        return NO_EXISTE;

    memcpy(d,(*p)->info,MIN(tam,(*p)->tamInfo));

    return eliminarRaizArbolBinBusq(p);
}

int eliminarRaizArbolBinBusq(tArbolBinBusq *p)
{
    int hi, hd;
    tNodoArbol* nae;
    tNodoArbol** reemp;

    if(!*p)
        return NO_EXISTE;

    free((*p)->info);

    if(!(*p)->izq && !(*p)->der)
    {
        free(*p);
        *p = NULL;
        return TODO_OK;
    }

    hi = alturaArbolBin(&(*p)->izq);
    hd = alturaArbolBin(&(*p)->der);

    reemp = (hi>hd)? mayorNodoArbol(&(*p)->izq) : menorNodoArbol(&(*p)->der);

    nae = *reemp;

    (*p)->info = nae->info;
    (*p)->tamInfo = nae->tamInfo;

    *reemp = (nae->izq)? nae->izq : nae->der;

    free(nae);

    return TODO_OK;
}

unsigned alturaArbolBin(const tArbolBinBusq *p)
{
    int hi, hd;

    if(!*p)
        return 0;

    hi = alturaArbolBin(&(*p)->izq);
    hd = alturaArbolBin(&(*p)->der);

    return ((hi>hd)? hi : hd) + 1;
}

tNodoArbol** mayorNodoArbol(tArbolBinBusq *p)
{
    if(!*p)
        return NULL;

    while((*p)->der)
        p = &(*p)->der;

    return (tNodoArbol**)p;
}

tNodoArbol** menorNodoArbol(tArbolBinBusq *p)
{
    if(!*p)
        return NULL;

    while((*p)->izq)
        p = &(*p)->izq;

    return (tNodoArbol**)p;
}

void vaciarArbolBin(tArbolBinBusq *p)
{
    if(!*p)
        return;

    vaciarArbolBin(&(*p)->izq);
    vaciarArbolBin(&(*p)->der);

    free((*p)->info);
    free(*p);

    *p = NULL;
}

int grabarEnArchivoOrdenadoArbolBin(tArbolBinBusq* p, const char* path)
{
    FILE* pf = fopen(path, "wb");
    if(!pf)
        return ERROR_ARCHIVO;

    recorrerEnOrdenSimpleArbolBinBusq_res(p,pf,grabarArch);

    fclose(pf);

    return TODO_OK;
}

void recorrerEnOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params, void (*accion)(void *, unsigned, void *))
{
    if(!*p) ///EXPLOTA! (?
        return;

    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->izq,params,accion);

    accion((*p)->info,(*p)->tamInfo, params);

    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->der,params,accion);
}

void grabarArch(void* d ,unsigned tam, void* pf)
{
    fwrite(d,tam,1,(FILE*)pf);
}


///

int insertarRecArbolBinBusq(tArbolBinBusq *p, const void *d, unsigned tam,int (*cmp)(const void*, const void *))
{
    int comp;

    if(*p)
    {
        if((comp = cmp(d,(*p)->info))<0)
            return insertarRecArbolBinBusq(&(*p)->izq,d,tam,cmp);

        if(comp>0)
            return insertarRecArbolBinBusq(&(*p)->der,d,tam,cmp);

        return DUPLICADO;
    }

    tNodoArbol* nue = malloc(sizeof(tNodoArbol));

    if(!nue || (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->info,d,tam);
    nue->tamInfo = tam;
    nue->izq = nue->der = NULL;

    *p = nue;

    return TODO_OK;
}
*/
