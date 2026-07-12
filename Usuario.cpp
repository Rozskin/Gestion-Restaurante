#include "Usuario.h"
#include <fstream>
#include <sstream>

TpUsuario registrarUsuario(TpUsuario lista, int id, string nom, string pwd, string rol) {
    TpUsuario nuevo = new(struct nodoUsuario);
    nuevo->id=id;
    nuevo->nombre = nom;
    nuevo->password= pwd;
    nuevo->rol = rol;
    nuevo->sig = NULL;

    // Si la lista esta vacia, el nuevo nodo es la cabecera
    if(lista == NULL) {
        lista=nuevo;
    } else {
        // Recorremos hasta el final para enlazar
        TpUsuario p = lista;
        while(p->sig!=NULL) {
            p = p->sig;
        }
        p->sig= nuevo;
    }
    return lista;
}

TpUsuario login(TpUsuario lista, string nom, string pwd) {
    TpUsuario p = lista;
    while(p != NULL) {
        // validamos credenciales
        if(p->nombre == nom && p->password == pwd) {
            return p; // retorna el nodo del usuario encontrado
        }
        p = p->sig;
    }
    return NULL; // no se encontro nada
}

void mostrarUsuarios(TpUsuario lista) {
    TpUsuario p= lista;
    if(p==NULL){
        cout<<"La lista de usuarios esta vacia.\n";
        return;
    }
    while(p != NULL) {
        cout<<"ID: "<<p->id<<" - User: "<<p->nombre<<" - Rol: "<<p->rol<<"\n";
        p= p->sig;
    }
}

void guardarUsuarios(TpUsuario lista){
    ofstream archivo("Usuarios.txt");
    TpUsuario p = lista;
    while(p != NULL){
        archivo << p->id << ";" << p->nombre << ";" << p->password << ";" << p->rol << endl;
        p = p->sig;
    }
    archivo.close();
}

TpUsuario cargarUsuarios(TpUsuario lista){
    ifstream archivo("Usuarios.txt");
    if(!archivo.is_open()) return lista; // Previene errores si no existe el txt
    string linea;
    while(getline(archivo,linea)){
        stringstream ss(linea);
        string sid, nombre, password, rol;
        getline(ss,sid,';'); getline(ss,nombre,';'); getline(ss,password,';'); getline(ss,rol);
        lista = registrarUsuario(lista, stoi(sid), nombre, password, rol);
    }
    archivo.close();
    return lista;
}
