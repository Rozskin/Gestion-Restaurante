#include "Mesa.h"

TpMesa agregarMesa(TpMesa lista, int id, int cap) {
    TpMesa nuevo = new(struct nodoMesa);
    nuevo->id=id;
    nuevo->capacidad = cap;
    nuevo->estado="Libre"; // Todas nacen libres
    nuevo->sig = NULL;

    if(lista == NULL) {
        lista=nuevo;
    } else {
        TpMesa p = lista;
        while(p->sig != NULL) {
            p = p->sig;
        }
        p->sig = nuevo;
    }
    return lista;
}

void mostrarMesas(TpMesa lista) {
    TpMesa p = lista;
    cout << "\n--- ESTADO DEL SALON ---\n";
    if(p==NULL){
        cout<<"No hay mesas configuradas.\n";
        return;
    }
    while(p!=NULL) {
        cout<<"Mesa "<<p->id<<" | Capacidad: "<<p->capacidad<<" | Estado: "<<p->estado<<"\n";
        p = p->sig;
    }
}

// Verifica si la mesa esta libre y si caben las personas
bool verificarMesaLibre(TpMesa lista, int id, int numPersonas) {
    TpMesa p = lista;
    while(p!=NULL) {
        if(p->id == id) {
            if(p->estado == "Libre" && p->capacidad >= numPersonas) {
                return true;
            } else {
                return false;
            }
        }
        p=p->sig;
    }
    return false;
}

void cambiarEstadoMesa(TpMesa lista, int id, string nuevoEstado) {
    TpMesa p = lista;
    while(p!=NULL) {
        if(p->id == id) {
            p->estado = nuevoEstado;
            return;
        }
        p=p->sig;
    }
}
