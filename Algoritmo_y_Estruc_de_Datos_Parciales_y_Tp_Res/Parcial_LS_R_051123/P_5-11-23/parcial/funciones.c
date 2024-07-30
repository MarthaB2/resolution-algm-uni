#include "funciones.h"

int crearArchivoImpuestoVencidos(char *ruta)
{
    FILE *pf=fopen(ruta,"wb");

    if(!pf)
    {
        printf("Error de apertura de archivo\n");
        return ERROr_ARCH;
    }

    tImpVenc imp[]={
                        {"AB123CD",1,"Flori",111,{2022,12,01},10500.55},
                        {"PP444PP",1,"Luca" ,222,{2022,12,02},12300   },
                        {"PP555PP",1,"Luca" ,222,{2023,02,01},10540.55},
                        {"CD321AB",1,"Flori",111,{2023,02,01},13420   },
                        {"AB123CD",2,"Flori",111,{2023,02,01},10550.55},
                        {"PP444PP",1,"Luca" ,222,{2023,02,01},10300.35},
                        {"DO222ML",6,"Ivan" ,333,{2023,01,01},12560.45},
                    };

    fwrite(imp,sizeof(tImpVenc),sizeof(imp)/sizeof(tImpVenc),pf);

    fclose(pf);
    return TODO_BIEN;
}


int procesarDeudas(char *ruta,void (*grabar)(tImpVenc *imp,FILE *pfD), int (*cmp)(const void *,const void *))
{
    FILE *pf=fopen(ruta,"rb");

    if(!pf)
    {
        printf("Error de apertura de archivo\n");
        return ERROr_ARCH;
    }


    tListaS lDeudas;

    crear_lista(&lDeudas);

    obtenerDeudas(&lDeudas,pf,cmp);
    fclose(pf);
    mostrarInformeDeudas(&lDeudas,"deuda.txt",grabar);




    return TODO_BIEN;
}


void obtenerDeudas(tListaS *pl, FILE *pfIV, int (*cmp)(const void *,const void *))
{
    tImpVenc imp;

    fseek(pfIV,0L,SEEK_SET);
    fread(&imp,sizeof(tImpVenc),1,pfIV);
    while(!feof(pfIV))
    {
        poner_en_orden_lista(pl,&imp,sizeof(tImpVenc),cmp,agruparDeuda);

        fread(&imp,sizeof(tImpVenc),1,pfIV);
    }
}


int cmp_dni(const void *na,const void *nb)
{
    tImpVenc *a=(tImpVenc *)na;
    tImpVenc *b=(tImpVenc *)nb;
    return a->dni - b->dni;
}

int cmp_dni_y_patente(const void *na,const void *nb)
{
    tImpVenc *a=(tImpVenc *)na;
    tImpVenc *b=(tImpVenc *)nb;

    if((a->dni - b->dni) == 0)
        return strcmp(a->patente,b->patente);

    return a->dni - b->dni;
}


void agruparDeuda(void *destinoN, const void *origenN)
{
    tImpVenc *destino=(tImpVenc *)destinoN;
    tImpVenc *origen=(tImpVenc *)origenN;

    destino->importe+=origen->importe;
}


void grabar_dni(tImpVenc *imp,FILE *pfD)
{
    fprintf(pfD,"DNI:%d|DEUDA TOTAL: $%.2f\n",imp->dni,imp->importe);
    printf("DNI:%d|DEUDA TOTAL: $%.2f\n",imp->dni,imp->importe);
}

void grabar_dni_y_patente(tImpVenc *imp,FILE *pfD)
{
    fprintf(pfD,"DNI:%d|PATENTE:%s|DEUDA TOTAL: $%.2f\n",imp->dni,imp->patente,imp->importe);
    printf("DNI:%d|PATENTE:%s|DEUDA TOTAL: $%.2f\n",imp->dni,imp->patente,imp->importe);
}


int mostrarInformeDeudas(tListaS *pl,char *ruta,void (*grabar)(tImpVenc *imp,FILE *pfD))
{
    FILE *pfDeu=fopen(ruta,"wt");
    if(!pfDeu)
    {
        printf("Error de apertura de archivo\n");
        return 0;
    }

    float total=0;

    tImpVenc imp;
    while(!lista_vacia(pl))
    {
        sacar_primero_lista(pl,&imp,sizeof(tImpVenc));
        total+=imp.importe;
        grabar(&imp,pfDeu);
    }
    fprintf(pfDeu,"TOTAL: $%.2f\n",total);
    printf("TOTAL: $%.2f\n",total);

    fclose(pfDeu);
    return 1;
}


