#ifndef EMPLEADOS_H_INCLUDED
#define EMPLEADOS_H_INCLUDED

#include <stdio.h>

#define DIMTEXTO 30

typedef struct
{
    int id;
    int dni;
    char nombreYApellido[DIMTEXTO];
    int edad;
    char puesto[DIMTEXTO];
    int activo;
}stEmpleado;

//ALTA
stEmpleado crearUnEmpleado(int id);
void altaEmpleado(char nombreArchivo[]);
int verificacionEmpleado(FILE *archi, stEmpleado empleado);
//BAJA
void bajaEmpleadoArchivo(char nombre[], int id);
//MODIFICACION
stEmpleado modificarEmpleado(FILE *archi, int id);
void modificarEmpleadoArchivo(char nombre[], int id);
//CONSULTA
void mostrarEmpleado(stEmpleado empleado);
void mostrarArchivoEmpleado(char nombre[]);
void mostrarEmpleadosArchivoID(char nombre[], int id);
//LISTADO
void listarEmpleadosSeleccionAlfabetica(char nombre[]);
int pasarArchivoArreglo(char nombre[], stEmpleado arreglo[], int dim);
void listarEmpleadosInsercionDni(char nombre[]);

#endif // EMPLEADOS_H_INCLUDED
