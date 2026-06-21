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
    int op;
    char nombre[DIMTEXTO] = "clientes.bin";
    do
    {
        printf("\x1b[34mCLIENTE\x1b[0m\n");
        printf("Ingrese la accion a realizar:\n");
        printf("_________________________\n");
        printf("|[1] ALTA DE CLIENTE    |\n");
        printf("|[2] BAJA DE CLIENTE    |\n");
        printf("|[3] MODIFICAR CLIENTE  |\n");
        printf("|[4] |\n");
        printf("|[5] |\n");
        printf("|\x1b[31m[0]        SALIR\x1b[0m       |\n");
        printf("-------------------------\n");
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
            break;
            case 2:

            break;
            case 3:

            break;
            case 4:

            break;
        }
    }while(op != 0);
}

void menuEmpleado()
{

}

void menuProducto()
{

}
