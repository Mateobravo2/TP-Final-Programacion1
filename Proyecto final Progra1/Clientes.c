#include "Clientes.h"
#include <string.h>

//ALTA CLIENTE
stCliente crearCliente(int id)
{
    stCliente aux;
    printf("_______________________________\n");
    aux.id = id;
    printf("Ingrese el DNI del cliente: \n");
    scanf("%i", &aux.dni);
    printf("Ingrese el nombre del cliente: \n");
    scanf(" %s", &aux.nombre);
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
        if(fread(&aux, sizeof(stCliente), 1, archi) > 0)
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
            fseek(archi, -sizeof(stCliente), SEEK_CUR);
            fwrite(&aux, sizeof(stCliente), 1, archi);
            printf("\nCliente guardado correctamente.\n");
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
            }
        }
        if(encontrado == 0)
        {
            printf("\nERROR: Cliente no encontrado.\n");
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
                printf("\n---Modificando cliente ID: &i\n", aux.id);
                printf("Quiere modificar el DNI? (s/n): ");
                if(op == 's' || op == 'S')
                {
                    printf("\nIngrese el nuevo DNI: ");
                    scanf("%i", &aux.dni);
                }
                printf("Quiere modificar el nombre? (s/n): ");
                if(op == 's' || op == 'S')
                {
                    printf("\nIngrese el nuevo nombre: ");
                    scanf(" %s", &aux.nombre);
                }
                printf("Quiere modificar el carrito? (s/n): ");
                if(op == 's' || op == 'S')
                {
                    printf("\nIngrese el nuevo carrito: ");
                    //LLAMAR FUNCION DE CREAR CARRITO !!!!
                }
                fseek(archi, -sizeof(stCliente), SEEK_CUR);
                fwrite(&aux, sizeof(stCliente), 1, archi);
            }
        }
        if(encontrado == 0)
        {
            printf("\nERROR: Cliente no encontrado.\n");
        }
    return aux;
}

//CONSULTA DE CLIENTE
void mostrarCliente(stCliente cliente)
{
    printf("\x1b[34mCLIENTE:\x1b[0m\n\n");
    printf("____________________________\n");
    printf("| ID: %i |\n", cliente.id);
    printf("| DNI %i |\n", cliente.dni);
    printf("| NOMBRE: %s\n", cliente.nombre);
    //LLAMAR A FUNCION DE MOSTRAR PRODUCTO
    printf("-----------------------------\n");
}

void mostrarClientesArchivo(char nombre[], int id)
{
    int encontrado = 0;
    stCliente aux;
    FILE *archi = fopen(nombre, "rb");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            if(aux.id == id && aux.activo == 1)
            {
                mostrarCliente(aux);
                encontrado = 1;
            }
        }
        if(encontrado = 0)
        {
            printf("\nERROR: Cliente no encontrado.\n");
        }
        fclose(archi);
    }
}

//LISTADOS DE CLIENTE
void listarClientesAlfabetico(char nombre[])
{
    FILE *archi = fopen(nombre, "rb");
    if(archi != NULL)
    {

        fclose(archi);
    }
}
