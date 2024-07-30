#include "funciones.h"


int crearArchivoPedido(char *ruta)
{
    FILE *pf=fopen(ruta,"wb");
    if(!pf)
    {
        printf("Error de apertura de archivo.\n");
        return ERROR_ARCH;
    }


    tPedido ped[TAM_PRODS]={
        {3,9,200,10},
        {3,2,100,90},
        {3,5,50,10},
        {3,6,150,10},
        {4,3,400,10},
        {5,1,170,10},
        {5,7,110,10},
        {6,2,8,1000},
        {6,5,9,500},
        {8,1,200,100}
    };

    fwrite(ped,sizeof(tPedido),TAM_PRODS,pf);

    fclose(pf);

    return TODO_BIEN;
}


int procesarPedidos(char *ruta)
{
    FILE *pf=fopen(ruta,"rb");
    if(!pf)
    {
        printf("Error de apertura del archivo pedidos.\n");
        return ERROR_ARCH;
    }


    FILE *pfSup=fopen("pedidosSuperiores.txt","wt");
    if(!pfSup)
    {
        printf("Error de apertura del archivo superiores.\n");
        fclose(pf);
        return ERROR_ARCH;
    }

    FILE *pfInf=fopen("pedidosInferiores.txt","wt");
    if(!pfInf)
    {
        printf("Error de apertura de archivo inferiores.\n");
        fclose(pf);
        fclose(pfSup);
        return ERROR_ARCH;
    }


    tCola cola;
    crear_cola(&cola);

    tPedido ped;
    tPedido pedAux;
    int nroPedAnt;

    float totalNroPed

    ;

    fread(&ped,sizeof(tPedido),1,pf);

    while(!feof(pf))
    {
        totalNroPed=0;
        nroPedAnt=ped.NRO_PED;
        while(nroPedAnt==ped.NRO_PED && !feof(pf))
        {
            if(!cola_llena(&cola,sizeof(tPedido)))
                poner_en_cola(&cola,&ped,sizeof(tPedido));
            else
            {
                if(!cola_vacia(&cola))
                    vaciar_cola(&cola);
                return SIN_MEM;
            }


            nroPedAnt=ped.NRO_PED;
            totalNroPed+=ped.CANT_PED*ped.PRECIO_UNI;
            fread(&ped,sizeof(tPedido),1,pf);
        }


        if(totalNroPed>=10000)
        {
            while(!cola_vacia(&cola))
            {
                sacar_de_cola(&cola,&pedAux,sizeof(tPedido));
                fprintf(pfSup,"%d|%d|%d|%.2f\n",pedAux.NRO_PED,pedAux.NRO_ART,pedAux.CANT_PED,pedAux.PRECIO_UNI);
            }
        }
        else
        {
            while(!cola_vacia(&cola))
            {
                sacar_de_cola(&cola,&pedAux,sizeof(tPedido));
                fprintf(pfInf,"%d|%d|%d|%.2f\n",pedAux.NRO_PED,pedAux.NRO_ART,pedAux.CANT_PED,pedAux.PRECIO_UNI);
            }
        }

    }



    fclose(pf);
    fclose(pfSup);
    fclose(pfInf);
    return TODO_BIEN;
}
