#include "funciones.h"

int main()
{
    ///VERSION 1
    /*
    FILE *pf=fopen("vuelos_confirmados.txt","wt");
    if(!pf)
    {
        printf("Error de apertura de archivo.\n");
        return -1;
    }
    tVuelo vuelo;
    tVuelo vueloAux;
    tCola cola;
    crear_cola(&cola);

    do
    {
        ingresarDatos(&vuelo);
        if(vuelo.codigo_de_evento=='S')
        {
            if(!cola_llena(&cola,sizeof(tVuelo)))
                poner_en_cola(&cola,&vuelo,sizeof(tVuelo));
            else
            {
                printf("Sin memoria.\n");
                return -2;
            }

        }
        if(vuelo.codigo_de_evento=='A')
        {
            if(!cola_vacia(&cola))
            {
                sacar_de_cola(&cola,&vueloAux,sizeof(tVuelo));
                fprintf(pf,"%ld|%ld\n",vueloAux.identificacion,vuelo.identificacion);
            }
            else
            {
                printf("No hay solicitudes para ser asignadas.\n");
            }
        }
    }
    while(vuelo.codigo_de_evento!='*');
    fclose(pf);
    */

    tCola cola;
    crear_cola(&cola);

    procesarVuelos("vuelosConfirmadosv2.txt",&cola);




    return 0;
}

/*
cod	nro pasaporte
S	1234
S	4567
S	3456
S	6789
S	2345

cod nro_pasaje
A	1000
A 	2000
A	3000

ARCHIVO CONFIRMADOS
nropasaporte nro_pasaje
1234	1000
4567	2000
3456	3000

ARCHIVO NO CONFIRMADOS
nropasaporte
6789
2345
*/
