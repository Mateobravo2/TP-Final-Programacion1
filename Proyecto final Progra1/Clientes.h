#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <stdio.h>
#include "Productos.h"

#define DIMTEXTO 30

typedef struct
{
    int id;
    int dni;
    char nombre[DIMTEXTO];
    stProducto carrito[DIMTEXTO];
    int activo;
}stCliente;

//ALTA
stCliente crearCliente();
void altaClientesArchivo(char nombre[]);
int verificacionCliente(FILE *archi, stCliente clienteNuevo);
//BAJA
void bajaDeClienteDeArchivo(char nombre[], int id);
//MODIFICACION
void modificarClienteDeArchivo(char nombre[], int id);
stCliente modificarCliente(FILE *archi, int id);
//CONSULTA
void mostrarCliente(stCliente cliente);
void mostrarClientesArchivo(char nombre[], int id);
//LISTADOS


#endif // CLIENTES_H_INCLUDED
