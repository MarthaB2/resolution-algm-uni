#include "funciones.h"

int crearArchivoPedido(char *ruta)
{
    FILE *pf=fopen(ruta,"wb");
    if(!pf)
    {
        printf("Error de apertura de archivo pedidos.\n");
        return ERROR_ARCH;
    }

    tPedido ped[CANT_PED]=
    {
        {100,"Banana",10,10},
        {900,"Pera",15,20},
        {200,"Tomate",5,25},
        {700,"Durazno",10,400},
        {900,"Papa",150,10},
        {900,"Lechuga",50,25},
        {700,"Cebolla",100,10},
        {500,"Ajo",40,20},
        {800,"Remolacha",12,100},
        {200,"Sandia",5,200}
    };

    fwrite(ped,sizeof(tPedido),CANT_PED,pf);

    fclose(pf);
    return TODO_BIEN;
}

int procesarPedidos(char *ruta)
{
    FILE *pf=fopen(ruta,"rb");
    if(!pf)
    {
        printf("Error de apertura de archivo pedidos.\n");
        return ERROR_ARCH;
    }

    FILE *pfA=fopen("pedidosAscendentes.txt","wt");
    if(!pfA)
    {
        printf("Error de apertura de archivo ascendentes.\n");
        fclose(pf);
        return ERROR_ARCH;
    }

    tLista lista;
    crear_lista(&lista);

    tPedido ped;
    tPedido pedAux;
    tPedidoTotal pedT;
    fread(&ped,sizeof(tPedido),1,pf);
    while(!feof(pf))
    {
        pedT.importe_total=0;
        pedAux=ped;
        while(pedAux.nro_pedido==ped.nro_pedido && !feof(pf))
        {
            pedT.nro_pedido=ped.nro_pedido;
            pedT.importe_total=ped.cantidad_pedida*ped.precio_unitario;
            if(!lista_llena(&lista,sizeof(tPedido)))
            {
                insertar_en_orden(&lista,&pedT,sizeof(tPedidoTotal),cmp_nroPedido,acumular_importe);
            }
            else
            {
                printf("Sin memoria.\n");
                return SIN_MEM;
            }
            pedAux.nro_pedido=ped.nro_pedido;
            fread(&ped,sizeof(tPedido),1,pf);
        }
    }

    while(!lista_vacia(&lista))
    {
        sacar_inicio_lista(&lista,&pedT,sizeof(tPedidoTotal));
        grabarArchivoTotales(pfA,&pedT);
    }

    fclose(pf);
    fclose(pfA);
    return TODO_BIEN;
}

int cmp_nroPedido(const void *a1,const void *b1)
{
    tPedidoTotal *a=(tPedidoTotal *)a1;
    tPedidoTotal *b=(tPedidoTotal *)b1;

    return a->nro_pedido-b->nro_pedido;
}

void acumular_importe( void *a1, const void *b1)
{
    tPedidoTotal *a=(tPedidoTotal *)a1;
    tPedidoTotal *b=(tPedidoTotal *)b1;

    a->importe_total+=b->importe_total;
}


void grabarArchivoTotales(FILE *pf,tPedidoTotal *pedT)
{
    fprintf(pf,"%d|%.2f\n",pedT->nro_pedido,pedT->importe_total);
    printf("%d|%.2f\n",pedT->nro_pedido,pedT->importe_total);
}
