#include "Historial.h"
#include <fstream>
#include <sstream>

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

void guardarHistorial(TpHistorial pila){
    ofstream archivo("Historial.txt");
    TpHistorial p = pila;
    while(p != NULL){
        archivo << p->idAccion << ";" << p->descripcion << endl;
        p = p->sig;
    }
    archivo.close();
}

TpHistorial cargarHistorial(TpHistorial pila){
    ifstream archivo("Historial.txt");
    if(!archivo.is_open()) return pila;
    string linea;
    while(getline(archivo, linea)){
        stringstream ss(linea);
        string sid, descripcion;
        getline(ss, sid, ';'); getline(ss, descripcion);
        registrarAccion(pila, stoi(sid), descripcion);
    }
    archivo.close();
    return pila;
}
