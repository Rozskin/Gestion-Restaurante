#ifndef PEDIDO_H
#define PEDIDO_H
#include "Definiciones.h"
#include "Mesa.h" // Se agrego para usar TpMesa en la firma de marcarEntregado()

typedef struct nodoPedido *TpPedido;

struct nodoPedido {
    int id;
    string tipo; // "Salon" (se elimino Delivery, ya no aplica)
    string estado; // "Recibido", "En preparacion", "Listo", "Entregado", "Cancelado"

    // Calculo de impuestos
    float subtotal;
    float igv; // 18%
    // Se elimino costoEnvio porque se elimino el modulo Delivery
    float total;

    // Se agrego idMesa para poder liberar la mesa al entregar el pedido (Regla N.9)
    int idMesa;

    // Se agrego detalle como lista enlazada de productos dentro del pedido
    DetallePedido* detalle;

    // Se eliminaron: direccion, telefono, idRepartidor (eran exclusivos de Delivery)

    TpPedido sig;
};

// Funciones de Cola (FIFO) - se mantienen igual
void encolarPedido(TpPedido &frente, TpPedido &final, int id, int idMesa, float subtotal);
void atenderPedidoCocina(TpPedido &frente, TpPedido &listaActivos);
void mostrarColaCocina(TpPedido frente);

// Se cambio a bool para saber si el pedido fue encontrado y asi no registrar acciones falsas
bool marcarEntregado(TpPedido listaActivos, int idPedido, TpMesa listaMesas);

// Se agrego para cancelar pedido con motivo obligatorio si esta en preparacion (Regla N.6)
// Se cambio a bool para saber si el pedido fue encontrado
bool cancelarPedido(TpPedido &frente, TpPedido &listaActivos, int idPedido);

// Se elimino despacharDelivery() porque se elimino el modulo Delivery
// Se agrego: muestra los pedidos que ya salieron de la cola y estan en preparacion
void mostrarPedidosActivos(TpPedido listaActivos);

#endif
