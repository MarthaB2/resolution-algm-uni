#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MENU_MSJ "Mostrar impuesto vencidos de:\n"\
                 "[A] - cada dni\n"\
                 "[B] - cada dni y patente\n"\
                 "[X] - salir\n"\

#define MENU_OPC "ABX"

char  menu(const char *msj, const char *opc);

#endif // UTILITARIAS_H_INCLUDED
