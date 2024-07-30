#include "indice.h"



/* inicializa
 la estructura a índice vacío y almacena en la estructura de índice el tamaño de la clave genérica a
 utilizar y la función de comparación.*/
void ind_crear (t_indice* ind, size_t tam_clave, int (*cmp)(const void*, const void*))
{
    crearArbol(&ind->a);
    ind->tamClave=tam_clave;
    ind->cmp=cmp;
}

/* inserta en orden el registro
 reg_ind según la clave. (1)*/


int ind_insertar (t_indice* ind, void *clave, unsigned nro_reg)
{
    char *dato=(char *)malloc(ind->tamClave+sizeof(unsigned));
    memcpy(dato,clave,ind->tamClave);
    memcpy(dato+ind->tamClave,&nro_reg,sizeof(unsigned));

    if(insertarArbol(&ind->a,dato,ind->tamClave+sizeof(unsigned),ind->cmp)==1)
        return 1;
    else
        return 0;
}


/* elimina la entrada del índice
 correspondiente a la clave y devuelve en nro_reg el número de registro asociado. (1)*/ ///consultar por esto: devuelve en nro_reg el número de registro asociado

int ind_eliminar (t_indice* ind, void *clave, unsigned *nro_reg)
{
    char *dato=(char *)malloc(ind->tamClave+sizeof(unsigned));
    memcpy(dato,clave,ind->tamClave);

    if(eliminarDeArbol(&ind->a,dato,ind->tamClave+sizeof(unsigned),ind->cmp)==1)
    {
        memcpy(nro_reg,dato+ind->tamClave,sizeof(unsigned));
        return 1;
    }
    else
    {
        return 0;
    }
}

/*: Busca la clave recibida por
 parámetro y devuelve en nro_reg el número de registro asociado. (1)*/

int ind_buscar (const t_indice* ind, void *clave, unsigned *nro_reg)
{
    char *dato=(char *)malloc(ind->tamClave+sizeof(unsigned));
    memcpy(dato,clave,ind->tamClave);

    if(buscarElemArbol(&ind->a,dato,ind->tamClave+sizeof(unsigned),ind->cmp) == 1)
    {
        memcpy(nro_reg,dato+ind->tamClave,sizeof(unsigned));
        return 1;
    }
    else
    {
        return 0;
    }
}



 /*: Carga el índice a partir de un archivo binario
 ordenado (típicamente de extensión ‘.idx’), donde cada registro del archivo tiene la estructura
 definida, clave-nro_reg. (1)*/

int ind_cargar (t_indice* ind, const char* path)
{
    int veri;
    veri=cargarArchivoBinOrdenadoArbol(&ind->a,path,ind->tamClave+sizeof(unsigned)); // verificar
    if(veri!=TODO_BIEN)
        return SIN_MEM;
    return 1;
}


void ind_vaciar (t_indice* ind)
{
    vaciarArbol(&(ind->a));
} //: deja el índice en su estado de vacío.


int ind_recorrer (const t_indice* ind, void (*accion)(const void *, unsigned, void *), void* param)
{
    recorrerEnOrdenSimpleArbol(&ind->a, param, accion);
    return 1;
}


/*: Graba un archivo binario ordenado
 (típicamente de extensión ‘.idx’) con el contenido del índice con la estructura clave-nro_reg. (1)*/

int ind_grabar (const t_indice* ind, const char* path)
{
    int veri=grabarEnArchivoOrdenadoArbolBin(&ind->a,path);
    if(veri!=TODO_BIEN)
        return SIN_MEM;
    return 1;
}
