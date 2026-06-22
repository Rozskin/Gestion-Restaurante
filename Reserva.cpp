#include "Reserva.h"

TpReserva crearReserva(TpReserva listaReservas, TpMesa listaMesas, int idRes, string f, string h, int numP, int idMesa) {
    // Primero validamos la regla de negocio
    if(verificarMesaLibre(listaMesas, idMesa, numP) == false) {
        cout<<">> ERROR: La mesa "<<idMesa<<" no esta disponible o no tiene capacidad suficiente.\n";
        return listaReservas; // Retornamos la lista sin cambios
    }

    // Si pasa la validacion, creamos el nodo
    TpReserva nuevo = new(struct nodoReserva);
    nuevo->id = idRes;
    nuevo->fecha = f;
    nuevo->hora = h;
    nuevo->numPersonas = numP;
    nuevo->idMesa = idMesa;
    nuevo->sig=NULL;

    if(listaReservas == NULL) {
        listaReservas = nuevo;
    } else {
        TpReserva p = listaReservas;
        while(p->sig != NULL) {
            p = p->sig;
        }
        p->sig = nuevo;
    }

    // Bloqueamos la disponibilidad de la mesa asignada (Regla del PDF)
    cambiarEstadoMesa(listaMesas, idMesa, "Reservada");
    cout<<">> EXITO: Reserva confirmada. Mesa "<<idMesa<<" bloqueada.\n";

    return listaReservas;
}

void mostrarReservas(TpReserva lista) {
    TpReserva p = lista;
    cout << "\n--- LISTA DE RESERVAS ACTIVAS ---\n";
    if(p==NULL){
        cout<<"No hay reservas registradas.\n";
        return;
    }
    while(p!=NULL) {
        cout<<"Reserva #"<<p->id<<" | Fecha: "<<p->fecha<<" "<<p->hora<<" | Personas: "<<p->numPersonas<<" | Mesa Asignada: "<<p->idMesa<<"\n";
        p = p->sig;
    }
}
