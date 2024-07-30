#include "funciones.h"

int main()
{
    char opc;
    crearArchivoImpuestoVencidos("impuestosVencidos.dat");

    opc=menu(MENU_MSJ,MENU_OPC);

    switch(opc)
    {
        case 'A':
            procesarDeudas("impuestosVencidos.dat",grabar_dni,cmp_dni);
            break;
        case 'B':
            procesarDeudas("impuestosVencidos.dat",grabar_dni_y_patente,cmp_dni_y_patente);
            break;
        case 'X':
            printf("Saliendo del programa\n");
            break;
    }

    return 0;
}
