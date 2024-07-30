#include"../include/cola_dinamica.h"
#include<ferreteria.h>
#include<utilitarias.h>
#include<string.h>
#include<stdlib.h>


int procesar_pedidos(const char * path_prods, const char * path_pedidos)
{
    FILE *pfProd=fopen(path_prods,"r+b");
    if(!pfProd)
    {
        printf("Error de apertura de archivo productos\n");
        return ARCH_ERROR;
    }
    FILE *pfPed=fopen(path_pedidos,"rt");
    if(!pfPed)
    {
        printf("Error de apertura de archivo pedidos\n");
        fclose(pfProd);
        return ARCH_ERROR;
    }
    FILE *pfRea=fopen("../Archivos/pedidos_realizados.txt","wt");
    if(!pfRea)
    {
        printf("Error de apertura de archivo productos\n");
        fclose(pfProd);
        fclose(pfPed);
        return ARCH_ERROR;
    }
    FILE *pfFal=fopen("../Archivos/pedidos_faltantes.txt","wt");
    if(!pfFal)
    {
        printf("Error de apertura de archivo pedidos\n");
        fclose(pfProd);
        fclose(pfPed);
        fclose(pfRea);
        return ARCH_ERROR;
    }

    tCola c;
    crear_cola(&c);

    int cod_pedAux;
    int estado=1;

    char linea[TAM_LINEA];
    t_pedido ped;

    fgets(linea,TAM_LINEA,pfPed);
    trozarLF(&ped,linea);

    while(!feof(pfPed))
    {
        cod_pedAux=ped.cod_ped;
        while(!feof(pfPed) && ped.cod_ped==cod_pedAux)
        {
            cod_pedAux=ped.cod_ped;
            agregarPedidoEnCola(&c,&ped,&estado,pfProd);
            fgets(linea,TAM_LINEA,pfPed);
            trozarLF(&ped,linea);
        }

        if(estado)
        {
            procesarPedidosRealizados(&c,pfProd,pfRea,&cod_pedAux);
        }
        else
        {
            procesarPedidosFaltantes(&c,pfProd,pfFal,&cod_pedAux);
        }

    }

    vaciar_cola_alu(&c);
    fclose(pfProd);
    fclose(pfPed);
    fclose(pfRea);
    fclose(pfFal);

    return TODO_OK;
}

void trozarLF(t_pedido *ped,char *linea)
{
    char *act=strchr(linea,'\n');
    if(act)
    {
        *act='\0';
        act-=3;
        sscanf(act,"%u",&ped->cant);
        *act='\0';
        act-=6;
        sscanf(act,"%u",&ped->cod_prod);
        *act='\0';
        sscanf(linea,"%u",&ped->cod_ped);
    }
}

void agregarPedidoEnCola(tCola* pc, t_pedido* ped, int* estadoPed, FILE* pfProd)
{
    t_producto_stock prod;
    if(!cola_llena(pc,sizeof(t_pedido)))
        poner_en_cola(pc,ped,sizeof(t_pedido));

    obtener_producto(&prod,ped->cod_prod,pfProd);
    *estadoPed= ped->cant <= prod.stock ? *estadoPed : 0;
}


void obtener_producto(t_producto_stock *prod,int pos,FILE *pfProd)
{
    fseek(pfProd,(pos-1)*sizeof(t_producto_stock),SEEK_SET);
    fread(prod,sizeof(t_producto_stock),1,pfProd);
}



void procesarPedidosRealizados(tCola* pc, FILE* pfProd, FILE* pfPedRea, int* codPrevio)
{
    float totalFinal=0;
    float total=0;
    t_pedido pedAux;
    t_producto_stock prod;

    fprintf(pfPedRea,"Pedido %d procesado\n",*codPrevio);

    while(!cola_vacia(pc))
    {
        sacar_de_cola(pc,&pedAux,sizeof(t_pedido));
        fseek(pfProd,(pedAux.cod_prod-1)*sizeof(t_producto_stock),SEEK_SET);
        fread(&prod,sizeof(t_producto_stock),1,pfProd);
        actualizarStock(&pedAux,&prod,pfProd);
        total = prod.precio*pedAux.cant;
        totalFinal+=total;
        fprintf(pfPedRea,"-%6u-%-20s:\t%3u $ %.2f $ %.2f\n",pedAux.cod_prod,prod.descripcion,
                pedAux.cant,prod.precio,total);
        total=0;
    }
    fprintf(pfPedRea,"\t\t\t\t\tTOTAL: %.2f\n\n",totalFinal);
}

void actualizarStock(t_pedido* ped, t_producto_stock* prod, FILE* pfProd)
{
    fseek(pfProd,-(long)(sizeof(t_producto_stock)),SEEK_CUR);
    prod->stock -= ped->cant;
    fwrite(prod,sizeof(t_producto_stock),1,pfProd);
}


void procesarPedidosFaltantes(tCola* pc, FILE* pfProd, FILE* pfFalta, int* codPrevio)
{
    t_pedido pedAux;
    t_producto_stock prod;

    fprintf(pfFalta,"Pedido %d con faltantes\n",*codPrevio);
    while(!cola_vacia(pc))
    {
        sacar_de_cola(pc,&pedAux,sizeof(t_pedido));
        fseek(pfProd,(pedAux.cod_prod-1)*sizeof(t_producto_stock),SEEK_SET);
        fread(&prod,sizeof(t_producto_stock),1,pfProd);
        if(prod.stock>pedAux.cant)
        {
            fprintf(pfFalta,"-%6u-%-20s:\t%d\t%3u\n",pedAux.cod_prod,prod.descripcion,prod.stock,
                pedAux.cant);
        }
        else
        {
            fprintf(pfFalta,"-%6u-%-20s:\t%d\t%3u %c\n",pedAux.cod_prod,prod.descripcion,prod.stock,
                pedAux.cant,'F');
        }

    }

}
