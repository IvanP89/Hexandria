///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/Core/programa.h
// Propósito:   Clases que constituyen al programa en sí.
// Autor:       Iván Pizarro.
//
// En este archivo se declaran los diseños de las clases que representan al
// programa propiamente dicho.
///////////////////////////////////////////////////////////////////////////////

#ifndef PROGRAMA_H
#define PROGRAMA_H

#include "bibliografia.h"
#include "personas.h"

// Declaración anticipada.
class ProgramaSombra;

// ----------------------------------------------------------------------------
// Programa: clase principal que constituye el núcleo del programa.
//
// Contiene los atributos y métodos necesarios para realizar la totalidad de
// operaciones del programa excepto manejo de eventos de la interfaz gráfica. 
// ----------------------------------------------------------------------------

class Programa {
	
protected:
	bool cambios;
	bool estan_todos_los_binarios;
	bool carga_exitosa;
	bibliotecario *cuenta_activa;
	string cuenta_admin;
	string pass_admin;
	
public:
	Programa();
	~Programa();
	// Para realizar la carga desde binarios desde determinadas clases derivadas.
	virtual void inicializar();
	// CARGAR - GUARDAR
	virtual bool comprobar_archivos() const;
	virtual bool cargar();
	virtual bool guardar();
	virtual bool get_carga_exitosa() const;
	// LOGIN
	virtual void set_cuenta_activa( bibliotecario *_activa );
	bibliotecario* get_cuenta_activa() const;
	// ATRIBUTOS PÚBLICOS
	autores_database autores;
	libros_database libros;
	socios_database socios;
	bibliotecarios_database bibliotecarios;
	// ADMINISTRACIÓN DE CONTRASEÑAS
	bool comprobar_cta_admin( const string &_cta_admin ) const;
	bool comprobar_pass_admin( const string &_pass_admin ) const;
	// REGISTRAR CAMBIOS
	bool get_cambios() const;
	bool set_cambios( const bool &_cambios );
	void set_cambios_sombra( const Programa* const _programa );
	// REGISTRAR PRÉSTAMOS Y DEVOLUCIONES
	bool prestamo_dni( const int &_DNI_socio, const int &_codigo_libro );
	bool prestamo_nro( const int &_nro_socio, const int &_codigo_libro );
	bool devolucion_dni( const int &_DNI_socio, const int &_codigo_libro );
	bool devolucion_nro( const int &_nro_socio, const int &_codigo_libro );
	// OTROS
	virtual bool es_sombra() const;
	virtual void no_instanciar() = 0;
	
};


// ----------------------------------------------------------------------------
// Singleton: clase para que sólo exista una instancia de programa
//
// El programa en sí no va a trabajar directamente con la clase Programa, en
// su lugar que va a utilizar esta clase derivada, que no necesita ser 
// instanciada sino que se debe utilizar el método obtener_instancia() que
// devuelve un puntero a la única instancia creada, o la crea si no existe.
// ----------------------------------------------------------------------------

class Singleton : public Programa {
	
private:
	/* Puntero a la única instancia principal del programa (la que accede a los
	   binarios). */
	static Singleton *instancia;
	/* Puntero a la instancia activa del programa, ya sea la principal o una
	   instancia sombra. */
	static Programa *base_activa;
	Singleton( ) { }
	
public:
	static Singleton* obtener_instancia();
	static Programa* get_base_activa();
	static Programa* set_base_activa( Programa *_activa );
	// Redefinición del método virtual puro de la clase padre "Programa".
	void no_instanciar() { }
	
};


// ----------------------------------------------------------------------------
// ProgramaSombra: clase para hacer un backup de los atributos del programa.
//
// Esta clase sirve a modo de punto de restauración del programa. De este modo,
// cuando una ventana que no es la principal necesita levantar y modificar los
// datos del programa, copia los datos de Programa a esta clase, de esta forma
// si el usuario al terminar de usar esta ventana, en lugar de aceptar cancela
// todos los cambios, el Programa principal sigue intacto y simplemente se 
// cierra la ventana; si guarda los cambios se copian los atributos. Como es
// ésta su función, ProgramaSombra no tiene métodos para acceder a los binarios.
// ----------------------------------------------------------------------------

class ProgramaSombra: public Programa {
	
public:
	ProgramaSombra( const Programa* const _programa );
	~ProgramaSombra();
	void inicializar() { }
	bool comprobar_archivos() const { return false; }
	bool cargar() { return false; }
	bool guardar() { return false; }
	bool get_carga_exitosa() const { return false; }
	void set_cuenta_activa( bibliotecario *_activa ) { }
	bool es_sombra() const { return true; }
	// Redefinición del método virtual puro de la clase padre "Programa".
	void no_instanciar() { }
	
};

#endif

