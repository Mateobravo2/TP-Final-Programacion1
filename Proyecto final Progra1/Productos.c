#include "Productos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

///ALTA PRODUCTO
void cargarStProducto(char archivoProducto[], Pila* economico)
{
    stProducto prod;
    int i = 0;
    FILE* archi = fopen(archivoProducto, "a+b");
    if(archi!=NULL)
    {
        char control='s';
        while(fread(&prod, sizeof(stProducto), 1, archi) > 0)
        {
            i++;
        }
        while(control == 's')
        {
            prod = cargaProducto(i+1);
            i++;
            if(prod.economico == 1)
            {
                apilar(economico, i);
            }
            fwrite(&prod, sizeof(stProducto), 1, archi);
            printf("desea seguir cargando datos? s/n\n");
            scanf(" %c", &control);
        }
        fclose(archi);
    }
}


stProducto cargaProducto(int i) // Le saqué el parámetro de stock erróneo
{
    stProducto aux;
    aux.id = i;

    printf("ingrese el nombre del producto: ");
    scanf(" %s", aux.nombre);
   /* fgets( aux.nombre, DIMTEXTO, stdin);
    aux.nombre[strcspn( aux.nombre, "\n")] = '\0';*/

    printf("ingrese el precio del producto: ");

    while (scanf("%f", &aux.precio) != 1 || aux.precio<=0)
    {
        printf("dato invalido. ingrese nuevamente: ");
        while(getchar() != '\n');
    }
    if(aux.precio <= 2000)
    {
        aux.economico = 1;
    }
    else
    {
        aux.economico = 0;
    }

    printf("ingrese la cantidad de productos: ");
    while (scanf("%i", &aux.stock) != 1 || aux.stock<=0)
    {
        printf("dato invalido. ingrese nuevamente: ");
        while(getchar() != '\n');
    }
    aux.activo=1;

    return aux;
}

///CONSULTA PRODUCTOS
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
    printf("_________________________\n");
    printf("id de producto %i\n", prod.id);
    printf("%s\n", prod.nombre);
    printf(" precio $%.2f\n", prod.precio);
    printf("unidades %i\n", prod.stock);
    printf("-------------------------\n");
}

void buscarProducto(char archivoProducto[])
{
    FILE* archi= fopen(archivoProducto, "r+b");
    if(archi!=NULL)
    {
        int controlP;
        do
        {
            printf("-------MENU-------\n");
            printf("\n");
            printf("seleccione por numero\n");
            printf("1. buscar producto por nombre\n");
            printf("2. buscar producto por id\n");
            printf("0. si desea salir\n");

            while (scanf("%i", &controlP) != 1)
           {
            printf("dato invalido. ingrese nuevamente:\n");
                while(getchar() != '\n');
            }
            system("cls");

            switch(controlP)
        {
        case 1:
            buscarPorNombre(archi);
                break;
            case 2:
                buscarPorId(archi);
                break;
            }
        }
        while(controlP==0);
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
        scanf(" %s", &nombreAux);
        system("cls");

        while(fread(&prod, sizeof(stProducto), 1, archi)>0 && banderaP==0)
        {
            if (strcmpi(nombreAux,prod.nombre) == 0 && prod.activo==1)
            {
                mostrarP(prod);
                printf("desea ingresar al menu del producto? s/n\n");
                scanf(" %c", &banderaNo);
                system("cls");

                if(banderaNo=='s')
                {
                    prod = menuProdElegido(prod);
                    fseek(archi, sizeof(stProducto)*(-1), SEEK_CUR);
                    fwrite(&prod, sizeof(stProducto),1, archi);
                    banderaP=1;
                }
                else
                {
                    banderaP=1;
                }
            }
        }
        if(banderaP==0)
        {
            printf("error el producto buscado no existe\n");
        }
        printf("desea buscar otro producto? s/n\n");
        scanf(" %c", &banderaN);
        system("cls");
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
        printf("ingrese el id del producto\n");

        while (scanf("%i", &idAux) != 1)
        {
            printf("dato invalido. ingrese nuevamente:\n");
            while(getchar() != '\n');
        }
        system("cls");
        while(fread(&prod, sizeof(stProducto), 1, archi)>0 && banderap==0 )
        {
            if (idAux==prod.id && prod.activo==1)
            {
                mostrarP(prod);

                printf("desea ingresar al menu del producto? s/n\n");
                scanf(" %c", &banderaP);
                system("cls");

                if(banderaP=='s')
                {
                    prod = menuProdElegido(prod);
                    fseek(archi, sizeof(stProducto)*(-1), SEEK_CUR);
                    fwrite(&prod, sizeof(stProducto),1, archi);
                    banderap=1;
                }
                else
                {
                    banderap=1;
                }
            }
        }
        if(banderap==0)
        {
            printf("error el producto buscado no existe\n");
        }
        printf("desea buscar otro producto? s/n\n");
        scanf(" %c", &banderaId);
        system("cls");
        fseek(archi, 0, SEEK_SET);
        banderap=0;
    }
}

//MODIFICACION Y BAJA



//MODIFICACION Y BAJA
stProducto menuProdElegido(stProducto prod)
{
    int opp;
    stProducto aux;
    do
    {
        printf("________MENU PRODUCTO %s________\n", prod.nombre);
        printf("|1|. MODIFICAR NOMBRE\n");
        printf("|2|. MODIFICAR PRECIO\n");
        printf("|3|. MODIFICAR STOCK\n");
        printf("|4|. ELIMINAR PRODUCTO\n");
        printf("|0|. SALIR\n");

        while (scanf("%i", &opp) != 1)
        {
            printf("Invalido. Intente de nuevo: ");
            getchar() != '\n';
        }

        system("cls");
        switch(opp)
        {
        case 1:
            while(getchar() != '\n');
            printf("escriba el nuevo nombre\n");
            fgets(prod.nombre, DIMTEXTO, stdin);
            prod.nombre[strcspn(prod.nombre, "\n")] = '\0';
            break;
        case 2:
            printf("que precio quiere seleccionar para %s\n", prod.nombre);
            while (scanf("%f", &aux.precio) != 1 || aux.precio <= 0)
            {
                printf("dato invalido. ingrese nuevamente:\n");
                while(getchar() != '\n');
            }
            if(aux.precio<=2000)
            {
                aux.economico=1;
            }
            else
            {
                aux.economico=0;
            }
            prod.precio= aux.precio;
            break;
        case 3:
            printf("cuantas unidades va querer en %s\n", prod.nombre);
            while (scanf("%i", &aux.stock) != 1 || aux.stock<=0 )
            {
                printf("dato invalido. ingrese nuevamente:\n");
                while(getchar() != '\n');
            }

            prod.stock= aux.stock;
            break;
        case 4:
            prod.activo=0;
            printf("el archivo a sido eliminado.\n");
            opp = 0;
            break;
        }
    }
    while(opp != 0);
    return prod;
}

//LISTADO ECONOMICO
void mostrarProductoEconomico(char archivoProducto[], Pila cant)
{
    stProducto prod;
    FILE* archi= fopen(archivoProducto, "rb");
    if(archi!=NULL)
    {
        printf("------PRODUCTOS ECONOMICOS------\n");
        while(!pilavacia(&cant))
        {
           fseek(archi, sizeof(stProducto)*desapilar(&cant), SEEK_SET);
           fseek(archi, sizeof(stProducto)*-1, SEEK_CUR);
           fread(&prod, sizeof(stProducto),1,archi);
           mostrarP(prod);
        }
        fclose(archi);
    }

}

