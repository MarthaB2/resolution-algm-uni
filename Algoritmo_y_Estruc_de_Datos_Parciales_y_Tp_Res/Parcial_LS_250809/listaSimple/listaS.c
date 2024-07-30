#include "listaS.h"

void crear_lista(tLista *pl)
{
    *pl=NULL;
}

int insertar_en_orden(tLista *pl, void *d, unsigned tamD, int (*cmp)(const void *,const void *), void (*acumular)( void *, const void *))
{
    int comp;
    tNodo *nue;
    while(*pl && (comp=cmp(d,(*pl)->info))>0)
    {
        pl=&(*pl)->sig;
    }
    if(comp==0 && *pl)
    {
        acumular((*pl)->info,d);
        return 1;
    }
    nue=(tNodo *)malloc(sizeof(tNodo));
    if(!nue)
        return 0;
    nue->info=malloc(tamD);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info,d,tamD);
    nue->tamInfo=tamD;
    nue->sig=*pl;

    (*pl)=nue;

    return 1;
}

bool buscar_en_orden(tLista *pl, void *d, unsigned tamD, int (*cmp)(const void *,const void *))
{
    int comp;
    tNodo *aux;
    while(*pl && (comp=cmp(d,(*pl)->info))>0)
    {
        pl=&(*pl)->sig;
    }
    if(comp!=0)
        return false; //no encontrado

    aux=*pl;
    memcpy(d,aux->info,MINIMO(aux->tamInfo,tamD));

    return true;
}


int lista_vacia(const tLista *pl)
{
    return *pl==NULL;
}

int lista_llena(const tLista *pl, unsigned tamD)
{
    tNodo *nue=(tNodo *)malloc(sizeof(tNodo));
    void *info=malloc(tamD);

    free(nue);
    free(info);

    return (nue==NULL || info==NULL);
}


int sacar_inicio_lista(tLista *pl, void *d, unsigned tamD)
{
    tNodo *elim=*pl;
    if(!elim)
        return 0;

    *pl=elim->sig;

    memcpy(d,elim->info,MINIMO(tamD,elim->tamInfo));
    free(elim->info);
    free(elim);
    return 1;
}
