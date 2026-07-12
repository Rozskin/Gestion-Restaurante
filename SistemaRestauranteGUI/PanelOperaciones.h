#pragma once

#include <msclr/marshal_cppstd.h>
#include "../Usuario.h"
#include "../Definiciones.h"
#include "../Historial.h"
#include "../Mesa.h"
#include "../Pedido.h"
#include "../Producto.h"
#include "../Reserva.h"
#include "../ColaEspera.h"

namespace SistemaRestauranteGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for PanelOperaciones
	/// </summary>
	public ref class PanelOperaciones : public System::Windows::Forms::Form
	{
	private:
		TpUsuario usrActual;
		TpUsuario lstUsr;
		TpProducto lstProd;
		TpMesa lstMesas;
		TpPedido frenteCocina;
		TpPedido finalCocina;
		TpHistorial pilaHist;
		TpReserva lstRes;

		TpEspera frenteEspera;
		TpEspera finalEspera;
		TpPedido listaPedidosActivos;

		// Contadores globales
		int idPedGlobal = 1;
		int idAccGlobal = 1;
		float subtotalTemporal = 0.0f;

	private: System::Windows::Forms::DataGridView^ dgvMenu;
	private: System::Windows::Forms::TextBox^ txtCantProd;

	private: System::Windows::Forms::TextBox^ txtIdProd;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::DataGridView^ dgvInventario;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ComboBox^ cmbAccionInv;
	private: System::Windows::Forms::Button^ btnProcesarInv;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::DataGridView^ dgvMesas;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::DataGridView^ dgvReservas;

	private: System::Windows::Forms::DateTimePicker^ dtpFecha;
	private: System::Windows::Forms::DateTimePicker^ dtpHora;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ txtIdMesa;
	private: System::Windows::Forms::TextBox^ txtNumPersonas;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Button^ btnDeshacer;
	private: System::Windows::Forms::DataGridView^ dgvHistorial;
	private: System::Windows::Forms::DataGridView^ dgvCocina;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label11;

	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label8;

	private: System::Windows::Forms::Button^ btnDespachar;

	private: System::Windows::Forms::Button^ btnAtender;
	private: System::Windows::Forms::Button^ btnEncolar;
	private: System::Windows::Forms::TextBox^ txtIdProdPed;











	private: System::Windows::Forms::TabPage^ tabPageUsuarios;
	private: System::Windows::Forms::DataGridView^ dgvUsuarios;
	private: System::Windows::Forms::TextBox^ txtIdMesaPed;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ txtIdPedidoEntregar;
	private: System::Windows::Forms::DataGridView^ dgvColaEspera;
	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Button^ btnAtenderEspera;
	private: System::Windows::Forms::TextBox^ txtMesaAsignar;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::DataGridView^ dgvActivos;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::TextBox^ txtIdCancelar;
	private: System::Windows::Forms::Button^ btnCancelarPedido;
	private: System::Windows::Forms::TextBox^ txtCantProdPed;

	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Button^ btnAgregarAlPedido;
	private: System::Windows::Forms::Label^ lblSubtotalAcumulado;
	private: System::Windows::Forms::Button^ btnCancelarReserva;
	private: System::Windows::Forms::TextBox^ txtIdReservaCancelar;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::TabPage^ tabPageReportes;
	private: System::Windows::Forms::Panel^ panel6;
	private: System::Windows::Forms::Label^ lblPlatoMas;

private: System::Windows::Forms::Label^ lblTotalRecaudado;

	private: System::Windows::Forms::Label^ lblTotalIGV;
	private: System::Windows::Forms::Label^ lblTotalVentas;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::Button^ btnGenerarReporte;
private: System::Windows::Forms::Label^ lblPlatoMenos;
private: System::Windows::Forms::Panel^ panelAdminMenu;
private: System::Windows::Forms::TextBox^ txtEliminarIdPlato;

private: System::Windows::Forms::Label^ label27;
private: System::Windows::Forms::Button^ btnEliminarPlato;

private: System::Windows::Forms::Button^ btnAgregarPlato;

private: System::Windows::Forms::Label^ label26;
private: System::Windows::Forms::TextBox^ txtNuevoPrecioPlato;

private: System::Windows::Forms::Label^ label25;
private: System::Windows::Forms::TextBox^ txtNuevoStockPlato;

private: System::Windows::Forms::Label^ label20;
private: System::Windows::Forms::TextBox^ txtNuevoIdPlato;
private: System::Windows::Forms::TextBox^ txtNuevoNomPlato;

private: System::Windows::Forms::Label^ label22;
private: System::Windows::Forms::Label^ label23;
private: System::Windows::Forms::Label^ label24;












		   int idReservaActual = 1;

	public:
		PanelOperaciones(TpUsuario usuarioLogueado, TpUsuario usuarios, TpProducto productos, TpMesa mesas, TpPedido frenteC, TpPedido finalC, TpHistorial historial, TpReserva reservas, TpEspera fEspera, TpEspera finEspera, TpPedido activos)
		{
			InitializeComponent();

			// Guardamos los datos recibidos en las variables de la clase
			usrActual = usuarioLogueado;
			lstUsr = usuarios;
			lstProd = productos;
			lstMesas = mesas;
			frenteCocina = frenteC;
			finalCocina = finalC;
			pilaHist = historial;
			lstRes = reservas;

			frenteEspera = fEspera;
			finalEspera = finEspera;
			listaPedidosActivos = activos;

			if (usrActual->rol != "Administrador") {
				tabControl1->TabPages->Remove(tabPageUsuarios);
				tabControl1->TabPages->Remove(tabPageReportes);
				panelAdminMenu->Visible = false; // Oculta el panel de agregar o quitar platos
			}
			// Lógica de roles: Ocultar pestañas si el usuario es "Cliente"
			/*if (usrActual->rol == "Cliente") {
				// Ocultamos todo menos "Menú Digital" y "Reservas"
				tabControl1->TabPages->Remove(tabPage2);
				tabControl1->TabPages->Remove(tabPage3);
				tabControl1->TabPages->Remove(tabPage5);
				tabControl1->TabPages->Remove(tabPage6);
			}*/
		}
	private:
		void cargarMenuDigital() {
			dgvMenu->Rows->Clear();
			dgvMenu->Columns->Clear();

			dgvMenu->Columns->Add("ColID", "ID");
			dgvMenu->Columns->Add("ColNombre", "Plato / Combo");
			dgvMenu->Columns->Add("ColPrecio", "Precio (S/.)");
			dgvMenu->Columns->Add("ColStock", "Disponibilidad");

			dgvMenu->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenu->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenu->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenu->Columns[3]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			TpProducto p = lstProd;
			while (p != NULL) {
				String^ idStr = p->id.ToString();
				String^ nomStr = msclr::interop::marshal_as<String^>(p->nombre);
				String^ precioStr = p->precio.ToString("F2");

				String^ estadoStock = "";
				if (p->stock == 0) {
					estadoStock = "NO DISPONIBLE";
				}
				else {
					estadoStock = "Stock: " + p->stock.ToString();
				}

				dgvMenu->Rows->Add(idStr, nomStr, precioStr, estadoStock);
				p = p->sig;
			}
		}
	private:
		void cargarInventario() {
			dgvInventario->Rows->Clear();
			dgvInventario->Columns->Clear();

			dgvInventario->Columns->Add("ColID", "ID");
			dgvInventario->Columns->Add("ColNombre", "Producto");
			dgvInventario->Columns->Add("ColStock", "Stock Actual");

			dgvInventario->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvInventario->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvInventario->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			TpProducto p = lstProd;
			while (p != NULL) {
				String^ idStr = p->id.ToString();
				String^ nomStr = msclr::interop::marshal_as<String^>(p->nombre);
				String^ stockStr = p->stock.ToString();

				dgvInventario->Rows->Add(idStr, nomStr, stockStr);
				p = p->sig;
			}
		}
	private:
		void cargarMesas() {
			//Limpiamos la tabla
			dgvMesas->Rows->Clear();
			dgvMesas->Columns->Clear();

			//Definimos las columnas
			dgvMesas->Columns->Add("ColIDMesa", "Mesa #");
			dgvMesas->Columns->Add("ColCapacidad", "Capacidad (Personas)");
			dgvMesas->Columns->Add("ColEstado", "Estado Actual");

			//Ajustamos el tamaño de las columnas
			dgvMesas->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMesas->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMesas->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			//Recorremos la lista enlazada de mesas
			TpMesa m = lstMesas;
			while (m != NULL) {
				// Convertimos a String^ para Windows Forms
				String^ idStr = m->id.ToString();
				String^ capStr = m->capacidad.ToString();
				String^ estStr = msclr::interop::marshal_as<String^>(m->estado);

				//Agregamos la fila
				dgvMesas->Rows->Add(idStr, capStr, estStr);
				m = m->sig;
			}
		}
	private:
		void cargarReservas() {
			//Limpiamos la tabla
			dgvReservas->Rows->Clear();
			dgvReservas->Columns->Clear();

			//Definimos las columnas
			dgvReservas->Columns->Add("ColID", "ID");
			dgvReservas->Columns->Add("ColFecha", "Fecha");
			dgvReservas->Columns->Add("ColHora", "Hora");
			dgvReservas->Columns->Add("ColNumP", "Personas");
			dgvReservas->Columns->Add("ColMesa", "Mesa #");

			//Ajustamos el tamaño de las columnas
			dgvReservas->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvReservas->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvReservas->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvReservas->Columns[3]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvReservas->Columns[4]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			//Recorremos la lista enlazada
			TpReserva r = lstRes;
			while (r != NULL) {
				String^ idStr = r->id.ToString();
				String^ fStr = msclr::interop::marshal_as<String^>(r->fecha);
				String^ hStr = msclr::interop::marshal_as<String^>(r->hora);
				String^ npStr = r->numPersonas.ToString();
				String^ mStr = r->idMesa.ToString();

				dgvReservas->Rows->Add(idStr, fStr, hStr, npStr, mStr);

				r = r->sig;
			}
		}
	private:
		void cargarHistorial() {
			//Limpiamos la tabla
			dgvHistorial->Rows->Clear();
			dgvHistorial->Columns->Clear();

			//Definimos las columnas
			dgvHistorial->Columns->Add("ColID", "ID Acción");
			dgvHistorial->Columns->Add("ColDesc", "Descripción del Evento");

			//Ajustamos el tamaño de las columnas
			dgvHistorial->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvHistorial->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			//Recorremos la pila
			TpHistorial h = pilaHist;
			while (h != NULL) {
				String^ idStr = h->idAccion.ToString();
				String^ descStr = msclr::interop::marshal_as<String^>(h->descripcion);

				dgvHistorial->Rows->Add(idStr, descStr);

				h = h->sig;
			}
		}
	private:
		void cargarCocina() {
			dgvCocina->Rows->Clear();
			dgvCocina->Columns->Clear();

			dgvCocina->Columns->Add("ColID", "ID");
			dgvCocina->Columns->Add("ColMesa", "Mesa #");
			dgvCocina->Columns->Add("ColEst", "Estado");
			dgvCocina->Columns->Add("ColTotal", "Total (S/.)");

			dgvCocina->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvCocina->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvCocina->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvCocina->Columns[3]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			// Recorremos la cola desde el frente
			TpPedido p = frenteCocina;
			while (p != NULL) {
				String^ idStr = p->id.ToString();
				String^ mesaStr = p->idMesa.ToString();
				String^ estStr = msclr::interop::marshal_as<String^>(p->estado);
				String^ totStr = p->total.ToString("F2"); // Muestra el total ya calculado con IGV y Envio

				dgvCocina->Rows->Add(idStr, mesaStr, estStr, totStr);
				p = p->sig;
			}
		}

	private:
		void cargarColaEspera() {
			dgvColaEspera->Rows->Clear();
			dgvColaEspera->Columns->Clear();

			dgvColaEspera->Columns->Add("ColNom", "Nombre Cliente");
			dgvColaEspera->Columns->Add("ColPer", "N° Personas");

			dgvColaEspera->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvColaEspera->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			TpEspera p = frenteEspera;
			while (p != NULL) {
				String^ nomStr = msclr::interop::marshal_as<String^>(p->nombreCliente);
				String^ perStr = p->numPersonas.ToString();

				dgvColaEspera->Rows->Add(nomStr, perStr);
				p = p->sig;
			}
		}

	private:
		void cargarPedidosActivos() {
			dgvActivos->Rows->Clear();
			dgvActivos->Columns->Clear();

			dgvActivos->Columns->Add("ColID", "ID Pedido");
			dgvActivos->Columns->Add("ColMesa", "Mesa #");
			dgvActivos->Columns->Add("ColEst", "Estado");
			dgvActivos->Columns->Add("ColTotal", "Total (S/.)");

			dgvActivos->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvActivos->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvActivos->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvActivos->Columns[3]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			// Recorremos la NUEVA lista de activos que hicieron tus compañeros
			TpPedido p = listaPedidosActivos;
			while (p != NULL) {
				String^ idStr = p->id.ToString();
				String^ mesaStr = p->idMesa.ToString();
				String^ estStr = msclr::interop::marshal_as<String^>(p->estado);
				String^ totStr = p->total.ToString("F2");

				dgvActivos->Rows->Add(idStr, mesaStr, estStr, totStr);
				p = p->sig;
			}
		}

	private:
		void cargarUsuarios() {
			dgvUsuarios->Rows->Clear();
			dgvUsuarios->Columns->Clear();

			dgvUsuarios->Columns->Add("ColID", "ID");
			dgvUsuarios->Columns->Add("ColUser", "Nombre de Usuario");
			dgvUsuarios->Columns->Add("ColRol", "Rol en el Sistema");

			dgvUsuarios->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvUsuarios->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvUsuarios->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			// Recorremos la lista de usuarios
			TpUsuario u = lstUsr;
			while (u != NULL) {
				String^ idStr = u->id.ToString();
				String^ nomStr = msclr::interop::marshal_as<String^>(u->nombre);
				String^ rolStr = msclr::interop::marshal_as<String^>(u->rol);

				dgvUsuarios->Rows->Add(idStr, nomStr, rolStr);
				u = u->sig;
			}
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PanelOperaciones()
		{
			if (components)
			{
				delete components;
			}
		}

		//GUARDA EN TXT AL CERRAR EL PANEL DE OPERACIONES
		virtual void OnFormClosing(System::Windows::Forms::FormClosingEventArgs^ e) override {
			guardarProductos(lstProd);
			guardarHistorial(pilaHist);
			guardarPedidos(frenteCocina);
			guardarMesas(lstMesas);
			guardarReservas(lstRes);
			guardarUsuarios(lstUsr);
			Form::OnFormClosing(e); // Llama al cierre normal de Windows
		}
	private: System::Windows::Forms::TabControl^ tabControl1;
	protected:

	protected:

	protected:

	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::TabPage^ tabPage4;
	private: System::Windows::Forms::TabPage^ tabPage5;
	private: System::Windows::Forms::TabPage^ tabPage6;
	private: System::Windows::Forms::TabPage^ tabPage1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->dgvMenu = (gcnew System::Windows::Forms::DataGridView());
			this->panelAdminMenu = (gcnew System::Windows::Forms::Panel());
			this->txtEliminarIdPlato = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->btnEliminarPlato = (gcnew System::Windows::Forms::Button());
			this->btnAgregarPlato = (gcnew System::Windows::Forms::Button());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->txtNuevoPrecioPlato = (gcnew System::Windows::Forms::TextBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->txtNuevoStockPlato = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->txtNuevoIdPlato = (gcnew System::Windows::Forms::TextBox());
			this->txtNuevoNomPlato = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->dgvInventario = (gcnew System::Windows::Forms::DataGridView());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->btnProcesarInv = (gcnew System::Windows::Forms::Button());
			this->txtCantProd = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtIdProd = (gcnew System::Windows::Forms::TextBox());
			this->cmbAccionInv = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->dgvMesas = (gcnew System::Windows::Forms::DataGridView());
			this->dgvColaEspera = (gcnew System::Windows::Forms::DataGridView());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->btnAtenderEspera = (gcnew System::Windows::Forms::Button());
			this->txtMesaAsignar = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->dgvReservas = (gcnew System::Windows::Forms::DataGridView());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->btnCancelarReserva = (gcnew System::Windows::Forms::Button());
			this->txtIdReservaCancelar = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->txtIdMesa = (gcnew System::Windows::Forms::TextBox());
			this->txtNumPersonas = (gcnew System::Windows::Forms::TextBox());
			this->dtpHora = (gcnew System::Windows::Forms::DateTimePicker());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->dtpFecha = (gcnew System::Windows::Forms::DateTimePicker());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->dgvCocina = (gcnew System::Windows::Forms::DataGridView());
			this->dgvActivos = (gcnew System::Windows::Forms::DataGridView());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->btnAgregarAlPedido = (gcnew System::Windows::Forms::Button());
			this->lblSubtotalAcumulado = (gcnew System::Windows::Forms::Label());
			this->txtCantProdPed = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->txtIdCancelar = (gcnew System::Windows::Forms::TextBox());
			this->btnCancelarPedido = (gcnew System::Windows::Forms::Button());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->txtIdPedidoEntregar = (gcnew System::Windows::Forms::TextBox());
			this->txtIdMesaPed = (gcnew System::Windows::Forms::TextBox());
			this->btnDespachar = (gcnew System::Windows::Forms::Button());
			this->btnAtender = (gcnew System::Windows::Forms::Button());
			this->btnEncolar = (gcnew System::Windows::Forms::Button());
			this->txtIdProdPed = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->tabPage6 = (gcnew System::Windows::Forms::TabPage());
			this->dgvHistorial = (gcnew System::Windows::Forms::DataGridView());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->btnDeshacer = (gcnew System::Windows::Forms::Button());
			this->tabPageReportes = (gcnew System::Windows::Forms::TabPage());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->lblPlatoMenos = (gcnew System::Windows::Forms::Label());
			this->lblPlatoMas = (gcnew System::Windows::Forms::Label());
			this->lblTotalRecaudado = (gcnew System::Windows::Forms::Label());
			this->lblTotalIGV = (gcnew System::Windows::Forms::Label());
			this->lblTotalVentas = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->btnGenerarReporte = (gcnew System::Windows::Forms::Button());
			this->tabPageUsuarios = (gcnew System::Windows::Forms::TabPage());
			this->dgvUsuarios = (gcnew System::Windows::Forms::DataGridView());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMenu))->BeginInit();
			this->panelAdminMenu->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvInventario))->BeginInit();
			this->panel1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMesas))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvColaEspera))->BeginInit();
			this->panel5->SuspendLayout();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvReservas))->BeginInit();
			this->panel2->SuspendLayout();
			this->tabPage5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvCocina))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvActivos))->BeginInit();
			this->panel4->SuspendLayout();
			this->tabPage6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvHistorial))->BeginInit();
			this->panel3->SuspendLayout();
			this->tabPageReportes->SuspendLayout();
			this->panel6->SuspendLayout();
			this->tabPageUsuarios->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvUsuarios))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage6);
			this->tabControl1->Controls->Add(this->tabPageReportes);
			this->tabControl1->Controls->Add(this->tabPageUsuarios);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(691, 538);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->dgvMenu);
			this->tabPage1->Controls->Add(this->panelAdminMenu);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(683, 512);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Menú Digital";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// dgvMenu
			// 
			this->dgvMenu->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvMenu->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvMenu->Location = System::Drawing::Point(3, 3);
			this->dgvMenu->Name = L"dgvMenu";
			this->dgvMenu->Size = System::Drawing::Size(404, 506);
			this->dgvMenu->TabIndex = 0;
			// 
			// panelAdminMenu
			// 
			this->panelAdminMenu->Controls->Add(this->txtEliminarIdPlato);
			this->panelAdminMenu->Controls->Add(this->label27);
			this->panelAdminMenu->Controls->Add(this->btnEliminarPlato);
			this->panelAdminMenu->Controls->Add(this->btnAgregarPlato);
			this->panelAdminMenu->Controls->Add(this->label26);
			this->panelAdminMenu->Controls->Add(this->txtNuevoPrecioPlato);
			this->panelAdminMenu->Controls->Add(this->label25);
			this->panelAdminMenu->Controls->Add(this->txtNuevoStockPlato);
			this->panelAdminMenu->Controls->Add(this->label20);
			this->panelAdminMenu->Controls->Add(this->txtNuevoIdPlato);
			this->panelAdminMenu->Controls->Add(this->txtNuevoNomPlato);
			this->panelAdminMenu->Controls->Add(this->label22);
			this->panelAdminMenu->Controls->Add(this->label23);
			this->panelAdminMenu->Controls->Add(this->label24);
			this->panelAdminMenu->Dock = System::Windows::Forms::DockStyle::Right;
			this->panelAdminMenu->Location = System::Drawing::Point(407, 3);
			this->panelAdminMenu->Name = L"panelAdminMenu";
			this->panelAdminMenu->Size = System::Drawing::Size(273, 506);
			this->panelAdminMenu->TabIndex = 1;
			// 
			// txtEliminarIdPlato
			// 
			this->txtEliminarIdPlato->Location = System::Drawing::Point(141, 291);
			this->txtEliminarIdPlato->Name = L"txtEliminarIdPlato";
			this->txtEliminarIdPlato->Size = System::Drawing::Size(100, 20);
			this->txtEliminarIdPlato->TabIndex = 39;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label27->Location = System::Drawing::Point(6, 291);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(78, 16);
			this->label27->TabIndex = 38;
			this->label27->Text = L"ID del plato:";
			// 
			// btnEliminarPlato
			// 
			this->btnEliminarPlato->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnEliminarPlato->Location = System::Drawing::Point(27, 317);
			this->btnEliminarPlato->Name = L"btnEliminarPlato";
			this->btnEliminarPlato->Size = System::Drawing::Size(110, 35);
			this->btnEliminarPlato->TabIndex = 37;
			this->btnEliminarPlato->Text = L"Eliminar Plato";
			this->btnEliminarPlato->UseVisualStyleBackColor = true;
			this->btnEliminarPlato->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnEliminarPlato_Click);
			// 
			// btnAgregarPlato
			// 
			this->btnAgregarPlato->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAgregarPlato->Location = System::Drawing::Point(27, 192);
			this->btnAgregarPlato->Name = L"btnAgregarPlato";
			this->btnAgregarPlato->Size = System::Drawing::Size(110, 35);
			this->btnAgregarPlato->TabIndex = 36;
			this->btnAgregarPlato->Text = L"Agregar Plato";
			this->btnAgregarPlato->UseVisualStyleBackColor = true;
			this->btnAgregarPlato->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnAgregarPlato_Click);
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label26->Location = System::Drawing::Point(6, 252);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(118, 18);
			this->label26->TabIndex = 35;
			this->label26->Text = L"Eliminar Plato:";
			// 
			// txtNuevoPrecioPlato
			// 
			this->txtNuevoPrecioPlato->Location = System::Drawing::Point(141, 153);
			this->txtNuevoPrecioPlato->Name = L"txtNuevoPrecioPlato";
			this->txtNuevoPrecioPlato->Size = System::Drawing::Size(100, 20);
			this->txtNuevoPrecioPlato->TabIndex = 34;
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label25->Location = System::Drawing::Point(6, 153);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(49, 16);
			this->label25->TabIndex = 33;
			this->label25->Text = L"Precio:";
			// 
			// txtNuevoStockPlato
			// 
			this->txtNuevoStockPlato->Location = System::Drawing::Point(141, 117);
			this->txtNuevoStockPlato->Name = L"txtNuevoStockPlato";
			this->txtNuevoStockPlato->Size = System::Drawing::Size(100, 20);
			this->txtNuevoStockPlato->TabIndex = 32;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->Location = System::Drawing::Point(6, 117);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(81, 16);
			this->label20->TabIndex = 31;
			this->label20->Text = L"Stock Inicial:";
			// 
			// txtNuevoIdPlato
			// 
			this->txtNuevoIdPlato->Location = System::Drawing::Point(141, 46);
			this->txtNuevoIdPlato->Name = L"txtNuevoIdPlato";
			this->txtNuevoIdPlato->Size = System::Drawing::Size(100, 20);
			this->txtNuevoIdPlato->TabIndex = 30;
			// 
			// txtNuevoNomPlato
			// 
			this->txtNuevoNomPlato->Location = System::Drawing::Point(141, 82);
			this->txtNuevoNomPlato->Name = L"txtNuevoNomPlato";
			this->txtNuevoNomPlato->Size = System::Drawing::Size(100, 20);
			this->txtNuevoNomPlato->TabIndex = 29;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->Location = System::Drawing::Point(6, 82);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(115, 16);
			this->label22->TabIndex = 28;
			this->label22->Text = L"Nombre del Plato:";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label23->Location = System::Drawing::Point(6, 47);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(118, 16);
			this->label23->TabIndex = 27;
			this->label23->Text = L"ID del nuevo plato:";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label24->Location = System::Drawing::Point(6, 15);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(115, 18);
			this->label24->TabIndex = 26;
			this->label24->Text = L"Agregar Plato:";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->dgvInventario);
			this->tabPage2->Controls->Add(this->panel1);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(683, 512);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Inventario";
			this->tabPage2->UseVisualStyleBackColor = true;
			this->tabPage2->Click += gcnew System::EventHandler(this, &PanelOperaciones::tabPage2_Click);
			// 
			// dgvInventario
			// 
			this->dgvInventario->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvInventario->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvInventario->Location = System::Drawing::Point(3, 3);
			this->dgvInventario->Name = L"dgvInventario";
			this->dgvInventario->Size = System::Drawing::Size(446, 506);
			this->dgvInventario->TabIndex = 4;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->btnProcesarInv);
			this->panel1->Controls->Add(this->txtCantProd);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->txtIdProd);
			this->panel1->Controls->Add(this->cmbAccionInv);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel1->Location = System::Drawing::Point(449, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(231, 506);
			this->panel1->TabIndex = 8;
			// 
			// btnProcesarInv
			// 
			this->btnProcesarInv->Location = System::Drawing::Point(122, 126);
			this->btnProcesarInv->Name = L"btnProcesarInv";
			this->btnProcesarInv->Size = System::Drawing::Size(75, 23);
			this->btnProcesarInv->TabIndex = 7;
			this->btnProcesarInv->Text = L"Procesar";
			this->btnProcesarInv->UseVisualStyleBackColor = true;
			this->btnProcesarInv->Click += gcnew System::EventHandler(this, &PanelOperaciones::button2_Click);
			// 
			// txtCantProd
			// 
			this->txtCantProd->Location = System::Drawing::Point(122, 48);
			this->txtCantProd->Name = L"txtCantProd";
			this->txtCantProd->Size = System::Drawing::Size(100, 20);
			this->txtCantProd->TabIndex = 1;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(75, 88);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(43, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Acción:";
			// 
			// txtIdProd
			// 
			this->txtIdProd->Location = System::Drawing::Point(122, 12);
			this->txtIdProd->Name = L"txtIdProd";
			this->txtIdProd->Size = System::Drawing::Size(100, 20);
			this->txtIdProd->TabIndex = 0;
			// 
			// cmbAccionInv
			// 
			this->cmbAccionInv->FormattingEnabled = true;
			this->cmbAccionInv->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Descontar por Venta", L"Reabastecer" });
			this->cmbAccionInv->Location = System::Drawing::Point(122, 85);
			this->cmbAccionInv->Name = L"cmbAccionInv";
			this->cmbAccionInv->Size = System::Drawing::Size(100, 21);
			this->cmbAccionInv->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(49, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(67, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"ID Producto:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(5, 51);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(113, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Cantidad de unidades:";
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->dgvMesas);
			this->tabPage3->Controls->Add(this->dgvColaEspera);
			this->tabPage3->Controls->Add(this->panel5);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(683, 512);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Salón (Mesas)";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// dgvMesas
			// 
			this->dgvMesas->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvMesas->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvMesas->Location = System::Drawing::Point(3, 3);
			this->dgvMesas->Name = L"dgvMesas";
			this->dgvMesas->Size = System::Drawing::Size(477, 302);
			this->dgvMesas->TabIndex = 0;
			// 
			// dgvColaEspera
			// 
			this->dgvColaEspera->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvColaEspera->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->dgvColaEspera->Location = System::Drawing::Point(3, 305);
			this->dgvColaEspera->Name = L"dgvColaEspera";
			this->dgvColaEspera->Size = System::Drawing::Size(477, 204);
			this->dgvColaEspera->TabIndex = 1;
			// 
			// panel5
			// 
			this->panel5->Controls->Add(this->btnAtenderEspera);
			this->panel5->Controls->Add(this->txtMesaAsignar);
			this->panel5->Controls->Add(this->label13);
			this->panel5->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel5->Location = System::Drawing::Point(480, 3);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(200, 506);
			this->panel5->TabIndex = 2;
			// 
			// btnAtenderEspera
			// 
			this->btnAtenderEspera->Location = System::Drawing::Point(46, 85);
			this->btnAtenderEspera->Name = L"btnAtenderEspera";
			this->btnAtenderEspera->Size = System::Drawing::Size(113, 41);
			this->btnAtenderEspera->TabIndex = 10;
			this->btnAtenderEspera->Text = L"Asignar Mesa y Atender";
			this->btnAtenderEspera->UseVisualStyleBackColor = true;
			this->btnAtenderEspera->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnAtenderEspera_Click);
			// 
			// txtMesaAsignar
			// 
			this->txtMesaAsignar->Location = System::Drawing::Point(90, 43);
			this->txtMesaAsignar->Name = L"txtMesaAsignar";
			this->txtMesaAsignar->Size = System::Drawing::Size(100, 20);
			this->txtMesaAsignar->TabIndex = 8;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(6, 46);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(78, 13);
			this->label13->TabIndex = 3;
			this->label13->Text = L"Mesa a Enviar:";
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->dgvReservas);
			this->tabPage4->Controls->Add(this->panel2);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(683, 512);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Reservas";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// dgvReservas
			// 
			this->dgvReservas->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvReservas->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvReservas->Location = System::Drawing::Point(3, 3);
			this->dgvReservas->Name = L"dgvReservas";
			this->dgvReservas->Size = System::Drawing::Size(404, 506);
			this->dgvReservas->TabIndex = 0;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->btnCancelarReserva);
			this->panel2->Controls->Add(this->txtIdReservaCancelar);
			this->panel2->Controls->Add(this->label19);
			this->panel2->Controls->Add(this->label18);
			this->panel2->Controls->Add(this->button2);
			this->panel2->Controls->Add(this->txtIdMesa);
			this->panel2->Controls->Add(this->txtNumPersonas);
			this->panel2->Controls->Add(this->dtpHora);
			this->panel2->Controls->Add(this->label5);
			this->panel2->Controls->Add(this->dtpFecha);
			this->panel2->Controls->Add(this->label7);
			this->panel2->Controls->Add(this->label6);
			this->panel2->Controls->Add(this->label4);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel2->Location = System::Drawing::Point(407, 3);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(273, 506);
			this->panel2->TabIndex = 1;
			// 
			// btnCancelarReserva
			// 
			this->btnCancelarReserva->Location = System::Drawing::Point(68, 279);
			this->btnCancelarReserva->Name = L"btnCancelarReserva";
			this->btnCancelarReserva->Size = System::Drawing::Size(113, 41);
			this->btnCancelarReserva->TabIndex = 13;
			this->btnCancelarReserva->Text = L"Cancelar Reserva";
			this->btnCancelarReserva->UseVisualStyleBackColor = true;
			this->btnCancelarReserva->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnCancelarReserva_Click);
			// 
			// txtIdReservaCancelar
			// 
			this->txtIdReservaCancelar->Location = System::Drawing::Point(131, 243);
			this->txtIdReservaCancelar->Name = L"txtIdReservaCancelar";
			this->txtIdReservaCancelar->Size = System::Drawing::Size(100, 20);
			this->txtIdReservaCancelar->TabIndex = 12;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(19, 246);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(75, 13);
			this->label19->TabIndex = 11;
			this->label19->Text = L"ID a Cancelar:";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label18->Location = System::Drawing::Point(6, 215);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(147, 18);
			this->label18->TabIndex = 10;
			this->label18->Text = L"Cancelar Reserva:";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(68, 150);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(113, 41);
			this->button2->TabIndex = 9;
			this->button2->Text = L"Registrar Reserva";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &PanelOperaciones::button2_Click_1);
			// 
			// txtIdMesa
			// 
			this->txtIdMesa->Location = System::Drawing::Point(131, 109);
			this->txtIdMesa->Name = L"txtIdMesa";
			this->txtIdMesa->Size = System::Drawing::Size(100, 20);
			this->txtIdMesa->TabIndex = 8;
			// 
			// txtNumPersonas
			// 
			this->txtNumPersonas->Location = System::Drawing::Point(131, 79);
			this->txtNumPersonas->Name = L"txtNumPersonas";
			this->txtNumPersonas->Size = System::Drawing::Size(100, 20);
			this->txtNumPersonas->TabIndex = 7;
			// 
			// dtpHora
			// 
			this->dtpHora->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->dtpHora->Location = System::Drawing::Point(68, 46);
			this->dtpHora->Name = L"dtpHora";
			this->dtpHora->ShowUpDown = true;
			this->dtpHora->Size = System::Drawing::Size(93, 20);
			this->dtpHora->TabIndex = 6;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(19, 53);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(33, 13);
			this->label5->TabIndex = 5;
			this->label5->Text = L"Hora:";
			// 
			// dtpFecha
			// 
			this->dtpFecha->Location = System::Drawing::Point(68, 13);
			this->dtpFecha->Name = L"dtpFecha";
			this->dtpFecha->Size = System::Drawing::Size(200, 20);
			this->dtpFecha->TabIndex = 4;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(19, 116);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(56, 13);
			this->label7->TabIndex = 3;
			this->label7->Text = L"Mesa (ID):";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(19, 86);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(84, 13);
			this->label6->TabIndex = 2;
			this->label6->Text = L"N° de Personas:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(19, 19);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(40, 13);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Fecha:";
			// 
			// tabPage5
			// 
			this->tabPage5->Controls->Add(this->dgvCocina);
			this->tabPage5->Controls->Add(this->dgvActivos);
			this->tabPage5->Controls->Add(this->panel4);
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(683, 512);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"Pedidos y Cocina";
			this->tabPage5->UseVisualStyleBackColor = true;
			// 
			// dgvCocina
			// 
			this->dgvCocina->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvCocina->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvCocina->Location = System::Drawing::Point(3, 3);
			this->dgvCocina->Name = L"dgvCocina";
			this->dgvCocina->Size = System::Drawing::Size(418, 273);
			this->dgvCocina->TabIndex = 0;
			// 
			// dgvActivos
			// 
			this->dgvActivos->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvActivos->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->dgvActivos->Location = System::Drawing::Point(3, 276);
			this->dgvActivos->Name = L"dgvActivos";
			this->dgvActivos->Size = System::Drawing::Size(418, 233);
			this->dgvActivos->TabIndex = 2;
			// 
			// panel4
			// 
			this->panel4->Controls->Add(this->btnAgregarAlPedido);
			this->panel4->Controls->Add(this->lblSubtotalAcumulado);
			this->panel4->Controls->Add(this->txtCantProdPed);
			this->panel4->Controls->Add(this->label17);
			this->panel4->Controls->Add(this->label15);
			this->panel4->Controls->Add(this->label16);
			this->panel4->Controls->Add(this->txtIdCancelar);
			this->panel4->Controls->Add(this->btnCancelarPedido);
			this->panel4->Controls->Add(this->label14);
			this->panel4->Controls->Add(this->label10);
			this->panel4->Controls->Add(this->txtIdPedidoEntregar);
			this->panel4->Controls->Add(this->txtIdMesaPed);
			this->panel4->Controls->Add(this->btnDespachar);
			this->panel4->Controls->Add(this->btnAtender);
			this->panel4->Controls->Add(this->btnEncolar);
			this->panel4->Controls->Add(this->txtIdProdPed);
			this->panel4->Controls->Add(this->label12);
			this->panel4->Controls->Add(this->label11);
			this->panel4->Controls->Add(this->label9);
			this->panel4->Controls->Add(this->label8);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel4->Location = System::Drawing::Point(421, 3);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(259, 506);
			this->panel4->TabIndex = 1;
			// 
			// btnAgregarAlPedido
			// 
			this->btnAgregarAlPedido->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnAgregarAlPedido->Location = System::Drawing::Point(14, 176);
			this->btnAgregarAlPedido->Name = L"btnAgregarAlPedido";
			this->btnAgregarAlPedido->Size = System::Drawing::Size(110, 35);
			this->btnAgregarAlPedido->TabIndex = 27;
			this->btnAgregarAlPedido->Text = L"Agregar Plato";
			this->btnAgregarAlPedido->UseVisualStyleBackColor = true;
			this->btnAgregarAlPedido->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnAgregarAlPedido_Click);
			// 
			// lblSubtotalAcumulado
			// 
			this->lblSubtotalAcumulado->AutoSize = true;
			this->lblSubtotalAcumulado->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblSubtotalAcumulado->Location = System::Drawing::Point(6, 148);
			this->lblSubtotalAcumulado->Name = L"lblSubtotalAcumulado";
			this->lblSubtotalAcumulado->Size = System::Drawing::Size(105, 16);
			this->lblSubtotalAcumulado->TabIndex = 26;
			this->lblSubtotalAcumulado->Text = L"Subtotal: S/. 0.00";
			// 
			// txtCantProdPed
			// 
			this->txtCantProdPed->Location = System::Drawing::Point(115, 114);
			this->txtCantProdPed->Name = L"txtCantProdPed";
			this->txtCantProdPed->Size = System::Drawing::Size(100, 20);
			this->txtCantProdPed->TabIndex = 25;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(6, 114);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(64, 16);
			this->label17->TabIndex = 24;
			this->label17->Text = L"Cantidad:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(5, 214);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(137, 18);
			this->label15->TabIndex = 23;
			this->label15->Text = L"Cancelar Pedido:";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(5, 247);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(135, 16);
			this->label16->TabIndex = 22;
			this->label16->Text = L"ID pedido a cancelar:";
			// 
			// txtIdCancelar
			// 
			this->txtIdCancelar->Location = System::Drawing::Point(153, 246);
			this->txtIdCancelar->Name = L"txtIdCancelar";
			this->txtIdCancelar->Size = System::Drawing::Size(100, 20);
			this->txtIdCancelar->TabIndex = 21;
			// 
			// btnCancelarPedido
			// 
			this->btnCancelarPedido->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnCancelarPedido->Location = System::Drawing::Point(42, 277);
			this->btnCancelarPedido->Name = L"btnCancelarPedido";
			this->btnCancelarPedido->Size = System::Drawing::Size(132, 23);
			this->btnCancelarPedido->TabIndex = 20;
			this->btnCancelarPedido->Text = L"Cancelar Pedido";
			this->btnCancelarPedido->UseVisualStyleBackColor = true;
			this->btnCancelarPedido->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnCancelarPedido_Click);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(5, 388);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(134, 18);
			this->label14->TabIndex = 19;
			this->label14->Text = L"Entregar Pedido:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(5, 421);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(133, 16);
			this->label10->TabIndex = 18;
			this->label10->Text = L"ID pedido a entregar:";
			// 
			// txtIdPedidoEntregar
			// 
			this->txtIdPedidoEntregar->Location = System::Drawing::Point(153, 420);
			this->txtIdPedidoEntregar->Name = L"txtIdPedidoEntregar";
			this->txtIdPedidoEntregar->Size = System::Drawing::Size(100, 20);
			this->txtIdPedidoEntregar->TabIndex = 17;
			// 
			// txtIdMesaPed
			// 
			this->txtIdMesaPed->Location = System::Drawing::Point(115, 43);
			this->txtIdMesaPed->Name = L"txtIdMesaPed";
			this->txtIdMesaPed->Size = System::Drawing::Size(100, 20);
			this->txtIdMesaPed->TabIndex = 16;
			// 
			// btnDespachar
			// 
			this->btnDespachar->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDespachar->Location = System::Drawing::Point(42, 459);
			this->btnDespachar->Name = L"btnDespachar";
			this->btnDespachar->Size = System::Drawing::Size(172, 27);
			this->btnDespachar->TabIndex = 11;
			this->btnDespachar->Text = L"Marcar como entregado";
			this->btnDespachar->UseVisualStyleBackColor = true;
			this->btnDespachar->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnDespachar_Click);
			// 
			// btnAtender
			// 
			this->btnAtender->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAtender->Location = System::Drawing::Point(8, 346);
			this->btnAtender->Name = L"btnAtender";
			this->btnAtender->Size = System::Drawing::Size(129, 29);
			this->btnAtender->TabIndex = 10;
			this->btnAtender->Text = L"Atender Siguiente";
			this->btnAtender->UseVisualStyleBackColor = true;
			this->btnAtender->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnAtender_Click);
			// 
			// btnEncolar
			// 
			this->btnEncolar->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnEncolar->Location = System::Drawing::Point(128, 176);
			this->btnEncolar->Name = L"btnEncolar";
			this->btnEncolar->Size = System::Drawing::Size(110, 35);
			this->btnEncolar->TabIndex = 10;
			this->btnEncolar->Text = L"Encolar Pedido";
			this->btnEncolar->UseVisualStyleBackColor = true;
			this->btnEncolar->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnEncolar_Click);
			// 
			// txtIdProdPed
			// 
			this->txtIdProdPed->Location = System::Drawing::Point(115, 79);
			this->txtIdProdPed->Name = L"txtIdProdPed";
			this->txtIdProdPed->Size = System::Drawing::Size(100, 20);
			this->txtIdProdPed->TabIndex = 8;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(6, 79);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(78, 16);
			this->label12->TabIndex = 4;
			this->label12->Text = L"ID del plato:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(6, 44);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(68, 16);
			this->label11->TabIndex = 3;
			this->label11->Text = L"Mesa (ID):";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(5, 314);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(213, 18);
			this->label9->TabIndex = 1;
			this->label9->Text = L"Atención en Cocina: (FIFO)";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(6, 12);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(118, 18);
			this->label8->TabIndex = 0;
			this->label8->Text = L"Nuevo Pedido:";
			// 
			// tabPage6
			// 
			this->tabPage6->Controls->Add(this->dgvHistorial);
			this->tabPage6->Controls->Add(this->panel3);
			this->tabPage6->Location = System::Drawing::Point(4, 22);
			this->tabPage6->Name = L"tabPage6";
			this->tabPage6->Padding = System::Windows::Forms::Padding(3);
			this->tabPage6->Size = System::Drawing::Size(683, 512);
			this->tabPage6->TabIndex = 5;
			this->tabPage6->Text = L"Historial";
			this->tabPage6->UseVisualStyleBackColor = true;
			// 
			// dgvHistorial
			// 
			this->dgvHistorial->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvHistorial->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvHistorial->Location = System::Drawing::Point(3, 3);
			this->dgvHistorial->Name = L"dgvHistorial";
			this->dgvHistorial->Size = System::Drawing::Size(514, 506);
			this->dgvHistorial->TabIndex = 0;
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->btnDeshacer);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel3->Location = System::Drawing::Point(517, 3);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(163, 506);
			this->panel3->TabIndex = 1;
			// 
			// btnDeshacer
			// 
			this->btnDeshacer->Location = System::Drawing::Point(12, 14);
			this->btnDeshacer->Name = L"btnDeshacer";
			this->btnDeshacer->Size = System::Drawing::Size(144, 32);
			this->btnDeshacer->TabIndex = 0;
			this->btnDeshacer->Text = L"Deshacer Última Acción";
			this->btnDeshacer->UseVisualStyleBackColor = true;
			this->btnDeshacer->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnDeshacer_Click);
			// 
			// tabPageReportes
			// 
			this->tabPageReportes->Controls->Add(this->panel6);
			this->tabPageReportes->Location = System::Drawing::Point(4, 22);
			this->tabPageReportes->Name = L"tabPageReportes";
			this->tabPageReportes->Padding = System::Windows::Forms::Padding(3);
			this->tabPageReportes->Size = System::Drawing::Size(683, 512);
			this->tabPageReportes->TabIndex = 7;
			this->tabPageReportes->Text = L"Reportes";
			this->tabPageReportes->UseVisualStyleBackColor = true;
			// 
			// panel6
			// 
			this->panel6->Controls->Add(this->lblPlatoMenos);
			this->panel6->Controls->Add(this->lblPlatoMas);
			this->panel6->Controls->Add(this->lblTotalRecaudado);
			this->panel6->Controls->Add(this->lblTotalIGV);
			this->panel6->Controls->Add(this->lblTotalVentas);
			this->panel6->Controls->Add(this->label21);
			this->panel6->Controls->Add(this->btnGenerarReporte);
			this->panel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel6->Location = System::Drawing::Point(3, 3);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(677, 506);
			this->panel6->TabIndex = 0;
			// 
			// lblPlatoMenos
			// 
			this->lblPlatoMenos->AutoSize = true;
			this->lblPlatoMenos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPlatoMenos->Location = System::Drawing::Point(18, 160);
			this->lblPlatoMenos->Name = L"lblPlatoMenos";
			this->lblPlatoMenos->Size = System::Drawing::Size(155, 16);
			this->lblPlatoMenos->TabIndex = 8;
			this->lblPlatoMenos->Text = L"Plato MENOS Pedido: ---";
			// 
			// lblPlatoMas
			// 
			this->lblPlatoMas->AutoSize = true;
			this->lblPlatoMas->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPlatoMas->Location = System::Drawing::Point(18, 133);
			this->lblPlatoMas->Name = L"lblPlatoMas";
			this->lblPlatoMas->Size = System::Drawing::Size(135, 16);
			this->lblPlatoMas->TabIndex = 7;
			this->lblPlatoMas->Text = L"Plato MÁS Pedido: ---";
			// 
			// lblTotalRecaudado
			// 
			this->lblTotalRecaudado->AutoSize = true;
			this->lblTotalRecaudado->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblTotalRecaudado->Location = System::Drawing::Point(18, 106);
			this->lblTotalRecaudado->Name = L"lblTotalRecaudado";
			this->lblTotalRecaudado->Size = System::Drawing::Size(189, 16);
			this->lblTotalRecaudado->TabIndex = 6;
			this->lblTotalRecaudado->Text = L"TOTAL RECAUDADO: S/. 0.00";
			// 
			// lblTotalIGV
			// 
			this->lblTotalIGV->AutoSize = true;
			this->lblTotalIGV->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTotalIGV->Location = System::Drawing::Point(18, 76);
			this->lblTotalIGV->Name = L"lblTotalIGV";
			this->lblTotalIGV->Size = System::Drawing::Size(112, 16);
			this->lblTotalIGV->TabIndex = 5;
			this->lblTotalIGV->Text = L"IGV Total: S/. 0.00";
			// 
			// lblTotalVentas
			// 
			this->lblTotalVentas->AutoSize = true;
			this->lblTotalVentas->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTotalVentas->Location = System::Drawing::Point(18, 48);
			this->lblTotalVentas->Name = L"lblTotalVentas";
			this->lblTotalVentas->Size = System::Drawing::Size(144, 16);
			this->lblTotalVentas->TabIndex = 4;
			this->lblTotalVentas->Text = L"Pedidos Entregados: 0";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label21->Location = System::Drawing::Point(18, 14);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(149, 18);
			this->label21->TabIndex = 2;
			this->label21->Text = L"Reporte del Turno:";
			// 
			// btnGenerarReporte
			// 
			this->btnGenerarReporte->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnGenerarReporte->Location = System::Drawing::Point(21, 200);
			this->btnGenerarReporte->Name = L"btnGenerarReporte";
			this->btnGenerarReporte->Size = System::Drawing::Size(212, 31);
			this->btnGenerarReporte->TabIndex = 0;
			this->btnGenerarReporte->Text = L"Generar Reporte del Turno";
			this->btnGenerarReporte->UseVisualStyleBackColor = true;
			this->btnGenerarReporte->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnGenerarReporte_Click);
			// 
			// tabPageUsuarios
			// 
			this->tabPageUsuarios->Controls->Add(this->dgvUsuarios);
			this->tabPageUsuarios->Location = System::Drawing::Point(4, 22);
			this->tabPageUsuarios->Name = L"tabPageUsuarios";
			this->tabPageUsuarios->Padding = System::Windows::Forms::Padding(3);
			this->tabPageUsuarios->Size = System::Drawing::Size(683, 512);
			this->tabPageUsuarios->TabIndex = 6;
			this->tabPageUsuarios->Text = L"Usuarios";
			this->tabPageUsuarios->UseVisualStyleBackColor = true;
			// 
			// dgvUsuarios
			// 
			this->dgvUsuarios->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvUsuarios->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvUsuarios->Location = System::Drawing::Point(3, 3);
			this->dgvUsuarios->Name = L"dgvUsuarios";
			this->dgvUsuarios->Size = System::Drawing::Size(677, 506);
			this->dgvUsuarios->TabIndex = 0;
			// 
			// PanelOperaciones
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(691, 538);
			this->Controls->Add(this->tabControl1);
			this->Name = L"PanelOperaciones";
			this->Text = L"Sistema de Gestión de Restaurante";
			this->Load += gcnew System::EventHandler(this, &PanelOperaciones::PanelOperaciones_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMenu))->EndInit();
			this->panelAdminMenu->ResumeLayout(false);
			this->panelAdminMenu->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvInventario))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMesas))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvColaEspera))->EndInit();
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->tabPage4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvReservas))->EndInit();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->tabPage5->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvCocina))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvActivos))->EndInit();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->tabPage6->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvHistorial))->EndInit();
			this->panel3->ResumeLayout(false);
			this->tabPageReportes->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			this->tabPageUsuarios->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvUsuarios))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void PanelOperaciones_Load(System::Object^ sender, System::EventArgs^ e) {
		cargarMenuDigital();
		cargarInventario();
		cargarMesas();
		cargarReservas();
		cargarHistorial();
		cargarCocina();
		cargarUsuarios();
		cargarColaEspera();
		cargarPedidosActivos();
	}
	private: System::Void tabPage2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	cargarMenuDigital();
	
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	// Asegurarnos de que el usuario llenó las cajas
	if (txtIdProd->Text == "" || txtCantProd->Text == "" || cmbAccionInv->SelectedIndex == -1) {
		MessageBox::Show("Por favor complete todos los campos.", "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		// Convertir el texto de Windows Forms a números de C++
		int idProd = System::Convert::ToInt32(txtIdProd->Text);
		int cant = System::Convert::ToInt32(txtCantProd->Text);
		String^ accionSeleccionada = cmbAccionInv->SelectedItem->ToString();

		// LOGICA DE NEGOCIO
		if (accionSeleccionada == "Descontar por Venta") {
			if (verificarStock(lstProd, idProd, cant) == true) {
				actualizarStock(lstProd, idProd, cant);

				std::string desc = "Venta/Descuento de producto ID " + std::to_string(idProd);
				TpHistorial tempHist = pilaHist;
				registrarAccion(tempHist, idAccGlobal, desc);
				pilaHist = tempHist;
				idAccGlobal++;

				MessageBox::Show("Stock descontado correctamente.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Stock insuficiente o producto no encontrado.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}
		else if (accionSeleccionada == "Reabastecer") {
			// Pasamos la cantidad en negativo para que sume
			actualizarStock(lstProd, idProd, -cant);

			std::string desc = "Reabastecimiento de producto ID " + std::to_string(idProd);
			TpHistorial tempHist = pilaHist;
			registrarAccion(tempHist, idAccGlobal, desc);
			pilaHist = tempHist;
			idAccGlobal++;

			MessageBox::Show("Almacén reabastecido correctamente.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		//ACTUALIZAR LAS VISTAS
		cargarInventario();   // Refresca la tabla de inventario
		cargarMenuDigital();  // Refresca la tabla del menu publico
		cargarHistorial();

		//LIMPIAR EL FORMULARIO
		txtIdProd->Clear();
		txtCantProd->Clear();
		cmbAccionInv->SelectedIndex = -1;

	}
	catch (System::FormatException^) { // Atrapamos el error si el usuario escribe letras en vez de números
		MessageBox::Show("El ID y la Cantidad deben ser números enteros.", "Error de Formato", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

private: System::Void button2_Click_1(System::Object^ sender, System::EventArgs^ e) {
	//Validamos que las cajas de texto restantes no estén vacías
	if (txtNumPersonas->Text == "" || txtIdMesa->Text == "") {
		MessageBox::Show("Por favor complete el número de personas y el ID de la mesa.", "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		//Extraemos los valores de los controles
		int numP = System::Convert::ToInt32(txtNumPersonas->Text);
		int idM = System::Convert::ToInt32(txtIdMesa->Text);
		// Extraemos la fecha con el formato deseado (DD/MM/AAAA)
		String^ fechaFormateada = dtpFecha->Value.ToString("dd/MM/yyyy");
		// Extraemos la hora con formato (HH:MM)
		String^ horaFormateada = dtpHora->Value.ToString("HH:mm");

		// Convertimos a std::string para pasarlo a tu backend
		std::string fechaCpp = msclr::interop::marshal_as<std::string>(fechaFormateada);
		std::string horaCpp = msclr::interop::marshal_as<std::string>(horaFormateada);
		// ------------------------------------

		//Validar disponibilidad de mesa
		if (verificarMesaLibre(lstMesas, idM, numP) == false) {
			MessageBox::Show("La mesa seleccionada no está libre o no tiene capacidad suficiente.", "Error de Reserva", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		//Crear la reserva
		lstRes = crearReserva(lstRes, lstMesas, idReservaActual, fechaCpp, horaCpp, numP, idM);

		//REGISTRAR EN EL HISTORIAL
		std::string desc = "Se registro la Reserva #" + std::to_string(idReservaActual);
		TpHistorial tempHist = pilaHist;
		registrarAccion(tempHist, idAccGlobal, desc); // Llama al backend C++
		pilaHist = tempHist;

		idReservaActual++;
		idAccGlobal++;

		//ACTUALIZACION
		MessageBox::Show("Reserva confirmada con éxito. Mesa " + idM + " bloqueada.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);

		cargarReservas();
		cargarMesas();
		cargarHistorial();

		//LIMPIAR EL FORMULARIO
		txtNumPersonas->Clear();
		txtIdMesa->Clear();
		//Resetea los DateTimePickers a la fecha y hora actual
		//dtpFecha->Value = System::DateTime::Now;
		//dtpHora->Value = System::DateTime::Now;

	}
	catch (System::FormatException^) {
		MessageBox::Show("El número de personas y el ID de la mesa deben ser números.", "Error de Formato", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
private: System::Void btnDeshacer_Click(System::Object^ sender, System::EventArgs^ e) {
	//Valida que la pila no esté vacía
	if (pilaHist == NULL) {
		MessageBox::Show("No hay acciones en el registro para deshacer.", "Historial Vacío", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return;
	}

	//Extrae la descripción antes de eliminar el nodo para poder mostrarla en el mensaje
	String^ descDeshecha = msclr::interop::marshal_as<String^>(pilaHist->descripcion);

	//Pasa a una variable local, elimina el primer nodo (Pop), y regresa el resultado
	TpHistorial tempHist = pilaHist;
	deshacerAccion(tempHist); // Llama al backend C++
	pilaHist = tempHist;

	//Actualiza y avisa al usuario
	cargarHistorial();
	MessageBox::Show("Se eliminó del registro:\n" + descDeshecha, "Deshacer exitoso", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

private: System::Void btnEncolar_Click(System::Object^ sender, System::EventArgs^ e) {
	if (txtIdMesaPed->Text == "") {
		MessageBox::Show("Ingrese la Mesa destino.");
		return;
	}

	if (subtotalTemporal == 0) {
		MessageBox::Show("No ha agregado ningún producto al pedido.");
		return;
	}

	try{
		int idM = System::Convert::ToInt32(txtIdMesaPed->Text);

		TpPedido tempFrente = frenteCocina;
		TpPedido tempFinal = finalCocina;

		//Mandamos los temporales
		encolarPedido(tempFrente, tempFinal, idPedGlobal, idM, subtotalTemporal);

		frenteCocina = tempFrente;
		finalCocina = tempFinal;

		cambiarEstadoMesa(lstMesas, idM, "Ocupada");

		std::string desc = "Se encolo el Pedido #" + std::to_string(idPedGlobal);
		TpHistorial tempHist = pilaHist;
		registrarAccion(tempHist, idAccGlobal, desc);
		pilaHist = tempHist;

		idPedGlobal++;
		idAccGlobal++;

		cargarCocina();
		cargarMesas();
		cargarHistorial();

		//Limpiamos todo para el siguiente pedido
		txtIdMesaPed->Clear();
		subtotalTemporal = 0.0f;
		lblSubtotalAcumulado->Text = "Subtotal actual: S/. 0.00";

		MessageBox::Show("¡Pedido enviado a cocina exitosamente!");
	}
		catch (System::FormatException^) {
		MessageBox::Show("Ingrese un ID de mesa válido.");
	}
}
private: System::Void btnAtender_Click(System::Object^ sender, System::EventArgs^ e) {
	if (frenteCocina == NULL) {
		MessageBox::Show("La cola está vacía.");
		return;
	}

	TpPedido tempFrente = frenteCocina;
	TpPedido tempActivos = listaPedidosActivos;

	atenderPedidoCocina(tempFrente, tempActivos);

	frenteCocina = tempFrente;
	listaPedidosActivos = tempActivos;

	// Si la cola se vació, actualizamos también el puntero final
	if (frenteCocina == NULL) finalCocina = NULL;

	// Historial
	TpHistorial tempHist = pilaHist;
	registrarAccion(tempHist, idAccGlobal, "Se despacho pedido de Cocina");
	pilaHist = tempHist;
	idAccGlobal++;

	cargarCocina();
	cargarHistorial();
	cargarPedidosActivos();
}
private: System::Void btnDespachar_Click(System::Object^ sender, System::EventArgs^ e) {
	if (txtIdPedidoEntregar->Text == "") {
		MessageBox::Show("Ingrese el ID del pedido a marcar como entregado.");
		return;
	}

	try {
		int idPed = System::Convert::ToInt32(txtIdPedidoEntregar->Text);

		if (marcarEntregado(listaPedidosActivos, idPed, lstMesas)) {
			// Historial
			std::string desc = "Pedido #" + std::to_string(idPed) + " entregado";
			TpHistorial tempHist = pilaHist;
			registrarAccion(tempHist, idAccGlobal, desc);
			pilaHist = tempHist;
			idAccGlobal++;

			MessageBox::Show("Pedido entregado y mesa liberada con éxito.");

			cargarMesas(); // Actualizamos las mesas para ver que se liberó
			cargarHistorial();
			cargarPedidosActivos();
			txtIdPedidoEntregar->Clear();

		}
		else {
			MessageBox::Show("No se encontró el pedido o no está en preparación.");
		}
	}
	catch (System::FormatException^) {
		MessageBox::Show("El ID debe ser un número entero.");
	}
}

private: System::Void btnAtenderEspera_Click(System::Object^ sender, System::EventArgs^ e) {
	if (frenteEspera == NULL) {
		MessageBox::Show("No hay clientes en espera.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return;
	}

	if (txtMesaAsignar->Text == "") {
		MessageBox::Show("Ingrese el ID de la mesa que desea asignar al primer cliente.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		int idMesa = System::Convert::ToInt32(txtMesaAsignar->Text);
		int personasRequeridas = frenteEspera->numPersonas;

		//Verificamos si la mesa existe, está libre y entra la gente
		if (verificarMesaLibre(lstMesas, idMesa, personasRequeridas)) {

			//Ocupamos la mesa
			cambiarEstadoMesa(lstMesas, idMesa, "Ocupada");

			String^ nomCli = msclr::interop::marshal_as<String^>(frenteEspera->nombreCliente);

			//Lo sacamos de la cola
			TpEspera tempFrente = frenteEspera;
			atenderClienteEspera(tempFrente);
			frenteEspera = tempFrente;
			if (frenteEspera == NULL) finalEspera = NULL;

			//Registramos en el historial
			std::string desc = "Cliente asignado a la Mesa #" + std::to_string(idMesa);
			TpHistorial tempHist = pilaHist;
			registrarAccion(tempHist, idAccGlobal, desc);
			pilaHist = tempHist;
			idAccGlobal++;

			//Actualizamos el UI
			cargarMesas();
			cargarColaEspera();
			cargarHistorial();
			txtMesaAsignar->Clear();

			MessageBox::Show("Mesa " + idMesa + " asignada correctamente a " + nomCli + ".");
		}
		else {
			MessageBox::Show("La Mesa " + idMesa + " no está libre o no tiene capacidad suficiente para " + personasRequeridas + " personas.\nEl cliente permanece en la cola.", "Error de Asignación", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	catch (System::FormatException^) {
		MessageBox::Show("El ID de la mesa debe ser numérico.");
	}
}
private: System::Void btnAgregarAlPedido_Click(System::Object^ sender, System::EventArgs^ e) {
	if (txtIdProdPed->Text == "" || txtCantProdPed->Text == "") return;

	try {
		int idProd = System::Convert::ToInt32(txtIdProdPed->Text);
		int cant = System::Convert::ToInt32(txtCantProdPed->Text);

		TpProducto pProd = lstProd;
		bool encontrado = false;

		while (pProd != NULL) {
			if (pProd->id == idProd) {
				encontrado = true;
				if (verificarStock(lstProd, idProd, cant)) {
					//Descontamos stock
					actualizarStock(lstProd, idProd, cant);

					//Sumamos el dinero a nuestra memoria temporal
					subtotalTemporal += pProd->precio * cant;
					pProd->contadorVentas += cant; // Actualizamos ventas

					//Mostramos el nuevo subtotal en la pantalla
					lblSubtotalAcumulado->Text = "Subtotal actual: S/. " + subtotalTemporal.ToString("F2");

					MessageBox::Show("Producto agregado. Stock descontado.");

					//Refrescamos tablas visuales
					cargarInventario();
					cargarMenuDigital();
				}
				else {
					MessageBox::Show("Stock insuficiente para este producto.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				break;
			}
			pProd = pProd->sig;
		}

		if (!encontrado) MessageBox::Show("Producto no encontrado.");

		txtIdProdPed->Clear();
		txtCantProdPed->Clear();
	}
	catch (System::FormatException^) {
		MessageBox::Show("Ingrese números enteros válidos.");
	}
}
private: System::Void btnCancelarReserva_Click(System::Object^ sender, System::EventArgs^ e) {
	if (txtIdReservaCancelar->Text == "") {
		MessageBox::Show("Ingrese el ID de la reserva a cancelar.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		int idRes = System::Convert::ToInt32(txtIdReservaCancelar->Text);

		//Llama a la función del backend para cancelar
		lstRes = cancelarReserva(lstRes, lstMesas, idRes);

		//Registra en el historial
		std::string desc = "Cancelacion de reserva #" + std::to_string(idRes);
		TpHistorial tempHist = pilaHist;
		registrarAccion(tempHist, idAccGlobal, desc);
		pilaHist = tempHist;
		idAccGlobal++;

		// Actualiza la vista
		cargarReservas();
		cargarMesas(); // La mesa vuelve a estar libre
		cargarHistorial();
		txtIdReservaCancelar->Clear();

		MessageBox::Show("Operación completada. Revise la tabla para confirmar la cancelación.");
	}
	catch (System::FormatException^) {
		MessageBox::Show("El ID debe ser un número entero.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
private: System::Void btnCancelarPedido_Click(System::Object^ sender, System::EventArgs^ e) {
	if (txtIdCancelar->Text == "") {
		MessageBox::Show("Ingrese el ID del pedido a cancelar.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		int idPed = System::Convert::ToInt32(txtIdCancelar->Text);

		//Uso de temporales para no perder los datos
		TpPedido tempFrente = frenteCocina;
		TpPedido tempActivos = listaPedidosActivos;

		//devuelve un bool si lo encuentra
		bool encontrado = cancelarPedido(tempFrente, tempActivos, idPed);

		frenteCocina = tempFrente;
		listaPedidosActivos = tempActivos;

		if (encontrado) {
			System::Windows::Forms::DialogResult respuesta = MessageBox::Show(
				"El pedido fue cancelado exitosamente.\n\n¿Desea ir a la pestaña del inventario?",
				"Pedido Cancelado Exitosamente",
				MessageBoxButtons::YesNo,
				MessageBoxIcon::Question);
			if (respuesta == System::Windows::Forms::DialogResult::Yes) {
				tabControl1->SelectedTab = tabPage2; // Salta directo a la pestaña Inventario
			}

			// Guardamos en el historial
			std::string desc = "Cancelacion registrada del pedido #" + std::to_string(idPed);
			TpHistorial tempHist = pilaHist;
			registrarAccion(tempHist, idAccGlobal, desc);
			pilaHist = tempHist;
			idAccGlobal++;

			// Actualizamos la vista
			cargarCocina();
			cargarPedidosActivos();
			cargarHistorial();
			txtIdCancelar->Clear();
		}
		else {
			MessageBox::Show("No se encontró el pedido o ya fue entregado.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	catch (System::FormatException^) {
		MessageBox::Show("El ID debe ser un número entero.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
private: System::Void btnGenerarReporte_Click(System::Object^ sender, System::EventArgs^ e) {
	//REPORTE DE VENTAS DEL TURNO
	TpPedido p = listaPedidosActivos;
	float totalRecaudado = 0.0f;
	float totalIGV = 0.0f;
	int contPedidos = 0;

	//Recorremos buscando pedidos Entregados
	while (p != NULL) {
		if (p->estado == "Entregado") {
			totalRecaudado += p->total;
			totalIGV += p->igv;
			contPedidos++;
		}
		p = p->sig;
	}

	//Actualizamos los Labels en pantalla
	lblTotalVentas->Text = "Pedidos entregados: " + contPedidos.ToString();
	lblTotalIGV->Text = "IGV total recaudado: S/. " + totalIGV.ToString("F2");
	lblTotalRecaudado->Text = "TOTAL RECAUDADO: S/. " + totalRecaudado.ToString("F2");

	//REPORTE DE PLATOS (MAS Y MENOS PEDIDOS)
	TpProducto mas = platoMasPedido(lstProd);
	TpProducto menos = platoPedido(lstProd); //plato menos pedido

	if (mas != NULL) {
		String^ nomMas = msclr::interop::marshal_as<String^>(mas->nombre);
		lblPlatoMas->Text = "Plato MÁS pedido: " + nomMas + " (" + mas->contadorVentas.ToString() + " veces)";
	}
	else {
		lblPlatoMas->Text = "Plato MÁS pedido: Sin datos aún";
	}

	if (menos != NULL) {
		String^ nomMenos = msclr::interop::marshal_as<String^>(menos->nombre);
		lblPlatoMenos->Text = "Plato MENOS pedido: " + nomMenos + " (" + menos->contadorVentas.ToString() + " veces)";
	}
	else {
		lblPlatoMenos->Text = "Plato MENOS pedido: Sin datos aún";
	}

	MessageBox::Show("Reporte generado exitosamente con los datos actuales del turno.", "Reporte Listo", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void btnAgregarPlato_Click(System::Object^ sender, System::EventArgs^ e) {
	if (txtNuevoIdPlato->Text == "" || txtNuevoNomPlato->Text == "" || txtNuevoStockPlato->Text == "" || txtNuevoPrecioPlato->Text == "") {
		MessageBox::Show("Por favor complete todos los campos para el nuevo plato.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		int id = System::Convert::ToInt32(txtNuevoIdPlato->Text);
		int stock = System::Convert::ToInt32(txtNuevoStockPlato->Text);
		float precio = (float)System::Convert::ToDouble(txtNuevoPrecioPlato->Text);
		std::string nombre = msclr::interop::marshal_as<std::string>(txtNuevoNomPlato->Text);

		lstProd = agregarProducto(lstProd, id, nombre, stock, precio);

		//Registro en historial
		std::string desc = "Se agrego el plato '" + nombre + "' al menu";
		TpHistorial tempHist = pilaHist;
		registrarAccion(tempHist, idAccGlobal, desc);
		pilaHist = tempHist;
		idAccGlobal++;

		//Actualizamos todas las vistas relacionadas
		cargarMenuDigital();
		cargarInventario();
		cargarHistorial();

		//Limpiamos las cajas
		txtNuevoIdPlato->Clear();
		txtNuevoNomPlato->Clear();
		txtNuevoStockPlato->Clear();
		txtNuevoPrecioPlato->Clear();

		MessageBox::Show("Plato agregado exitosamente al sistema.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	catch (System::FormatException^) {
		MessageBox::Show("Asegúrese de ingresar números válidos en ID, Stock y Precio.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

private: System::Void btnEliminarPlato_Click(System::Object^ sender, System::EventArgs^ e) {
	if (txtEliminarIdPlato->Text == "") {
		MessageBox::Show("Ingrese el ID del plato a eliminar.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		int idElim = System::Convert::ToInt32(txtEliminarIdPlato->Text);

		lstProd = eliminarProducto(lstProd, idElim);

		// Registro en historial
		std::string desc = "Se elimino el plato ID " + std::to_string(idElim) + " del menu";
		TpHistorial tempHist = pilaHist;
		registrarAccion(tempHist, idAccGlobal, desc);
		pilaHist = tempHist;
		idAccGlobal++;

		// Actualizamos las vistas
		cargarMenuDigital();
		cargarInventario();
		cargarHistorial();

		txtEliminarIdPlato->Clear();

		MessageBox::Show("Comando ejecutado. Revise el Menú/Inventario para verificar la eliminación.", "Operación Completada", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	catch (System::FormatException^) {
		MessageBox::Show("El ID debe ser un número entero.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
};
}
