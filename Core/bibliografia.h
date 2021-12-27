///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/Core/bibliografia.h
// Prop�sito:   Clases necesarias para trabajar con los objetos que constituyen
//				la bibliograf�a.
// Autor:       Iv�n Pizarro.
//
// En este archivo se declaran los dise�os de las clases que representan el
// cuerpo bibliogr�fico de la biblioteca.
///////////////////////////////////////////////////////////////////////////////

#ifndef BIBLIOGRAFIA_H
#define BIBLIOGRAFIA_H

#include "utilidades.h"
#include "personas.h"

#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Declaraci�n anticipada para usar en la clase autor.
class libro;

// ----------------------------------------------------------------------------
// autor: objetos que consituyen la base de datos de autores del programa.
// ----------------------------------------------------------------------------

class autor {
	
private:
	// Nombre completo del autor.
	string nombre;
	// Breve descripci�n del autor (como el primer p�rrafo de su art en wiki).
	string resumen;
	// Direcci�n a una p�gina con informaci�n m�s completa sobre el autor.
	string url;
	// C�digos de los los libros de la biblioteca que son de su autor�a.
	vector<int> bibliografia;
	// C�digo del autor.
	int codigo;
	// Cantidad de veces que se sac� un libro del autor.
	int cant_lecturas; 
	// Contador para asignar nuevos c�digos de autor no repetidos.
	static int codigos_no_disponibles;
	// Generar un nuevo c�digo no repetido.
	static int get_nuevo_codigo();
	
public:
	autor( const string &_nombre = "",
		   const string &_resumen = "",
		   const string &_url = "" );
	~autor();
	// CARGAR - GUARDAR
	bool cargar( ifstream &_archi );
	bool guardar( ofstream &_archi ) const;
	// OBTENER DATOS
	string get_nombre() const;
	string get_resumen() const;
	string get_url() const;
	int get_codigo() const;
	int get_bibliografia( const int &_pos ) const;
	int get_cant_bibliografia() const;
	int get_cant_lecturas() const;
	static int get_codigos_no_disponibles();
	// SETEAR ATRIBUTOS
	void set_nombre( const string &_nombre );
	void set_resumen( const string &_resumen );
	void set_url( const string &_url );
	void push_bibliografia( const int &_cod_libro );
	void set_codigo();
	void sumar_lectura();
	static void set_codigos_no_disponibles( const int &_nro );
	bool borrar_bibliografia( const int &_cod_libro );
	// BUSQUEDA
	bool buscar_contenido( const string &_tag ) const;
	// FUNCIONES AMIGAS
	friend bool autores_por_nombre( const autor &_comp1, const autor &_comp2 );
	friend bool autores_por_prestamos( const autor &_comp1, const autor &_comp2 );
	
};


// ----------------------------------------------------------------------------
// save_autor: estructura para guardar los objetos de la clase autor en binario.
// ----------------------------------------------------------------------------

struct save_autor {
	
	char nombre[100];
	char resumen[2000];
	char url[100];
	int bibliografia[100];
	int codigo;
	int cant_lecturas;
	int cant_bibliografia;
	
};

// ----------------------------------------------------------------------------
// Funciones para ordenar los autores segun diferentes criterios con std::sort
// ----------------------------------------------------------------------------

enum criterios_orden_autores { AutoresPorNombre, AutoresPorPrestamos };

bool autores_por_nombre( const autor &_comp1, const autor &_comp2 );
bool autores_por_prestamos( const autor &_comp1, const autor &_comp2 );


// ----------------------------------------------------------------------------
// autores_database: base de datos de autores del programa.
//
// Esta clase funciona a modo de contenedor, gestiona todos los objetos "autor"
// del programa y proporciona todos los m�todos necesarios para trabajar con
// ellos con el fin de lograr simplicidad en el uso del programa principal.
// ----------------------------------------------------------------------------

class autores_database {
	
private:
	// Contenedor de los objetos "autor".
	vector<autor> autores;
	// Nombre del binario desde donde cargar y guardar.
	string nombre_archivo;
	// Objeto autor con prop�sito an�logo a string::npos.
	static autor nautor;
	
public:
	autores_database( const string &_path_binario = "Data\\Autores.dat" );
	~autores_database();
	// Cargar y guardar los datos.
	bool cargar();
	bool guardar() const;
	// Obtener y setear el nombre del archivo de guardado y carga.
	string get_nombre_archivo() const;
	void set_nombre_archivo( const string &_path );
	// Obtener la cantidad de autores del contenedor.
	int size() const;
	// Obtener la posici�n de un objeto "autor" en el vector a partir de su c�digo.
	int get_pos_autor( const int &_codigo );
	// Obtener el objeto autor indicado por su c�digo o su posici�n en el vector.
	autor & get_autor( const int &_codigo );
	autor & get_autor_pos( const int &_pos );
	// Agregar un nuevo autor.
	void push( const autor &_nuevo );
	void push( const string &_nombre,
			   const string &_resumen = "",
			   const string &_url = "" );
	// Eliminar un autor.
	bool pop( const int &_codigo );
	bool pop_pos( const int &_pos );
	/* Ordenar el vector seg�n los criterios, que son las funciones amigas de
	la clase "autor". */
	void sort( const int &_criterio = AutoresPorNombre );
	// Sobrecarga de operadores.
	autores_database & operator=( const autores_database &_asignando );
	
};

// ----------------------------------------------------------------------------
// Enum de los tipos de pr�stamo, para que sea m�s eficiente y entendible.
enum tipos_de_prestamo { a_domicilio, consulta };


// CDU:
// Estructura para almacenar la ubicaci�n del libro en la biblioteca seg�n un
// sistema simplificado basado en el CDU (clasificaci�n decimal universal).
// http://es.wikipedia.org/wiki/Clasificaci%C3%B3n_Decimal_Universal

struct CDU {
	// Clasificaci�n principal.
	int c1;
	// Primera subcategor�a.
	int c2;
	// Segunda subcategor�a.
	int c3;
	// Iniciales del autor.
	char inicial_ape_autor;
	char inicial_nom_autor;
	
	CDU ( ) {
		
		c1 = c2 = c3 = -1;
		inicial_ape_autor = inicial_nom_autor = 'X';
		
	}
	string str() const {
		
		/* Retorna un string con la ubicaci�n completa, cuyo formato es:
		"c1c2c3 InicialapellidoInicialnombre", por ej: "327 KF" */
		
		stringstream ss;
		ss<<c1;
		ss<<c2;
		ss<<c3;
		ss<<" ";
		string retorno = ss.str();
		retorno.push_back( inicial_ape_autor );
		retorno.push_back( inicial_nom_autor );
		
		return retorno;
		
	}
	
};

// ----------------------------------------------------------------------------
// libro: objeto que representa a un libro de la biblioteca.
// ----------------------------------------------------------------------------

class libro {
	
private:
	string titulo;
	string nombre_autores;
	vector<int> codigo_autores;
	string resumen; // Breve rese�a.
	string datos_publicacion;
	string url; // Direcci�n de una p�gina web con informaci�n sobre el libro.
	string tags; // Contenido del libro en forma de tags o palabras clave.
	int tipo_prestamo; // Se maneja con el enum declarado arriba.
	CDU ubicacion;
	fecha fecha_agregado;
	fecha fecha_devolucion;
	int cant_prestamos;
	int codigo; // C�digo �nico que identifica al libro.
	bool prestado; // Bandera que indica si el libro est� prestado o disponible.
	int nro_socio_prestado; // C�digo del socio que actualmente tiene el libro.
	static int codigos_no_disponibles; // Contador para generar c�digos.
	static int get_nuevo_codigo(); // Obtener un nuevo c�digo �nico.
	
public:
	libro( const string &_titulo = "",
		   const int &_codigo_autor = -1,
		   const string &_resumen = "",
		   const string &_publicacion = "",
		   const string &_url = "",
		   const string &_tags = "",
		   const CDU &_ubicacion = CDU(),
		   const int &_tipo_prestamo = a_domicilio );
	~libro();
	// CARGAR - GUARDAR
	bool cargar( ifstream &_archi );
	bool guardar( ofstream &_archi ) const;
	// OBTENER DATOS
	string get_titulo() const;
	string get_nombre_autores() const;
	int get_codigo_autor( const int &_pos ) const;
	int get_cant_autores() const;
	string get_resumen() const;
	string get_url() const;
	string get_publicacion() const;
	int get_tipo_prestamo() const;
	CDU get_ubicacion() const;
	string get_tags() const;
	fecha get_fecha_agregado() const;
	fecha get_fecha_devolucion() const;
	int get_cant_prestamos() const;
	int get_codigo() const;
	string get_codigo_str() const;
	bool get_prestado() const;
	int get_nro_socio_prestado() const;
	static int get_cod_no_disponibles();
	vector<prestamo> get_historial() const;
	// SETEAR ATRIBUTOS
	void set_titulo( const string &_titulo );
	void agregar_autor( const int &_codigo, autores_database *_autores = NULL );
	bool eliminar_autor( const int &_pos );
	void set_resumen( const string &_resumen );
	void set_url( const string &_url );
	void set_publicacion( const string &_publicacion );
	void set_tipo_prestamo( const int &_tipo );
	void agregar_tag( const string &_tag );
	void set_tags( const string &_tags );
	void set_codigo();
	void set_prestado( const bool &_prestado, const int &_nro_socio = -1 );
	void set_ubicacion( const CDU &_ubicacion );
	void set_fecha_devolucion();
	static void set_codigos_no_disponibles( const int &_nro );
	void sumar_prestamo(); // Aumenta el contador de veces que el libro fue prestado.
	// BUSQUEDA
	bool buscar_contenido( const string &_tag ) const;
	// SOBRECARGA DE OPERADORES
	libro & operator=( const libro &_asignando );
	// FUNCIONES AMIGAS
	friend bool libros_por_titulo( const libro &_comp1, const libro &_comp2 );
	friend bool libros_por_prestamos( const libro &_comp1, const libro &_comp2 );
	friend bool libros_por_fecha_alta( const libro &_comp1, const libro &_comp2 );
	
};


// ----------------------------------------------------------------------------
// save_libro: estructura para guardar los objetos de la clase libro en binario.
// ----------------------------------------------------------------------------

struct save_libro {
	
	char titulo[100];
	int cant_autores;
	int codigo_autor[10];
	char nombre_autores[200];
	char resumen[2000];
	char url[100];
	char datos_publicacion[200];
	int tipo_prestamo;
	CDU ubicacion;
	fecha fecha_agregado;
	fecha fecha_devolucion;
	char tags[500];
	int codigo;
	int cant_prestamos;
	bool prestado;
	int nro_socio_prestado;
	
};

// ----------------------------------------------------------------------------
// Funciones para ordenar los libros segun diferentes criterios con std::sort
// ----------------------------------------------------------------------------

enum criterios_orden_libros { LibrosPorTitulo , LibrosPorPrestamos,
	                          LibrosPorAutor, LibrosPorAlta };

bool libros_por_titulo( const libro &_comp1, const libro &_comp2 );
bool libros_por_prestamos( const libro &_comp1, const libro &_comp2 );
bool libros_por_autor( const libro &_comp1, const libro &_comp2 );
bool libros_por_fecha_alta( const libro &_comp1, const libro &_comp2 );


// ----------------------------------------------------------------------------
// libros_database: base de datos de libros del programa.
//
// Esta clase funciona a modo de contenedor, gestiona todos los objetos "libro"
// del programa y proporciona todos los m�todos necesarios para trabajar con
// ellos con el fin de lograr simplicidad en el uso del programa principal.
// ----------------------------------------------------------------------------

class libros_database {
	
private:
	// Contenedor de los objetos "libro".
	vector<libro> libros;
	// Nombre del binario desde donde cargar y guardar.
	string nombre_archivo;
	
public:
	libros_database( const string &_path_binario = "Data\\Libros.dat" );
	~libros_database();
	// Cargar y guardar los datos.
	bool cargar();
	bool guardar() const;
	/* Obtener y setear el nombre del archivo donde se guardan los datos de la
	clase. */
	string get_nombre_archivo() const;
	void set_nombre_archivo( const string &_path );
	/* Obtener el objeto libro indicado por su t�tulo, su c�digo o su posici�n
	en el vector. */
	libro & get_libro( const string &_titulo );
	libro & get_libro( const int &_codigo );
	libro & get_libro_pos( const int &_pos );
	// Obtener la cantidad de libros del vector.
	int get_cant_libros() const;
	// Agregar un nuevo libro.
	void push( const libro &_nuevo );
	void push( const string &_titulo = "",
			   const int &_codigo_autor = -1,
		       const string &_resumen = "",
			   const string &_publicacion = "",
			   const string &_url = "",
			   const string &_tags = "",
			   const CDU &_ubicacion = CDU(),
			   const int &_tipo_prestamo = a_domicilio );
	// Borrar un libro
	bool pop( const string &_titulo );
	bool pop( const int &_codigo );
	bool pop_pos( const int &_pos );
	/* Ordenar el vector seg�n los criterior indicados por las funciones amigas
	de la clase "libro" */
	void sort( const int &_criterio = LibrosPorTitulo );
	// Objeto de retorno que indica que el libro solicitado no existe.
	static libro nlibro;
	
};

#endif

