#include "funciones.h"

int main()
{
    crearArchivoPedido("pedidos.dat");

    printf("Pedidos:\n\n");
    printf("nro_pedido|importe_total\n");
    procesarPedidos("pedidos.dat");

    return 0;
}
