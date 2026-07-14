#pragma once

#include <msclr/marshal_cppstd.h>
#include "PanelOperaciones.h"
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
	/// Summary for MenuPrincipal
	/// </summary>
	public ref class MenuPrincipal : public System::Windows::Forms::Form
	{
	private:
		TpUsuario listaUsuarios;
		TpUsuario logueado;
		TpProducto listaProductos;
		TpMesa listaMesas;
		TpPedido frenteCocina;
		TpPedido finalCocina;
		TpHistorial pilaAcciones;
		TpReserva listaReservas;

		TpEspera frenteEspera;
		TpEspera finalEspera;
		TpPedido listaPedidosActivos;

		int idReservaActual = 1;
		int idAccGlobal = 1;

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::DataGridView^ dgvMenuPublico;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ txtNombreCli;

	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ txtPersonasCli;
	private: System::Windows::Forms::Button^ btnUnirseCola;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Button^ btnReservarCli;

	private: System::Windows::Forms::TextBox^ txtMesaReservaCli;

	private: System::Windows::Forms::TextBox^ txtNumPersonas;
	private: System::Windows::Forms::DateTimePicker^ dtpHoraReservaCli;

	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::DateTimePicker^ dtpFechaReservaCli;

	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;


	private: System::Windows::Forms::Button^ btnSalir;


		   
	public:
		MenuPrincipal(void)
		{
			InitializeComponent();

			listaUsuarios = NULL;
			logueado = NULL;
			listaProductos = NULL;
			listaMesas = NULL;
			frenteCocina = NULL;
			finalCocina = NULL;
			pilaAcciones = NULL;
			listaReservas = NULL;

			frenteEspera = NULL;
			finalEspera = NULL;
			listaPedidosActivos = NULL;

			//CARGAMOS DATOS DE LOS .TXT
			pilaAcciones = cargarHistorial(pilaAcciones);

			// Truco temporal para cargarPedidos por referencia
			TpPedido tempFrente = frenteCocina;
			TpPedido tempFinal = finalCocina;
			tempFrente = cargarPedidos(tempFrente, tempFinal);
			frenteCocina = tempFrente;
			finalCocina = tempFinal;

			listaUsuarios = cargarUsuarios(listaUsuarios);
			listaProductos = cargarProductos(listaProductos);
			listaMesas = cargarMesas(listaMesas);
			listaReservas = cargarReservas(listaReservas, listaMesas);

			//Continua desde el último valor guardado
			TpReserva r = listaReservas;
			while (r != NULL) {
				if (r->id >= idReservaActual) idReservaActual = r->id + 1;
				r = r->sig;
			}

			TpHistorial h = pilaAcciones;
			while (h != NULL) {
				if (h->idAccion >= idAccGlobal) idAccGlobal = h->idAccion + 1;
				h = h->sig;
			}

			//(Solo si los .txt están vacíos)
			if (listaUsuarios == NULL) {
				listaUsuarios = registrarUsuario(listaUsuarios, 1, "admin", "admin123", "Administrador");
				listaUsuarios = registrarUsuario(listaUsuarios, 3, "diego", "qwer", "Trabajador");
			}

			if (listaProductos == NULL) {
				listaProductos = agregarProducto(listaProductos, 101, "Combo Hamburguesa Big Boss", 20, 18.50f);
				listaProductos = agregarProducto(listaProductos, 102, "Pollo Frito Crujiente KFC", 15, 21.90f);
				listaProductos = agregarProducto(listaProductos, 103, "Mostrito con Pollo a la Brasa", 0, 19.00f);
			}

			if (listaMesas == NULL) {
				listaMesas = agregarMesa(listaMesas, 1, 2);
				listaMesas = agregarMesa(listaMesas, 2, 4);
				listaMesas = agregarMesa(listaMesas, 3, 4);
				listaMesas = agregarMesa(listaMesas, 4, 6);
				listaMesas = agregarMesa(listaMesas, 5, 6);
				listaMesas = agregarMesa(listaMesas, 6, 8);
				listaMesas = agregarMesa(listaMesas, 7, 2);
				listaMesas = agregarMesa(listaMesas, 8, 10);
			}
		}
	private:
		void cargarMenuPublico() {
			dgvMenuPublico->Rows->Clear();
			dgvMenuPublico->Columns->Clear();

			dgvMenuPublico->Columns->Add("ColID", "ID");
			dgvMenuPublico->Columns->Add("ColNombre", "Plato / Combo");
			dgvMenuPublico->Columns->Add("ColPrecio", "Precio (S/.)");
			dgvMenuPublico->Columns->Add("ColStock", "Disponibilidad");

			dgvMenuPublico->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenuPublico->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenuPublico->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenuPublico->Columns[3]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			// Recorremos la lista de productos
			TpProducto p = listaProductos;
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

				dgvMenuPublico->Rows->Add(idStr, nomStr, precioStr, estadoStock);
				p = p->sig;
			}

			// Hacemos que la tabla sea de solo lectura para que los usuarios no puedan editarla
			dgvMenuPublico->ReadOnly = true;
			dgvMenuPublico->AllowUserToAddRows = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MenuPrincipal()
		{
			if (components)
			{
				delete components;
			}
		}

		//GUARDA EL TXT AL CERRAR LA VENTANA 
		virtual void OnFormClosing(System::Windows::Forms::FormClosingEventArgs^ e) override {
			guardarProductos(listaProductos);
			guardarHistorial(pilaAcciones);
			guardarPedidos(frenteCocina);
			guardarMesas(listaMesas);
			guardarReservas(listaReservas);
			guardarUsuarios(listaUsuarios);
			Form::OnFormClosing(e); // Llama al cierre normal de Windows
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txtUsuario;
	private: System::Windows::Forms::TextBox^ txtPass;


	private: System::Windows::Forms::Button^ button1;
	protected:

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtUsuario = (gcnew System::Windows::Forms::TextBox());
			this->txtPass = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->btnUnirseCola = (gcnew System::Windows::Forms::Button());
			this->txtPersonasCli = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtNombreCli = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->btnSalir = (gcnew System::Windows::Forms::Button());
			this->dgvMenuPublico = (gcnew System::Windows::Forms::DataGridView());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->btnReservarCli = (gcnew System::Windows::Forms::Button());
			this->txtMesaReservaCli = (gcnew System::Windows::Forms::TextBox());
			this->txtNumPersonas = (gcnew System::Windows::Forms::TextBox());
			this->dtpHoraReservaCli = (gcnew System::Windows::Forms::DateTimePicker());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->dtpFechaReservaCli = (gcnew System::Windows::Forms::DateTimePicker());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMenuPublico))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 41);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Usuario:";
			this->label1->Click += gcnew System::EventHandler(this, &MenuPrincipal::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(15, 84);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(64, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Contraseña:";
			this->label2->Click += gcnew System::EventHandler(this, &MenuPrincipal::label2_Click);
			// 
			// txtUsuario
			// 
			this->txtUsuario->Location = System::Drawing::Point(123, 38);
			this->txtUsuario->Name = L"txtUsuario";
			this->txtUsuario->Size = System::Drawing::Size(100, 20);
			this->txtUsuario->TabIndex = 2;
			this->txtUsuario->TextChanged += gcnew System::EventHandler(this, &MenuPrincipal::textBox1_TextChanged);
			// 
			// txtPass
			// 
			this->txtPass->Location = System::Drawing::Point(123, 81);
			this->txtPass->Name = L"txtPass";
			this->txtPass->PasswordChar = '*';
			this->txtPass->Size = System::Drawing::Size(100, 20);
			this->txtPass->TabIndex = 3;
			this->txtPass->TextChanged += gcnew System::EventHandler(this, &MenuPrincipal::txtPass_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(119, 128);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(102, 23);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Iniciar Sesión";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MenuPrincipal::button1_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->btnReservarCli);
			this->panel1->Controls->Add(this->txtMesaReservaCli);
			this->panel1->Controls->Add(this->txtNumPersonas);
			this->panel1->Controls->Add(this->dtpHoraReservaCli);
			this->panel1->Controls->Add(this->label7);
			this->panel1->Controls->Add(this->dtpFechaReservaCli);
			this->panel1->Controls->Add(this->label9);
			this->panel1->Controls->Add(this->label10);
			this->panel1->Controls->Add(this->label11);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->btnUnirseCola);
			this->panel1->Controls->Add(this->txtPersonasCli);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->txtNombreCli);
			this->panel1->Controls->Add(this->label8);
			this->panel1->Controls->Add(this->btnSalir);
			this->panel1->Controls->Add(this->txtUsuario);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->txtPass);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel1->Location = System::Drawing::Point(430, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(269, 508);
			this->panel1->TabIndex = 5;
			// 
			// btnUnirseCola
			// 
			this->btnUnirseCola->Location = System::Drawing::Point(60, 253);
			this->btnUnirseCola->Name = L"btnUnirseCola";
			this->btnUnirseCola->Size = System::Drawing::Size(146, 23);
			this->btnUnirseCola->TabIndex = 11;
			this->btnUnirseCola->Text = L"Unirse a Cola de Espera";
			this->btnUnirseCola->UseVisualStyleBackColor = true;
			this->btnUnirseCola->Click += gcnew System::EventHandler(this, &MenuPrincipal::btnUnirseCola_Click);
			// 
			// txtPersonasCli
			// 
			this->txtPersonasCli->Location = System::Drawing::Point(123, 227);
			this->txtPersonasCli->Name = L"txtPersonasCli";
			this->txtPersonasCli->Size = System::Drawing::Size(100, 20);
			this->txtPersonasCli->TabIndex = 10;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(8, 230);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(108, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Número de personas:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(8, 200);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(81, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Nombre (titular):";
			// 
			// txtNombreCli
			// 
			this->txtNombreCli->Location = System::Drawing::Point(123, 197);
			this->txtNombreCli->Name = L"txtNombreCli";
			this->txtNombreCli->Size = System::Drawing::Size(100, 20);
			this->txtNombreCli->TabIndex = 7;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(6, 166);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(121, 18);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Solicitar Mesa:";
			// 
			// btnSalir
			// 
			this->btnSalir->Location = System::Drawing::Point(11, 128);
			this->btnSalir->Name = L"btnSalir";
			this->btnSalir->Size = System::Drawing::Size(102, 23);
			this->btnSalir->TabIndex = 5;
			this->btnSalir->Text = L"Salir";
			this->btnSalir->UseVisualStyleBackColor = true;
			this->btnSalir->Click += gcnew System::EventHandler(this, &MenuPrincipal::btnSalir_Click);
			// 
			// dgvMenuPublico
			// 
			this->dgvMenuPublico->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvMenuPublico->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvMenuPublico->Location = System::Drawing::Point(0, 0);
			this->dgvMenuPublico->Name = L"dgvMenuPublico";
			this->dgvMenuPublico->Size = System::Drawing::Size(430, 508);
			this->dgvMenuPublico->TabIndex = 6;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(1, 9);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(115, 18);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Iniciar Sesión:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(3, 279);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(125, 18);
			this->label6->TabIndex = 13;
			this->label6->Text = L"Hacer Reserva:";
			// 
			// btnReservarCli
			// 
			this->btnReservarCli->Location = System::Drawing::Point(72, 446);
			this->btnReservarCli->Name = L"btnReservarCli";
			this->btnReservarCli->Size = System::Drawing::Size(113, 41);
			this->btnReservarCli->TabIndex = 22;
			this->btnReservarCli->Text = L"Registrar Reserva";
			this->btnReservarCli->UseVisualStyleBackColor = true;
			this->btnReservarCli->Click += gcnew System::EventHandler(this, &MenuPrincipal::btnReservarCli_Click);
			// 
			// txtMesaReservaCli
			// 
			this->txtMesaReservaCli->Location = System::Drawing::Point(123, 411);
			this->txtMesaReservaCli->Name = L"txtMesaReservaCli";
			this->txtMesaReservaCli->Size = System::Drawing::Size(100, 20);
			this->txtMesaReservaCli->TabIndex = 21;
			// 
			// txtNumPersonas
			// 
			this->txtNumPersonas->Location = System::Drawing::Point(123, 381);
			this->txtNumPersonas->Name = L"txtNumPersonas";
			this->txtNumPersonas->Size = System::Drawing::Size(100, 20);
			this->txtNumPersonas->TabIndex = 20;
			// 
			// dtpHoraReservaCli
			// 
			this->dtpHoraReservaCli->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->dtpHoraReservaCli->Location = System::Drawing::Point(60, 348);
			this->dtpHoraReservaCli->Name = L"dtpHoraReservaCli";
			this->dtpHoraReservaCli->ShowUpDown = true;
			this->dtpHoraReservaCli->Size = System::Drawing::Size(93, 20);
			this->dtpHoraReservaCli->TabIndex = 19;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(11, 355);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(33, 13);
			this->label7->TabIndex = 18;
			this->label7->Text = L"Hora:";
			// 
			// dtpFechaReservaCli
			// 
			this->dtpFechaReservaCli->Location = System::Drawing::Point(60, 315);
			this->dtpFechaReservaCli->Name = L"dtpFechaReservaCli";
			this->dtpFechaReservaCli->Size = System::Drawing::Size(200, 20);
			this->dtpFechaReservaCli->TabIndex = 17;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(11, 418);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(56, 13);
			this->label9->TabIndex = 16;
			this->label9->Text = L"Mesa (ID):";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(11, 388);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(84, 13);
			this->label10->TabIndex = 15;
			this->label10->Text = L"N° de Personas:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(11, 321);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(40, 13);
			this->label11->TabIndex = 14;
			this->label11->Text = L"Fecha:";
			// 
			// MenuPrincipal
			// 
			this->AcceptButton = this->button1;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(699, 508);
			this->Controls->Add(this->dgvMenuPublico);
			this->Controls->Add(this->panel1);
			this->Name = L"MenuPrincipal";
			this->Text = L"Sistema de Gestión de Restaurante";
			this->Load += gcnew System::EventHandler(this, &MenuPrincipal::MenuPrincipal_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMenuPublico))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		
		std::string userCpp = msclr::interop::marshal_as<std::string>(txtUsuario->Text);
		std::string passCpp = msclr::interop::marshal_as<std::string>(txtPass->Text);

		logueado = login(listaUsuarios, userCpp, passCpp);

		if (logueado != NULL) {
			String^ nombreBienvenida = msclr::interop::marshal_as<String^>(logueado->nombre);
			MessageBox::Show("Bienvenido, " + nombreBienvenida, "Acceso Concedido");

			this->Hide();
			PanelOperaciones^ panel = gcnew PanelOperaciones(logueado, listaUsuarios, listaProductos, listaMesas, frenteCocina, finalCocina, pilaAcciones, listaReservas, frenteEspera, finalEspera, listaPedidosActivos);
			panel->ShowDialog();
			this->Show();

			//RECARGAR DATOS DESDE LOS .TXT AL VOLVER 
			//Vaciamos la memoria vieja
			listaUsuarios = NULL; listaProductos = NULL; listaMesas = NULL;
			frenteCocina = NULL; finalCocina = NULL; pilaAcciones = NULL; listaReservas = NULL;

			//Volvemos a leer de los .txt actualizados
			pilaAcciones = cargarHistorial(pilaAcciones);
			
			//Usamos temporal para cargarPedidos por referencia
			TpPedido tempFrente = frenteCocina;
			TpPedido tempFinal = finalCocina;
			tempFrente = cargarPedidos(tempFrente, tempFinal);
			frenteCocina = tempFrente;
			finalCocina = tempFinal;

			listaUsuarios = cargarUsuarios(listaUsuarios);
			listaProductos = cargarProductos(listaProductos);
			listaMesas = cargarMesas(listaMesas);
			listaReservas = cargarReservas(listaReservas, listaMesas);

			cargarMenuPublico(); // Actualizamos la tabla visual

			txtUsuario->Clear();
			txtPass->Clear();
		}
		else {
			MessageBox::Show("Credenciales inválidas", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

	}
private: System::Void txtPass_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void MenuPrincipal_Load(System::Object^ sender, System::EventArgs^ e) {
	cargarMenuPublico();
}
private: System::Void btnSalir_Click(System::Object^ sender, System::EventArgs^ e) {
	if (MessageBox::Show("¿Desea salir completamente del sistema?", "Salir", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
		Application::Exit(); // Esto mata el proceso completo del programa
	}
}
private: System::Void btnUnirseCola_Click(System::Object^ sender, System::EventArgs^ e) {
	if (txtNombreCli->Text == "" || txtPersonasCli->Text == "") {
		MessageBox::Show("Por favor, ingrese su nombre y la cantidad de personas.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		// Convertimos los datos
		std::string nom = msclr::interop::marshal_as<std::string>(txtNombreCli->Text);
		int numP = System::Convert::ToInt32(txtPersonasCli->Text);

		if (numP <= 0 || numP > 10) {
			MessageBox::Show("El límite es de 1 a 10 personas por reserva.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		TpEspera tempFrente = frenteEspera;
		TpEspera tempFinal = finalEspera;

		// Llamamos al backend para encolar al cliente
		encolarCliente(tempFrente, tempFinal, nom, numP);

		frenteEspera = tempFrente;
		finalEspera = tempFinal;

		MessageBox::Show("¡" + txtNombreCli->Text + " añadido a la cola de espera exitosamente!\nPor favor aguarde a ser llamado por el personal.", "Cola de Espera", MessageBoxButtons::OK, MessageBoxIcon::Information);

		// Limpiamos
		txtNombreCli->Clear();
		txtPersonasCli->Clear();
	}
	catch (System::FormatException^) {
		MessageBox::Show("El número de personas debe ser un número entero.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
private: System::Void btnReservarCli_Click(System::Object^ sender, System::EventArgs^ e) {
	//Validamos que no falten datos
	if (txtNumPersonas->Text == "" || txtMesaReservaCli->Text == "") {
		MessageBox::Show("Por favor, ingrese el número de personas y la mesa que desea.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		//Extraemos los valores
		int numP = System::Convert::ToInt32(txtNumPersonas->Text);
		int idM = System::Convert::ToInt32(txtMesaReservaCli->Text);

		if (numP <= 0 || numP > 10) {
			MessageBox::Show("El límite es de 1 a 10 personas por reserva.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		//Formateamos Fecha y Hora
		String^ fechaFormateada = dtpFechaReservaCli->Value.ToString("dd/MM/yyyy");
		String^ horaFormateada = dtpHoraReservaCli->Value.ToString("HH:mm");
		std::string fechaCpp = msclr::interop::marshal_as<std::string>(fechaFormateada);
		std::string horaCpp = msclr::interop::marshal_as<std::string>(horaFormateada);

		//Validar disponibilidad de mesa
		if (verificarMesaLibre(listaMesas, idM, numP) == false) {
			MessageBox::Show("Lo sentimos, la mesa seleccionada no está libre o no tiene capacidad suficiente.", "Reserva Fallida", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		//Crear la reserva
		listaReservas = crearReserva(listaReservas, listaMesas, idReservaActual, fechaCpp, horaCpp, numP, idM);

		//Historial
		std::string desc = "Cliente (Público) registró Reserva #" + std::to_string(idReservaActual);
		TpHistorial tempHist = pilaAcciones;
		registrarAccion(tempHist, idAccGlobal, desc);
		pilaAcciones = tempHist;

		//Actualizar contadores y notificar
		idReservaActual++;
		idAccGlobal++;

		MessageBox::Show("¡Su reserva en la Mesa " + idM + " ha sido confirmada con éxito!\nLo esperamos el " + fechaFormateada + " a las " + horaFormateada + ".", "Reserva Exitosa", MessageBoxButtons::OK, MessageBoxIcon::Information);

		//Limpiar cajas
		txtPersonasCli->Clear();
		txtMesaReservaCli->Clear();
	}
	catch (System::FormatException^) {
		MessageBox::Show("El número de personas y el ID de la mesa deben ser números.", "Error de Formato", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
};
}
