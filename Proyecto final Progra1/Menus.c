#include "Menus.h"
#include "Clientes.h"
#include "Empleados.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define DIMTEXTO 30

void menuPrincipal()
{
    int op;
    do
    {
        printf("Ingrese una opcion:\n");
        printf("_________________\n");
        printf("|\x1b[34m[1] CLIENTE\x1b[0m    |\n");
        printf("|\x1b[33m[2] EMPLEADO\x1b[0m   |\n");
        printf("|\x1b[32m[3] PRODUCTO\x1b[0m   |\n");
        printf("|\x1b[31m[0] SALIR\x1b[0m      |\n");
        printf("-----------------\n");
        if (scanf("%i", &op) != 1)
        {
            while (getchar() != '\n');
            op = -1;
        }
        system("cls");
        switch(op)
        {
        default:
            printf("~ ~ ~ INGRESE UNA OPCION VALIDA ~ ~ ~\n");
            system("pause");
            system("cls");
            break;
        case 1:
            system("cls");
            barraCarga();
            menuClientes();
            break;
        case 2:
            system("cls");
            barraCarga();
            menuEmpleado();
            break;
        case 3:
            system("cls");
            barraCarga();
            menuProducto();
            break;
        case 0:
            printf("- - - FINALIZANDO EL PROGRAMA - - -\n");
            break;
        }
    }
    while(op != 0);
}

void barraCarga()
{
    char cian[] = "\x1b[36m";
    char verde[] = "\x1b[32m";
    char reset[] = "\x1b[0m";
    printf("\n\n\n\n\n");
    printf("                                    %sCargando sistema...%s\n", cian, reset);
    printf("                                    [");
    for (int i = 0; i < 25; i++)
    {
        printf("%s%c%s", verde, 219,reset);
        Sleep(80);
    }
    printf("] 100%%\n");
    Sleep(500);
    system("cls");
}

void menuClientes()
{
    int op, id;
    char nombre[DIMTEXTO] = "clientes.bin";
    do
    {
        printf("\x1b[34mCLIENTE\x1b[0m\n");
        printf("Ingrese la accion a realizar:\n");
        printf("_____________________________________\n");
        printf("|[1] ALTA DE CLIENTE                |\n");
        printf("|[2] BAJA DE CLIENTE                |\n");
        printf("|[3] MODIFICAR CLIENTE              |\n");
        printf("|[4] MOSTRAR TODOS LOS CLIENTES     |\n");
        printf("|[5] MOSTRAR CLIENTE POR ID         |\n");
        printf("|[6] MOSTRAR CLIENTE A-Z            |\n");
        printf("|[7] MOSTRAR CLIENTE ORDEN POR DNI  |\n");
        printf("|\x1b[31m[0]          SALIR\x1b[0m                 |\n");
        printf("-------------------------------------\n");
        if (scanf("%i", &op) != 1)
        {
            while (getchar() != '\n');
            op = -1;
        }
        system("cls");
        switch(op)
        {
        default:
            printf("~ ~ ~ INGRESE UNA OPCION VALIDA ~ ~ ~\n");
            system("pause");
            system("cls");
            break;
        case 0:
            printf("- - - VOLVIENDO AL MENU PRINCIPAL - - -");
            barraCarga();
            break;
        case 1:
            altaClientesArchivo(nombre);
            system("pause");
            system("cls");
            break;
        case 2:
            printf("Ingrese el ID del cliente: ");
            if (scanf("%i", &id) != 1)
            {
                printf("\nERROR: Ingrese un valor valido.\n");
                while (getchar() != '\n');
                op = -1;
                system("pause");
                system("cls");
            }
            bajaDeClienteDeArchivo(nombre, id);
            break;
        case 3:
            printf("Ingrese el ID del cliente: ");
            if (scanf("%i", &id) != 1)
            {
                printf("\nERROR: Ingrese un valor valido.\n");
                while (getchar() != '\n');
                op = -1;
            }
            modificarClienteDeArchivo(nombre, id);
            system("pause");
            system("cls");
            break;
        case 4:
            mostrarArchivoClientes(nombre);
            system("pause");
            system("cls");
            break;
        case 5:
            printf("Ingrese el ID del cliente: ");
            if (scanf("%i", &id) != 1)
            {
                printf("\nERROR: Ingrese un valor valido.\n");
                while (getchar() != '\n');
                op = -1;
            }
            mostrarClientesArchivoID(nombre, id);
            system("pause");
            system("cls");
            break;
        case 6:
            listarClientesSeleccionAlfabetica(nombre);
            system("pause");
            system("cls");
            break;
        case 7:
            listarClientesInsercionDni(nombre);
            system("pause");
            system("cls");
            break;
        }
    }
    while(op != 0);
}

void menuEmpleado()
{
    int op, id;
    char nombreArchivo[DIMTEXTO] = "empleados.bin";
    do
    {
        printf("_____________________________________\n");
        printf("|[1] ALTA DE EMPLEADO               |\n");
        printf("|[2] BAJA DE EMPLEADO               |\n");
        printf("|[3] MODIFICAR EMPLEADO             |\n");
        printf("|[4] MOSTRAR TODOS LOS EMPLEADO     |\n");
        printf("|[5] MOSTRAR EMPLEADO POR ID        |\n");
        printf("|[6] MOSTRAR EMPLEADO A-Z           |\n");
        printf("|[7] MOSTRAR EMPLEADO ORDEN POR DNI |\n");
        printf("|\x1b[31m[0]          SALIR\x1b[0m                 |\n");
        printf("-------------------------------------\n");
        if (scanf("%i", &op) != 1)
        {
            while (getchar() != '\n');
            op = -1;
        }
        system("cls");
        switch(op)
        {
        case 1:
            altaEmpleado(nombreArchivo);
            system("pause");
            system("cls");
            break;
        case 2:
            printf("Ingrese la ID del empleado: ");
            if (scanf("%i", &id) != 1)
            {
                while (getchar() != '\n');
                op = -1;
                system("pause");
                system("cls");
            }
            bajaEmpleadoArchivo(nombreArchivo, id);
            break;
        case 3:
            printf("Ingrese la ID del empleado: ");
            if (scanf("%i", &id) != 1)
            {
                while (getchar() != '\n');
                op = -1;
                system("pause");
                system("cls");
            }
            modificarEmpleadoArchivo(nombreArchivo, id);
            break;
        case 4:
            mostrarArchivoEmpleado(nombreArchivo);
            system("pause");
            system("cls");
            break;
        case 5:
            printf("Ingrese la ID del empleado: ");
            if (scanf("%i", &id) != 1)
            {
                while (getchar() != '\n');
                op = -1;
                system("pause");
                system("cls");
            }
            mostrarEmpleadosArchivoID(nombreArchivo, id);
            break;
        case 6:
            listarEmpleadosSeleccionAlfabetica(nombreArchivo);
            system("pause");
            system("cls");
            break;
        case 7:
            listarEmpleadosInsercionDni(nombreArchivo);
            system("pause");
            system("cls");
            break;
        case 0:
            printf("- - - VOLVIENDO AL MENU PRINCIPAL - - -");
            barraCarga();
            break;
        default:
            printf("~ ~ ~ INGRESE UNA OPCION VALIDA ~ ~ ~\n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(op != 0);
}

void menuProducto()
{
    char archivoProducto[]="producto.bin";
    int controlP=0;
        do
        {
            printf("------MENU PRODUCTO------\n");
            printf("1. cargar producto\n");
            printf("2. buscar producto\n");
            printf("3. mostrar producto\n");
            printf("4. mostrar productos economicos\n");
            printf("0. salir\n");

            scanf(" %i", &controlP);

            switch(controlP)
            {
            case 1:
                cargarStProducto(archivoProducto);
                break;

            case 2:
                buscarProducto(archivoProducto);
                break;

            case 3:
                mostrarProducto(archivoProducto);
                break;

            case 4:
                mostrarProductoEconomico(archivoProducto);
                break;

            case 0:
                printf("FIN DE LA EJECUCION...\n");
                break;
            }

        }
        while(controlP != 0);
}
