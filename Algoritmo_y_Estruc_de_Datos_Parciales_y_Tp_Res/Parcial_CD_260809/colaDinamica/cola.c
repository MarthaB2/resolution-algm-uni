#include "cola.h"

void crear_cola(tCola *pc)
{
{
    tNodo *nue=(tNodo *)malloc(sizeof(tNodo));
    pc->pri=NULL;
    pc->ult=NULL;
}

int poner_en_cola(tCola *pc, void *d, unsigned tamD)
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
    nue->sig=NULL;

    if(pc->ult)
    {
        pc->ult->sig=nue;
    }
    else
    {
        pc->pri=nue;
    }
    pc->ult=nue;
    return 1;
}
int sacar_de_cola(tCola *pc, void *d, unsigned tamD)
{
    tNodo *elim=pc->pri;

    if(!elim)
        return 0;

    pc->pri=elim->sig;

    memcpy(d,elim->info,MINIMO(tamD,elim->tamInfo));

    if(!pc->pri)
        pc->ult=NULL;

    free(elim->info);
    free(elim);

    return 1;
}
int cola_vacia(const tCola *pc)
{
    return pc->pri==NULL;
}

int cola_llena(const tCola *pc, unsigned tamD)
{
    tNodo *nue=(tNodo *)malloc(sizeof(tNodo));
    void *info=malloc(sizeof(tamD));

    free(nue);
    free(info);
    return nue==NULL || info==NULL;
}

void vaciar_cola(tCola *pc)
{
    while(pc->pri)
    {
        tNodo *aux=pc->pri;
        pc->pri=aux->sig;
        free(aux->info);
        free(aux);
    }
    pc->ult=NULL;
}
