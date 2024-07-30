#include "socios.h"

int crearArchivoTexto(char *ruta)
{
    FILE *pf=fopen(ruta,"wt");
    if(!pf)
    {
        puts("Error de archivo\n");
        return ERROR_ARCH;
    }
    int i;

    T_Socio vSocio[CANT_SO]={
        {12345678, "Perez", "Juan", {1,1,1990}, 'M', {15,1,2022}, "ADULTO", {1,06,2024}, 'A',{0} },
        {23456789, "Garcia", "Maria", {10,5,1985}, 'F', {20,3,2021}, "ADULTO", {15,5,2024}, 'A', {0}},
        {34567890, "Rodriguez", "Carlos", {25,9,2000}, 'M', {28,2,2020}, "CADETE", {20,4,2024}, 'A', {0}},
        {45678901, "Lopez", "Ana", {15,12,1975}, 'F', {10,6,2019}, "ADULTO", {30,3,2024}, 'A', {0}},
        {56789012, "Martinez", "Lucia", {5,11,1995}, 'F', {23,11,2018}, "ADULTO", {25,2,2024}, 'A', {0}},
        {67890123, "Sanchez", "Pedro", {18,07,1960}, 'M', {14,8,2017}, "JUBILADO", {20,1,2024}, 'A', {0}},
        {78901234, "Gomez", "Sofia", {11,3,2005}, 'F', {1,5,2023}, "MENOR", {1,6,2024}, 'A', {0}},
        {89012345, "Diaz", "Javier", {22,2,1980}, 'M', {25,10,2016}, "ADULTO", {15,4,2024}, 'A', {0}},
        {90123456, "Fernandez", "Laura", {29,8,1992}, 'F', {5,9,2015}, "ADULTO", {10,3,2024}, 'A', {0}},
        {53492991, "Ruiz", "Marta", {2,12,1998}, 'F', {30,7,2014}, "CADETE", {5,2,2020}, 'I', {5,2,2024}},
        {23918374, "Barra", "Isabela", {1,3,1992}, 'F', {15,4,2022}, "ADULTO", {9,03,2024}, 'A',{0} },
        {43456789, "Cruz", "Lila", {10,5,1995}, 'F', {20,8,2021}, "ADULTO", {15,6,2024}, 'A', {0}},
        {89967890, "Ruiz", "Carlos", {25,9,2004}, 'M', {28,2,2021}, "CADETE", {11,3,2024}, 'A', {0}},
        {33678901, "Lopez", "Juliana", {15,12,1995}, 'F', {10,6,2019}, "ADULTO", {29,1,2021}, 'I', {0}},
        {66789012, "Sanchez", "Karina", {5,10,1999}, 'F', {23,11,2018}, "ADULTO", {21,2,2024}, 'A', {0}},
        {18590123, "Claros", "Gustavo", {18,9,1998}, 'M', {14,8,2017}, "JUBILADO", {20,1,2020}, 'I', {0}},
        {71901234, "Paque", "Gisela", {14,4,2001}, 'F', {1,6,2023}, "MENOR", {1,4,2024}, 'A', {0}},
        {82212345, "Aro", "Andres", {23,6,2000}, 'M', {25,12,2020}, "ADULTO", {17,3,2024}, 'A', {0}}
    };

    for(i=0; i<CANT_SO ; i++)
    {
        fprintf(pf,"%ld,%s,%s,%d/%d/%d,%c,%d/%d/%d,%s,%d/%d/%d,%c,%d/%d/%d\n",vSocio[i].dni,vSocio[i].apellido,vSocio[i].nombre,
                vSocio[i].fechaNacimiento.dia,vSocio[i].fechaNacimiento.mes,vSocio[i].fechaNacimiento.anio,vSocio[i].sexo,
                vSocio[i].fechaAfiliacion.dia,vSocio[i].fechaAfiliacion.mes,vSocio[i].fechaAfiliacion.anio,vSocio[i].categoria,
                vSocio[i].fechaUltimaCuotaPaga.dia,vSocio[i].fechaUltimaCuotaPaga.mes,vSocio[i].fechaUltimaCuotaPaga.anio,
                vSocio[i].estado,vSocio[i].fechaBaja.dia,vSocio[i].fechaBaja.mes,vSocio[i].fechaBaja.anio);
    }

    fclose(pf);
    return TODO_OK;
}


int archTxtaBin(const char *narcht, const char *narchb, size_t tamreg, int (*TxtaBin)(char *, void *))
{
    FILE *archt = fopen(narcht,"rt");
    if(!archt)
    {
        printf("Error apertura de archivo de texto");
        return ERROR_ARCH;
    }

    FILE *archb = fopen(narchb,"wb");
    if(!archb)
    {
        printf("Error apertura de archivo binario");
        fclose(archt);
        return ERROR_ARCH;
    }

    void * reg = malloc(tamreg);
    if(!reg)
        return ERROR_SINMEM;

    char linea[TAM_LINEA];
    int ret;
    fgets(linea, TAM_LINEA, archt);
    while(!feof(archt))
    {
        ret = TxtaBin(linea, reg); //convertir de binario a texto
        if(ret == TODO_OK)
            fwrite(reg, tamreg, 1, archb);
        fgets(linea, TAM_LINEA, archt);
    }
    fclose(archb);
    fclose(archt);
    return TODO_OK;
}


int trozarSocioLV(char *linea, void *reg)
{
    T_Socio * socio = (T_Socio *)reg;

    char *actual = strchr(linea, '\n');
    *actual = '\0';

    actual = strrchr(linea, ',');
    sscanf(actual+1, "%d/%d/%d", &socio->fechaBaja.dia, &socio->fechaBaja.mes, &socio->fechaBaja.anio);
    *actual = '\0';

    actual = strrchr(linea, ',');
    sscanf(actual+1, "%c", &socio->estado);
    *actual = '\0';

    actual = strrchr(linea, ',');
    sscanf(actual+1, "%d/%d/%d", &socio->fechaUltimaCuotaPaga.dia, &socio->fechaUltimaCuotaPaga.mes, &socio->fechaUltimaCuotaPaga.anio);
    *actual = '\0';

    actual = strrchr(linea, ',');
    strncpy(socio->categoria, actual+1, 11); ///no pone el \0 ///VERIFICAR EL 11
    socio->categoria[10] = '\0';
    *actual = '\0';

    actual = strrchr(linea, ',');
    sscanf(actual+1, "%d/%d/%d", &socio->fechaAfiliacion.dia, &socio->fechaAfiliacion.mes, &socio->fechaAfiliacion.anio);
    *actual = '\0';

    actual = strrchr(linea, ',');
    sscanf(actual+1, "%c", &socio->sexo);
    *actual = '\0';

    actual = strrchr(linea, ',');
    sscanf(actual+1, "%d/%d/%d", &socio->fechaNacimiento.dia, &socio->fechaNacimiento.mes, &socio->fechaNacimiento.anio);
    *actual = '\0';

    actual = strrchr(linea, ',');
    strncpy(socio->nombre, actual+1, 61);
    socio->nombre[60] = '\0';
    *actual = '\0';

    actual = strrchr(linea, ',');
    strncpy(socio->apellido, actual+1, 61);
    socio->apellido[60] = '\0';
    *actual = '\0';

    sscanf(linea, "%ld", &socio->dni);

    return TODO_OK;
}



int mostrarSocios(char *ruta)
{
    FILE *pf=fopen(ruta,"rb");
    if(pf==NULL)
    {
        printf("Error de apertura de archivos\n");
        return 0;
    }

    T_Socio socio;

    fread(&socio,sizeof(T_Socio),1,pf);
    while(!feof(pf))
    {
        if(socio.fechaBaja.anio!= 0)
        {
            printf("%ld,%s,%s,%d/%d/%d,%c,%d/%d/%d,%s,%d/%d/%d,%c,%d/%d/%d\n",socio.dni,socio.apellido,socio.nombre,
                socio.fechaNacimiento.dia,socio.fechaNacimiento.mes,socio.fechaNacimiento.anio,socio.sexo,
                socio.fechaAfiliacion.dia,socio.fechaAfiliacion.mes,socio.fechaAfiliacion.anio,socio.categoria,
                socio.fechaUltimaCuotaPaga.dia,socio.fechaUltimaCuotaPaga.mes,socio.fechaUltimaCuotaPaga.anio,
                socio.estado,socio.fechaBaja.dia,socio.fechaBaja.mes,socio.fechaBaja.anio);
        }
        else
        {
            printf("%ld,%s,%s,%d/%d/%d,%c,%d/%d/%d,%s,%d/%d/%d,%c,---\n",socio.dni,socio.apellido,socio.nombre,
                socio.fechaNacimiento.dia,socio.fechaNacimiento.mes,socio.fechaNacimiento.anio,socio.sexo,
                socio.fechaAfiliacion.dia,socio.fechaAfiliacion.mes,socio.fechaAfiliacion.anio,socio.categoria,
                socio.fechaUltimaCuotaPaga.dia,socio.fechaUltimaCuotaPaga.mes,socio.fechaUltimaCuotaPaga.anio,
                socio.estado);
        }

        fread(&socio,sizeof(T_Socio),1,pf);
    }

    fclose(pf);
    return 1;
}

