#include <stdio.h>
#include <stdlib.h>
#include <ferreteria.h>
#include <utilitarias.h>

#define PATH_PRODUCTOS "../Archivos/productos.dat"
#define PATH_PEDIDOS "../Archivos/pedidos.txt"

int main()
{

    crear_archivo_productos_res(PATH_PRODUCTOS);
    crear_archivo_pedidos_res(PATH_PEDIDOS);
    mostrar_archivo_productos_res(PATH_PRODUCTOS);
    printf("\n\n");
    mostrar_archivo_pedidos_res(PATH_PEDIDOS);
    /**
        Esta función debe realizar la actualización del achivo de stock de productos
        a partir de los pedidos
    */
    //procesar_pedidos_res(PATH_PRODUCTOS,PATH_PEDIDOS);
    procesar_pedidos(PATH_PRODUCTOS,PATH_PEDIDOS);

    printf("\n\n********  RESULTADOS  ***********\n");

    mostrar_archivo_productos_res(PATH_PRODUCTOS);

    printf("\n\n*********  REALIZADOS  ***********\n");
    mostrar_archivo_texto_res("../Archivos/pedidos_realizados.txt");
    printf("\n*********  FIN REALIZADOS  ***********\n\n");

    printf("\n\n*********  FALTANTES  ***********\n");
    mostrar_archivo_texto_res("../Archivos/pedidos_faltantes.txt");
    printf("\n*********  FIN FALTANTES  ***********\n\n");

    return 0;
}
