#include "Producto.h"

TpProducto agregarProducto(TpProducto lista, int id, string nom, int stock, float precio) {
    TpProducto nuevo = new(struct nodoProducto);
    nuevo->id = id;
    nuevo->nombre=nom;
    nuevo->stock =stock;
    nuevo->precio = precio;
    nuevo->contadorVentas = 0; // Se agrego: inicia en 0 al crear el plato
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

// Se agrego: elimina un plato de la lista enlazada por su ID
TpProducto eliminarProducto(TpProducto lista, int id) {
    TpProducto p = lista, ant = NULL;
    while(p != NULL) {
        if(p->id == id) {
            if(ant == NULL) {
                lista = p->sig;
            } else {
                ant->sig = p->sig;
            }
            cout << ">> Plato '" << p->nombre << "' eliminado del menu.\n";
            delete p;
            return lista;
        }
        ant = p;
        p = p->sig;
    }
    cout << ">> No se encontro el plato con ID " << id << ".\n";
    return lista;
}

// Se agrego: recorre la lista y retorna el nodo con mayor contadorVentas
TpProducto platoMasPedido(TpProducto lista) {
    if(lista == NULL) return NULL;
    TpProducto mayor = lista;
    TpProducto p = lista->sig;
    while(p != NULL) {
        if(p->contadorVentas > mayor->contadorVentas)
            mayor = p;
        p = p->sig;
    }
    return mayor;
}

// Se agrego: recorre la lista y retorna el nodo con menor contadorVentas
TpProducto platoPedido(TpProducto lista) {
    if(lista == NULL) return NULL;
    TpProducto menor = lista;
    TpProducto p = lista->sig;
    while(p != NULL) {
        if(p->contadorVentas < menor->contadorVentas)
            menor = p;
        p = p->sig;
    }
    return menor;
}
