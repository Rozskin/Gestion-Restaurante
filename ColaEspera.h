#ifndef COLAESPERA_H
#define COLAESPERA_H
#include "Definiciones.h"

typedef struct nodoEspera *TpEspera;

// Mismo patron de nodo enlazado que el resto del proyecto
struct nodoEspera {
    string nombreCliente;
    int numPersonas;
    TpEspera sig;
};

// Funciones de Cola (FIFO) - mismo patron que Pedido.h
void encolarCliente(TpEspera &frente, TpEspera &final, string nombre, int numPersonas);
void atenderClienteEspera(TpEspera &frente);
void mostrarColaEspera(TpEspera frente);

#endif
