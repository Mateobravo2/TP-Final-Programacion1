#include "Clientes.h"
#include <string.h>
#include "Productos.h"
#include <stdlib.h>

//ALTA CLIENTE
stCliente crearCliente(int id)
{
    stCliente aux;
    printf("_______________________________\n");
    aux.id = id;
    printf("Ingrese el DNI del cliente: ");
    scanf("%i", &aux.dni);
    while(getchar() != '\n');
    printf(" Ingrese el nombre del cliente: ");
    fgets(aux.nombre, DIMTEXTO, stdin);
    aux.nombre[strcspn(aux.nombre, "\n")] = '\0';
    aux.activo = 1;
    printf("-------------------------------\n");
    return aux;
}

void altaClientesArchivo(char nombre[])
{
    int i = 0;
    stCliente aux;
    FILE *archi = fopen(nombre, "a+b");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            i++;
        }
        aux = crearCliente(i+1);
        if(verificacionCliente(archi, aux) == 1)
        {
            printf("\n- - - ESTE CLIENTE YA EXISTE - - -\n");
        }
        else
        {
            fwrite(&aux, sizeof(stCliente), 1, archi);
            printf("\nCliente guardado correctamente.\n");
            mostrarCliente(aux);
        }
        fclose(archi);
    }
}

int verificacionCliente(FILE *archi, stCliente clienteNuevo)
{
    stCliente aux;
    int existe = 0;
    fseek(archi, 0, SEEK_SET);
    while(existe == 0 && fread(&aux, sizeof(stCliente), 1, archi) > 0)
    {
        if(aux.dni == clienteNuevo.dni && aux.activo == 1)
        {
            existe = 1;
        }
    }
    return existe;
}

//BAJA DE CLIENTE
void bajaDeClienteDeArchivo(char nombre[], int id)
{
    int encontrado = 0;
    stCliente aux;
    FILE *archi = fopen(nombre, "r+b");
    if(archi != NULL)
    {
        while(encontrado == 0 && fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            if(aux.id == id && aux.activo == 1)
            {
                aux.activo = 0;
                fseek(archi, -sizeof(stCliente), SEEK_CUR);
                fwrite(&aux, sizeof(stCliente), 1, archi);
                encontrado = 1;
                printf("\nCliente dado de baja correctamente.\n");
                mostrarCliente(aux);
            }
        }
        if(encontrado == 0)
        {
            printf("\nERROR: Cliente no encontrado o inactivo.\n");
        }
        fclose(archi);
    }
}

//MODIFICACION DE CLIENTE
void modificarClienteDeArchivo(char nombre[], int id)
{
    FILE *archi = fopen(nombre, "r+b");
    if(archi != NULL)
    {
        modificarCliente(archi, id);
        fclose(archi);
    }
}

stCliente modificarCliente(FILE *archi, int id)
{
    int encontrado = 0;
    char op = 'n';
    stCliente aux;
    while(encontrado == 0 && fread(&aux, sizeof(stCliente), 1, archi) > 0)
    {
        if(aux.id == id && aux.activo == 1)
        {
            encontrado = 1;
            printf("\n---Modificando cliente ID: %i\n", aux.id);
            printf("Quiere modificar el DNI? (s/n): ");
            scanf(" %c", &op);
            if(op == 's' || op == 'S')
            {
                printf("\n Ingrese el nuevo DNI: ");
                scanf("%i", &aux.dni);
            }
            printf("\nQuiere modificar el nombre? (s/n): ");
            scanf(" %c", &op);
            if(op == 's' || op == 'S')
            {
                while (getchar() != '\n');
                printf("\n Ingrese el nuevo nombre: ");
                fgets(aux.nombre, DIMTEXTO, stdin);
                aux.nombre[strcspn(aux.nombre, "\n")] = '\0';
            }
            printf("\nQuiere modificar el carrito? (s/n): ");
            scanf(" %c", &op);
            if(op == 's' || op == 'S')
            {
                printf("\n Ingrese el nuevo carrito: ");
            }
            fseek(archi, -sizeof(stCliente), SEEK_CUR);
            fwrite(&aux, sizeof(stCliente), 1, archi);
            mostrarCliente(aux);
        }
    }
    if(encontrado == 0)
    {
        printf("\nERROR: Cliente no encontrado o inactivo.\n");
    }
    return aux;
}

//CONSULTA DE CLIENTE
void mostrarCliente(stCliente cliente)
{
    printf("\x1b[34mCLIENTE ID |%i|:\x1b[0m\n\n", cliente.id);
    printf("____________________________\n");
    printf(" DNI %i\n", cliente.dni);
    printf(" NOMBRE: %s\n", cliente.nombre);
    if(cliente.activo == 1)
    {
        printf(" ESTADO: ACTIVO\n");
    }
    else
    {
        printf(" ESTADO: INACTIVO\n");
    }
    printf("-----------------------------\n");
}

void mostrarArchivoClientes(char nombre[])
{
    stCliente aux;
    FILE *archi = fopen(nombre, "rb");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            mostrarCliente(aux);
        }
        fclose(archi);
    }
}


void mostrarClientesArchivoID(char nombre[], int id)
{
    int encontrado = 0;
    stCliente aux;
    FILE *archi = fopen(nombre, "rb");
    if(archi != NULL)
    {
        while(encontrado == 0 && fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            if(aux.id == id && aux.activo == 1)
            {
                mostrarCliente(aux);
                encontrado = 1;
            }
        }
        if(encontrado == 0)
        {
            printf("\nERROR: Cliente no encontrado o inactivo.\n");
        }
        fclose(archi);
    }
}

void hacerVenta(char nombre[], char archivoProducto[], int id)
{

    stCliente comprador;
    stCliente aux;

    int bandera=0;

    FILE* archio= fopen(nombre, "r+b");
    FILE* archi= fopen(archivoProducto, "r+b");
    if(archi!=NULL || archio!=NULL)
    {
        printf("ingrese su numero de dni:\n");
        while (scanf("%i", &aux.dni) != 1)
        {
            printf("dato invalido. ingrese nuevamente:\n");
            while(getchar() != '\n');
        }

        while(fread(&comprador, sizeof(stCliente),1, archio) && bandera==0)
        {
            if(aux.dni == comprador.dni)
            {
                mostrarProducto(archivoProducto);
                menuVenta(aux, archivoProducto);
                bandera=1;
            }
        }
        fclose(archi);
        fclose(archio);
    }
}

void menuVenta(stCliente comprador, char archivoProducto[])
{
    int op;
    stProducto prod;
    char pro[20];
    int cant;
    int bandera=0;
    char band='s';
    FILE* archi= fopen(archivoProducto, "r+b");
    if(archi!=NULL)
    {
        while(band=='s')
        {
            while(getchar() != '\n');
            printf("QUE DESEA COMPRAR?\n");
            fgets(pro, DIMTEXTO, stdin);
            pro[strcspn(pro, "\n")] = '\0';
            while(fread(&prod, sizeof(stProducto),1, archi) && bandera==0)
            {
                if(strcmpi(pro, prod.nombre)==0)
                {
                    printf("CUANTOS DESEA COMPRAR?\n");
                    while (scanf("%i", &cant) != 1)
                    {
                        printf("Dato invalido. Ingrese nuevamente:\n");
                        while(getchar() != '\n');
                    }

                    if(cant<=prod.stock)
                    {
                        fseek(archi, sizeof(stProducto)*(-1), SEEK_CUR);
                        prod.stock-=cant;
                        fwrite(&prod, sizeof(stProducto),1, archi);
                        printf("Venta realizada correctamente, usted ha comprado %i %s", cant, pro);
                        bandera=1;
                    }
                    else
                    {
                        printf("ERROR: no existe esa cantidad de productos\n");
                    }
                }
                else
                {
                    printf("No existe ese producto\n");
                }
            }
            printf("Desea hacer otra compra? s/n\n");
            scanf(" %c", &band);
            fseek(archi, 0, SEEK_SET);
            system("cls");
            bandera=0;
        }
        fclose(archi);
    }

}

//LISTADOS DE CLIENTE
void listarClientesSeleccionAlfabetica(char nombre[])
{
    stCliente lista[100];
    int validos = pasarArchivoAArreglo(nombre, lista, 100);
    int posMenor;
    stCliente temp;
    for(int i = 0; i < validos - 1; i++)
    {
        posMenor = i;
        for(int j = i + 1; j < validos; j++)
        {
            if(strcasecmp(lista[j].nombre, lista[posMenor].nombre) < 0)
            {
                posMenor = j;
            }
        }
        temp = lista[posMenor];
        lista[posMenor] = lista[i];
        lista[i] = temp;
    }
    printf("\n--- LISTADO ALFABETICO ---\n");
    for(int i = 0; i < validos; i++)
    {
        mostrarCliente(lista[i]);
    }
}

int pasarArchivoAArreglo(char nombre[], stCliente arreglo[], int dim)
{
    stCliente aux;
    FILE *archi = fopen(nombre, "rb");
    int i = 0;
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stCliente), 1, archi) > 0 && i < dim)
        {
            if(aux.activo == 1)
            {
                arreglo[i] = aux;
                i++;
            }
        }
        fclose(archi);
    }
    return i;
}

void listarClientesInsercionDni(char nombre[])
{
    stCliente lista[100];
    int validos = pasarArchivoAArreglo(nombre, lista, 100);
    int j;
    stCliente aux;
    for(int i = 1; i < validos; i++)
    {
        aux = lista[i];
        j = i - 1;
        while(j >= 0 && lista[j].dni > aux.dni)
        {
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = aux;
    }
    printf("\n--- LISTADO POR DNI ---\n");
    for(int i = 0; i < validos; i++)
    {
        mostrarCliente(lista[i]);
    }
}
