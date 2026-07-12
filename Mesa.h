#ifndef MESA_H
#define MESA_H

#include "Definiciones.h"

typedef struct nodoMesa *TpMesa;

struct nodoMesa {
    int id;
    int capacidad;
    string estado; 
    TpMesa sig;
};

// Prototipos
TpMesa agregarMesa(TpMesa lista, int id, int cap);
void mostrarMesas(TpMesa lista);
bool verificarMesaLibre(TpMesa lista, int id, int numPersonas);
void cambiarEstadoMesa(TpMesa lista, int id, string nuevoEstado);
void guardarMesas(TpMesa lista);
TpMesa cargarMesas(TpMesa lista);

#endif
