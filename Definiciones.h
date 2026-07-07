#ifndef DEFINICIONES_H
#define DEFINICIONES_H
#include <iostream>
#include <string>
using namespace std;

// Detalle de un pedido: lista enlazada de productos dentro de un pedido
struct DetallePedido {
    int idProducto;
    int cantidad;
    float subtotal;
    DetallePedido* sig;
};

#endif
