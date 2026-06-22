#include "Producto.h"

TpProducto agregarProducto(TpProducto lista, int id, string nom, int stock, float precio) {
    TpProducto nuevo = new(struct nodoProducto);
    nuevo->id = id;
    nuevo->nombre=nom;
    nuevo->stock =stock;
    nuevo->precio = precio;
    nuevo->sig = NULL;
	
    if(lista == NULL) {
        lista = nuevo;
    } else {
        TpProducto p = lista;
        while(p->sig != NULL) {
            p = p->sig;
        }
        p->sig = nuevo;
    }
    return lista;
}

void mostrarMenuDigital(TpProducto lista) {
    TpProducto p = lista;
    cout << "\n--- MENU DIGITAL DE PLATOS ---\n";
    if(p == NULL) {
        cout << "No hay productos registrados en el menu.\n";
        return;
    }
    while(p != NULL) {
        cout << "ID: " << p->id << " | " << p->nombre << " - S/. " << p->precio;
        // Regla de negocio: Disponibilidad Dinamica
        if(p->stock == 0) {
            cout << " -> [NO DISPONIBLE]";
        } else {
            cout << " (Stock: " << p->stock << ")";
        }
        cout << "\n";
        p = p->sig;
    }
}

bool verificarStock(TpProducto lista, int id, int cantidad) {
    TpProducto p = lista;
    while(p != NULL) {
        if(p->id == id) {
            return p->stock >= cantidad;
        }
        p = p->sig;
    }
    return false; // No se encontro el producto
}

void actualizarStock(TpProducto lista, int id, int cantidad) {
    TpProducto p = lista;
    while(p != NULL) {
        if(p->id == id) {
            p->stock = p->stock - cantidad;
            if(p->stock < 0) {
                p->stock = 0; 
            }
            return;
        }
        p = p->sig;
    }
}
