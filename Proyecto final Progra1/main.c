#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DIMTEXTO 30

//STRUCTS
typedef struct
{
    int id;
    char nombre[DIMTEXTO];
    float precio;
}stProducto;

typedef struct
{
    int id;
    int dni;
    char nombreYApellido[DIMTEXTO];
    int edad;
    char puesto[DIMTEXTO];
    int activo;
}stEmpleado;

typedef struct
{
    int id;
    int dni;
    char nombre[DIMTEXTO];
    stProducto carrito[DIMTEXTO];
    int activo;
}stCliente;

//MENÚ Y SUBMENÚS
void menu();
void barraCarga();
void menuClientes();
void menuProducto();
void menuEmpleado();
//ALTA
////CLIENTE
stCliente crearCliente();
void altaClientesArchivo(char nombre[]);
int verificacionCliente(FILE *archi, stCliente clienteNuevo);
////EMPLEADO
stEmpleado crearUnEmpleado(int id);
void altaEmpleado(char nombreArchivo[]);
int verificacionEmpleado(FILE *archi, stEmpleado empleado);
//BAJA
void bajaDeClienteDeArchivo(char nombre[], int id);
//MODIFICACION
void modificarClienteDeArchivo(char nombre[], int id);
stCliente modificarCliente(FILE *archi, int id);
//CONSULTA
void mostrarCliente(stCliente cliente);
void mostrarClientesArchivo(char nombre[], int id);
//LISTADOS


int main()
{
    menu();
    return 0;
}

void menu()
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

//MENÚ Y SUBMENÚS
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

//ABMCL DE CLIENTE
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
    int existe = 0, i = 0;
    stCliente aux;
    FILE *archi = fopen(nombre, "r+b");
    if(archi != NULL)
    {
        if(fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            i++;
        }
        aux = crearCliente(i+1);
        existe = verificacionCliente(archi, aux);
        if(existe == 1)
        {
            printf("\n- - - ESTE CLIENTE YA EXISTE - - -\n");
        }
        else
        {
            fwrite(&aux, sizeof(stCliente), 1, archi);
        }
        fclose(archi);
    }
}

int verificacionCliente(FILE *archi, stCliente clienteNuevo)
{
    stCliente aux;
    int existe = 0;
    fseek(archi, 0, SEEK_SET);
    while(fread(&aux, sizeof(stCliente), 1, archi) > 0)
    {
        if(aux.id == clienteNuevo.id || aux.dni == clienteNuevo.dni)
        {
            existe = 1;
        }
    }
    return existe;
}

//BAJA DE CLIENTE
void bajaDeClienteDeArchivo(char nombre[], int id)
{
    stCliente aux;
    FILE *archi = fopen(nombre, "r+b");
    if(archi != NULL)
    {
        if(fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            if(aux.id == id)
            {
                aux.activo = 0;
            }
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
    char op = 'n';
    stCliente aux;
    if(fread(&aux, sizeof(stCliente), 1, archi) > 0)
        {
            if(aux.id == id)
            {
                printf("Quiere modificar el DNI? (s/n): ");
                if(op == 's')
                {
                    printf("\nIngrese el nuevo DNI: ");
                    scanf("%i", &aux.dni);
                }
                printf("Quiere modificar el nombre? (s/n): ");
                if(op == 's')
                {
                    printf("\nIngrese el nuevo nombre: ");
                    scanf(" %s", &aux.nombre);
                }
                printf("Quiere modificar el carrito? (s/n): ");
                if(op == 's')
                {
                    printf("\nIngrese el nuevo carrito: ");
                    //LLAMAR FUNCION DE CREAR CARRITO !!!!
                }
            }
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
    stCliente aux;
    FILE *archi = fopen(nombre, "rb");
    if(archi != NULL)
    {
        if(fread(&aux, sizeof(stCliente), 1, archi) > 0 && aux.id == id)
        {
            if(aux.activo == 1)
            {
                mostrarCliente(aux);
            }
        }
        fclose(archi);
    }
}

//LISTADOS DE CLIENTE


//ALTA EMPLEADO
stEmpleado crearUnEmpleado(int id)
{
    char nombre[DIMTEXTO];
    char apellido[DIMTEXTO];
    stEmpleado aux;
    id++;
    aux.id = id;
    aux.activo = 1;
    printf("________________\n ");
    printf("Ingrese el dni del empleado: ");
    scanf(" %i", &aux.dni);
    int edad;
    do
    {
        printf("ingrese edad del empleado: ");
        scanf(" %i", &edad);
    }
    while(edad < 18 || edad > 60);
    printf("Ingrese el nombre del empleado: \n");
    scanf(" %s", &nombre);
    printf("Ingrese el apellido del empleado: \n");
    scanf(" %s", &apellido);
    strcat(nombre, " ");
    strcat(nombre, apellido);
    strcpy(aux.nombreYApellido, nombre);
    printf("ingrese puesto: ");
    scanf(" %s", &aux.puesto);
}

void altaEmpleado(char nombreArchivo[])
{
    int i = 0, existe = 0;
    stEmpleado aux;
    FILE *archi = fopen(nombreArchivo, "r+b");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stEmpleado), 1, archi) > 0)
        {
            i++;
        }
        aux = crearUnEmpleado(i+1);
        existe = verificacionEmpleado(archi, aux);
        if(existe == 1)
        {
            printf("\n- - - ESTE EMPLEADO YA EXISTE - - -\n");
        }
        else
        {
         fwrite(&aux, sizeof(stEmpleado), 1, archi);
        }
        fclose(archi);
    }
}

int verificacionEmpleado(FILE *archi, stEmpleado empleado)
{
    stEmpleado aux;
    int existe = 0;
    fseek(archi, 0, SEEK_SET);
    if(fread(&aux, sizeof(stEmpleado), 1, archi) > 0)
    {
        if(aux.id == empleado.id || aux.dni == empleado.dni)
        {
            existe = 1;
        }
    }
    return existe;
}
