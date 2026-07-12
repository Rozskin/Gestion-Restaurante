#include "Reserva.h"
#include <fstream>
#include <sstream>

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

// Se agrego: cancela una reserva (elimina el nodo) y libera la mesa asociada
TpReserva cancelarReserva(TpReserva listaReservas, TpMesa listaMesas, int idRes) {
    TpReserva p = listaReservas, ant = NULL;
    while(p != NULL) {
        if(p->id == idRes) {
            // Liberamos la mesa que estaba bloqueada por esta reserva
            cambiarEstadoMesa(listaMesas, p->idMesa, "Libre");

            // Sacamos el nodo de la lista (igual logica que el resto del proyecto)
            if(ant == NULL) {
                listaReservas = p->sig;
            } else {
                ant->sig = p->sig;
            }
            cout << ">> Reserva #" << idRes << " cancelada. Mesa " << p->idMesa << " liberada.\n";
            delete p;
            return listaReservas;
        }
        ant = p;
        p = p->sig;
    }
    cout << ">> No se encontro la reserva #" << idRes << ".\n";
    return listaReservas;
}

void guardarReservas(TpReserva lista){
    ofstream archivo("Reservas.txt");
    TpReserva p = lista;
    while(p != NULL){
        archivo << p->id << ";" << p->fecha << ";" << p->hora << ";" << p->numPersonas << ";" << p->idMesa << endl;
        p = p->sig;
    }
    archivo.close();
}

TpReserva cargarReservas(TpReserva lista, TpMesa listaMesas){
    ifstream archivo("Reservas.txt");
    if(!archivo.is_open()) return lista;
    string linea;
    while(getline(archivo, linea)){
        stringstream ss(linea);
        string sid, fecha, hora, snumPersonas, sidMesa;
        getline(ss, sid, ';'); getline(ss, fecha, ';'); getline(ss, hora, ';'); 
        getline(ss, snumPersonas, ';'); getline(ss, sidMesa);
        lista = crearReserva(lista, listaMesas, stoi(sid), fecha, hora, stoi(snumPersonas), stoi(sidMesa));
    }
    archivo.close();
    return lista;
}