#include<utilitarias.h>
#include<string.h>
#include<varias.h>



/*

int baja (tAlumno * alu, FILE * arch, tArbolBinBusq* pa)
{
    tRegInd idx;

    idx.dni = alu->dni;

    if(!eliminarElemArbolBinBusq(pa,&idx,sizeof(tRegInd),cmpDni))
        return NO_EXISTE;

    fseek(arch,(idx.nro_reg)*(sizeof(tAlumno)),SEEK_SET);
    fread(alu,sizeof(tAlumno),1,arch);

    alu->estado = 'B';

    fseek(arch, -(long)(sizeof(tAlumno)),SEEK_CUR);
    fwrite(alu,sizeof(tAlumno),1,arch);


    fseek(arch,0,SEEK_SET);

    return TODO_OK;
}

int alta (tAlumno * alu, FILE * arch, tArbolBinBusq* pa)
{
    tRegInd idx;

    idx.dni = alu->dni;

    fseek(arch,0,SEEK_END);
    idx.nro_reg = (ftell(arch) / sizeof(tAlumno));

    if( insertarRecArbolBinBusq(pa,&idx,sizeof(tRegInd),cmpDni) == DUPLICADO)
        return DUPLICADO;

    fwrite(alu, sizeof(tAlumno),1,arch);

    fseek(arch,0,SEEK_SET);

    return TODO_OK;
}

int baja_ultimo(FILE * arch, tArbolBinBusq* pa)
{
    tAlumno alu;
    tRegInd idx;

    if(feof(arch))
        return NO_EXISTE;

    fseek(arch,-(long)(sizeof(tAlumno)),SEEK_END);
    fread(&alu,sizeof(tAlumno),1,arch);

    while(alu.estado != 'A')
    {
        fseek(arch,-2*(long)(sizeof(tAlumno)),SEEK_CUR);
        fread(&alu,sizeof(tAlumno),1,arch);
    }

    alu.estado = 'B';

    fseek(arch,-(long)(sizeof(tAlumno)),SEEK_CUR);
    fwrite(&alu,sizeof(tAlumno),1, arch);

    idx.dni = alu.dni;

    eliminarElemArbolBinBusq(pa,&idx,sizeof(tRegInd),cmpDni);

    fseek(arch,0,SEEK_SET);

    imprimirAlumno_res(&alu);
    return TODO_OK;
}

int agregar_materia(FILE * arch, tArbolBinBusq * pindice)
{
    tAlumno alu;
    tRegInd idx;
    float nuevaNota;

    printf("Ingrese numero de DNI: ");
    scanf("%d", &(idx).dni);

    if(!buscarElemArbolBinBusq(pindice,&idx,sizeof(tRegInd),cmpDni))
        return NO_EXISTE;

    fseek(arch,(idx.nro_reg)*sizeof(tAlumno),SEEK_SET);
    fread(&alu,sizeof(tAlumno),1,arch);

    imprimirAlumno_res(&alu);
    printf("\nIngrese la nueva nota:");
    scanf("%f", &nuevaNota);

    alu.promedio = (((alu.promedio * alu.cant_materias) + nuevaNota) / (alu.cant_materias + 1));

    fseek(arch,-(long)sizeof(tAlumno),SEEK_CUR);
    fwrite(&alu,sizeof(tAlumno),1,arch);

    fseek(arch, 0, SEEK_SET);

    imprimirAlumno_res(&alu);

    return TODO_OK;
}

int compactar_y_reindexar(FILE ** arch, tArbolBinBusq * pindice, const char * path)
{
    int i=0;
    tAlumno alu;

    //Eliminar alumnos en 'B' con temporal

    FILE* archTemp = fopen("../archivos/alumTemp.dat","wb");
    if(!archTemp)
        return ERROR_ARCHIVO;

    fread(&alu,sizeof(tAlumno),1,*arch);

    while(!feof(*arch))
    {
        if(alu.estado == 'A')
            fwrite(&alu,sizeof(tAlumno),1,archTemp);

        fread(&alu,sizeof(tAlumno),1,*arch);
    }

    fclose(archTemp);
    fclose(*arch);

    *arch = archTemp;

    remove(path);
    rename("../archivos/alumTemp.dat", path);

    //Rearmar arbol

    vaciarArbolBin(pindice);

    *arch = fopen(path,"r+b");
    if(!*arch)
        return ERROR_ARCHIVO;

    fread(&alu,sizeof(tAlumno),1,*arch);

    while(!feof(*arch))
    {
        tRegInd idx = {alu.dni, i};

        insertarRecArbolBinBusq(pindice,&idx,sizeof(tRegInd),cmpDni);

        fread(&alu,sizeof(tAlumno),1,*arch);
        i++;
    }

    fseek(*arch, 0, SEEK_SET);

    return TODO_OK;
}


int cmpDni(const void* a, const void* b)
{
    tRegInd* idx1 = (tRegInd*)a;
    tRegInd* idx2 = (tRegInd*)b;

    return idx1->dni - idx2->dni;
}

int cmpNReg(const void* a, const void* b)
{
    return ((tRegInd*)a)->nro_reg - ((tRegInd*)b)->nro_reg;
}


