#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include <stdio.h>
#include <string.h>
#define DIMTEXTO 30
#include "pila.h"

typedef struct
{
    int id;
    char nombre[DIMTEXTO];
    float precio;
    int stock;
    int economico;
    int activo;
} stProducto;

//ALTA
void cargarStProducto(char archivoProducto[], Pila* economico);
stProducto cargaProducto(int i);
//BAJA Y MODIFICACION
stProducto menuProdElegido(stProducto prod);
//CONSULTA
void mostrarProducto(char archivoProducto[]);
void mostrarP(stProducto prod);
void buscarProducto(char archivoProducto[]);
void buscarPorNombre(FILE* archi);
void buscarPorId(FILE* archi);
//LISTADO
void mostrarProductoEconomico(char archivoProducto[], Pila cant);

#endif // PRODUCTOS_H_INCLUDED
