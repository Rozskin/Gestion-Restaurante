#include "Pedido.h"
#include "Mesa.h" // Se agrego para poder llamar cambiarEstadoMesa() al entregar (Regla N.9)
#include <fstream>
#include <sstream>

// Encolar (Push_back)
// Se simplfico la firma: se elimino tipo y distanciaKm porque ya no hay Delivery
void encolarPedido(TpPedido &frente, TpPedido &final, int id, int idMesa, float subtotal) {
    TpPedido nuevo = new(struct nodoPedido);
    nuevo->id = id;
    nuevo->tipo = "Salon"; // Se elimino Delivery, siempre es Salon
    nuevo->estado = "Recibido";
    nuevo->idMesa = idMesa; // Se agrego para vincular pedido con mesa (Regla N.9)
    nuevo->subtotal = subtotal;
    nuevo->detalle = NULL; // Se agrego: lista de productos del pedido (por ahora vacia)

    // Se corrigio: en Peru el precio ya incluye IGV, se extrae del subtotal (no se suma)
	nuevo->igv = subtotal - (subtotal / 1.18);
	nuevo->total = subtotal; // El total es el mismo subtotal, el IGV ya esta incluido

    nuevo->sig = NULL;

    // Logica de Cola - se mantiene igual
    if(frente == NULL) {
        frente = nuevo;
        final = nuevo;
    } else {
        final->sig = nuevo;
        final = nuevo;
    }
    // Se actualizo el mensaje: el IGV esta incluido en el precio, no se suma
	cout<< ">> Pedido #" << id << " ingresado a la cola."
     	<< " Total: S/." << nuevo->total
     	<< " (incluye IGV: S/." << nuevo->igv << ")\n";
}

// Desencolar (Pop_front) - CORREGIDO: antes hacia delete aux, ahora mueve el nodo a listaActivos
// Se agrego parametro listaActivos para no perder el pedido al salir de la cola
void atenderPedidoCocina(TpPedido &frente, TpPedido &listaActivos) {
    if(frente == NULL) {
        cout << ">> La cola de cocina esta vacia.\n";
        return;
    }

    // Sacamos el nodo del frente de la cola
    TpPedido aux = frente;
    frente = frente->sig;
    aux->sig = NULL;

    // Se cambio delete aux por insercion en listaActivos (antes se perdia el pedido)
    aux->estado = "En preparacion";
    if(listaActivos == NULL) {
        listaActivos = aux;
    } else {
        TpPedido p = listaActivos;
        while(p->sig != NULL) p = p->sig;
        p->sig = aux;
    }

    cout << ">> Pedido #" << aux->id << " esta siendo preparado. Mesa #" << aux->idMesa << "\n";
}

// Se mantiene igual, solo se actualizo el encabezado del mensaje
void mostrarColaCocina(TpPedido frente) {
    TpPedido p = frente;
    cout << "\n--- COLA DE PEDIDOS EN COCINA (FIFO) ---\n";
    if(p == NULL) {
        cout << "No hay pedidos pendientes.\n";
        return;
    }
    while(p != NULL) {
        cout << "Pedido #" << p->id << " | Mesa #" << p->idMesa
             << " | Estado: " << p->estado << "\n";
        p = p->sig;
    }
}

// Se agrego: marca el pedido como Entregado y libera la mesa (Regla N.9)
// Se corrigio: ahora recibe listaMesas para llamar cambiarEstadoMesa() correctamente
// Se cambio void por bool: retorna true si encontro el pedido, false si no
bool marcarEntregado(TpPedido listaActivos, int idPedido, TpMesa listaMesas) {
    TpPedido p = listaActivos;
    while(p != NULL) {
        if(p->id == idPedido) {
            p->estado = "Entregado";
            cambiarEstadoMesa(listaMesas, p->idMesa, "Libre");
            cout << ">> Pedido #" << idPedido << " entregado. Mesa #"
                 << p->idMesa << " liberada.\n";
            return true; // Se encontro y se proceso correctamente
        }
        p = p->sig;
    }
    cout << ">> No se encontro el pedido #" << idPedido << " en pedidos activos.\n";
    return false; // No se encontro el pedido
}

// Se agrego: cancela un pedido con motivo obligatorio si ya esta En preparacion (Regla N.6)
bool cancelarPedido(TpPedido &frente, TpPedido &listaActivos, int idPedido) {
    // Buscar primero en la cola (estado Recibido)
    TpPedido p = frente, ant = NULL;
    while(p != NULL) {
        if(p->id == idPedido) {
            p->estado = "Cancelado";
            // No requiere motivo si aun esta en cola
            if(ant == NULL) frente = p->sig;
            else ant->sig = p->sig;
            cout << ">> Pedido #" << idPedido << " cancelado.\n";
            return true; // Se encontro en la cola
        }
        ant = p;
        p = p->sig;
    }
    // Buscar en lista activa (estado En preparacion - requiere motivo)
    p = listaActivos; ant = NULL;
    while(p != NULL) {
        if(p->id == idPedido) {
            // Regla N.6: motivo obligatorio si ya estaba en preparacion
            string motivo;
            cout << ">> El pedido ya esta En preparacion. Ingrese motivo de cancelacion: ";
            cin.ignore();
            getline(cin, motivo);
            p->estado = "Cancelado";
            cout << ">> Pedido #" << idPedido << " cancelado. Motivo: " << motivo << "\n";
            return true; // Se encontro en lista activa
        }
        ant = p;
        p = p->sig;
    }
    cout << ">> No se encontro el pedido #" << idPedido << "\n";
    return false; // No se encontro
}

// Se elimino despacharDelivery() porque se elimino el modulo Delivery

// Se agrego: muestra la lista de pedidos activos (En preparacion, Listo, etc.)
void mostrarPedidosActivos(TpPedido listaActivos) {
    TpPedido p = listaActivos;
    cout << "\n--- PEDIDOS EN PREPARACION ---\n";
    if(p == NULL) {
        cout << "No hay pedidos en preparacion.\n";
        return;
    }
    while(p != NULL) {
        cout << "Pedido #" << p->id << " | Mesa #" << p->idMesa
             << " | Estado: " << p->estado << "\n";
        p = p->sig;
    }
}

void guardarPedidos(TpPedido pila){
    ofstream archivo("Pedido.txt");
    TpPedido p = pila;
    while(p != NULL){
        archivo << p->id << ";" << p->idMesa << ";" << p->estado << ";" 
                << p->subtotal << ";" << p->igv << ";" << p->total << endl;
        p = p->sig;
    }
    archivo.close();
}

TpPedido cargarPedidos(TpPedido frente, TpPedido &final){
    ifstream archivo("Pedido.txt");
    if(!archivo.is_open()) return frente;
    string linea;
    while(getline(archivo, linea)){
        stringstream ss(linea);
        string sid, sidMesa, sestado, ssubtotal, sigv, stotal;
        getline(ss, sid, ';'); getline(ss, sidMesa, ';'); getline(ss, sestado, ';');
        getline(ss, ssubtotal, ';'); getline(ss, sigv, ';'); getline(ss, stotal);

        // Reconstruimos el pedido con las reglas nuevas
        encolarPedido(frente, final, stoi(sid), stoi(sidMesa), stof(ssubtotal));
        
        // Pisamos los datos de estado para recuperarlos exactamente como estaban
        final->estado = sestado;
        final->igv = stof(sigv);
        final->total = stof(stotal);
    }
    archivo.close();
    return frente;
}

