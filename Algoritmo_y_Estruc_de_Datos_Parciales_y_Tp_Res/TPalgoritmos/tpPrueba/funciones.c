#include "funciones.h"

int cmp_dni(const void *na,const void *nb)
{
    char *a=(char *)na;
    char *b=(char *)nb;

    long *x=malloc(sizeof(a)-sizeof(unsigned));
    long *y=malloc(sizeof(b)-sizeof(unsigned));

    memcpy(x,a,sizeof(a)-sizeof(unsigned));
    memcpy(y,b,sizeof(b)-sizeof(unsigned));

    return *x - *y;
}



int cargarIndiceConArchBinNoOrdenadoPorInsercion(t_indice *ind, const char *path)
{
    FILE *pf=fopen(path,"rb");
    if(!pf)
        return ERROR_ARCH;

    T_Socio soc;
    int i=1;

    fread(&soc,sizeof(T_Socio),1,pf);

    while(!feof(pf))
    {
        ind_insertar(ind,&soc.dni,i);
        i++;

        fread(&soc,sizeof(T_Socio),1,pf);
    }

    fclose(pf);
    return TODO_BIEN;
}




void ingresarNuevoSocio(T_Socio *socio)
{
    printf("Ingrese nuevo socio\n");
    printf("\nDNI: ");
    scanf("%ld",&socio->dni);
    printf("\nApellido: ");
    fflush(stdin);
    gets(socio->apellido);
    printf("\nNombre: ");
    fflush(stdin);
    gets(socio->nombre);
    printf("\nFecha de nacimiento: ");
    scanf("%d/%d/%d",&socio->fechaNacimiento.dia,&socio->fechaNacimiento.mes,&socio->fechaNacimiento.anio);
    printf("\nSexo: ");
    fflush(stdin);
    scanf("%c",&socio->sexo);
    printf("\nFecha de afiliacion: ");
    scanf("%d/%d/%d",&socio->fechaAfiliacion.dia,&socio->fechaAfiliacion.mes,&socio->fechaAfiliacion.anio);
    printf("\nCategoria: ");
    fflush(stdin);
    gets(socio->categoria);
    while(strcmp(socio->categoria,"MENOR")!=0 && strcmp(socio->categoria,"CADETE")!=0 && strcmp(socio->categoria,"ADULTO")!=0 && strcmp(socio->categoria,"VITALICIO")!=0 && strcmp(socio->categoria,"HONORARIO")!=0 && strcmp(socio->categoria,"JUBILADO")!=0)
    {
        printf("Error de catagoria. Ingrese de nuevo.\n");
        printf("\nCategoria: ");
        fflush(stdin);
        gets(socio->categoria);
    }
    printf("\nFecha de ultima cuota pagada: ");
    scanf("%d/%d/%d",&socio->fechaUltimaCuotaPaga.dia,&socio->fechaUltimaCuotaPaga.mes,&socio->fechaUltimaCuotaPaga.anio);
    socio->estado='A';
    socio->fechaBaja.dia=0;
    socio->fechaBaja.mes=0;
    socio->fechaBaja.anio=0;
}


int alta(T_Socio *socio,FILE *maestro,t_indice *ind)
{
    T_Socio socAux;
    unsigned nroReg;
    fseek(maestro,0L,SEEK_END);
    nroReg=ftell(maestro)/sizeof(T_Socio) + 1;

    if(!ind_insertar(ind,&socio->dni,nroReg))
    {
        ind_buscar(ind,&socio->dni,&nroReg);
        fseek(maestro,(nroReg-1)*sizeof(T_Socio),SEEK_SET);
        fread(&socAux,sizeof(T_Socio),1,maestro);
        if(socAux.estado=='I')
        {
            fseek(maestro,-(long)sizeof(T_Socio),SEEK_CUR);
            fwrite(socio,sizeof(T_Socio),1,maestro);
            return TODO_BIEN;
        }
        else
            return DUPLICADO;
    }


    fwrite(socio,sizeof(T_Socio),1,maestro);
    fseek(maestro,0L,SEEK_SET);
    return TODO_BIEN;
}


int ingresarModiSocio(T_Socio *socio,t_indice *ind, FILE *maestro)
{

    unsigned nroReg;
    printf("\nIngrese socio a modificar \n");
    printf("\nDNI: ");
    scanf("%ld",&socio->dni);

    if(ind_buscar(ind,&socio->dni,&nroReg)==0)
    {
        printf("No existe dni.\n");
        return 0;
    }

    fseek(maestro,(nroReg-1)*sizeof(T_Socio),SEEK_SET);
    fread(socio,sizeof(T_Socio),1,maestro);
    return TODO_BIEN;
}


void modificar(T_Socio *socio,FILE *maestro)
{
    char opc;
    do
    {
        opc = menu("Elija una opcion:\n\n"
                   "1 - Apellido\n"
                   "2 - Nombre\n"
                   "3 - Categoria\n"
                   "4 - Sexo\n"
                   "5 - Fecha de ultima cuota paga\n"
                   "0 - Salir\n"
                   "--->",
                   "123450");

        switch(opc)
        {
        case '1' :
            printf("\nApellido: ");
            fflush(stdin);
            gets(socio->apellido);
            break;
        case '2' :
            printf("\nNombre: ");
            fflush(stdin);
            gets(socio->nombre);
            break;
        case '3' :
            printf("\nCategoria: ");
            fflush(stdin);
            gets(socio->categoria);
            while(strcmp(socio->categoria,"MENOR")!=0 && strcmp(socio->categoria,"CADETE")!=0 && strcmp(socio->categoria,"ADULTO")!=0 && strcmp(socio->categoria,"VITALICIO")!=0 && strcmp(socio->categoria,"HONORARIO")!=0 && strcmp(socio->categoria,"JUBILADO")!=0)
            {
                printf("Error de catagoria. Ingrese de nuevo.\n");
                printf("\nCategoria: ");
                fflush(stdin);
                gets(socio->categoria);
            }
            break;
        case '4' :
            printf("\nSexo: ");
            fflush(stdin);
            scanf("%c",&socio->sexo);
            break;
        case '5' :
            printf("\nFecha de ultima cuota pagada: ");
            scanf("%d/%d/%d",&socio->fechaUltimaCuotaPaga.dia,&socio->fechaUltimaCuotaPaga.mes,&socio->fechaUltimaCuotaPaga.anio);
            break;
        case '0' :
            printf("Saliendo\n");
            break;
        }
    }
    while(opc !='0');


    fseek(maestro,-(long)(sizeof(T_Socio)),SEEK_CUR);
    fwrite(socio,sizeof(T_Socio),1,maestro);


    fseek(maestro,0L,SEEK_SET);
}


int ingresarSocioABajar(T_Socio *socio,t_indice *ind, FILE *maestro)
{
    time_t t;
    struct tm tm;

    unsigned nroReg;
    printf("\nIngrese socio a dar de baja \n");
    printf("\nDNI: ");
    scanf("%ld",&socio->dni);

    if(ind_buscar(ind,&socio->dni,&nroReg)==0)
    {
        printf("No existe dni.\n");
        return NO_EXISTE;
    }

    fseek(maestro,(nroReg-1)*sizeof(T_Socio),SEEK_SET);
    fread(socio,sizeof(T_Socio),1,maestro);

    if(socio->estado=='I')
    {
        ind_eliminar(ind,&socio->dni,&nroReg);
        printf("Ya esta dado de baja.\n");
        fseek(maestro,0L,SEEK_SET);
        return TODO_BIEN;
    }
    else
    {
        socio->estado='I';
        ind_eliminar(ind,&socio->dni,&nroReg);
        fseek(maestro,-(long)sizeof(T_Socio),SEEK_CUR);


        t = time(NULL);
        tm = *localtime(&t);
        socio->fechaBaja.dia = tm.tm_mday;
        socio->fechaBaja.mes = tm.tm_mon + 1;
        socio->fechaBaja.anio = tm.tm_year + 1900;
        fwrite(socio,sizeof(T_Socio),1,maestro);


        fseek(maestro,0L,SEEK_SET);
        return TODO_BIEN;
    }
}



int listar(T_Socio *socio,t_indice *ind, FILE *maestro)
{
    ind_recorrer(ind,mostrarMaestro,maestro);

    fseek(maestro,0L,SEEK_SET);
    return TODO_BIEN;
}


void mostrarMaestro(const void *info, unsigned tam, void *params)
{
    unsigned nro_reg;
    T_Socio socio;

    memcpy(&nro_reg,info+sizeof(long),sizeof(unsigned));

    fseek((FILE *)params,(nro_reg-1)*sizeof(T_Socio),SEEK_SET);
    fread(&socio,sizeof(T_Socio),1,(FILE *)params);
    if(socio.estado!='I')
    {
        printf("%ld,%s,%s,%d/%d/%d,%c,%d/%d/%d,%s,%d/%d/%d,%c\n",socio.dni,socio.apellido,socio.nombre,
               socio.fechaNacimiento.dia,socio.fechaNacimiento.mes,socio.fechaNacimiento.anio,socio.sexo,
               socio.fechaAfiliacion.dia,socio.fechaAfiliacion.mes,socio.fechaAfiliacion.anio,socio.categoria,
               socio.fechaUltimaCuotaPaga.dia,socio.fechaUltimaCuotaPaga.mes,socio.fechaUltimaCuotaPaga.anio,
               socio.estado);

    }
}




void mostrarDato(const void * info, unsigned tam, void * params)
{
    long clave;
    unsigned nro_reg;

    memcpy(&clave,info,sizeof(long));
    memcpy(&nro_reg,info+sizeof(long),sizeof(unsigned));
    printf("%ld-%u\n",clave,nro_reg);
}


