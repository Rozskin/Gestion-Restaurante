#ifndef RESERVA_H
#define RESERVA_H
#include "Definiciones.h"
#include "Mesa.h" // Incluimos Mesa.h porque la reserva altera el estado de la mesa

typedef struct nodoReserva *TpReserva;

struct nodoReserva {
    int id;
    string fecha;
    string hora;
    int numPersonas;
    int idMesa;
    TpReserva sig;
};

TpReserva crearReserva(TpReserva listaReservas, TpMesa listaMesas, int idRes, string f, string h, int numP, int idMesa);
void mostrarReservas(TpReserva lista);

// Se agrego: cancela una reserva y libera la mesa asociada
TpReserva cancelarReserva(TpReserva listaReservas, TpMesa listaMesas, int idRes);

#endif
