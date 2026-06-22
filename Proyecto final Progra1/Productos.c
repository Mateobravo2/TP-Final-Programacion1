#include "Productos.h"
#include <string.h>
#include <stdio.h>

//ALTA PRODUCTO
void cargarStProducto(char archivoProducto[])
{
    stProducto prod;
    FILE* archi = fopen(archivoProducto, "r+b");
    if(archi!=NULL)
    {
        int i=0;
        char control='s';
        while(fread(&prod, sizeof(stProducto), 1, archi) > 0)
        {
            i++;
        }
        while(control =='s')
        {
            prod= cargaProducto(i+1, i);
            fwrite(&prod, sizeof(stProducto), 1, archi);
            printf("desea seguir cargando datos? s/n\n");
            scanf(" %c", &control);
        }
    }
}

stProducto cargaProducto(int i, int stock)
{
    stProducto aux;
    aux.id = i;
    printf("ingrese el nombre del producto\n");
    fgets(aux.nombre, DIMTEXTO, stdin);
    aux.nombre[strcspn(aux.nombre, "\n")] = '\0';
    printf("ingrese el precio del producto\n");
    scanf(" %f", &aux.precio);
    if(aux.precio < 2000)
    {
        aux.economico = 1;
    }
    else
    {
        aux.economico = 0;
    }
    aux.stock = stock;
    aux.activo = 1;
    return aux;
}

//CONSULTA PRODUCTOS
void mostrarProducto(char archivoProducto[])
{
    stProducto prod;
    FILE* archi= fopen(archivoProducto, "rb");
    if(archi!=NULL)
    {
        while(fread(&prod, sizeof(stProducto), 1, archi)>0)
        {
            if(prod.activo==1)
            {
                mostrarP(prod);
            }
        }
        fclose(archi);
    }
}

void mostrarP(stProducto prod)
{
    printf("\n");
    printf("PRODUCTO ID: [%i] %i\n", prod.id);
    printf("_________________________\n");
    printf("NOMBRE: %s\n", prod.nombre);
    printf("PERCIO: $%.2f\n", prod.precio);
    printf("UNIDADES: %i\n", prod.stock);
    printf("-------------------------\n");
}


void buscarProducto(char archivoProducto[])
{
    FILE* archi= fopen(archivoProducto, "r+b");
    if(archi!=NULL)
    {
        int controlP=0;
        do
        {
            printf("-------MENU-------\n");
            printf("\n");
            printf("seleccione por numero\n");
            printf("1. buscar producto por nombre\n");
            printf("2. buscar producto por id\n");
            printf("0. si desea salir\n");
            scanf(" %i", &controlP);
            switch(controlP)
            {
            case 1:
                buscarPorNombre(archi);
                break;
            case 2:
                buscarPorId(archi);
                break;
            }
        }while(controlP != 0);
        fclose(archi);
    }
}


void buscarPorNombre(FILE* archi)
{
    stProducto prod;
    int banderaP=0;
    char nombreAux[20];
    char banderaN='s';
    char banderaNo='s';
    while(banderaN=='s')
    {
        printf("ingrese el nombre del producto\n");
        fgets(prod.nombre, DIMTEXTO, stdin);
        prod.nombre[strcspn(prod.nombre, "\n")] = '\0';

        while(fread(&prod, sizeof(stProducto), 1, archi)>0 && banderaP==0)
        {
            if (strcmpi(nombreAux, prod.nombre) == 0 && prod.activo==1)
            {
                mostrarP(prod);
                printf("desea ingresar al menu del producto? s/n\n");
                scanf(" %c", &banderaNo);

                if(banderaNo=='s')
                {
                    prod = menuProdElegido(prod);
                    fseek(archi, sizeof(stProducto)*(-1), SEEK_CUR);
                    fwrite(&prod, sizeof(stProducto),1, archi);
                    banderaP = 1;
                }
                else
                {
                    banderaP = 1;
                }
            }
        }
        if(banderaP==0)
        {
            printf("ERROR: el producto buscado no existe\n");
        }
        printf("Desea buscar otro producto? s/n\n");
        scanf(" %c", &banderaN);
        fseek(archi, 0, SEEK_SET);
        banderaP=0;
    }
}

void buscarPorId(FILE* archi)
{
    stProducto prod;
    char banderaP = 's';
    int idAux;
    int banderap=0;
    char banderaId='s';
    while(banderaId=='s')
    {
        printf("Ingrese el id del producto\n");
        scanf("%i", &idAux);
        while(fread(&prod, sizeof(stProducto), 1, archi)>0 && banderap==0 )
        {
            if (idAux == prod.id && prod.activo == 1)
            {
                mostrarP(prod);

                printf("Desea ingresar al menu del producto? s/n\n");
                scanf(" %c", &banderaP);
                if(banderaP == 's')
                {
                    prod = menuProdElegido(prod);
                    fseek(archi, sizeof(stProducto)*(-1), SEEK_CUR);
                    fwrite(&prod, sizeof(stProducto),1, archi);
                    banderap = 1;
                }
                else
                {
                    banderap = 1;
                }
            }
        }
        if(banderap == 0)
        {
            printf("ERROR: el producto buscado no existe\n");
        }
        printf("Desea buscar otro producto? s/n\n");
        scanf(" %c", &banderaId);
        fseek(archi, 0, SEEK_SET);
        banderap = 0;
    }
}
    //MODIFICACION Y BAJA

stProducto menuProdElegido(stProducto prod)
{
    int opp = 0;
    stProducto aux;
    do
    {
        printf("------MENU PRODUCTO %s-----\n", prod.nombre);
        printf("1. modificar nombre\n");
        printf("2. modificar precio\n");
        printf("3. modificar stock\n");
        printf("4. eliminar producto\n");
        printf("0. salir\n");
        scanf("%i", &opp);
        switch(opp)
        {
        case 1:
            printf("Escriba el nuevo nombre\n");
            fgets(aux.nombre, DIMTEXTO, stdin);
            aux.nombre[strcspn(aux.nombre, "\n")] = '\0';
            break;
        case 2:
            printf("Que precio quiere seleccionar para %s\n", prod.nombre);
            scanf("%f", &aux.precio);
            while(aux.precio < 0)
            {
                printf("ERROR: el precio debe ser de 0 o mas\n");
                scanf("%f", &aux.precio);
            }
            if(aux.precio<=2000)
            {
                aux.economico=1;
            }
            else
            {
                aux.economico=0;
            }
            prod.precio = aux.precio;
            break;
        case 3:
            printf("Cuantas unidades va querer en %s\n", prod.nombre);
            scanf("%i", &aux.stock);
             while(aux.stock < 0)
            {
                printf("ERROR: el stock debe ser de 0 o mas\n");
                scanf("%i", &aux.stock);
            }
            prod.stock = aux.stock;
            break;
        case 4:
            prod.activo=0;
            printf("El producto ha sido eliminado.\n");
            break;
        }
    }while(opp != 0);
    return prod;
}

//LISTADO ECONOMICO
void mostrarProductoEconomico(char archivoProducto[])
{
    stProducto prod;
    FILE* archi= fopen(archivoProducto, "rb");
    if(archi!=NULL)
    {
        printf("------PRODUCTOS ECONOMICOS------\n");
        while(fread(&prod, sizeof(stProducto), 1, archi)>0)
        {
            if(prod.economico == 1 && prod.activo == 1)
            {
                mostrarP(prod);
            }
        }
        fclose(archi);
    }
}
