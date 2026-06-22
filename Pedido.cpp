#include "Pedido.h"

// Encolar (Push_back)
void encolarPedido(TpPedido &frente, TpPedido &final, int id, string tipo, float subtotal, float distanciaKm) {
    TpPedido nuevo = new(struct nodoPedido);
    nuevo->id=id;
    nuevo->tipo=tipo;
    nuevo->estado="Recibido";
    nuevo->subtotal = subtotal;
    
    // Regla de negocio: Calculo automatico de IGV 
    nuevo->igv = subtotal * 0.18; 
    
    // Regla de negocio: Tarifa de envio por distancia
    if(tipo == "Delivery") {
        nuevo->costoEnvio = distanciaKm * 2.50; // S/ 2.50 por Km de ejemplo
    } else {
        nuevo->costoEnvio = 0;
    }
    
    nuevo->total = nuevo->subtotal + nuevo->igv + nuevo->costoEnvio;
    nuevo->direccion = "";
    nuevo->telefono = "";
    nuevo->idRepartidor = 0;
    nuevo->sig=NULL;

    // Logica de Cola
    if(frente == NULL) {
        frente = nuevo;
        final = nuevo;
    } else {
        final->sig = nuevo;
        final = nuevo;
    }
    cout<<">> Pedido #"<<id<<" ingresado a la cola ("<<tipo<<"). Total a pagar: S/."<<nuevo->total<<"\n";
}

// Desencolar (Pop_front) para pasar a preparacion/entregado
void atenderPedidoCocina(TpPedido &frente) {
    if(frente == NULL) {
        cout<<">> La cola de cocina esta vacia.\n";
        return;
    }
    
    frente->estado = "En preparacion";
    cout<<">> El Pedido #"<<frente->id<<" esta siendo preparado por el Chef.\n";
    
    // Para simplificar, lo sacamos de la cola de 'Recibidos'
    TpPedido aux = frente;
    frente = frente->sig;
    // Ojo: en un sistema real, pasariamos este nodo a otra cola de "Listos"
    delete aux; 
}

void mostrarColaCocina(TpPedido frente) {
    TpPedido p = frente;
    cout << "\n--- COLA DE PEDIDOS EN COCINA (FIFO) ---\n";
    if(p==NULL){
        cout<<"No hay pedidos pendientes.\n";
        return;
    }
    while(p != NULL) {
        cout<<"Pedido #"<<p->id<<" | Tipo: "<<p->tipo<<" | Estado: "<<p->estado<<"\n";
        p=p->sig;
    }
}

// Validacion estricta de Delivery
void despacharDelivery(TpPedido frente, int idPedido, int idRep, string dir, string tel) {
    TpPedido p = frente;
    while(p!=NULL) {
        if(p->id == idPedido && p->tipo == "Delivery") {
            p->direccion = dir;
            p->telefono = tel;
            p->idRepartidor = idRep;
            
            // Regla de negocio
            if(p->idRepartidor != 0 && p->direccion != "" && p->telefono != "") {
                p->estado = "En camino";
                cout<<">> EXITO: Pedido #"<<idPedido<<" despachado correctamente.\n";
            } else {
                cout<<">> ERROR DE VALIDACION: Faltan datos para el despacho.\n";
            }
            return;
        }
        p = p->sig;
    }
    cout<<">> No se encontro un pedido de delivery con ese ID en la cola.\n";
}
