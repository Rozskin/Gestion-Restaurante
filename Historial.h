#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "Definiciones.h"

typedef struct nodoHistorial *TpHistorial;

struct nodoHistorial {
    int idAccion;
    string descripcion;
    TpHistorial sig;
};

// Funciones de Pila (LIFO)
void registrarAccion(TpHistorial &pila, int id, string desc);
void deshacerAccion(TpHistorial &pila);
void mostrarHistorial(TpHistorial pila);

#endif
