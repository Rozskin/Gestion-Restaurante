#include <iostream>
#include <string>
#include <sstream>
#include "Definiciones.h"
#include "Usuario.h"
#include "Producto.h"
#include "Mesa.h"
#include "Reserva.h"
#include "Historial.h"
#include "Pedido.h"
#include "ColaEspera.h"

using namespace std;

int main() {
    // 1. Inicializacion de todas las estructuras de datos (Punteros a NULL)
    TpUsuario listaUsuarios = NULL;
    TpProducto listaProductos = NULL;
    TpMesa listaMesas = NULL;
    TpReserva listaReservas = NULL;

    // Pila para el historial (LIFO)
    TpHistorial pilaAcciones = NULL;

    // Cola para la cocina (FIFO)
    TpPedido frenteCocina = NULL;
    TpPedido finalCocina = NULL;
    
    // Se agrego: cola de espera de clientes sin reserva (FIFO)
	TpEspera frenteEspera = NULL;
	TpEspera finalEspera = NULL;

    // Se agrego: lista de pedidos activos (los que salen de la cola y no se eliminan)
    TpPedido listaPedidosActivos = NULL;

    // 2. Carga de datos de prueba (Quemados en memoria para testing)
    // Usuarios - se elimino el usuario "fernando" tipo Cliente porque el cliente ya no inicia sesion
    listaUsuarios = registrarUsuario(listaUsuarios, 1, "admin", "admin123", "Administrador");
    listaUsuarios = registrarUsuario(listaUsuarios, 3, "diego", "qwer", "Trabajador");

    // Inventario inicial
    listaProductos = agregarProducto(listaProductos, 101, "Combo Hamburguesa Big Boss", 20, 18.50);
    listaProductos = agregarProducto(listaProductos, 102, "Pollo Frito Crujiente KFC", 15, 21.90);
    listaProductos = agregarProducto(listaProductos, 103, "Mostrito con Pollo a la Brasa", 0, 19.00); // Agotado

    // Salon (Mesas)
	// Se amplio a 8 mesas para mayor realismo
	listaMesas = agregarMesa(listaMesas, 1, 2);
	listaMesas = agregarMesa(listaMesas, 2, 4);
	listaMesas = agregarMesa(listaMesas, 3, 4);
	listaMesas = agregarMesa(listaMesas, 4, 6);
	listaMesas = agregarMesa(listaMesas, 5, 6);
	listaMesas = agregarMesa(listaMesas, 6, 8);
	listaMesas = agregarMesa(listaMesas, 7, 2);
	listaMesas = agregarMesa(listaMesas, 8, 10);

    // Contadores globales para IDs correlativos
    int idPedGlobal = 1;
    int idAccGlobal = 1;
    int idReservaActual = 1;

    // Variables de control de flujo
    int op, opSub;
    string user, pass;
    TpUsuario logueado = NULL;

    do {
        cout << "\n=========================================\n";
        cout << "   SISTEMA DE GESTION DE RESTAURANTE\n";
        cout << "=========================================\n";
        cout << "1. Iniciar Sesion (Trabajador/Administrador)\n";
        cout << "2. Ver Menu Digital (Publico)\n";
        // Se agrego opcion 3 para el Cliente (sin login, segun el informe)
        cout << "3. Solicitar Mesa / Hacer Reserva (Cliente)\n";
        cout << "4. Salir del Sistema\n";
        cout << "Opcion: ";
        cin >> op;

        switch(op) {
            case 1:
                cout << "Usuario: "; cin >> user;
                cout << "Contrasena: "; cin >> pass;

                logueado = login(listaUsuarios, user, pass);

                if(logueado != NULL) {
                    cout << "\n>> Acceso Concedido. Bienvenido, " << logueado->nombre << "!\n";

                    // MENU INTERNO - ya no necesita distinguir Cliente porque ya no inicia sesion
                    do {
                        cout << "\n--- PANEL DE OPERACIONES: " << logueado->rol << " ---\n";

                        // Se separo el menu segun rol: Trabajador ve opciones operativas, Admin ve gestion
                        if(logueado->rol == "Trabajador") {
                            cout << "1.  Ver Menu e Inventario\n";
                            cout << "2.  Modificar Inventario (Stock)\n";
                            cout << "3.  Ver Estado del Salon (Mesas)\n";
                            cout << "4.  Registrar Nueva Reserva\n";
                            cout << "5.  Ver Reservas Activas\n";
                            cout << "6.  Generar Nuevo Pedido\n";
                            cout << "7.  Ver y Procesar Cola de Cocina (FIFO)\n";
                            cout << "8.  Marcar Pedido como Entregado\n";
                            cout << "9.  Cancelar Pedido / Cancelar Reserva\n";
                            cout << "10. Atender Cola de Espera de Clientes\n";
                            cout << "0.  Cerrar Sesion\n";
                        } else if(logueado->rol == "Administrador") {
                            cout << "1.  Ver Menu e Inventario\n";
                            cout << "2.  Gestionar Platos del Menu (Agregar / Eliminar)\n";
                            cout << "3.  Modificar Inventario (Stock)\n";
                            cout << "4.  Ver Estado del Salon (Mesas)\n";
                            cout << "5.  Registrar / Cancelar Reserva\n";
                            cout << "6.  Ver Reservas Activas\n";
                            cout << "7.  Generar Nuevo Pedido\n";
                            cout << "8.  Reporte de Ventas del Turno\n";
                            cout << "9.  Plato Mas Pedido / Menos Pedido\n";
                            cout << "10. Control de Cambios: Historial y Deshacer (LIFO)\n";
                            cout << "0.  Cerrar Sesion\n";
                        }
                        cout << "Opcion: ";
                        cin >> opSub;

                        // --- LOGICA DE EJECUCION DE LAS OPCIONES ---

                        // Opciones compartidas entre Trabajador y Administrador
if(opSub == 1) {
    mostrarMenuDigital(listaProductos);
}

// --- OPCIONES EXCLUSIVAS DEL TRABAJADOR ---
else if(opSub == 2 && logueado->rol == "Trabajador") {
    int idProd, cant, accionInv;
    cout << "\n1. Descontar por Venta Directa | 2. Reabastecer Almacen: "; cin >> accionInv;
    cout << "ID Producto: "; cin >> idProd;
    cout << "Cantidad de unidades: "; cin >> cant;
    if(accionInv == 1) {
        if(verificarStock(listaProductos, idProd, cant)) {
            actualizarStock(listaProductos, idProd, cant);
            cout << ">> Stock actualizado con exito.\n";
            stringstream ss;
            ss << "Venta/Descuento de producto ID " << idProd;
            registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
        } else {
            cout << ">> ERROR: Stock insuficiente o producto No Disponible.\n";
        }
    } else if(accionInv == 2) {
        actualizarStock(listaProductos, idProd, -cant);
        cout << ">> Almacen reabastecido con exito.\n";
        stringstream ss;
        ss << "Reabastecimiento de producto ID " << idProd;
        registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
    }
}

else if(opSub == 3 && logueado->rol == "Trabajador") {
    mostrarMesas(listaMesas);
}

else if(opSub == 4 && logueado->rol == "Trabajador") {
    string f, h;
    int numP, idM;
    cout << "Fecha (DD/MM/AAAA): "; cin >> f;
    cout << "Hora (HH:MM): "; cin >> h;
    cout << "Numero de personas: "; cin >> numP;
    mostrarMesas(listaMesas);
    cout << "Seleccione ID de mesa: "; cin >> idM;
    listaReservas = crearReserva(listaReservas, listaMesas, idReservaActual, f, h, numP, idM);
    stringstream ss;
    ss << "Se registro la Reserva #" << idReservaActual;
    registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
    idReservaActual++;
}

else if(opSub == 5 && logueado->rol == "Trabajador") {
    mostrarReservas(listaReservas);
}

else if(opSub == 6 && logueado->rol == "Trabajador") {
    int idM;
    cout << "ID de Mesa del pedido: "; cin >> idM;
    mostrarMenuDigital(listaProductos);

    // Se reemplazo el subtotal manual por un bucle de seleccion de productos
    float subt = 0;
    int opProd = 1;
    while(opProd != 0) {
        int idProd, cant;
        cout << "\nID del producto a agregar (0 para terminar): "; cin >> idProd;
        if(idProd == 0) break;
        cout << "Cantidad: "; cin >> cant;

        // Buscar el producto y verificar stock
        TpProducto pProd = listaProductos;
        bool encontrado = false;
        while(pProd != NULL) {
            if(pProd->id == idProd) {
                encontrado = true;
                if(verificarStock(listaProductos, idProd, cant)) {
                    // Descontar stock automaticamente (Regla N.8)
                    actualizarStock(listaProductos, idProd, cant);
                    // Acumular subtotal con el precio del producto
                    subt += pProd->precio * cant;
                    // Incrementar contador de ventas
                    pProd->contadorVentas++;
                    cout << ">> Producto '" << pProd->nombre << "' x" << cant
                         << " agregado. Subtotal parcial: S/." << subt << "\n";
                } else {
                    cout << ">> ERROR: Stock insuficiente para '" << pProd->nombre << "'.\n";
                }
                break;
            }
            pProd = pProd->sig;
        }
        if(!encontrado) cout << ">> Producto no encontrado.\n";
    }

    if(subt > 0) {
        encolarPedido(frenteCocina, finalCocina, idPedGlobal, idM, subt);
        // Regla N.2: la mesa pasa a Ocupada al registrar un pedido activo
    	cambiarEstadoMesa(listaMesas, idM, "Ocupada");
        stringstream ss;
        ss << "Se encolo el Pedido #" << idPedGlobal;
        registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
        idPedGlobal++;
    } else {
        cout << ">> Pedido cancelado: no se agrego ningun producto.\n";
    }
}

else if(opSub == 7 && logueado->rol == "Trabajador") {
    mostrarColaCocina(frenteCocina);
    if(frenteCocina != NULL) {
        int accC;
        cout << "\n1. Atender y preparar siguiente pedido en cola | 2. Volver: "; cin >> accC;
        if(accC == 1) {
            atenderPedidoCocina(frenteCocina, listaPedidosActivos);
            registrarAccion(pilaAcciones, idAccGlobal++, "Se despacho pedido de Cocina");
            mostrarPedidosActivos(listaPedidosActivos);
        }
    }
}

else if(opSub == 8 && logueado->rol == "Trabajador") {
    int idP;
    cout << "ID del pedido a marcar como Entregado: "; cin >> idP;
    if(marcarEntregado(listaPedidosActivos, idP, listaMesas)) {
        stringstream ss;
        ss << "Pedido #" << idP << " entregado";
        registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
    }
}

else if(opSub == 9 && logueado->rol == "Trabajador") {
    int tipoCancel;
    cout << "1. Cancelar Pedido | 2. Cancelar Reserva: "; cin >> tipoCancel;
    if(tipoCancel == 1) {
        int idP;
        cout << "ID del pedido a cancelar: "; cin >> idP;
        // Se agrego condicion: solo pregunta devolucion si el pedido fue encontrado
        if(cancelarPedido(frenteCocina, listaPedidosActivos, idP)){
        	// Se agrego: devolucion de stock al cancelar un pedido
        	int devolver;
        	cout << "Desea devolver stock de productos? (1. Si | 2. No): "; cin >> devolver;
        	if(devolver == 1) {
            	mostrarMenuDigital(listaProductos);
            	int seguir = 1;
            	while(seguir != 0) {
                	int idProd, cant;
                	cout << "ID del producto a devolver al stock (0 para terminar): "; cin >> idProd;
                	if(idProd == 0) break;
                	cout << "Cantidad a devolver: "; cin >> cant;
                	// Pasamos negativo para sumar stock (mismo patron que reabastecer)
                	actualizarStock(listaProductos, idProd, -cant);
                	cout << ">> Stock devuelto correctamente.\n";
            	}
        	}
        }
    } else if(tipoCancel == 2) {
        int idR;
        cout << "ID de la reserva a cancelar: "; cin >> idR;
        listaReservas = cancelarReserva(listaReservas, listaMesas, idR);
    }
    registrarAccion(pilaAcciones, idAccGlobal++, "Cancelacion registrada");
}

// Se elimino la opcion de agregar cliente manualmente, ahora solo se atiende
else if(opSub == 10 && logueado->rol == "Trabajador") {
    mostrarColaEspera(frenteEspera);
    if(frenteEspera == NULL) {
        cout << ">> No hay clientes en espera.\n";
    } else {
        int accE;
        cout << "\n1. Atender primer cliente | 2. Volver: "; cin >> accE;
        if(accE == 1) {
            mostrarMesas(listaMesas);
            int idMesa;
            cout << "Seleccione ID de mesa para asignar a "
                 << frenteEspera->nombreCliente << ": "; cin >> idMesa;
            if(verificarMesaLibre(listaMesas, idMesa, frenteEspera->numPersonas)) {
                cambiarEstadoMesa(listaMesas, idMesa, "Ocupada");
                cout << ">> Mesa " << idMesa << " asignada a "
                     << frenteEspera->nombreCliente << ".\n";
                atenderClienteEspera(frenteEspera);
            } else {
                cout << ">> ERROR: La mesa " << idMesa
                     << " no esta disponible o no tiene capacidad suficiente.\n";
                cout << ">> El cliente permanece en la cola de espera.\n";
            }
        }
    }
}

// --- OPCIONES EXCLUSIVAS DEL ADMINISTRADOR ---
else if(opSub == 2 && logueado->rol == "Administrador") {
    int accionMenu;
    cout << "\n1. Agregar nuevo plato | 2. Eliminar plato: "; cin >> accionMenu;
    if(accionMenu == 1) {
        int idNuevo, stockNuevo;
        float precioNuevo;
        string nombreNuevo;
        cout << "ID del nuevo plato: "; cin >> idNuevo;
        cout << "Nombre del plato: "; cin.ignore(); getline(cin, nombreNuevo);
        cout << "Stock inicial: "; cin >> stockNuevo;
        cout << "Precio: S/. "; cin >> precioNuevo;
        listaProductos = agregarProducto(listaProductos, idNuevo, nombreNuevo, stockNuevo, precioNuevo);
        cout << ">> Plato agregado al menu.\n";
        stringstream ss;
        ss << "Se agrego el plato '" << nombreNuevo << "' al menu";
        registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
    } else if(accionMenu == 2) {
        int idElim;
        mostrarMenuDigital(listaProductos);
        cout << "ID del plato a eliminar: "; cin >> idElim;
        listaProductos = eliminarProducto(listaProductos, idElim);
        stringstream ss;
        ss << "Se elimino el plato ID " << idElim << " del menu";
        registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
    }
}

else if(opSub == 3 && logueado->rol == "Administrador") {
    int idProd, cant, accionInv;
    cout << "\n1. Descontar Stock | 2. Reabastecer Almacen: "; cin >> accionInv;
    cout << "ID Producto: "; cin >> idProd;
    cout << "Cantidad de unidades: "; cin >> cant;
    if(accionInv == 1) {
        if(verificarStock(listaProductos, idProd, cant)) {
            actualizarStock(listaProductos, idProd, cant);
            cout << ">> Stock actualizado con exito.\n";
            stringstream ss;
            ss << "Venta/Descuento de producto ID " << idProd;
            registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
        } else {
            cout << ">> ERROR: Stock insuficiente.\n";
        }
    } else if(accionInv == 2) {
        actualizarStock(listaProductos, idProd, -cant);
        cout << ">> Almacen reabastecido con exito.\n";
        stringstream ss;
        ss << "Reabastecimiento de producto ID " << idProd;
        registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
    }
}

else if(opSub == 4 && logueado->rol == "Administrador") {
    mostrarMesas(listaMesas);
}

else if(opSub == 5 && logueado->rol == "Administrador") {
    int tipoRes;
    cout << "1. Registrar Reserva | 2. Cancelar Reserva: "; cin >> tipoRes;
    if(tipoRes == 1) {
        string f, h;
        int numP, idM;
        cout << "Fecha (DD/MM/AAAA): "; cin >> f;
        cout << "Hora (HH:MM): "; cin >> h;
        cout << "Numero de personas: "; cin >> numP;
        mostrarMesas(listaMesas);
        cout << "Seleccione ID de mesa: "; cin >> idM;
        listaReservas = crearReserva(listaReservas, listaMesas, idReservaActual, f, h, numP, idM);
        stringstream ss;
        ss << "Se registro la Reserva #" << idReservaActual;
        registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
        idReservaActual++;
    } else if(tipoRes == 2) {
        int idR;
        mostrarReservas(listaReservas);
        cout << "ID de la reserva a cancelar: "; cin >> idR;
        listaReservas = cancelarReserva(listaReservas, listaMesas, idR);
        registrarAccion(pilaAcciones, idAccGlobal++, "Cancelacion de reserva");
    }
}

else if(opSub == 6 && logueado->rol == "Administrador") {
    mostrarReservas(listaReservas);
}

else if(opSub == 7 && logueado->rol == "Administrador") {
    int idM;
    cout << "ID de Mesa del pedido: "; cin >> idM;
    mostrarMenuDigital(listaProductos);

    // Se reemplazo el subtotal manual por un bucle de seleccion de productos
    float subt = 0;
    int opProd = 1;
    while(opProd != 0) {
        int idProd, cant;
        cout << "\nID del producto a agregar (0 para terminar): "; cin >> idProd;
        if(idProd == 0) break;
        cout << "Cantidad: "; cin >> cant;

        TpProducto pProd = listaProductos;
        bool encontrado = false;
        while(pProd != NULL) {
            if(pProd->id == idProd) {
                encontrado = true;
                if(verificarStock(listaProductos, idProd, cant)) {
                    // Descontar stock automaticamente (Regla N.8)
                    actualizarStock(listaProductos, idProd, cant);
                    subt += pProd->precio * cant;
                    pProd->contadorVentas++;
                    cout << ">> Producto '" << pProd->nombre << "' x" << cant
                         << " agregado. Subtotal parcial: S/." << subt << "\n";
                } else {
                    cout << ">> ERROR: Stock insuficiente para '" << pProd->nombre << "'.\n";
                }
                break;
            }
            pProd = pProd->sig;
        }
        if(!encontrado) cout << ">> Producto no encontrado.\n";
    }

    if(subt > 0) {
        encolarPedido(frenteCocina, finalCocina, idPedGlobal, idM, subt);
        // Regla N.2: la mesa pasa a Ocupada al registrar un pedido activo
    	cambiarEstadoMesa(listaMesas, idM, "Ocupada");
        stringstream ss;
        ss << "Se encolo el Pedido #" << idPedGlobal;
        registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
        idPedGlobal++;
    } else {
        cout << ">> Pedido cancelado: no se agrego ningun producto.\n";
    }
}

// Se agrego: reporte de ventas del turno
else if(opSub == 8 && logueado->rol == "Administrador") {
    cout << "\n--- REPORTE DE VENTAS DEL TURNO ---\n";
    TpPedido p = listaPedidosActivos;
    float totalRecaudado = 0, totalIGV = 0;
    int contPedidos = 0;
    while(p != NULL) {
        if(p->estado == "Entregado") {
            totalRecaudado += p->total;
            totalIGV += p->igv;
            contPedidos++;
            cout << "Pedido #" << p->id << " | Mesa #" << p->idMesa
                 << " | Total: S/." << p->total << "\n";
        }
        p = p->sig;
    }
    cout << "--------------------------------\n";
    cout << "Pedidos entregados: " << contPedidos << "\n";
    cout << "IGV total recaudado: S/." << totalIGV << "\n";
    cout << "TOTAL RECAUDADO: S/." << totalRecaudado << "\n";
}

// Se agrego: plato mas pedido y menos pedido
else if(opSub == 9 && logueado->rol == "Administrador") {
    TpProducto mas = platoMasPedido(listaProductos);
    TpProducto menos = platoPedido(listaProductos);
    cout << "\n--- REPORTE DE PLATOS ---\n";
    if(mas != NULL)
        cout << "Plato MAS pedido:   " << mas->nombre
             << " (" << mas->contadorVentas << " veces)\n";
    if(menos != NULL)
        cout << "Plato MENOS pedido: " << menos->nombre
             << " (" << menos->contadorVentas << " veces)\n";
}

else if(opSub == 10 && logueado->rol == "Administrador") {
    mostrarHistorial(pilaAcciones);
    if(pilaAcciones != NULL) {
        int accH;
        cout << "\n1. [DESHACER] Revertir ultima accion | 2. Volver: "; cin >> accH;
        if(accH == 1) {
            deshacerAccion(pilaAcciones);
        }
    }
}

                    } while(opSub != 0);

                    logueado = NULL; // Limpiamos la sesion al salir
                    cout << ">> Sesion cerrada.\n";
                } else {
                    cout << "\n>> ERROR: Credenciales invalidas.\n";
                }
                break;

            case 2:
                mostrarMenuDigital(listaProductos);
                break;

            // Se agrego: menu publico de Cliente sin login
            case 3: {
    			cout << "\n--- ATENCION AL CLIENTE (sin registro) ---\n";
    			cout << "1. Solicitar Mesa | 2. Hacer Reserva: ";
    			int opCliente; cin >> opCliente;
				
    			if(opCliente == 1) {
        			mostrarMesas(listaMesas);
        			// Se agrego: si no hay mesa libre, el cliente se registra en la cola
        			string nomCli;
        			int numP;
        			cout << "Hay alguna mesa libre? Si no, puede unirse a la cola de espera.\n";
        			cout << "1. Unirse a cola de espera | 2. Volver: "; 
        			int opEspera; cin >> opEspera;
        			if(opEspera == 1) {
            			cout << "Su nombre: "; cin >> nomCli;
            			cout << "Numero de personas: "; cin >> numP;
            			// Se conecto con el modulo ColaEspera
            			encolarCliente(frenteEspera, finalEspera, nomCli, numP);
        			}
    			} else if(opCliente == 2) {
        			string f, h;
        			int numP, idM;
        			cout << "Fecha (DD/MM/AAAA): "; cin >> f;
        			cout << "Hora (HH:MM): "; cin >> h;
        			cout << "Numero de personas: "; cin >> numP;
        			mostrarMesas(listaMesas);
        			cout << "Seleccione ID de mesa: "; cin >> idM;
					
        			listaReservas = crearReserva(listaReservas, listaMesas, idReservaActual, f, h, numP, idM);
        			idReservaActual++;
    			}
    			break;
			}

            case 4:
                cout << "\nFinalizando ejecucion del sistema. ¡Buen dia, Grupo 4!\n";
                break;

            default:
                cout << "Opcion incorrecta.\n";
        }
    } while(op != 4);

    return 0;
}
