#include "funciones.h"


void ingresarDatos(tVuelo *vuelo)
{
    printf("\n-----------------INGRESE DATOS A PROCESAR-----------------\n\n");
    printf("Ingrese codigo de evento: ");
    fflush(stdin);
    scanf("%c",&vuelo->codigo_de_evento);
    while(vuelo->codigo_de_evento!= 'S' && vuelo->codigo_de_evento!= 'A' && vuelo->codigo_de_evento!='*')
    {
        printf("Error.\nIngrese de nuevo codigo de evento: ");
        fflush(stdin);
        scanf("%c",&vuelo->codigo_de_evento);
    }
    printf("Ingrese identificacion: ");
    scanf("%ld",&vuelo->identificacion);
}



void ingresarCodigodeEvento(tVuelo *vuelo)
{
    printf("\n-----------------INGRESE DATOS A PROCESAR-----------------\n\n");
    printf("Ingrese codigo de evento: ");
    fflush(stdin);
    scanf("%c",&vuelo->codigo_de_evento);
    while(vuelo->codigo_de_evento!= 'S' && vuelo->codigo_de_evento!= 'A' && vuelo->codigo_de_evento!='*')
    {
        printf("Error.\nIngrese de nuevo codigo de evento: ");
        fflush(stdin);
        scanf("%c",&vuelo->codigo_de_evento);
    }

}

void ingresarIdentificacion(tVuelo *vuelo)
{
    printf("Ingrese identificacion: ");
    scanf("%ld",&vuelo->identificacion);

}

int procesarVuelos(char *ruta,tCola *cola)
{
    FILE *pf=fopen("vuelosConfirmadosv2.txt","wt");
    if(!pf)
    {
        printf("Error de apertura de archivo.\n");
        return -1;
    }

    FILE *pfNC=fopen("vuelosNoConfirmados.txt","wt");
    if(!pfNC)
    {
        printf("Error de apertura de archivo.\n");
        fclose(pf);
        return -1;
    }
    tVuelo vuelo;
    tVuelo vueloAux;

    ingresarCodigodeEvento(&vuelo);

    while(vuelo.codigo_de_evento!='*')
    {
        ingresarIdentificacion(&vuelo);
        if(vuelo.codigo_de_evento=='S')
        {
            if(!cola_llena(cola,sizeof(tVuelo)))
                poner_en_cola(cola,&vuelo,sizeof(tVuelo));
            else
                printf("Sin memoria.\n");
        }
        if(vuelo.codigo_de_evento=='A')
        {
            if(!cola_vacia(cola))
            {
                sacar_de_cola(cola,&vueloAux,sizeof(tVuelo));
                fprintf(pf,"%ld|%ld\n",vueloAux.identificacion,vuelo.identificacion);
            }
            else
            {
                printf("No hay solicitudes para ser asignadas.\n");
            }
        }
        ingresarCodigodeEvento(&vuelo);
    }

    while(!cola_vacia(cola))
    {
        sacar_de_cola(cola,&vueloAux,sizeof(tVuelo));
        fprintf(pfNC,"%ld\n",vueloAux.identificacion);
    }

    fclose(pf);
    fclose(pfNC);
    return 1;
}
