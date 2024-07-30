#include "colaE.h"


void crear_cola(tCola *pc)
{
    pc->pri=TAM-70;
    pc->ult=TAM-70;
    pc->tamDisp=TAM;
}

int poner_en_cola(tCola *pc, const void *d, unsigned tamD)
{
    unsigned ini,fin;

    if(pc->tamDisp<(tamD+sizeof(unsigned)))
        return SIN_MEM;

    ini=MINIMO(TAM-pc->ult,sizeof(unsigned));
    if(ini!=0)
        memcpy(pc->vec+pc->ult,&tamD,ini);

    fin=sizeof(unsigned)-ini;
    if(fin!=0)
        memcpy(pc->vec,((char *)&tamD)+ini,fin);

    pc->ult=fin ? fin : pc->ult+ini;

    ini=MINIMO(TAM-pc->ult,tamD);
    if(ini!=0)
        memcpy(pc->vec+pc->ult,d,ini);

    fin=tamD-ini;
    if(fin!=0)
        memcpy(pc->vec,((char *)d)+ini,fin);

    pc->ult=fin ? fin : pc->ult+ini;

    pc->tamDisp-=(sizeof(unsigned)+tamD);
    return TODO_BIEN;
}
int sacar_de_cola(tCola *pc, void *d, unsigned tamD)
{
    unsigned ini,fin,tamDato;

    if(pc->tamDisp==TAM)
        return -2;

    ini=MINIMO(TAM-pc->pri,sizeof(unsigned));
    if(ini!=0)
        memcpy(&tamDato,pc->vec+pc->pri,ini);

    fin=sizeof(unsigned)-ini;
    if(fin!=0)
        memcpy(((char *)&tamDato)+ini,pc->vec,fin);

    pc->pri=fin ? fin : pc->pri+ini;

    tamDato=MINIMO(tamDato,tamD);
    ini=MINIMO(TAM-pc->pri,tamDato);
    if(ini!=0)
        memcpy(d,pc->vec+pc->pri,ini);

    fin=tamD-ini;
    if(fin!=0)
        memcpy(((char *)d)+ini,pc->vec,fin);

    pc->pri=fin ? fin : pc->pri+ini;

    pc->tamDisp+=(sizeof(unsigned)+tamD);
    return TODO_BIEN;
}


int cola_vacia(const tCola *pc)
{
    return pc->tamDisp==TAM;
}

int cola_llena(const tCola *pc,unsigned tamD)
{
    return (pc->tamDisp<(tamD+sizeof(unsigned)));
}


void vaciar_cola( tCola *pc)
{
    pc->pri=pc->ult;
    pc->tamDisp=TAM;
}
