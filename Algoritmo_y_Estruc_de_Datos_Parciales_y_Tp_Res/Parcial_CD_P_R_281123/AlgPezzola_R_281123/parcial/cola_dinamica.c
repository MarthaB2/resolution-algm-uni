#include "../include/cola_dinamica.h"

#define SIN_MEM -1
#define COLA_VACIA 0
#define TODO_OK 1

void crear_cola(tCola* pc)
{
    pc->pri=pc->ult=NULL;
}

int poner_en_cola(tCola* pc, const void* pd, unsigned tam)
{
    tNodo *nue = (tNodo *)malloc(sizeof(tNodo));
    if(!nue)
        return SIN_MEM;

    nue->info=malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->info,pd,tam);
    nue->tamInfo=tam;
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

    return TODO_OK;
}

int sacar_de_cola(tCola* pc, void* pd, unsigned tam)
{
    tNodo *elim=pc->pri;

    if(!elim)
        return 0;

    memcpy(pd,elim->info,MINIMO(elim->tamInfo,tam));

    pc->pri=elim->sig;
    if(!pc->pri)
        pc->ult=NULL;

    free(elim->info);
    free(elim);
    return TODO_OK;
}
/*
int frente_de_cola(const tCola* pc, void* pd, unsigned tam)
{


    return TODO_OK;
}*/

int cola_llena(const tCola* pc, unsigned tam)
{
    tNodo *nue=(tNodo *)malloc(sizeof(tNodo));
    void *info=malloc(tam);

    free(nue);
    free(info);

    return !nue || !info;
}

int cola_vacia(const tCola* pc)
{
    return !pc->pri;
}

void vaciar_cola_alu(tCola * pc)
{
    while(pc->pri)
    {
        tNodo *aux=pc->pri;
        pc->pri=aux->sig;
        free(aux->info);
        free(aux);
    }
    pc->ult = NULL;
}
