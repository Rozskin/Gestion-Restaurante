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
    int contadorVentas; // Se agrego: cuenta cuantas veces fue pedido este plato
    TpProducto sig;
};

// Prototipos del modulo
TpProducto agregarProducto(TpProducto lista, int id, string nom, int stock, float precio);
void mostrarMenuDigital(TpProducto lista);
bool verificarStock(TpProducto lista, int id, int cantidad);
void actualizarStock(TpProducto lista, int id, int cantidad); // Sirve para restar o sumar stock

// Se agrego: eliminar un plato del menu por su ID
TpProducto eliminarProducto(TpProducto lista, int id);
// Se agrego: funciones de reporte de platos
TpProducto platoMasPedido(TpProducto lista);
TpProducto platoPedido(TpProducto lista); // Se agrego: retorna el plato menos pedido
#endif	
