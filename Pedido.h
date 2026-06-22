#ifndef PEDIDO_H
#define PEDIDO_H

#include "Definiciones.h"

typedef struct nodoPedido *TpPedido;

struct nodoPedido {
    int id;
    string tipo; // "Salon" o "Delivery"
    string estado; // "Recibido", "En preparacion", "En camino", "Entregado"
    
    // Calculo de impuestos y tarifas
    float subtotal;
    float igv; // 18%
    float costoEnvio; 
    float total;
    
    // Datos exclusivos para validacion de delivery
    string direccion;
    string telefono;
    int idRepartidor;
    
    TpPedido sig;
};

// Funciones de Cola (FIFO)
void encolarPedido(TpPedido &frente, TpPedido &final, int id, string tipo, float subtotal, float distanciaKm);
void atenderPedidoCocina(TpPedido &frente);
void mostrarColaCocina(TpPedido frente);
void despacharDelivery(TpPedido frente, int idPedido, int idRep, string dir, string tel);

#endif
