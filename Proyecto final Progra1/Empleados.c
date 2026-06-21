#include "Empleados.h"
#include <string.h>

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
    return aux;
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

