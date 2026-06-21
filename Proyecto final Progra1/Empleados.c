#include "Empleados.h"
#include <string.h>

//ALTA EMPLEADO
stEmpleado crearUnEmpleado(int id)
{
    int c;
    char nombre[DIMTEXTO];
    char apellido[DIMTEXTO];
    stEmpleado aux;
    id++;
    aux.id = id;
    aux.activo = 1;
    printf("_____________________________________________\n ");
    printf("Ingrese el dni del empleado: ");
    scanf(" %i", &aux.dni);
    int edad;
    do
    {
        printf("ingrese edad del empleado: ");
        scanf(" %i", &edad);
    }
    while(edad < 18 || edad > 60);
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Ingrese el nombre y apellido del empleado: \n");
    fgets(aux.nombreYApellido, DIMTEXTO, stdin);
    aux.nombreYApellido[strcspn(aux.nombreYApellido, "\n")] = '\0';
//    while ((c = getchar()) != '\n' && c != EOF);
    printf("ingrese puesto del empleado: ");
    fgets(aux.puesto, DIMTEXTO, stdin);
    aux.puesto[strcspn(aux.puesto, "\n")] = '\0';
    printf("---------------------------------------------\n ");
    return aux;
}

void altaEmpleado(char nombreArchivo[])
{
    int i = 0, existe = 0;
    stEmpleado aux;
    FILE *archi = fopen(nombreArchivo, "a+b");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stEmpleado), 1, archi) > 0)
        {
            i++;
        }
        aux = crearUnEmpleado(i+1);
        if(verificacionEmpleado(archi, aux) == 0)
        {
            printf("\n- - - ESTE EMPLEADO YA EXISTE - - -\n");
        }
        else
        {
            fseek(archi, -sizeof(stEmpleado), SEEK_SET);
            fwrite(&aux, sizeof(stEmpleado), 1, archi);
            printf("\nEmpleado guardado correctamente.\n");
            mostrarEmpleado(aux);
        }
        fclose(archi);
    }
}

int verificacionEmpleado(FILE *archi, stEmpleado empleado)
{
    stEmpleado aux;
    int existe = 0;
    fseek(archi, 0, SEEK_SET);
    while(fread(&aux, sizeof(stEmpleado), 1, archi) > 0)
    {
        if(aux.dni == empleado.dni && aux.activo == 1)
        {
            existe = 1;
        }
    }
    return existe;
}

//BAJA EMPLEADOS
void bajaEmpleadoArchivo(char nombre[], int id)
{
    int encontrado = 0;
    stEmpleado aux;
    FILE *archi = fopen(nombre, "r+b");
    if(archi != NULL)
    {
        while(encontrado == 0 && fread(&aux, sizeof(stEmpleado), 1, archi) > 0)
        {
            if(aux.id == id && aux.activo == 1)
            {
                aux.activo = 0;
                fseek(archi, -sizeof(stEmpleado), SEEK_CUR);
                fwrite(&aux, sizeof(stEmpleado), 1, archi);
                encontrado = 1;
                printf("\nEmpleado dado de baja correctamente.\n");
                mostrarEmpleado(aux);
            }
        }
        if(encontrado == 0)
        {
            printf("\nERROR: Empleado no encontrado.\n");
        }
        fclose(archi);
    }
}

//MODIFICAR EMPLEADO
void modificarEmpleadoArchivo(char nombre[], int id)
{
    FILE *archi = fopen(nombre, "r+b");
    if(archi != NULL)
    {
        modificarEmpleado(archi, id);
        fclose(archi);
    }
}

stEmpleado modificarEmpleado(FILE *archi, int id)
{
    int encontrado = 0;
    char op = 'n';
    stEmpleado aux;
    while(encontrado == 0 && fread(&aux, sizeof(stEmpleado), 1, archi) > 0)
        {
            if(aux.id == id && aux.activo == 1)
            {
                encontrado = 1;
                printf("\n---Modificando Empleado ID: &i\n", aux.id);
                printf("Quiere modificar el DNI? (s/n): ");
                scanf(" %c", &op);
                if(op == 's' || op == 'S')
                {
                    printf("\nIngrese el nuevo DNI: ");
                    scanf("%i", &aux.dni);
                }
                printf("\nQuiere modificar el nombre y apellido? (s/n): ");
                scanf(" %c", &op);
                if(op == 's' || op == 'S')
                {
                    printf("\nIngrese el nuevo nombre y apellido: ");
                    fgets(aux.nombreYApellido, DIMTEXTO, stdin);
                    aux.nombreYApellido[strcspn(aux.nombreYApellido, "\n")] = '\0';
                }
                printf("\nQuiere modificar la edad? (s/n): ");
                scanf(" %c", &op);
                if(op == 's' || op == 'S')
                {
                    printf("\nIngrese la nueva edad: ");
                    scanf("%i", &aux.edad);
                }
                printf("\nQuiere modificar el puesto? (s/n): ");
                scanf(" %c", &op);
                if(op == 's' || op == 'S')
                {
                    printf("\nIngrese el nuevo puesto: ");
                    fgets(aux.puesto, DIMTEXTO, stdin);
                    aux.puesto[strcspn(aux.puesto, "\n")] = '\0';
                }
                fseek(archi, -sizeof(stEmpleado), SEEK_CUR);
                fwrite(&aux, sizeof(stEmpleado), 1, archi);
                mostrarEmpleado(aux);
            }
        }
        if(encontrado == 0)
        {
            printf("\nERROR: Cliente no encontrado.\n");
        }
    return aux;
}

//CONSULTA
void mostrarEmpleado(stEmpleado empleado)
{
    printf("\x1b[34mEMPLEADO ID |%i|:\x1b[0m\n\n", empleado.id);
    printf("____________________________\n");
    printf(" DNI %i\n", empleado.dni);
    printf(" NOMBRE: %s\n", empleado.nombreYApellido);
    printf(" EDAD: %i\n", empleado.edad);
    printf(" PUESTO: %s\n", empleado.puesto);
    if(empleado.activo == 1)
    {
        printf("ESTADO: ACTIVO\n");
    }
    else
    {
        printf("ESTADO: INACTIVO\n");
    }
    printf("-----------------------------\n");
}

void mostrarArchivoEmpleado(char nombre[])
{
    stEmpleado aux;
    FILE *archi = fopen(nombre, "rb");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stEmpleado), 1, archi) > 0)
        {
                mostrarEmpleado(aux);
        }
        fclose(archi);
    }
}

void mostrarEmpleadosArchivoID(char nombre[], int id)
{
    int encontrado = 0;
    stEmpleado aux;
    FILE *archi = fopen(nombre, "rb");
    if(archi != NULL)
    {
        while(encontrado == 0 && fread(&aux, sizeof(stEmpleado), 1, archi) > 0)
        {
            if(aux.id == id && aux.activo == 1)
            {
                mostrarEmpleado(aux);
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

//LISTADOS
void listarEmpleadosSeleccionAlfabetica(char nombre[])
{
    stEmpleado lista[100];
    int validos = pasarArchivoArreglo(nombre, lista, 100);
    int posMenor;
    stEmpleado temp;
    for(int i = 0; i < validos - 1; i++)
    {
        posMenor = i;
        for(int j = i + 1; j < validos; j++)
        {
            if(strcasecmp(lista[j].nombreYApellido, lista[posMenor].nombreYApellido) < 0)
            {
                posMenor = j;
            }
        }
        temp = lista[posMenor];
        lista[posMenor] = lista[i];
        lista[i] = temp;
    }
    printf("\n--- LISTADO ALFABETICO (SELECCION) ---\n");
    for(int i = 0; i < validos; i++)
    {
        mostrarEmpleado(lista[i]);
    }
}

int pasarArchivoArreglo(char nombre[], stEmpleado arreglo[], int dim)
{
    stEmpleado aux;
    FILE *archi = fopen(nombre, "rb");
    int i = 0;
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stEmpleado), 1, archi) > 0 && i < dim)
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

void listarEmpleadosInsercionDni(char nombre[])
{
    stEmpleado lista[100];
    int validos = pasarArchivoArreglo(nombre, lista, 100);
    int j;
    stEmpleado aux;
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
    printf("\n--- LISTADO POR DNI (INSERCION) ---\n");
    for(int i = 0; i < validos; i++)
    {
        mostrarEmpleado(lista[i]);
    }
}
