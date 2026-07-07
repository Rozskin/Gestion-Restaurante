#include "ColaEspera.h"

// Encolar cliente sin reserva (Push_back) - mismo patron que encolarPedido()
void encolarCliente(TpEspera &frente, TpEspera &final, string nombre, int numPersonas) {
    TpEspera nuevo = new(struct nodoEspera);
    nuevo->nombreCliente = nombre;
    nuevo->numPersonas = numPersonas;
    nuevo->sig = NULL;

    // Logica de Cola - identica a la de Pedido.cpp
    if(frente == NULL) {
        frente = nuevo;
        final = nuevo;
    } else {
        final->sig = nuevo;
        final = nuevo;
    }
    cout << ">> Cliente " << nombre << " agregado a la cola de espera ("
         << numPersonas << " personas).\n";
}

// Desencolar (Pop_front) - atiende al primer cliente en espera
void atenderClienteEspera(TpEspera &frente) {
    if(frente == NULL) {
        cout << ">> No hay clientes en espera.\n";
        return;
    }
    cout << ">> Atendiendo a: " << frente->nombreCliente
         << " (" << frente->numPersonas << " personas). Asigne una mesa libre.\n";

    // Eliminamos el nodo del frente (ya fue atendido)
    TpEspera aux = frente;
    frente = frente->sig;
    delete aux;
}

// Muestra todos los clientes en espera - mismo patron que mostrarColaCocina()
void mostrarColaEspera(TpEspera frente) {
    TpEspera p = frente;
    cout << "\n--- COLA DE ESPERA DE CLIENTES (FIFO) ---\n";
    if(p == NULL) {
        cout << "No hay clientes en espera.\n";
        return;
    }
    int pos = 1;
    while(p != NULL) {
        cout << "Posicion " << pos << ": " << p->nombreCliente
             << " | Personas: " << p->numPersonas << "\n";
        pos++;
        p = p->sig;
    }
}
