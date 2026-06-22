#include "Historial.h"

void registrarAccion(TpHistorial &pila, int id, string desc) {
    TpHistorial nuevo = new(struct nodoHistorial);
    nuevo->idAccion = id;
    nuevo->descripcion = desc;
    
    // Insercion al inicio (Push)
    nuevo->sig = pila;
    pila = nuevo;
}

void deshacerAccion(TpHistorial &pila) {
    if(pila == NULL) {
        cout << ">> No hay acciones para deshacer.\n";
        return;
    }
    // Eliminacion al inicio (Pop)
    TpHistorial aux = pila;
    pila = pila->sig;
    
    cout << ">> Accion deshecha: " << aux->descripcion << "\n";
    delete aux; // Liberamos memoria
}

void mostrarHistorial(TpHistorial pila) {
    TpHistorial p = pila;
    cout << "\n--- HISTORIAL DE ACCIONES (LIFO) ---\n";
    if(p == NULL){
        cout<<"El historial esta vacio.\n";
        return;
    }
    while(p!=NULL) {
        cout<<"[Accion "<<p->idAccion<<"] : "<<p->descripcion<<"\n";
        p = p->sig;
    }
}
