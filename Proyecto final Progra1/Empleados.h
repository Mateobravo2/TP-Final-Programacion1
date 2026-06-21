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

////EMPLEADO
stEmpleado crearUnEmpleado(int id);
void altaEmpleado(char nombreArchivo[]);
int verificacionEmpleado(FILE *archi, stEmpleado empleado);

#endif // EMPLEADOS_H_INCLUDED
