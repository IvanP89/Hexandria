///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/Core/personas.h
// Propósito:   Clases necesarias para trabajar con los objetos "personas".
// Autor:       Iván Pizarro.
//
// En este archivo se declaran los diseños de las clases que representan a
// las personas que involucra el problema a resolver. Ellas derivan de la clase
// base "persona".
///////////////////////////////////////////////////////////////////////////////

#ifndef PERSONAS_H
#define PERSONAS_H

#include <string>
#include <vector>
#include <fstream>

#include "utilidades.h"

using namespace std;


// ----------------------------------------------------------------------------
// persona: base para heredar las futuras clases que representen personas.
//
// Contiene los atributos y métodos necesarios para realizar las operaciones
// comunes a cualquier clase de persona que intervenga en el problema. De ella
// heredarán las más específicas.
// ----------------------------------------------------------------------------

class persona {

protected:
	int DNI;
	string telefono;
	string nombre;
	string apellido;
	string domicilio;
	string path_foto;
	fecha fecha_nacimiento;
	fecha fecha_ingreso;
	fecha fecha_de_alta;
	
public:
	persona( const int &_DNI = -1,
			 const string &_nombre = "",
			 const string &_apellido = "",
	         const fecha &_nacimiento = fecha::npos,
	         const string &_domicilio = "",
			 const string &_tel = "",
	         const string &_path_foto = "Img\\Resources\\no-user.png",
	         const fecha &_fecha_ingreso = fecha::get_actual() );
	~persona();
	// OBTENER ATRIBUTOS
	virtual int get_dni() const;
	virtual string get_dni_str() const;
	virtual string get_tel() const;
	virtual string get_nombre() const;
	virtual string get_apellido() const;
	virtual string get_nombre_completo() const;
	virtual string get_domicilio() const;
	virtual string get_path_foto() const;
	virtual fecha get_fecha_nac() const;
	virtual int get_edad() const;
	virtual string get_edad_str() const;
	virtual fecha get_fecha_ingreso() const;
	virtual fecha get_fecha_de_alta() const;
	virtual int get_antiguedad() const;
	virtual string get_antiguedad_str() const;
	// SETEAR ATRIBUTOS
	virtual void set_dni( const int &_dni );
	virtual void set_tel( const string &_tel );
	virtual void set_nombre( const string &_nom );
	virtual void set_apellido( const string &_ape );
	virtual void set_domicilio( const string &_dom );
	virtual void set_path_foto( const string &_path );
	virtual void set_fecha_nac( const int &_dia,
								const int &_mes,
								const int &_anyo );
	virtual void set_fecha_ingreso( const int &_dia,
									const int &_mes,
									const int &_anyo );
	virtual void set_fecha_ingreso( const fecha &_ingreso );
	
};


// ----------------------------------------------------------------------------
// prestamo: estructura para representar los préstamos a un socio.
// ----------------------------------------------------------------------------

struct prestamo {
	
	int codigo_libro;
	int nro_socio;
	fecha fecha_prestamo;
	fecha fecha_devolucion;
	bool operator<( const prestamo &_comp ) {
		
		return fecha_prestamo < _comp.fecha_prestamo;
		
	}
	
};


// ----------------------------------------------------------------------------
// socio: clase para representar a los socios de la biblioteca.
// ----------------------------------------------------------------------------

class socio: public persona {
	
private:
	// Vector con la información de los libros actualmente en pocesión del socio.
	vector<prestamo> a_devolver;
	// Cantidad total de préstamos del socio.
	int cant_prestamos;
	// Número único de socio.
	int nro_socio;
	// Contador static para obtener códigos de socios no repetidos.
	static int numeros_no_disponibles;
	// Método para obtener un nuevo número único.
	static int get_nuevo_numero();
	// Método para cargar el historial de préstamos del socio desde el binario.
	vector<prestamo> cargar_historial() const;
	// Método para guardar el último préstamo devuelto en el binario.
	bool archivar_prestamo( const int &_pos ) const;
	
public:
	socio( const int &_DNI = -1,
		   const string &_nombre = "",
		   const string &_apellido = "",
		   const fecha &_nacimiento = fecha::npos,
		   const string &_domicilio = "",
		   const string &_tel = "",
		   const string &_path_foto = "Img\\Resources\\no-user.png",
		   const fecha &_fecha_ingreso = fecha::get_actual(),
		   const int &_cant_prestamos = 0,
		   const vector<prestamo> &_a_devolver = vector<prestamo>() );
	~socio();
	// CARGAR - GUARDAR
	bool cargar( ifstream &_archi );
	bool guardar( ofstream &_archi ) const;
	// OBTENER ATRIBUTOS
	vector<prestamo> get_a_devolver() const;
	int get_cant_a_devolver() const;
	int get_a_devolver( const int &_pos ) const;
	string get_pendientes() const;
	vector<prestamo> get_historial() const;
	int get_cant_leidos() const;
	int get_leido( const int &_pos ) const;
	int get_nro_socio() const;
	string get_nro_socio_str() const;
	static int get_nros_no_disponibles();
	// SETEAR ATRIBUTOS
	void set_nro_socio();
	static void set_nros_no_disponibles( const int &_nro );
	// AGREGAR
	bool push_prestamo( const int &_cod_libro );
	// BORRAR
	bool libro_devuelto( const int &_cod_libro );
	// BUSQUEDA
	bool socio_buscado( const string &_parametro ) const;
	// SOBRECARGA DE OPERADORES
	bool operator!=( const socio &_comp ) const;
	// FUNCIONES AMIGAS
	friend bool socios_por_nombre( const socio &_comp1, const socio &_comp2 );
	friend bool socios_por_prestamos( const socio &_comp1, const socio &_comp2 );
	friend bool socios_por_fecha_alta( const socio &_comp1, const socio &_comp2 );
	friend bool socios_por_antiguedad( const socio &_comp1, const socio &_comp2 );
	
};


// -----------------------------------------------------------------------------
// save_socio: estructura para el guardado de datos de la clase socio en binario.
// -----------------------------------------------------------------------------

struct save_socio {
	
	int DNI;
	char telefono[50];
	char nombre[100];
	char apellido[100];
	char domicilio[100];
	char path_foto[260];
	fecha fecha_nacimiento;
	fecha fecha_ingreso;
	fecha fecha_de_alta;
	int cant_devolver;
	int cant_prestamos;
	prestamo a_devolver[3]; // La biblioteca presta hasta 3 libros a la vez.
	int nro_socio;
	
};

// ----------------------------------------------------------------------------
// Funciones para ordenar los socios segun diferentes criterios con std::sort
// ----------------------------------------------------------------------------

enum criterios_orden_socios { SociosPorNombre, SociosPorEdad,
							  SociosPorLecturas, SociosPorAlta,
							  SociosPorPendientes, SociosPorAntig };

bool socios_por_nombre( const socio &_comp1, const socio &_comp2 );
bool socios_por_edad( const socio &_comp1, const socio &_comp2 );
bool socios_por_lecturas( const socio &_comp1, const socio &_comp2 );
bool socios_por_fecha_alta( const socio &_comp1, const socio &_comp2 );
bool socios_por_pendientes( const socio &_comp1, const socio &_comp2 );
bool socios_por_antiguedad( const socio &_comp1, const socio &_comp2 );


// ----------------------------------------------------------------------------
// socios_database: base de datos de socios del programa.
//
// Esta clase funciona a modo de contenedor, gestiona todos los objetos "socio"
// del programa y proporciona todos los métodos necesarios para trabajar con
// ellos con el fin de lograr simplicidad en el uso del programa principal.
// ----------------------------------------------------------------------------

class socios_database {
	
private:
	// Vector de los objetos contenidos.
	vector<socio> socios;
	// Nombre del archivo donde se guardan y cargan los datos.
	string nombre_archivo;
	
public:
	socios_database( const string &_path_binario = "Data\\Socios.dat" );
	~socios_database();
	// Cargar y guardar los objetos
	bool cargar();
	bool guardar() const;
	string get_nombre_archivo() const;
	socio & get_socio( const int &_DNI );
	socio & get_socio_cod( const int &_codigo );
	socio & get_socio_pos( const int &_pos );
	int get_cant_socios() const;
	void set_nombre_archivo( const string &_path );
	void push( const socio &_nuevo );
	void push( const int &_DNI = -1,
			   const string &_nombre = "",
			   const string &_apellido = "",
			   const fecha &_nacimiento = fecha::npos,
			   const string &_domicilio = "",
			   const string &_tel = "",
			   const string &_path_foto = "Img\\Resources\\no-user.png",
			   const fecha &_fecha_ingreso = fecha::get_actual(),
			   const int &_cant_prestamos = 0,
			   const vector<prestamo> &_a_devolver = vector<prestamo>() );
	bool pop( const int &_DNI );
	bool pop_pos( const int &_pos );
	void sort( const int &_criterio = SociosPorNombre );
	static socio nsocio;
	
};


// ----------------------------------------------------------------------------
// bibliotecario: clase para representar a los bibliotecarios de la biblioteca.
// ----------------------------------------------------------------------------

class bibliotecario: public persona {
	
private:
	int cant_prestamos;
	float salario;
	string curriculum;
	string cta_usuario;
	string cta_pass;
	
public:
	bibliotecario( const int &_DNI = -1,
		           const string &_nombre = "",
		           const string &_apellido = "",
		           const fecha &_nacimiento = fecha::npos,
		           const string &_domicilio = "",
				   const string &_tel = "",
		           const string &_path_foto = "Img\\Resources\\no-user.png",
		           const fecha &_fecha_ingreso = fecha::get_actual(),
		           const int &_cant_prestamos = 0,
		           const float &_salario = -1,
		           const string &_curriculum = "",		
		           const string &_cta_usuario = "",		
		           const string &_cta_pass = "" );
	~bibliotecario();
	// GET's
	int get_cant_prestamos() const;
	string get_cant_prestamos_str() const;
	float get_salario() const;
	string get_salario_str() const;
	string get_curriculum() const;
	string get_cta_usuario() const;
	string get_cta_pass() const;
	bool buscado( const string &_criterio );
	// SET's
	void set_salario( const float &_salario );
	void set_curriculum( const string &_curriculum );
	void set_cta_usuario( const string &_usr );
	void set_cta_pass( const string &_pass );
	// AGREGAR
	int sumar_prestamo();
	// CARGAR - GUARDAR
	bool cargar( ifstream &_archi );
	bool guardar( ofstream &_archi ) const;
	// SOBRECARGA DE OPERADORES
	bibliotecario & operator=( const bibliotecario &_asignando );
	// FUNCIONES AMIGAS
	friend bool bibliotecarios_por_nombre( const bibliotecario &_comp1,
										   const bibliotecario &_comp2 );
	
	friend bool bibliotecarios_por_prestamos( const bibliotecario &_comp1,
		                                      const bibliotecario &_comp2 );
	
	friend bool bibliotecarios_por_antiguedad( const bibliotecario &_comp1,
		                                       const bibliotecario &_comp2 );
	
	friend bool bibliotecarios_por_fecha_alta( const bibliotecario &_comp1,
		                                       const bibliotecario &_comp2 );
	
	friend bool bibliotecarios_por_salario( const bibliotecario &_comp1,
		                                    const bibliotecario &_comp2 );
	
};

// ----------------------------------------------------------------------------
// save_bibliotecario: estructura para el guardado de datos de la clase
// bibliotecario en binario.
// ----------------------------------------------------------------------------

struct save_bibliotecario {
	
	int DNI;
	char telefono[50];
	char nombre[100];
	char apellido[100];
	char domicilio[100];
	char path_foto[260];
	fecha fecha_nacimiento;
	fecha fecha_ingreso;
	fecha fecha_de_alta;
	int cant_prestamos;
	float salario;
	char curriculum[10000];
	char cta_usuario[21];
	char cta_pass[21];
	
};

// ----------------------------------------------------------------------------
// Funciones para ordenar los bibliotecarios segun diferentes criterios con
// std::sort
// ----------------------------------------------------------------------------

enum criterios_orden_bibliotecarios{ BibPorNombre, BibPorPrestamos, BibPorAntig,
	                                 BibPorAlta, BibPorSalario };

bool bibliotecarios_por_nombre( const bibliotecario &_comp1,
	const bibliotecario &_comp2 );

bool bibliotecarios_por_prestamos( const bibliotecario &_comp1,
	const bibliotecario &_comp2 );

bool bibliotecarios_por_antiguedad( const bibliotecario &_comp1,
	const bibliotecario &_comp2 );

bool bibliotecarios_por_fecha_alta( const bibliotecario &_comp1,
	const bibliotecario &_comp2 );

bool bibliotecarios_por_salario( const bibliotecario &_comp1,
	const bibliotecario &_comp2 );


// ----------------------------------------------------------------------------
// bibliotecarios_database: base de datos de bibliotecarios del programa.
// ----------------------------------------------------------------------------

class bibliotecarios_database {
	
private:
	vector<bibliotecario> bibliotecarios;
	string nombre_archivo;
	
public:
	bibliotecarios_database( const string &_path_binario = "Data\\Bibliotecarios.dat" );
	~bibliotecarios_database();
	// CARGAR - GUARDAR
	bool cargar();
	bool guardar() const;
	// GET´s
	string get_nombre_archivo() const;
	int size() const;
	bibliotecario & get_bibliotecario( const string &_cta_usuario );
	bibliotecario & get_bibliotecario( const int &_DNI );
	bibliotecario & get_bibliotecario_pos( const int &_pos );
	int get_pos_bibliotecario( const string &_cta_usuario ) const;
	// SET's
	void set_nombre_archivo( const string &_path );
	// AGREGAR - BORRAR
	void push( const bibliotecario &_nuevo );
	void push( const int &_DNI = -1,
			   const string &_nombre = "",
			   const string &_apellido = "",
			   const fecha &_nacimiento = fecha::npos,
			   const string &_domicilio = "",
			   const string &_tel = "",
			   const string &_path_foto = "Img\\Resources\\no-user.png",
			   const fecha &_fecha_ingreso = fecha::get_actual(),
			   const int &_cant_prestamos = 0,
			   const float &_salario = -1,
			   const string &_curriculum = "",		
			   const string &_cta_usuario = "",		
			   const string &_cta_pass = "" );
	bool pop( const int &_DNI );
	bool pop_pos( const int &_pos );
	// COMPROBAR
	int comprobar_cta_bibliotecario( const string &_cta_bib ) const;
	bool comprobar_pass_bibliotecario( const int &_pos,
		                               const string &_pass_bib ) const;
	// ORDENAR
	void sort( const int &_criterio = BibPorNombre );
	// ATRIBUTOS STATIC
	static bibliotecario nbib;
	
};

#endif

