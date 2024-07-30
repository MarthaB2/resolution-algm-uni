#include "funciones.h"

void mensajes( int resp);

int main()
{
    int resp;
    crearArchivoPedido("ARCH_PED.dat");

    resp=procesarPedidos("ARCH_PED.dat");

    mensajes(resp);
    return 0;
}


void mensajes( int resp)
{
    switch(resp)
    {
    case TODO_BIEN:
        printf("Operacion realizada exitosamente.\n");
        break;
    case ERROR_ARCH:
        printf("Error de apertura de archivo.\n");
        break;
    case SIN_MEM:
        printf("Sin memoria.\n");
        break;
    }

}
