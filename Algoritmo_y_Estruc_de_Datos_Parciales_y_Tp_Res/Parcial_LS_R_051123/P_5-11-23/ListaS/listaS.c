#include "listaS.h"


void crear_lista(tListaS *pl)
{
    *pl=NULL;
}

int poner_en_orden_lista(tListaS *pl,const void *dato,unsigned tamDato,int (*cmp)(const void *,const void *),void (*agrupar)( void *,const void *))
{
    tNodo *nue;
    int comp;


    while(*pl && (comp=cmp(dato,(*pl)->info))>0)
    {
        pl=&(*pl)->sig;
    }

    if(comp==0)
    {
        agrupar((*pl)->info,dato);
        return 1;
    }
    nue=(tNodo *)malloc(sizeof(tNodo));
    if(!nue)
    {
        return 0;
    }
    nue->info=malloc(tamDato);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info,dato,tamDato);
    nue->tamInfo=tamDato;
    nue->sig=*pl;

    *pl=nue;
    return 1;
}


int lista_vacia(tListaS *pl)
{
    return *pl==NULL;
}


int sacar_primero_lista(tListaS *pl,void *dato,unsigned tamDato)
{
    tNodo *elim=*pl;
    if(!elim)
        return 0;

    *pl=elim->sig;

    memcpy(dato,elim->info,MINIMO(tamDato,elim->tamInfo));
    free(elim->info);
    free(elim);

    return 1;
}
