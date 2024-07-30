#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <utilitarias.h>
#include <ferreteria.h>

int leer_pedido(t_pedido * mov, FILE * arch_mov)
{
    char linea[TAM_LINEA];

    if(fgets(linea,TAM_LINEA,arch_mov))
    {
        sscanf(linea, "%6d%6d%3d", &(mov->cod_ped), &(mov->cod_prod), &(mov->cant));
        return TODO_OK;
    }

    return 0;
}
