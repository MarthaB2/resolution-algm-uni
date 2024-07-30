#include "funciones.h"


int darDeAltaSocio(t_indice *ind,FILE *maestro);
int modificarSocio(t_indice *ind,FILE *maestro);
int darDeBajarSocio(t_indice *ind,FILE *maestro);
int listarSociosPorDNI(t_indice *ind,FILE *maestro);
int listarTop10(t_indice *ind,FILE *maestro);



int mostrarIndice(char *ruta, t_indice* ind);

int main()
{
    char opc;
    t_indice indice;
    FILE *maestro;
    ///Descomentar en caso de querer reiniciar el archivo.
    crearArchivoTexto("socios.csv");
    archTxtaBin("socios.csv","socios.bin",sizeof(T_Socio),trozarSocioLV);
    printf("\n\nArchivo socios:\n\n");
    mostrarSocios("socios.bin");


    ind_crear(&indice,sizeof(long),cmp_dni);

    cargarIndiceConArchBinNoOrdenadoPorInsercion(&indice,"socios.bin");

    maestro=fopen("socios.bin","r+b");
    if(!maestro)
    {
        printf("Error de apertura de archivo\n");
        return ERROR_ARCH;
    }


    do
    {
        opc = menu("Elija una opcion:\n\n"
                   "A - Dar de alta a un socio\n"
                   "M - Modificar socio\n"
                   "B - Dar de baja a un socio\n"
                   "L - Listar socios por DNI\n"
                   "P - Listar los 10 con mayor retraso en la fecha de pago\n"
                   "S - Salir\n"
                   "--->",
                   "AMBLPSsplbma");
        opc = toupper(opc);
        switch(opc)
        {
            case 'A' :
                darDeAltaSocio(&indice,maestro);
                break;

            case 'M' :
                modificarSocio(&indice,maestro);
                break;
            case 'B' :
                darDeBajarSocio(&indice,maestro);
                break;
            case 'L' :
                listarSociosPorDNI(&indice,maestro);
                break;
            case 'P' :
                listarTop10(&indice,maestro);
                break;
            case 'S' : printf("Saliendo\n");
                break;
        }
    }while(opc !='S');

    ind_grabar(&indice,"socios.idx");
    ind_vaciar(&indice);
    fclose(maestro);
    return 0;
}


int darDeAltaSocio(t_indice *ind,FILE *maestro)
{
    int r;
    T_Socio socio;
    ingresarNuevoSocio(&socio);
    r=alta(&socio,maestro,ind);
    imprimirMensaje(r);
    return TODO_BIEN;
}


int modificarSocio(t_indice *ind,FILE *maestro)
{
    int r;
    T_Socio socio;


    r=ingresarModiSocio(&socio,ind,maestro);
    modificar(&socio,maestro);
    imprimirMensaje(r);
    return TODO_BIEN;
}


int darDeBajarSocio(t_indice *ind,FILE *maestro)
{
    int r;
    T_Socio socio;

    r=ingresarSocioABajar(&socio,ind,maestro);
    imprimirMensaje(r);
    return TODO_BIEN;
}

int listarSociosPorDNI(t_indice *ind,FILE *maestro)
{
    int r;
    T_Socio socio;

    r=listar(&socio,ind,maestro);
    imprimirMensaje(r);
    return TODO_BIEN;
}
int listarTop10(t_indice *ind,FILE *maestro)
{
    T_Socio socio;

    tLista listaTop;
    crearlista(&listaTop);

    fread(&socio,sizeof(T_Socio),1,maestro);
    while(!feof(maestro))
    {
        insertarTopN(&listaTop,&socio,sizeof(T_Socio),CANT_MAX,comparaFechas);
        fread(&socio,sizeof(T_Socio),1,maestro);
    }

    while(!listaVacia(&listaTop))
    {
        sacarDeInicioLista(&listaTop,&socio,sizeof(T_Socio));
        printf("%ld,%s,%s,%d/%d/%d,%c,%d/%d/%d,%s,%d/%d/%d,%c,%d/%d/%d\n",socio.dni,socio.apellido,socio.nombre,
                socio.fechaNacimiento.dia,socio.fechaNacimiento.mes,socio.fechaNacimiento.anio,socio.sexo,
                socio.fechaAfiliacion.dia,socio.fechaAfiliacion.mes,socio.fechaAfiliacion.anio,socio.categoria,
                socio.fechaUltimaCuotaPaga.dia,socio.fechaUltimaCuotaPaga.mes,socio.fechaUltimaCuotaPaga.anio,
                socio.estado,socio.fechaBaja.dia,socio.fechaBaja.mes,socio.fechaBaja.anio);
    }

    fseek(maestro,0L,SEEK_SET);

    return TODO_BIEN;
}

int mostrarIndice(char *ruta, t_indice* ind)
{
    FILE *pf=fopen(ruta,"rb");
    if(!pf)
        return ERROR_ARCH;

    long clave;
    unsigned nro_reg;
    void* dato = malloc(sizeof(ind->a->info));


    fread(dato,sizeof(ind->a->info),1,pf);

    while(!feof(pf))
    {

        memcpy(&clave,dato,ind->tamClave);
        memcpy(&nro_reg,dato+ind->tamClave,sizeof(unsigned));
        printf("%ld-%u\n",clave,nro_reg);
        fread(dato,sizeof(ind->a->info),1,pf);
    }
    free(dato);

    fclose(pf);
    return 1;
}
