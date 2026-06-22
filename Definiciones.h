#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#include <iostream>
#include <string>

using namespace std;

// Estructuras base iniciales para futuros modulos
// Las dejamos declaradas para no tener problemas de enlazado luego
struct DetallePedido {
    int cantidad;
    int idProducto;
    float subtotal;
};

struct PedidoBase {
    int id;
    string tipo; // Salon o Delivery
    string estado;
};

#endif
