///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/Core/bibliografia.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en bibliografia.h
///////////////////////////////////////////////////////////////////////////////

#include "bibliografia.h"

#include <algorithm>
#include <cstring>
#include <fstream>

#include "programa.h"
#include <sstream>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// CLASE "autor"
///////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR - DESTRUCTOR
autor::autor ( const string &_nombre, const string &_resumen, const string &_url ) {
	
	nombre = _nombre;
	resumen = _resumen;
	url = _url;
	codigo = -1;
	cant_lecturas = 0;
	
}

autor::~autor ( ) {
	
}

// CARGAR - GUARDAR
bool autor::cargar ( ifstream &_archi ) {
	
	save_autor carga;
	if ( !_archi.read( reinterpret_cast<char*>( &carga ), sizeof( carga ) ) ) {
		
		return false;
		
	}
	
	nombre = carga.nombre;
	resumen = carga.resumen;
	url = carga.url;
	codigo = carga.codigo;
	cant_lecturas = carga.cant_lecturas;
	
	for ( int i=0;i<carga.cant_bibliografia;i++ ) { 
		
		bibliografia.push_back( carga.bibliografia[i] );
		
	}
	
	return true;
	
}

bool autor::guardar (ofstream & _archi) const {
	
	if ( ( nombre.size() > 99 ) ||
		 ( resumen.size() > 1999 ) ||
		 ( url.size() > 99 ) ||
		 ( bibliografia.size() > 100 ) ) {
		
		return false;
		
	}
	
	save_autor guardando;
	
	strcpy( guardando.nombre, nombre.c_str() );
	strcpy( guardando.resumen, resumen.c_str() );
	strcpy( guardando.url, url.c_str() );
	guardando.codigo = codigo;
	guardando.cant_lecturas = cant_lecturas;
	
	guardando.cant_bibliografia = bibliografia.size();
	for ( int i=0;i<guardando.cant_bibliografia;i++ ) { 
		
		guardando.bibliografia[i] = bibliografia[i];
		
	}
	
	_archi.write( reinterpret_cast<char*>( &guardando ), sizeof( guardando ) );
	
	return true;
	
}

// GET's
string autor::get_nombre ( ) const {
	
	return nombre;
	
}

string autor::get_resumen ( ) const {
	
	return resumen;
	
}

string autor::get_url ( ) const {
	
	return url;
	
}

int autor::get_codigo ( ) const {
	
	return codigo;
	
}

int autor::get_bibliografia (  const int &_pos  ) const {
	
	return bibliografia[_pos];
	
}

int autor::get_cant_bibliografia( ) const {
	
	return bibliografia.size();
	
}

int autor::get_cant_lecturas ( ) const {
	
	return cant_lecturas;
	
}

// SET's
void autor::set_nombre ( const string &_nombre ) {
	
	nombre = _nombre;
	
}

void autor::set_resumen ( const string &_resumen ) {
	
	resumen = _resumen;
	
}

void autor::set_url ( const string &_url ) {
	
	url = _url;
	
}

void autor::push_bibliografia ( const int &_cod_libro ) {
	
	bibliografia.push_back( _cod_libro );
	
}

void autor::set_codigo( ) {
	
	codigo = get_nuevo_codigo();
	
}

void autor::sumar_lectura( ) {
	
	++cant_lecturas;
	
}

bool autor::borrar_bibliografia ( const int &_cod_libro ) {
	
	const int tamanyo = bibliografia.size();
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( bibliografia[i] == _cod_libro ) {
			
			bibliografia.erase( bibliografia.begin() + i );
			return true;
			
		}
		
	}
	
	return false;
	
}

// BUSQUEDA
bool autor::buscar_contenido ( const string &_tag ) const {
	
	if ( nombre.find( _tag ) != string::npos ) {
		
		return true;
		
	}
	
	return false;
	
}

// ATRIBUTOS Y MÉTODOS STATIC
int autor::get_nuevo_codigo ( ) {
	
	++codigos_no_disponibles;
	return codigos_no_disponibles - 1;
	
}

void autor::set_codigos_no_disponibles( const int &_nro ) {
	
	codigos_no_disponibles = _nro;
	
}

int autor::get_codigos_no_disponibles( ) {
	
	return codigos_no_disponibles;
	
}

// FUNCIONES EXTERNAS
bool autores_por_nombre( const autor &_comp1, const autor &_comp2 ) {
	
	return _comp1.nombre < _comp2.nombre;
	
}

bool autores_por_prestamos( const autor &_comp1, const autor &_comp2 ) {
	
	if ( _comp1.cant_lecturas != _comp2.cant_lecturas ) {
		
		return _comp1.cant_lecturas > _comp2.cant_lecturas;
		
	}
	
	return autores_por_nombre( _comp1, _comp2 );
	
}


int autor::codigos_no_disponibles = 0;
//
///////////////////////////////////////////////////////////////////////////////
/// CLASE "autores_database"
///////////////////////////////////////////////////////////////////////////////
//
autores_database::autores_database ( const string &_path_binario ) {
	
	nombre_archivo = _path_binario;
	
}

autores_database::~autores_database ( ) {
	
}

bool autores_database::cargar ( ) {
	
	ifstream i_archi( nombre_archivo.c_str(), ios::binary );
	if ( !i_archi.is_open() ) {
		
		return false;
		
	}
	
	int aux;
	if ( !i_archi.read( reinterpret_cast<char*>(&aux), sizeof( aux ) ) ) {
		
		aux = 0;
		
	}
	autor::set_codigos_no_disponibles( aux );
	
	autor carga_autor;
	
	while ( carga_autor.cargar( i_archi ) ) {
		
		autores.push_back( carga_autor );
		
	}
	
	i_archi.close();
	
	return true;
	
}

bool autores_database::guardar ( ) const {
	
	ofstream o_archi( nombre_archivo.c_str(), ios::binary );
	if ( !o_archi.is_open() ) {
		
		return false;
		
	}
	
	int aux = autor::get_codigos_no_disponibles();
	o_archi.write( reinterpret_cast<char*>(&aux), sizeof( aux ) );
	
	const int tamanyo = autores.size();
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( !autores[i].guardar( o_archi ) ) {
			
			return false;
			
		}
		
	}
	
	return true;
	
}

int autores_database::size ( ) const {
	
	return autores.size();
	
}

string autores_database::get_nombre_archivo ( ) const {
	
	return nombre_archivo;
	
}

int autores_database::get_pos_autor ( const int &_codigo ) {
	
	const int tamanyo = autores.size();
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( autores[i].get_codigo() == _codigo ) {
			
			return i;
			
		}
		
	}
	
	return -1;
	
}

autor & autores_database::get_autor( const int &_codigo ) {
	
	const int tamanyo = autores.size();
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( autores[i].get_codigo() == _codigo ) {
			
			return autores[i];
			
		}
		
	}
	
	return nautor;
	
}

autor & autores_database::get_autor_pos ( const int &_pos ) {
	
	if ( _pos < autores.size() && _pos >= 0 ) {
		
		return autores[_pos];
		
	}
	
	return nautor;
	
}

void autores_database::set_nombre_archivo ( const string &_path ) {
	
	nombre_archivo = _path;
	
}

void autores_database::push ( const autor &_nuevo ) {
	
	autores.push_back( _nuevo );
	
}

void autores_database::push ( const string &_nombre, const string &_resumen, const string &_url ) {
	
	autor nuevo( _nombre, _resumen, _url );
	nuevo.set_codigo();
	autores.push_back( nuevo );
	
}

bool autores_database::pop ( const int &_codigo ) {
	
	const int tamanyo = autores.size();
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( autores[i].get_codigo() == _codigo ) {
			
			autores.erase( autores.begin() + i );
			return true;
			
		}
		
	}
	
	return false;
	
}

bool autores_database::pop_pos ( const int &_pos ) {
	
	if ( _pos < autores.size() && _pos >= 0 ) {
		
		autores.erase( autores.begin() + _pos );
		return true;
		
	}
	
	return false;
	
}

void autores_database::sort ( const int &_criterio ) {
	
	switch ( _criterio ) {
		
	case AutoresPorNombre:
		std::sort( autores.begin(), autores.end(), autores_por_nombre );
		break;
		
	default:
		std::sort( autores.begin(), autores.end(), autores_por_prestamos );
		
	}
	
}

autores_database & autores_database::operator= ( const autores_database &_asignando ) {
	
	autores = _asignando.autores;
	nombre_archivo = _asignando.nombre_archivo;
	
	return *this;
	
}

autor autores_database::nautor = autor();
//
///////////////////////////////////////////////////////////////////////////////
/// CLASE "libro"
///////////////////////////////////////////////////////////////////////////////
//
// CONSTRUCTOR - DESTRUCTOR
libro::libro ( const string &_titulo, const int &_codigo_autor, const string &_resumen, const string &_publicacion, const string &_url, const string &_tags, const CDU &_ubicacion, const int &_tipo_prestamo ) {
	
	titulo = _titulo;
	if ( _codigo_autor != -1 ) {
		
		codigo_autores.push_back( _codigo_autor );
		
		Programa *programa = Singleton::get_base_activa();
		
		nombre_autores = programa->autores.get_autor( _codigo_autor ).get_nombre();
		nombre_autores += ".";
		
	} else {
		
		nombre_autores = "";
		
	}
	resumen = _resumen;
	datos_publicacion = _publicacion;
	url = _url;
	tags = _tags;
	tipo_prestamo = _tipo_prestamo;
	ubicacion = _ubicacion;
	fecha_agregado = fecha::get_actual();
	cant_prestamos = 0;
	codigo = -1;
	prestado = false;
	nro_socio_prestado = -1;
	
}

libro::~libro ( ) {
	
}

// CARGAR - GUARDAR
bool libro::cargar ( ifstream &_archi ) {
	
	save_libro carga;
	if ( !_archi.read( reinterpret_cast<char*>( &carga ), sizeof( carga ) ) ) {
		
		return false;
		
	}
	
	titulo = carga.titulo;
	resumen = carga.resumen;
	datos_publicacion = carga.datos_publicacion;
	url = carga.url;
	tags = carga.tags;
	tipo_prestamo = carga.tipo_prestamo;
	ubicacion = carga.ubicacion;
	fecha_agregado = carga.fecha_agregado;
	fecha_devolucion = carga.fecha_devolucion;
	cant_prestamos = carga.cant_prestamos;
	codigo = carga.codigo;
	prestado = carga.prestado;
	nro_socio_prestado = carga.nro_socio_prestado;
	
	for ( int i=0;i<carga.cant_autores;i++ ) { 
		
		codigo_autores.push_back( carga.codigo_autor[i] );
		
	}
	
	if ( carga.cant_autores > 0 ) {
		
		nombre_autores = carga.nombre_autores;
		
	} else {
		
		nombre_autores = "";
		
	}
	
	return true;
	
}

bool libro::guardar ( ofstream &_archi ) const {
	
	if ( ( titulo.size() > 99 ) ||
		 ( codigo_autores.size() > 10 ) ||
		 ( nombre_autores.size() > 199 ) ||
		 ( resumen.size() > 1999 ) ||
		 ( url.size() > 99 ) ||
		 ( datos_publicacion.size() > 199 ) ||
		 ( tags.size() > 499 ) ) {
		
		return false;
		
	}
	
	save_libro guardando;
	
	strcpy ( guardando.titulo, titulo.c_str() );
	guardando.cant_autores = codigo_autores.size();
	
	for ( int i=0;i<guardando.cant_autores;i++ ) { 
		
		guardando.codigo_autor[i] = codigo_autores[i];
		
	}
	
	strcpy ( guardando.nombre_autores, nombre_autores.c_str() );
	strcpy ( guardando.resumen, resumen.c_str() );
	strcpy ( guardando.url, url.c_str() );
	strcpy ( guardando.datos_publicacion, datos_publicacion.c_str() );
	guardando.tipo_prestamo = tipo_prestamo;
	guardando.ubicacion = ubicacion;
	guardando.fecha_agregado = fecha_agregado;
	guardando.fecha_devolucion = fecha_devolucion;
	strcpy ( guardando.tags, tags.c_str() );
	guardando.codigo = codigo;
	guardando.cant_prestamos = cant_prestamos;
	guardando.prestado = prestado;
	guardando.nro_socio_prestado = nro_socio_prestado;
	
	_archi.write( reinterpret_cast<char*>( &guardando ), sizeof( guardando ) );
	
	return true;
	
}

// GET's
string libro::get_titulo ( ) const {
	
	return titulo;
	
}

string libro::get_nombre_autores ( ) const {
	
	return nombre_autores;
	
}

int libro::get_cant_autores ( ) const {
	
	return codigo_autores.size();
	
}

int libro::get_codigo_autor ( const int &_pos ) const {
	
	return codigo_autores[_pos];
	
}

string libro::get_resumen ( ) const {
	
	return resumen;
	
}

string libro::get_url ( ) const {
	
	return url;
	
}

string libro::get_publicacion ( ) const {
	
	return datos_publicacion;
	
}

int libro::get_tipo_prestamo ( ) const {
	
	return tipo_prestamo;
	
}

CDU libro::get_ubicacion ( ) const {
	
	return ubicacion;
	
}

string libro::get_tags ( ) const {
	
	return tags;
	
}

fecha libro::get_fecha_agregado ( ) const {
	
	return fecha_agregado;
	
}

int libro::get_cant_prestamos ( ) const {
	
	return cant_prestamos;
	
}

int libro::get_codigo ( ) const {
	
	return codigo;
	
}

string libro::get_codigo_str ( ) const {
	
	stringstream ss;
	ss<<codigo;
	return ss.str();
	
}

bool libro::get_prestado ( ) const {
	
	return prestado;
	
}

int libro::get_nro_socio_prestado ( ) const {
	
	return nro_socio_prestado;
	
}

fecha libro::get_fecha_devolucion ( ) const {
	
	return fecha_devolucion;
	
}

vector<prestamo> libro::get_historial ( ) const {
	
	vector<prestamo> historial;
	prestamo carga;
	ifstream archi( "Data\\Prestamos.dat", ios::binary );
	
	while( archi.read( reinterpret_cast<char*>( &carga ), sizeof( carga ) ) ) {
		
		if ( carga.codigo_libro == this->codigo ) {
			
			historial.push_back( carga );
			
		}
		
	}
	
	archi.close();
	
	return historial;
	
}

// SET's
void libro::set_titulo ( const string &_titulo ) {
	
	titulo = _titulo;
	
}

void libro::agregar_autor ( const int &_codigo, autores_database *_autores ) {
	
	autores_database *autores;
	
	if ( _autores == NULL ) {
		
		autores = &( ( Singleton::get_base_activa() )->autores );
		
	} else {
		
		autores = _autores;
		
	}
	
	if ( codigo_autores.size() > 0 ) {
		
		// Se cambia el punto final por un punto y coma y se agrega un espacio.
		int pos_punto = nombre_autores.size() - 1;
		nombre_autores[pos_punto] = ';';
		nombre_autores.push_back( ' ' );
		
		// Se concatena el nombre del nuevo autor.
		nombre_autores += autores->get_autor( _codigo ).get_nombre();
		
		// Se vuelve a agregar el punto final.
		nombre_autores.push_back( '.' );
		
	} else {
		
		nombre_autores = autores->get_autor( _codigo ).get_nombre();
		nombre_autores.push_back( '.' );
		
	}
	
	codigo_autores.push_back( _codigo );
	
	autores->get_autor( _codigo ).push_bibliografia( codigo );
	
}

bool libro::eliminar_autor ( const int &_pos ) {
	
	Programa *programa = Singleton::get_base_activa();
	
	if ( _pos < codigo_autores.size() && _pos >= 0 ) {
		
		string nombre = programa->autores.get_autor( codigo_autores[_pos] ).get_nombre();
		
		int pos_inicio_nombre = nombre_autores.find_last_of( ';' );
		int pos_inicio_nombre2 = nombre_autores.find( nombre ) - 2;
		
		if ( pos_inicio_nombre == pos_inicio_nombre2 ) { // Si el nombre es el último de la lista de nombres...
			
			nombre_autores = nombre_autores.substr( 0, pos_inicio_nombre );
			nombre_autores.push_back( '.' );
			
		} else { // Si se encuentra entre otros dos nombres...
			
			string resto = nombre_autores.substr( pos_inicio_nombre2 + 2 + nombre.size() );
			nombre_autores = nombre_autores.substr( 0, pos_inicio_nombre2 );
			nombre_autores += resto;
			
		}
		
		programa->autores.get_autor( codigo_autores[_pos] ).borrar_bibliografia( codigo );
		codigo_autores.erase( codigo_autores.begin() + _pos );
		
		return true;
		
	}
	
	return false;
	
}

void libro::set_resumen ( const string &_resumen ) {
	
	if ( _resumen.size() > 1999 ) {
		
		resumen = _resumen.substr( 0, 1999 );
		
	} else {
		
		resumen = _resumen;
		
	}
	
}

void libro::set_url ( const string &_url ) {
		
	if ( _url.size() > 99 ) {
		
		url = _url.substr( 0, 99 );
		
	} else {
		
		url = _url;
		
	}
	
}

void libro::set_publicacion ( const string &_publicacion ) {
	
	if ( _publicacion.size() < 200 ) {
		
		datos_publicacion = _publicacion;
		
	} else {
		
		datos_publicacion = _publicacion.substr( 0, 199 );
		
	}
	
}

void libro::set_tipo_prestamo ( const int &_tipo ) {
	
	if ( _tipo <= 1 ) {
		
		tipo_prestamo = _tipo;
		
	}
	
}

void libro::set_codigo ( ) {
	
	codigo = get_nuevo_codigo();
	
	if ( codigo_autores.size() == 1 && codigo_autores[0] != -1 ) {
		
		Programa *programa = Singleton::get_base_activa();
		
		programa->autores.get_autor( codigo_autores[0] ).push_bibliografia( codigo );
		
	}
	
}

void libro::agregar_tag ( const string &_tag ) {
	
	int t1 = tags.size();
	int t2 = _tag.size();
	
	if ( ( t2 + t1 ) < 500 ) {
		
		if ( tags != "" ) {
			
			tags[t1-1] = ',';
			tags.push_back( ' ' );
			tags += _tag;
			tags.push_back( '.' );
			
		} else {
			
			tags = _tag;
			tags.push_back( '.' );
			
		}
		
	}
	
}

void libro::set_tags ( const string &_tags ) {
	
	tags = _tags;
	
	if ( tags.size() >= 500 ) {
		
		while ( tags.size() >= 499 ) {
			
			tags = tags.substr( 0, tags.find_last_of( ',' ) );
			
		}
		
		tags.push_back( '.' );
		
	}
	
}

void libro::sumar_prestamo ( ) {
	
	++cant_prestamos;
	
	Programa *programa = Singleton::get_base_activa();
	
	const int cant_autores = codigo_autores.size();
	
	for ( int i=0;i<cant_autores;i++ ) { 
		
		programa->autores.get_autor( codigo_autores[i] ).sumar_lectura();
		
	}
	
}

void libro::set_ubicacion ( const CDU &_ubicacion ) {
	
	ubicacion = _ubicacion;
	
}

void libro::set_prestado ( const bool &_prestado, const int &_nro_socio ) {
	
	if ( _prestado == false && prestado == true ) {
		
		this->sumar_prestamo();
		
	} else if ( _prestado == true && prestado == false ) {
		
		this->set_fecha_devolucion();
		nro_socio_prestado = _nro_socio;
		
	}
	
	prestado = _prestado;
	
}

void libro::set_fecha_devolucion ( ) {
	
	fecha_devolucion = ( fecha::get_actual() + fecha( 7 ) );
	
}

// BUSQUEDA
bool libro::buscar_contenido ( const string &_tag ) const {
	
	if ( tags.find( _tag ) != string::npos ||
		 nombre_autores.find( _tag ) != string::npos ||
		 titulo.find( _tag ) != string::npos ) {
		
		return true;
		
	}
	
	return false;
	
}

// SOBRECARGA DE OPERADORES
libro & libro::operator= ( const libro &_asignando ) {
	
	titulo = _asignando.titulo;
	nombre_autores = _asignando.nombre_autores;
	codigo_autores = _asignando.codigo_autores;
	resumen = _asignando.resumen;
	datos_publicacion = _asignando.datos_publicacion;
	url = _asignando.url;
	tags = _asignando.tags;
	tipo_prestamo = _asignando.tipo_prestamo;
	ubicacion = _asignando.ubicacion;
	fecha_agregado = _asignando.fecha_agregado;
	fecha_devolucion = _asignando.fecha_devolucion;
	cant_prestamos = _asignando.cant_prestamos;
	codigo = _asignando.codigo;
	prestado = _asignando.prestado;
	nro_socio_prestado = _asignando.nro_socio_prestado;
	
	return *this;
	
}

// ATRIBUTOS Y MÉTODOS STATIC
int libro::get_nuevo_codigo ( ) {
	
	++codigos_no_disponibles;
	return codigos_no_disponibles - 1;
	
}

void libro::set_codigos_no_disponibles ( const int &_nro ) {
	
	codigos_no_disponibles = _nro;
	
}

int libro::get_cod_no_disponibles ( ) {
	
	return codigos_no_disponibles;
	
}

int libro::codigos_no_disponibles = 0;

// FUNCIONES AMIGAS
bool libros_por_titulo( const libro &_comp1, const libro &_comp2 ) {
	
	if ( _comp1.titulo != _comp2.titulo ) {
		
		return _comp1.titulo < _comp2.titulo;
		
	}
	
	return _comp1.codigo < _comp2.codigo;
	
}

bool libros_por_prestamos( const libro &_comp1, const libro &_comp2 ) {
	
	if ( _comp1.cant_prestamos != _comp2.cant_prestamos ) {
		
		return _comp1.cant_prestamos > _comp2.cant_prestamos;
		
	}
	
	return libros_por_titulo( _comp1, _comp2 );
	
}

bool libros_por_autor( const libro &_comp1, const libro &_comp2 ) {
	
	if ( _comp1.get_nombre_autores() != _comp2.get_nombre_autores() ) {
		
		return _comp1.get_nombre_autores() < _comp2.get_nombre_autores();
		
	}
	
	return libros_por_titulo( _comp1, _comp2 );
	
}

bool libros_por_fecha_alta( const libro &_comp1, const libro &_comp2 ) {
	
	return _comp1.fecha_agregado < _comp2.fecha_agregado;
	
}
//
///////////////////////////////////////////////////////////////////////////////
/// CLASE "libros_database"
///////////////////////////////////////////////////////////////////////////////
//
// CONSTRUCTOR - DESTRUCTOR
libros_database::libros_database ( const string &_path_binario ) {
	
	nombre_archivo = _path_binario;
	
}

libros_database::~libros_database ( ) {
	
}

bool libros_database::cargar ( ) {
	
	ifstream i_archi( nombre_archivo.c_str(), ios::binary );
	if ( !i_archi.is_open() ) {
		
		return false;
		
	}
	
	int aux;
	if ( !i_archi.read( reinterpret_cast<char*>( &aux ), sizeof( aux ) ) ) {
		
		aux = 0;
		
	}
	libro::set_codigos_no_disponibles( aux );
	
	libro carga_libro;
	
	while ( carga_libro.cargar( i_archi ) ) {
		
		libros.push_back( carga_libro );
		
	}
	
	i_archi.close();
	
	return true;
	
}

bool libros_database::guardar ( ) const {
	
	ofstream o_archi( nombre_archivo.c_str(), ios::binary );
	if ( !o_archi.is_open() ) {
		
		return false;
		
	}
	
	int aux = libro::get_cod_no_disponibles();
	o_archi.write( reinterpret_cast<char*>( &aux ), sizeof( aux ) );
	
	const int tamanyo = libros.size();
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( !libros[i].guardar( o_archi ) ) {
			
			return false;
			
		}
		
	}
	
	return true;
	
}

string libros_database::get_nombre_archivo ( ) const {
	
	return nombre_archivo;
	
}

libro & libros_database::get_libro ( const string &_titulo ) {
	
	const int tamanyo = libros.size();
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( libros[i].get_titulo() == _titulo ) {
			
			return libros[i];
			
		}
		
	}
	
	return nlibro;
	
}

libro & libros_database::get_libro ( const int &_codigo ) {
	
	const int tamanyo = libros.size();
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( libros[i].get_codigo() == _codigo ) {
			
			return libros[i];
			
		}
		
	}
	
	return nlibro;
	
}

libro & libros_database::get_libro_pos (const int & _pos) {
	
	if ( _pos < libros.size() ) {
		
		return libros[_pos];
		
	}
	
	return nlibro;
	
}

int libros_database::get_cant_libros ( ) const {
	
	return libros.size();
	
}

void libros_database::set_nombre_archivo ( const string &_path ) {
	
	nombre_archivo = _path;
	
}

void libros_database::push ( const libro &_nuevo ) {
	
	libros.push_back( _nuevo );
	
}

void libros_database::push ( const string &_titulo, const int &_codigo_autor, const string &_resumen, const string &_publicacion, const string &_url, const string &_tags, const CDU &_ubicacion, const int &_tipo_prestamo ) {
	
	libro nuevo( _titulo, _codigo_autor, _resumen, _publicacion, _url, _tags, _ubicacion, _tipo_prestamo );
	nuevo.set_codigo();
	libros.push_back( nuevo );
	
}

bool libros_database::pop ( const string &_titulo ) {
	
	const int tamanyo = libros.size();
	
	Programa *_programa = Singleton::get_base_activa();
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( libros[i].get_titulo() == _titulo ) {
			
			// Desvincular el libro del autor.
			const int tamanyo = libros[i].get_cant_autores();
			
			for ( int j=0;j<tamanyo;j++ ) { 
				
				_programa->autores.get_autor( libros[i].get_codigo_autor(j) ).borrar_bibliografia( libros[i].get_codigo() );
				
			}
			
			// Borrar el libro.
			libros.erase( libros.begin() + i );
			return true;
			
		}
		
	}
	
	return false;
	
}

bool libros_database::pop ( const int &_codigo ) {
	
	const int tamanyo = libros.size();
	
	Programa *_programa = Singleton::get_base_activa();
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( libros[i].get_codigo() == _codigo ) {
			
			// Desvincular el libro del autor.
			const int tamanyo = libros[i].get_cant_autores();
			
			for ( int j=0;j<tamanyo;j++ ) { 
				
				_programa->autores.get_autor( libros[i].get_codigo_autor(j) ).borrar_bibliografia( libros[i].get_codigo() );
				
			}
			
			// Borrar el libro.
			libros.erase( libros.begin() + i );
			return true;
			
		}
		
	}
	
	return false;
	
}

bool libros_database::pop_pos ( const int &_pos ) {
	
	if ( _pos >= 0 && _pos < libros.size() ) {
		
		// Desvincular el libro del autor.
		const int tamanyo = libros[_pos].get_cant_autores();
		
		Programa *_programa = Singleton::get_base_activa();
		
		for ( int i=0;i<tamanyo;i++ ) { 
			
			_programa->autores.get_autor( libros[_pos].get_codigo_autor(i) ).borrar_bibliografia( libros[_pos].get_codigo() );
			
		}
		
		// Borrar el libro.
		libros.erase( libros.begin() + _pos );
		return true;
		
	}
	
	return false;
	
}

void libros_database::sort ( const int &_criterio ) {
	
	switch ( _criterio ) {
		
	case LibrosPorTitulo:
		std::sort( libros.begin(), libros.end(), libros_por_titulo );
		break;
		
	case LibrosPorPrestamos:
		std::sort( libros.begin(), libros.end(), libros_por_prestamos );
		break;
		
	case LibrosPorAutor:
		std::sort( libros.begin(), libros.end(), libros_por_autor );
		break;
		
	default:
		std::sort( libros.begin(), libros.end(), libros_por_fecha_alta );
		
	}
	
}

libro libros_database::nlibro = libro();

