#ifndef PRODUCTO_H
#define PRODUCTO_H

#include "Definiciones.h"

// Puntero para la lista de inventario/menu
typedef struct nodoProducto *TpProducto;

struct nodoProducto {
    int id;
    string nombre;
    int stock;
    float precio;
    TpProducto sig;
};

// Prototipos del modulo
TpProducto agregarProducto(TpProducto lista, int id, string nom, int stock, float precio);
void mostrarMenuDigital(TpProducto lista);
bool verificarStock(TpProducto lista, int id, int cantidad);
void actualizarStock(TpProducto lista, int id, int cantidad); // Sirve para restar o sumar stock

#endif	
