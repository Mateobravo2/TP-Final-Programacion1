#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include <stdio.h>
#define DIMTEXTO 30

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
void cargarStProducto(char archivoProducto[]);
stProducto cargaProducto(int i, int stock);
//BAJA Y MODIFICACION
stProducto menuProdElegido(stProducto prod);
//CONSULTA
void mostrarProducto(char archivoProducto[]);
void mostrarP(stProducto prod);
void buscarProducto(char archivoProducto[]);
void buscarPorNombre(FILE* archi);
void buscarPorId(FILE* archi);
//LISTADO
void mostrarProductoEconomico(char archivoProducto[]);

#endif // PRODUCTOS_H_INCLUDED
