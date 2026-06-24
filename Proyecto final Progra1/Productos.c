#include "Productos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

///ALTA PRODUCTO
void cargarStProducto(char archivoProducto[])
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
            fwrite(&prod, sizeof(stProducto), 1, archi);
            printf("Desea seguir cargando datos? s/n\n");
            scanf(" %c", &control);
        }
        fclose(archi);
    }
}

stProducto cargaProducto(int i) // Le saqué el parámetro de stock erróneo
{
    stProducto aux;
    aux.id = i;
    while(getchar() != '\n');
    printf("Ingrese el nombre del producto: ");
    fgets( aux.nombre, DIMTEXTO, stdin);
    aux.nombre[strcspn( aux.nombre, "\n")] = '\0';
    printf("Ingrese el precio del producto: ");
    while (scanf("%f", &aux.precio) != 1 || aux.precio<=0)
    {
        printf("Dato invalido. Ingrese nuevamente: ");
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

    printf("Ingrese la cantidad de productos: ");
    while (scanf("%i", &aux.stock) != 1 || aux.stock<=0)
    {
        printf("Dato invalido. ingrese nuevamente: ");
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
    printf("ID de producto %i\n", prod.id);
    printf("%s\n", prod.nombre);
    printf("Precio $%.2f\n", prod.precio);
    printf("Unidades %i\n", prod.stock);
    printf("-------------------------\n");
}

void buscarPorNombre(char archivoProducto[])
{
    stProducto prod;
    int banderaP=0;
    char nombreAux[20];
    char banderaN='s';
    char banderaNo='s';
    FILE *archi = fopen(archivoProducto, "rb");
    if(archi != NULL)
    {
         while(banderaN=='s')
        {
            while(getchar() != '\n');
            printf("Ingrese el nombre del producto\n");
            fgets(prod.nombre, DIMTEXTO, stdin);
            prod.nombre[strcspn(prod.nombre, "\n")] = '\0';
            system("cls");
            while(fread(&prod, sizeof(stProducto), 1, archi)>0 && banderaP==0)
            {
                if (strcmpi(nombreAux,prod.nombre) == 0 && prod.activo==1)
                {
                    mostrarP(prod);
                    printf("Desea ingresar al menu del producto? s/n\n");
                    scanf(" %c", &banderaNo);
                    system("cls");
                    if(banderaNo=='s')
                    {
                        prod = menuProdElegido(prod);
                        fseek(archi, sizeof(stProducto)*(-1), SEEK_CUR);
                        fwrite(&prod, sizeof(stProducto),1, archi);

                        fflush(archi);
                        banderaP=1;
                        break;
                    }
                    else
                    {
                        banderaP=1;
                    }
                }
            }
            if(banderaP==0)
            {
                printf("ERROR: el producto buscado no existe\n");
            }
            printf("Desea buscar otro producto? s/n\n");
            scanf(" %c", &banderaN);
            system("cls");
            fseek(archi, 0, SEEK_SET);
            banderaP=0;
        }
        fclose(archi);
    }
}

void buscarPorId(char archivoProducto[])
{
    stProducto prod;
    char banderaP = 's';
    int idAux;
    int banderap=0;
    char banderaId='s';
    FILE *archi = fopen(archivoProducto, "r+b");
    if(archi != NULL)
    {
        while(banderaId == 's')
        {
            printf("Ingrese el id del producto\n");

            while (scanf("%i", &idAux) != 1)
            {
                printf("Dato invalido. ingrese nuevamente:\n");
                while(getchar() != '\n');
            }
            system("cls");
            while(fread(&prod, sizeof(stProducto), 1, archi)>0 && banderap==0 )
            {
                if (idAux==prod.id && prod.activo==1)
                {
                    mostrarP(prod);

                    printf("Desea ingresar al menu del producto? s/n\n");
                    scanf(" %c", &banderaP);
                    system("cls");

                    if(banderaP=='s')
                    {
                        prod = menuProdElegido(prod);
                        fseek(archi, sizeof(stProducto)*(-1), SEEK_CUR);
                        fwrite(&prod, sizeof(stProducto),1, archi);
                        fflush(archi);
                        banderap = 1;
                    }
                    else
                    {
                        banderap=1;
                    }
                }
            }
            if(banderap==0)
            {
                printf("ERROR: el producto buscado no existe\n");
            }
            printf("Desea buscar otro producto? s/n\n");
            scanf(" %c", &banderaId);
            system("cls");
            fseek(archi, 0, SEEK_SET);
            banderap = 0;
        }
        fclose(archi);
    }
}

//MODIFICACION Y BAJA
stProducto menuProdElegido(stProducto prod)
{
    int opp;
    do
    {
        printf("________MENU PRODUCTO %s________\n", prod.nombre);
        printf("__________________________\n");
        printf("| [1] MODIFICAR NOMBRE   |\n");
        printf("| [2] MODIFICAR PRECIO   |\n");
        printf("| [3] MODIFICAR STOCK    |\n");
        printf("| [4] ELIMINAR PRODUCTO  |\n");
        printf("| [0] SALIR              |\n");
        printf("--------------------------\n");
        while (scanf("%i", &opp) != 1)
        {
            while(getchar() != '\n');
            opp = -1;
        }
        system("cls");
        switch(opp)
        {
        case 1:
            while(getchar() != '\n');
            printf("Escriba el nuevo nombre\n");
            fgets(prod.nombre, DIMTEXTO, stdin);
            prod.nombre[strcspn(prod.nombre, "\n")] = '\0';
            break;

        case 2:
            printf("Que precio quiere seleccionar para %s\n", prod.nombre);
            while (scanf("%f", &prod.precio) != 1 || prod.precio <= 0)
            {
                printf("Dato invalido. ingrese nuevamente:\n");
                while(getchar() != '\n');
            }
            if(prod.precio<=2000)
            {
                prod.economico=1;
            }
            else
            {
                prod.economico=0;
            }
            break;

        case 3:
            printf("Cuantas unidades va querer de %s\n", prod.nombre);
            while (scanf("%i", &prod.stock) != 1 || prod.stock<=0 )
            {
                printf("Dato invalido. ingrese nuevamente:\n");
                while(getchar() != '\n');
            }
            break;

        case 4:
            prod.activo = 0;
            printf("El elemento | %i | a sido eliminado.\n", prod.id);
            opp = 0;
            break;
        case 0:
            printf(" --- VOLVIENDO ---");
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
    int i=1;
    FILE* archi= fopen(archivoProducto, "rb");
    if(archi!=NULL)
    {
        while(fread(&prod, sizeof(stProducto),1,archi)>0)
        {
            if(prod.economico == 1 && prod.activo==1)
            {
                apilar(&cant, i);
            }
            i++;
        }
        fseek(archi, 0, SEEK_SET);
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

