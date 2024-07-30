/** *************************************************************************

 ** arbol_bin_busq.c definición primitivas TDA ÁRBOL bin. de búsqueda

 ** *********************************************************************** */

#include "arbol.h"


///**************CREAR ARBOL**************///
void crearArbol(t_arbol* pa)
{
    *pa = NULL;
}


///**************INSERTAR ARBOL**************///
//DE FORMA ITERATIVA. ADEMAS EL ARBOL ESTAR ORDENADO.
int insertarArbol(t_arbol *pa, const void *pd, size_t tam, int (*cmp)(const void *, const void *))
{
    t_nodoa* nue;
    int comp;

    while(*pa) // *pa == null
    {
        comp = cmp(pd,(*pa)->info);
        if(comp<0)
            pa=&(*pa)->izq;
        else if(comp>0)
            pa=&(*pa)->der;
        else
            return DUPLICADO;
    }

    nue = malloc(sizeof(t_nodoa));
    if(!nue)
    {
        return SIN_MEM;
    }
    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return SIN_MEM;
    }

    nue->tam = tam;
    memcpy(nue->info, pd,tam);
    nue->izq = nue->der = NULL;

    *pa= nue;

    return TODO_BIEN;
}



///**************RECORRER**************///

 void recorrerEnOrdenSimpleArbol(const t_arbol * pa, void * params, void (*accion)(const void *, unsigned, void *))
 {
    if(!*pa)
        return;

    recorrerEnOrdenSimpleArbol(&(*pa)->izq,params,accion);
    accion((*pa)->info, (*pa)->tam, params);
    recorrerEnOrdenSimpleArbol(&(*pa)->der,params,accion);

 }


 void recorrerPreOrdenSimpleArbol(const t_arbol * pa, void * params, void (*accion)(void *, unsigned, void *))
 {
    if(!*pa)
        return;

    accion((*pa)->info, (*pa)->tam, params);
    recorrerPreOrdenSimpleArbol(&(*pa)->izq,params,accion);
    recorrerPreOrdenSimpleArbol(&(*pa)->der,params,accion);
 }


 void recorrerPosOrdenSimpleArbol(const t_arbol * pa, void * params, void (*accion)(void *, unsigned, void *))
 {
    if(!*pa)
        return;

    recorrerPosOrdenSimpleArbol(&(*pa)->izq,params,accion);
    recorrerPosOrdenSimpleArbol(&(*pa)->der,params,accion);
    accion((*pa)->info, (*pa)->tam, params);
 }
/*
 void recorrerEnOrdenInversoRecArbol(const t_arbol * pa, void * params, void (*accion)(void *, unsigned, void *))
 {
    if(!*pa)
        return;

    recorrerEnOrdenSimpleArbol(&(*pa)->der,params,accion);
    accion((*pa)->info, (*pa)->tam, params);
    recorrerEnOrdenSimpleArbol(&(*pa)->izq,params,accion);
 }
*/
///**************ELIMINAR**************///

///ELIMINAR ARBOL

int eliminarDeArbol(t_arbol *pa,void *pd,size_t tam,int (*cmp)(const void *,const void *))
{
    int comp;

    while(*pa && (comp=cmp(pd,(*pa)->info))) // *pa == null
    {
        if(comp<0)
            pa=&(*pa)->izq;
        else if(comp>0)
            pa=&(*pa)->der;
    }
    if(!*pa)
        return NO_EXISTE;

    memcpy(pd,(*pa)->info,MIN((*pa)->tam,tam));
    return eliminarRaiz(pa);
}


///ELIMINAR RAIZ
int eliminarRaiz(t_arbol *pa)
{
    int hi,hd;


    t_arbol *reemp;
    t_nodoa *elim;

    if(!*pa)
        return NO_EXISTE; ///ARBOL VACIO
    free((*pa)->info);
    if(!(*pa)->izq && !(*pa)->der)
    {
        free(*pa);
        *pa=NULL;
        return TODO_BIEN;
    }

    hi=alturaArbol(&(*pa)->izq);
    hd=alturaArbol(&(*pa)->der);
    if(hi>hd)
        reemp=mayorNodoArbol(&(*pa)->izq);
    else
        reemp=menorNodoArbol(&(*pa)->der);

    elim=*reemp;
    (*pa)->info=elim->info;
    (*pa)->tam=elim->tam;

    *reemp=elim->izq ? elim->izq : elim->der;
    free(elim);
    return TODO_BIEN;
}


int eliminarElemArbol(t_arbol *pa, void *pd, size_t tam, int (*cmp)(const void*, const void *))
{
 if(!(pa = buscarNodoArbol(pa,pd,cmp)))
    return 0; ///NO_EXISTE

 memcpy(pd, (*pa)->info, MIN(tam, (*pa)->tam));

 return eliminarRaiz(pa);
}

///**************BUSCAR**************///

///SIN RECURSIVIDAD
t_nodoa **buscarNodoArbol(const t_arbol *pa, const void * pd, int (*cmp)(const void*, const void *))
{
 int rc;
 while(*pa && (rc=cmp(pd, (*pa)->info)))
 {
    if(rc<0)
        pa = &(*pa)->izq;
    else
        pa = &(*pa)->der;
 }
 if(!*pa)
    return NULL;

 return (t_nodoa **)pa;
}

///CON RECURSIVIDAD
t_nodoa **buscarRecNodoArbol(const t_arbol *pa, const void *pd, int (*cmp)(const void*, const void *))
{
 int rc;
 if(!*pa)
    return NULL;

 if(*pa && (rc=cmp(pd, (*pa)->info)))
 {
    if(rc<0)
        return buscarRecNodoArbol(&(*pa)->izq, pd, cmp);

    return buscarRecNodoArbol(&(*pa)->der, pd, cmp);
 }

 return (t_nodoa **) pa;
}

///ELEM
int buscarElemArbol(const t_arbol *pa, void *pd, size_t tam, int (*cmp)(const void *, const void *))
{
 if(!(pa = buscarNodoArbol(pa,pd,cmp)))
    return 0; ///NO_EXISTE

 memcpy(pd, (*pa)->info, MIN(tam, (*pa)->tam));

 return 1;
}

///**************MENOR Y MAYOR NODO**************///

///ITERATIVAS : se recomienda esta forma
t_arbol *mayorNodoArbol(t_arbol *pa)
{
    while(*pa && (*pa)->der)
        pa=&(*pa)->der;
    return pa;
}

t_arbol *menorNodoArbol(t_arbol *pa)
{
    while(*pa && (*pa)->izq)
        pa=&(*pa)->izq;
    return pa;
}
//elemento
/*
int menorElemArbol(const t_arbol *pa, void *pd, size_t tam)
{
 if(!(pa = menorNodoArbol(pa)))
    return 0;

 memcpy(pd, (*pa)->info, MIN(tam, (*pa)->tam));
 return 1;
}*/
/*
int mayorElemArbol(const t_arbol *pa, void *pd, size_t tam)
{
 if(!(pa = mayorNodoArbol(pa)))
    return 0;

 memcpy(pd, (*pa)->info, MIN(tam, (*pa)->tam));
 return 1;
}
*/
///RECURSIVAS
t_nodoa **mayorRecNodoArbol(const t_arbol *pa)
{
 if(!*pa)
    return NULL;

 if(!(*pa)->der)
    return (t_nodoa **) pa;

 return mayorRecNodoArbol(&(*pa)->der);
}


t_nodoa **menorRecNodoArbol(const t_arbol *p)
{
 if(!*p)
    return NULL;

 if(!(*p)->izq)
    return (t_nodoa **) p;

 return menorRecNodoArbol(&(*p)->izq);
}
///**************ALTURA**************///

int alturaArbol(const t_arbol *pa)
{
    int hi,hd;
    if(!*pa)
        return 0; //condicion de corte
    hi=alturaArbol(&(*pa)->izq);
    hd=alturaArbol(&(*pa)->der);

    return (hi>hd ? hi : hd)+1;
}

///**************CANTIDAD DE NODOS**************///

///CONTAR NODOS
int contar_nodos( const t_arbol *pa)
{
    if(!*pa)
        return 0;
    return contar_nodos(&(*pa)->izq) + contar_nodos(&(*pa)->der) +1;
}

///CONATAR NODOS HASTA N NIVEL
int cantNodosHastaNivelArbol(const t_arbol *pa, int n)
{
 if(!*pa)
    return 0;

 if(n==0)
    return 1;

 return cantNodosHastaNivelArbol(&(*pa)->izq, n-1) + cantNodosHastaNivelArbol(&(*pa)->der, n-1) + 1;
}

///**************COMPLETO**************///

///ES COMPLETO HASTA N NIVEL
int esCompletoHastaNivelArbol(const t_arbol *pa, int n)
{
 if(!*pa)
    return n<0;

 if(n==0)
    return 1;

 return esCompletoHastaNivelArbol(&(*pa)->izq,n-1) && esCompletoHastaNivelArbol(&(*pa)->der,n-1);
}

///ES COMPLETO
int esCompletoArbol(const t_arbol *pa)
{
 return esCompletoHastaNivelArbol(pa,alturaArbol(pa)-1);
}

///**************BALANCEADO**************///

int esBalanceadoArbol(const t_arbol *pa)
{
 return esCompletoHastaNivelArbol(pa,alturaArbol(pa)-2);
}

///**************AVL**************///

int esAVLArbol(const t_arbol *pa)
{
 int hi,hd;
 if(!*pa)
    return 1;

 hi = alturaArbol(&(*pa)->izq);
 hd = alturaArbol(&(*pa)->der);

 if (abs(hi-hd)>1)
    return 0;

 return esAVLArbol(&(*pa)->izq) && esAVLArbol(&(*pa)->der);
}

///**************VACIAR ARBOL**************///
void vaciarArbol(t_arbol *pa)
{
    if(!*pa)
        return;

    vaciarArbol(&(*pa)->izq);
    vaciarArbol(&(*pa)->der);

    free((*pa)->info);
    free(*pa);

    *pa = NULL;
}

///**************ARCHIVOS**************///

int cargarArchivoBinOrdenadoArbol(t_arbol * pa, const char * path, size_t tamInfo)
{
 int cantReg, r;
 FILE * pf;

 if(*pa)
    return SIN_INICIALIZAR;

 if(!(pf= fopen(path, "rb")))
    return ERROR_ARCH;

 fseek(pf, 0L, SEEK_END);

 cantReg = ftell(pf)/tamInfo;

 r = cargarDesdeDatosOrdenadosRec(pa, pf, leerDesdeArchivoBin, 0, cantReg-1, &tamInfo);

 fclose(pf);
 return r;
}

int cargarDesdeDatosOrdenadosRec(t_arbol * pa, void * ds, unsigned (*leer)(void **, void *, unsigned, void * params), int li, int ls, void * params)
{
 int m = (li+ls)/2, r;

 if (li>ls)
    return TODO_BIEN;

 (*pa) = (t_nodoa*) malloc(sizeof(t_nodoa));

 if (!*pa || !((*pa)->tam = leer(&(*pa)->info, ds, m, params)))
 {
    free(*pa);
    return SIN_MEM;
 }

 (*pa)->izq = (*pa)->der = NULL;

 if((r=cargarDesdeDatosOrdenadosRec(&(*pa)->izq, ds, leer, li, m-1, params))!= TODO_BIEN)
    return r;

 return cargarDesdeDatosOrdenadosRec(&(*pa)->der, ds, leer, m+1, ls, params);
}


unsigned leerDesdeArchivoBin(void ** d, void * pf, unsigned pos, void * params)
{
 size_t tam = *((int*)params);

 *d = malloc(tam);

 if(!*d)
    return 0;

 fseek((FILE*)pf, pos*tam, SEEK_SET);

 return fread(*d, tam, 1, (FILE*)pf);
}



int cargarArchivoBinOrdenadoAbiertoArbolBinBusq(t_arbol *pa, FILE * pf, size_t tamInfo)
{
 int cantReg;

 if(*pa || !pf)
    return 0;

 fseek(pf, 0L, SEEK_END);

 cantReg = ftell(pf)/tamInfo;

 return cargarDesdeDatosOrdenadosRec(pa, pf, leerDesdeArchivoBin, 0, cantReg-1, &tamInfo);
}

int cargarDesdeDatosOrdenadosArbolBin(t_arbol * pa, void * ds, unsigned cantReg, unsigned (*leer)(void **, void *, unsigned, void *params),void * params)
{
 if(*pa || !ds)
    return 0;
 return cargarDesdeDatosOrdenadosRec(pa, ds, leer, 0, cantReg-1, params);
}

int grabarEnArchivoOrdenadoArbolBin(const t_arbol* p, const char* path)
{
    FILE* pf = fopen(path, "wb");
    if(!pf)
        return ERROR_ARCH;

    recorrerEnOrdenSimpleArbol(p,pf,grabarArchBin);

    fclose(pf);

    return TODO_OK;
}

void grabarArchBin(const void *d, unsigned tamDato, void *pf)
{
    fwrite(d, tamDato, 1, (FILE*)pf);
}


/** *************************************************************************

 ** FIN -ArbolBinario.c definición primitivas TDA ÁRBOL bin. de búsqueda

 ** *********************************************************************** */
