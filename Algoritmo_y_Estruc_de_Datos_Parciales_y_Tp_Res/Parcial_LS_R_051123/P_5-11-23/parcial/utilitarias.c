#include "utilitarias.h"

char  menu(const char *msj, const char *opc)
{
    char opcEleg;
    int primeraVez=1;

    do
    {
        if(!primeraVez)
        {
            //primeraVez=1;
            printf("Opcion incorrecta. Ingrese de nuevo\n");
        }
        printf("%s",msj);

        fflush(stdin);
        scanf("%c",&opcEleg);
        //system(pause);
        opcEleg=toupper(opcEleg);
        primeraVez=0;
    }while(!strchr(opc,opcEleg));

    printf("La opcion elegida es %c\n",opcEleg);
    return opcEleg;
}
