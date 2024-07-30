#include "utilitarias.h"


char menu(const char *msj, const char *opc)
{
    char opta;
    int priVez = 1;

    do
    {
        printf("%s%s",
               priVez?priVez=0,"":"ERROR - Opcion NO VALIDA.\n", msj);
        fflush(stdin);
        scanf("%c", &opta);
    }while(strchr(opc, opta) == NULL);
    return opta;
}


void imprimirMensaje(int res)
{
    switch(res)
    {
        case TODO_BIEN:
            puts("Operacion realizada correctamente.");
            system("pause");
            system("cls");
            break;
        case SIN_MEM:
            puts("Error de memoria.");
            system("pause");
            system("cls");
            break;
        case ERROR_ARCH:
            puts("Error en el archivo.");
            system("pause");
            system("cls");
            break;
        case DUPLICADO:
            puts("Resgistro duplicado.");
            system("pause");
            system("cls");
            break;
        case NO_EXISTE:
            puts("Resgistro inexistente.");
            system("pause");
            system("cls");
            break;
    }
}



int comparaFechas(const void *sN1,const void *sN2)
{
    T_Socio *s1=(T_Socio *)sN1;
    T_Socio *s2=(T_Socio *)sN2;


    int cmp = s1->fechaUltimaCuotaPaga.anio - s2->fechaUltimaCuotaPaga.anio;
    if(cmp)
        return cmp;

    cmp = s1->fechaUltimaCuotaPaga.mes - s2->fechaUltimaCuotaPaga.mes;
    if(cmp)
        return cmp;

    return s1->fechaUltimaCuotaPaga.dia - s2->fechaUltimaCuotaPaga.dia;
}


 int mostrarTop10(T_Socio *vecS,int cant)
 {
     T_Socio *fin=vecS +(cant-1);

     while(vecS<=fin)
     {
         printf("%ld,%s,%s,%d/%d/%d,%c,%d/%d/%d,%s,%d/%d/%d,%c,%d/%d/%d\n",vecS->dni,vecS->apellido,vecS->nombre,
                vecS->fechaNacimiento.dia,vecS->fechaNacimiento.mes,vecS->fechaNacimiento.anio,vecS->sexo,
                vecS->fechaAfiliacion.dia,vecS->fechaAfiliacion.mes,vecS->fechaAfiliacion.anio,vecS->categoria,
                vecS->fechaUltimaCuotaPaga.dia,vecS->fechaUltimaCuotaPaga.mes,vecS->fechaUltimaCuotaPaga.anio,
                vecS->estado,vecS->fechaBaja.dia,vecS->fechaBaja.mes,vecS->fechaBaja.anio);
        vecS++;
     }
     return TODO_BIEN;
 }
