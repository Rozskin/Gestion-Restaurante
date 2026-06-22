#ifndef USUARIO_H
#define USUARIO_H

#include "Definiciones.h"

// Definimos el tipo de dato puntero para la lista
typedef struct nodoUsuario *TpUsuario;

struct nodoUsuario {
    int id;
    string nombre;
    string password;
    string rol; // Administrador, Trabajador, Cliente
    TpUsuario sig;
};

// Prototipos de las funciones
TpUsuario registrarUsuario(TpUsuario lista, int id, string nom, string pwd, string rol);
TpUsuario login(TpUsuario lista, string nom, string pwd);
void mostrarUsuarios(TpUsuario lista); // funcion de apoyo para el debug

#endif	
