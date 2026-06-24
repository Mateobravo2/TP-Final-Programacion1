#include "Menus.h"
#include "Clientes.h"
#include "Empleados.h"
#include "Productos.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "pila.h"

#define DIMTEXTO 30

void menuPrincipal()
{
    int op;
    int i=0;
    do
    {
        printf("Ingrese una opcion:\n");
        printf("___________________\n");
        printf("| \x1b[34m[1] CLIENTES\x1b[0m    |\n");
        printf("| \x1b[33m[2] EMPLEADOS\x1b[0m   |\n");
        printf("| \x1b[32m[3] PRODUCTOS\x1b[0m   |\n");
        printf("| \x1b[31m[0] SALIR\x1b[0m       |\n");
        printf("-------------------\n");
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

    }while(op != 0);
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
        printf("\x1b[34mCLIENTES\x1b[0m\n");
        printf("Ingrese la accion a realizar:\n");
        printf("______________________________________\n");
        printf("| [1] ALTA DE CLIENTE                |\n");
        printf("| [2] BAJA DE CLIENTE                |\n");
        printf("| [3] MODIFICAR CLIENTE              |\n");
        printf("| [4] MOSTRAR TODOS LOS CLIENTES     |\n");
        printf("| [5] MOSTRAR CLIENTE POR ID         |\n");
        printf("| [6] MOSTRAR CLIENTE A-Z            |\n");
        printf("| [7] MOSTRAR CLIENTE ORDEN POR DNI  |\n");
        printf("| \x1b[31m[0] VOLVER AL MENU PRINCIPAL\x1b[0m       |\n");
        printf("--------------------------------------\n");
        if (scanf("%i", &op) != 1)
        {
            while (getchar() != '\n');
            op = -1;
            system("cls");
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
                system("pause");
                system("cls");
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
    }while(op != 0);
}

void menuEmpleado()
{
    int op, id;
    char nombreArchivo[DIMTEXTO] = "empleados.bin";
    do
    {
        printf("-------\x1b[33mEMPLEADOS\x1b[0m-------\n");
        printf("______________________________________\n");
        printf("| [1] ALTA DE EMPLEADO               |\n");
        printf("| [2] BAJA DE EMPLEADO               |\n");
        printf("| [3] MODIFICAR EMPLEADO             |\n");
        printf("| [4] MOSTRAR TODOS LOS EMPLEADO     |\n");
        printf("| [5] MOSTRAR EMPLEADO POR ID        |\n");
        printf("| [6] MOSTRAR EMPLEADO A-Z           |\n");
        printf("| [7] MOSTRAR EMPLEADO ORDEN POR DNI |\n");
        printf("| \x1b[31m[0] VOLVER AL MENU PRINCIPAL\x1b[0m       |\n");
        printf("--------------------------------------\n");
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
            system("pause");
            system("cls");
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
            system("pause");
            system("cls");
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
            system("pause");
            system("cls");
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
    }while(op != 0);
}

void menuProducto()
{
    int controlP;
    char archivoProducto[DIMTEXTO] = "producto.bin";
    FILE* archi= fopen(archivoProducto, "ab");
    fclose(archi);
    Pila baratos;
    inicpila(&baratos);
        do
        {
            printf("------\x1b[32mPRODUCTOS\x1b[0m------\n");
            printf("_____________________________________\n");
            printf("| [1] CARGAR PRODUCTO               |\n");
            printf("| [2] BUSCAR PRODUCTO               |\n");
            printf("| [3] MOSTRAR PRODUCTO              |\n");
            printf("| [4] MOSTRAR PRODUCTOS ECONOMICOS  |\n");
            printf("| \x1b[31m[0] VOLVER AL MENU PRINCIPAL\x1b[0m      |\n");
            printf("-------------------------------------\n");
            if (scanf("%i", &controlP) != 1)
            {
                while (getchar() != '\n');
                controlP = -1;
            }
            system("cls");
            switch(controlP)
            {
            case 1:
                cargarStProducto(archivoProducto);
                system("pause");
                system("cls");
                break;

            case 2:
                menuBuscarProducto();
                system("pause");
                system("cls");
                break;

            case 3:
                mostrarProducto(archivoProducto);
                system("pause");
                system("cls");
                break;

            case 4:
                mostrarProductoEconomico(archivoProducto, baratos);
                system("pause");
                system("cls");
                break;

            case 0:
                printf("VOLVIENDO AL MENU...\n");
                barraCarga();
                break;

            default:
                printf("~ ~ ~ INGRESE UNA OPCION VALIDA ~ ~ ~\n");
                system("pause");
                system("cls");
                break;
            }
        }while(controlP != 0);
}

void menuBuscarProducto()
{
    int controlP;
    char archivoProducto[DIMTEXTO] = "producto.bin";
    do
    {
        printf("-------MENU BUSQUEDA DE PRODUCTO-------\n\n");
        printf("_______________________________________");
        printf("|    SELECCIONE LA OPCION DESEADA     |\n");
        printf("| [1] Buscar producto por nombre      |\n");
        printf("| [2] Buscar producto por ID          |\n");
        printf("| [0]           VOLVER                |\n");
        printf("---------------------------------------");
        while (scanf("%i", &controlP) != 1)
        {
            while(getchar() != '\n');
            controlP = -1;
        }
        system("cls");
        switch(controlP)
        {
        case 1:
            buscarPorNombre(archivoProducto);
            break;
        case 2:
            buscarPorId(archivoProducto);
            break;
        case 0:
            printf(" --- VOLVIENDO AL MENU DE PRODUCTOS---");
            barraCarga();
            break;
        default:
            printf("- - - INGRESE UNA OPCION VALIDA - - -\n");
            system("pause");
            system("cls");
            break;
        }
    }
    while(controlP==0);
}
