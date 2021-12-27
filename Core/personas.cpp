///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/Core/personas.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en personas.h
///////////////////////////////////////////////////////////////////////////////

#include "personas.h"
#include "programa.h"

#include <cstring>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// CLASE "persona"
///////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORES - DESTRUCTORES
persona::persona ( const int &_DNI, const string &_nombre, const string &_apellido, const fecha &_nacimiento, const string &_domicilio, const string &_tel, const string &_path_foto, const fecha &_fecha_ingreso ) {
	
	DNI = _DNI;
	nombre = _nombre;
	apellido = _apellido;
	fecha_nacimiento = _nacimiento;
	domicilio = _domicilio;
	telefono = _tel;
	path_foto = _path_foto;
	fecha_ingreso = _fecha_ingreso;
	fecha_de_alta = fecha::get_actual();
	
}

persona::~persona ( ) {
	
}

// GET'S
int persona::get_dni ( ) const {
	
	return DNI;
	
}

string persona::get_dni_str ( ) const {
	
	stringstream ss;
	ss<<DNI;
	return ss.str();
	
}

string persona::get_tel ( ) const {
	
	return telefono;
	
}

string persona::get_nombre ( ) const {
	
	return nombre;
	
}

string persona::get_apellido ( ) const {
	
	return apellido;
	
}

string persona::get_nombre_completo ( ) const {
	
	string retorno = apellido;
	retorno += ", ";
	retorno += nombre;
	return retorno;
	
}

string persona::get_domicilio ( ) const {
	
	return domicilio;
	
}

string persona::get_path_foto ( ) const {
	
	return path_foto;
	
}

fecha persona::get_fecha_nac ( ) const {
	
	return fecha_nacimiento;
	
}

int persona::get_edad ( ) const {
	
	return ( fecha::get_actual() - fecha_nacimiento ).get_anyo();
	
}

string persona::get_edad_str ( ) const {
	
	stringstream ss;
	ss<<( ( fecha::get_actual() - fecha_nacimiento ).get_anyo() );
	return ss.str();
	
}

fecha persona::get_fecha_ingreso ( ) const {
	
	return fecha_ingreso;
	
}

fecha persona::get_fecha_de_alta ( ) const {
	
	return fecha_de_alta;
	
}

int persona::get_antiguedad ( ) const {
	
	return ( fecha::get_actual() - fecha_ingreso ).get_anyo();
	
}

string persona::get_antiguedad_str ( ) const {
	
	stringstream ss;
	ss<<( ( fecha::get_actual() - fecha_ingreso ).get_anyo() );
	ss<<" años";
	return ss.str();
	
}

// SET's
void persona::set_dni ( const int &_dni ) {
	
	DNI = _dni;
	
}

void persona::set_tel ( const string &_tel ) {
	
	telefono = _tel;
	
}

void persona::set_nombre ( const string &_nom ) {
	
	nombre = _nom;
	
}

void persona::set_apellido ( const string &_ape ) {
	
	apellido = _ape;
	
}

void persona::set_domicilio ( const string &_dom ) {
	
	domicilio = _dom;
	
}

void persona::set_path_foto ( const string &_path ) {
	
	path_foto = _path;
	
}

void persona::set_fecha_nac ( const int &_dia, const int &_mes, const int &_anyo ) {
	
	fecha_nacimiento.set_dia( _dia );
	fecha_nacimiento.set_mes( _mes );
	fecha_nacimiento.set_anyo( _anyo );
	
}

void persona::set_fecha_ingreso ( const int &_dia, const int &_mes, const int &_anyo ) {
	
	fecha_ingreso.set_dia( _dia );
	fecha_ingreso.set_mes( _mes );
	fecha_ingreso.set_anyo( _anyo );
	
}

void persona::set_fecha_ingreso ( const fecha &_ingreso ) {
	
	fecha_ingreso = _ingreso;
	
}
//
///////////////////////////////////////////////////////////////////////////////
/// CLASE "socio"
///////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORES - DESTRUCTORES
socio::socio ( const int &_DNI, const string &_nombre, const string &_apellido, const fecha &_nacimiento, const string &_domicilio, const string &_tel, const string &_path_foto, const fecha &_fecha_ingreso, const int &_cant_prestamos, const vector<prestamo> &_a_devolver ): persona( _DNI, _nombre, _apellido, _nacimiento, _domicilio, _tel, _path_foto, _fecha_ingreso ) {
	
	cant_prestamos = _cant_prestamos;
	a_devolver = _a_devolver;
	nro_socio = -1;
	
}

socio::~socio ( ) {
	
}

// CARGAR - GUARDAR
bool socio::cargar ( ifstream & _archi ) {
	
	save_socio carga;
	if ( !_archi.read( reinterpret_cast<char*>( &carga ), sizeof( carga ) ) ) {
		
		return false;
		
	}
	
	DNI = carga.DNI;
	telefono = carga.telefono;
	nombre = carga.nombre;
	apellido = carga.apellido;
	domicilio = carga.domicilio;
	path_foto = carga.path_foto;
	fecha_nacimiento = carga.fecha_nacimiento;
	fecha_ingreso = carga.fecha_ingreso;
	fecha_de_alta = carga.fecha_de_alta;
	
	for ( int i=0;i<carga.cant_devolver;i++ ) { 
		
		a_devolver.push_back( carga.a_devolver[i] );
		
	}
	
	cant_prestamos = carga.cant_prestamos;
	nro_socio = carga.nro_socio;
	
	return true;
	
}

bool socio::guardar ( ofstream &_archi ) const {
	
	if ( ( nombre.size() > 99 ) ||
		( apellido.size() > 99 ) ||
		( telefono.size() > 49 ) ||
		( domicilio.size() > 99 ) ||
		( path_foto.size() > 259 ) ||
		( a_devolver.size() > 3 ) ) {
		
		return false;
		
	}
	
	save_socio guardando;
	
	guardando.DNI = DNI;
	strcpy( guardando.nombre, nombre.c_str() );
	strcpy( guardando.apellido, apellido.c_str() );
	strcpy( guardando.telefono, telefono.c_str() );
	strcpy( guardando.domicilio, domicilio.c_str() );
	strcpy( guardando.path_foto, path_foto.c_str() );
	guardando.fecha_nacimiento = fecha_nacimiento;
	guardando.fecha_ingreso = fecha_ingreso;
	guardando.fecha_de_alta = fecha_de_alta;
	guardando.cant_devolver = a_devolver.size();
	
	for ( int i=0;i<guardando.cant_devolver;i++ ) { 
		
		guardando.a_devolver[i] = a_devolver[i];
		
	}
	
	guardando.cant_prestamos = cant_prestamos;
	guardando.nro_socio = nro_socio;
	
	_archi.write( reinterpret_cast<char*>( &guardando ), sizeof( guardando ) );
	
	return true;
	
}

vector<prestamo> socio::cargar_historial ( ) const {
	
//	vector<prestamo> historial;
//	prestamo carga;
//	ifstream archi( "Data\\Prestamos.dat", ios::binary );
//	archi.seekg( ios::end );
//	int tamanyo = archi.tellg() / sizeof( prestamo );
//	archi.seekg( ios::beg );
//	
//	for ( int i=0;i<tamanyo;i++ ) { 
//		
//		archi.read( reinterpret_cast<char*>( &carga ), sizeof( carga ) );
//		if ( carga.nro_socio == nro_socio ) {
//			
//			historial.push_back( carga );
//			
//		}
//		
//	}
//	
//	return historial;
	
	vector<prestamo> historial;
	prestamo carga;
	ifstream archi( "Data\\Prestamos.dat", ios::binary );
	
	while( archi.read( reinterpret_cast<char*>( &carga ), sizeof( carga ) ) ) {
		
		if ( carga.nro_socio == this->nro_socio ) {
			
			historial.push_back( carga );
			
		}
		
	}
	
	archi.close();
	
	return historial;
	
}

bool socio::archivar_prestamo ( const int &_pos ) const {
	
	if ( _pos >= a_devolver.size() ) {
		
		return false;
		
	}
	
	ofstream archi( "Data\\Prestamos.dat", ios::binary | ios::app );
	if ( !archi.is_open() ) {
		
		return false;
		
	}
	
	prestamo aux = a_devolver[_pos];
	archi.write( reinterpret_cast<char*>( &aux ), sizeof( aux ) );
	
	archi.close();
	
	return true;
	
}

// GET'S
vector<prestamo> socio::get_a_devolver ( ) const {
	
	return a_devolver;
	
}

int socio::get_cant_a_devolver ( ) const {
	
	return a_devolver.size();
	
}

int socio::get_a_devolver ( const int &_pos ) const {
	
	return a_devolver[_pos].codigo_libro;
	
}

string socio::get_pendientes ( ) const {
	
	stringstream ss;
	ss<<a_devolver.size();
	return ss.str();
	
}

vector<prestamo> socio::get_historial ( ) const {
	
	return ( this->cargar_historial() );
	
}

int socio::get_cant_leidos ( ) const {
	
	return cant_prestamos;
	
}

int socio::get_leido ( const int &_pos ) const {
	
	vector<prestamo> historial;
	prestamo carga;
	ifstream archi( "Data\\Prestamos.dat", ios::binary );
	archi.seekg( ios::end );
	int tamanyo = archi.tellg() / sizeof( prestamo );
	archi.seekg( ios::beg );
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		archi.read( reinterpret_cast<char*>( &carga ), sizeof( carga ) );
		if ( carga.nro_socio == nro_socio ) {
			
			historial.push_back( carga );
			
		}
		
	}
	
	if ( _pos < historial.size() ) {
		
		return historial[_pos].codigo_libro;
		
	}
	
	return -1;
	
}

int socio::get_nro_socio ( ) const {
	
	return nro_socio;
	
}

string socio::get_nro_socio_str ( ) const {
	
	stringstream ss;
	ss<<nro_socio;
	return ss.str();
	
}

// SET's
void socio::set_nro_socio( ) {
	
	nro_socio = get_nuevo_numero();
	
}

// AGREGAR
bool socio::push_prestamo ( const int &_cod_libro ) {
	
	if ( a_devolver.size() < 3 ) {
		
		prestamo nuevo;
		nuevo.codigo_libro = _cod_libro;
		nuevo.nro_socio = nro_socio;
		nuevo.fecha_prestamo = fecha::get_actual();
		nuevo.fecha_devolucion = ( fecha::get_actual() + fecha( 7 ) );
		a_devolver.push_back( nuevo );
		return true;
		
	} else {
		
		return false;
		
	}
	
}

// BORRAR
bool socio::libro_devuelto ( const int & _cod_libro ) {
	
	int tamanyo = a_devolver.size();
	
	for( int i=0;i<tamanyo;i++ ) { 
		
		if ( _cod_libro == a_devolver[i].codigo_libro ) {
			
			a_devolver[i].fecha_devolucion = fecha::get_actual();
			if ( this->archivar_prestamo( i ) == false ) {
				
				return false;
				
			}
			++cant_prestamos;
			a_devolver.erase( a_devolver.begin() + i );
			return true;
			
		}
		
	}
	
	return false;
	
}

// BUSQUEDA
bool socio::socio_buscado ( const string &_parametro ) const {
	
	int es_numero = atoi( _parametro.c_str() );
	
	switch ( es_numero ) {
		
	case 0:
		if ( nombre.find( _parametro ) != string::npos || apellido.find( _parametro ) != string::npos ) {
			
			return true;
			
		}
		break;
		
	default:
		if ( nro_socio == es_numero || DNI == es_numero ) {
			
			return true;
			
		}
		
	}
	
	return false;
	
}

// ATRIBUTOS Y MÉTODOS STATIC
int socio::numeros_no_disponibles = 0;

int socio::get_nuevo_numero ( ) {
	
	++numeros_no_disponibles;
	return numeros_no_disponibles - 1;
	
}

void socio::set_nros_no_disponibles( const int &_nro ) {
	
	numeros_no_disponibles = _nro;
	
}

int socio::get_nros_no_disponibles( ) {
	
	return numeros_no_disponibles;
	
}

// SOBRECARGA DE OPERADORES
bool socio::operator!= ( const socio &_comp ) const {
	
	return nro_socio != _comp.nro_socio;
	
}

// FUNCIONES EXTERNAS
bool socios_por_nombre( const socio &_comp1, const socio &_comp2 ) {
	
	if ( _comp1.apellido != _comp2.apellido ) {
		
		return _comp1.apellido < _comp2.apellido;
		
	} else if ( _comp1.nombre != _comp2.nombre ) {
		
		return _comp1.nombre < _comp2.nombre;
		
	}
	
	return _comp1.DNI < _comp2.DNI;
	
}

bool socios_por_lecturas( const socio &_comp1, const socio &_comp2 ) {
	
	if ( _comp1.get_cant_leidos() != _comp2.get_cant_leidos() ) {
		
		return _comp1.get_cant_leidos() > _comp2.get_cant_leidos();
		
	}
	
	return socios_por_nombre( _comp1, _comp2 );
	
}

bool socios_por_fecha_alta( const socio &_comp1, const socio &_comp2 ) {
	
	if ( _comp1.fecha_de_alta != _comp2.fecha_de_alta ) {
		
		return _comp1.fecha_de_alta < _comp2.fecha_de_alta;
		
	}
	
	return socios_por_nombre( _comp1, _comp2 );
	
}

bool socios_por_edad( const socio &_comp1, const socio &_comp2 ) {
	
	if ( _comp1.get_edad_str() != _comp2.get_edad_str() ) {
		
		return _comp1.get_edad_str() < _comp2.get_edad_str();
		
	}
	
	return socios_por_nombre( _comp1, _comp2 );
	
}

bool socios_por_pendientes( const socio &_comp1, const socio &_comp2 ) {
	
	if ( _comp1.get_cant_a_devolver() != _comp2.get_cant_a_devolver() ) {
		
		return _comp1.get_cant_a_devolver() > _comp2.get_cant_a_devolver();
		
	}
	
	return socios_por_nombre( _comp1, _comp2 );
	
}

bool socios_por_antiguedad( const socio &_comp1, const socio &_comp2 ) {
	
	if ( _comp1.get_fecha_ingreso() != _comp2.get_fecha_ingreso() ) {
		
		return _comp1.get_fecha_ingreso() < _comp2.get_fecha_ingreso();
		
	}
	
	return socios_por_nombre( _comp1, _comp2 );
	
}
//
///////////////////////////////////////////////////////////////////////////////
/// CLASE "socios_database"
///////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORES - DESTRUCTOR
socios_database::socios_database ( const string &_path_binario ) {
	
	nombre_archivo = _path_binario;
	
}

socios_database::~socios_database ( ) {
	
}

// CARGAR - GUARDAR
bool socios_database::cargar ( ) {
	
	ifstream i_archi( nombre_archivo.c_str(), ios::binary );
	if ( !i_archi.is_open() ) {
		
		return false;
		
	}
	
	int aux;
	if ( !i_archi.read( reinterpret_cast<char*>( &aux ), sizeof( aux ) ) ) {
		
		aux = 0;
		
	}
	socio::set_nros_no_disponibles( aux );
	
	socio carga_socio;
	
	while ( carga_socio.cargar( i_archi ) ) {
		
		socios.push_back( carga_socio );
		
	}
	
	i_archi.close();
	
	return true;
	
}

bool socios_database::guardar ( ) const {
	
	ofstream o_archi( nombre_archivo.c_str(), ios::binary );
	if ( !o_archi.is_open() ) {
		
		return false;
		
	}
	
	int aux = socio::get_nros_no_disponibles();
	o_archi.write( reinterpret_cast<char*>( &aux ), sizeof( aux ) );
	
	const int tamanyo = socios.size();
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( !socios[i].guardar( o_archi ) ) {
			
			return false;
			
		}
		
	}
	
	return true;
	
}

// GET´s
string socios_database::get_nombre_archivo ( ) const {
	
	return nombre_archivo;
	
}

socio & socios_database::get_socio ( const int &_DNI ) {
	
	const int tamanyo = socios.size();
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( socios[i].get_dni() == _DNI ) {
			
			return socios[i];
			
		}
		
	}
	
	return nsocio;
	
}

socio & socios_database::get_socio_cod ( const int &_codigo ) {
	
	const int tamanyo = socios.size();
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( socios[i].get_nro_socio() == _codigo ) {
			
			return socios[i];
			
		}
		
	}
	
	return nsocio;
	
}

socio & socios_database::get_socio_pos ( const int &_pos ) {
	
	if ( _pos < socios.size() && _pos >= 0 ) {
		
		return socios[_pos];
		
	}
	
	return nsocio;
	
}

int socios_database::get_cant_socios ( ) const {
	
	return socios.size();
	
}

// SET's
void socios_database::set_nombre_archivo ( const string &_path ) {
	
	nombre_archivo = _path;
	
}

// AGREGAR - BORRAR
void socios_database::push ( const socio &_nuevo ) {
	
	socios.push_back( _nuevo );
	
}

void socios_database::push ( const int &_DNI, const string &_nombre, const string &_apellido, const fecha &_nacimiento, const string &_domicilio, const string &_tel, const string &_path_foto, const fecha &_fecha_ingreso, const int &_cant_prestamos, const vector<prestamo> &_a_devolver ) {
	
	socio nuevo( _DNI, _nombre, _apellido, _nacimiento, _domicilio, _tel, _path_foto, _fecha_ingreso, _cant_prestamos, _a_devolver );
	nuevo.set_nro_socio();
	socios.push_back( nuevo );
	
}

bool socios_database::pop ( const int &_DNI ) {
	
	const int tamanyo = socios.size();
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( socios[i].get_dni() == _DNI ) {
			
			socios.erase( socios.begin() + i );
			return true;
			
		}
		
	}
	
	return false;
	
}

bool socios_database::pop_pos ( const int &_pos ) {
	
	if ( _pos < socios.size() && _pos >= 0 ) {
		
		socios.erase( socios.begin() + _pos );
		return true;
		
	}
	
	return false;
	
}

// ORDENAR
void socios_database::sort ( const int &_criterio ) {
	
	switch ( _criterio ) {
		
	case SociosPorNombre:
		std::sort( socios.begin(), socios.end(), socios_por_nombre );
		break;
		
	case SociosPorEdad:
		std::sort( socios.begin(), socios.end(), socios_por_edad );
		break;
		
	case SociosPorLecturas:
		std::sort( socios.begin(), socios.end(), socios_por_lecturas );
		break;
		
	case SociosPorAlta:
		std::sort( socios.begin(), socios.end(), socios_por_fecha_alta );
		break;
		
	case SociosPorPendientes:
		std::sort( socios.begin(), socios.end(), socios_por_pendientes );
		break;
		
	case SociosPorAntig:
		std::sort( socios.begin(), socios.end(), socios_por_antiguedad );
		
	}
	
}

// ATRIBUTOS Y MÉTODOS STATIC
socio socios_database::nsocio = socio();
//
///////////////////////////////////////////////////////////////////////////////
/// CLASE "bibliotecario"
///////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORES - DESTRUCTOR
bibliotecario::bibliotecario ( const int &_DNI, const string &_nombre, const string &_apellido, const fecha &_nacimiento, const string &_domicilio, const string &_tel, const string &_path_foto, const fecha &_fecha_ingreso, const int &_cant_prestamos, const float &_salario, const string &_curriculum, const string &_cta_usuario, const string &_cta_pass ): persona( _DNI, _nombre, _apellido, _nacimiento, _domicilio, _tel, _path_foto, _fecha_ingreso ) {
	
	cant_prestamos = 0;
	salario = -1;
	curriculum = "";
	cta_pass = "";
	cta_usuario = "";
	
}

bibliotecario::~bibliotecario ( ) {
	
}

// CARGAR - GUARDAR
bool bibliotecario::cargar ( ifstream &_archi ) {
	
	save_bibliotecario carga;
	if ( !_archi.read( reinterpret_cast<char*>( &carga ), sizeof( carga ) ) ) {
		
		return false;
		
	}
	
	DNI = carga.DNI;
	telefono = carga.telefono;
	nombre = carga.nombre;
	apellido = carga.apellido;
	domicilio = carga.domicilio;
	path_foto = carga.path_foto;
	fecha_nacimiento = carga.fecha_nacimiento;
	fecha_ingreso = carga.fecha_ingreso;
	fecha_de_alta = carga.fecha_de_alta;
	cant_prestamos = carga.cant_prestamos;
	salario = carga.salario;
	curriculum = carga.curriculum;
	cta_usuario = carga.cta_usuario;
	cta_pass = carga.cta_pass;
	
	return true;
	
}

bool bibliotecario::guardar ( ofstream &_archi ) const {
	
	if ( ( nombre.size() > 99 ) ||
		 ( apellido.size() > 99 ) ||
		 ( telefono.size() > 49 ) ||
		 ( domicilio.size() > 99 ) ||
		 ( path_foto.size() > 259 ) ||
		 ( curriculum.size() > 9999 ) ||
		 ( cta_usuario.size() > 20 ) ||
		 ( cta_pass.size() > 20 ) ) {
		
		return false;
		
	}
	
	save_bibliotecario guardando;
	
	guardando.DNI = DNI;
	strcpy( guardando.nombre, nombre.c_str() );
	strcpy( guardando.apellido, apellido.c_str() );
	strcpy( guardando.telefono, telefono.c_str() );
	strcpy( guardando.domicilio, domicilio.c_str() );
	strcpy( guardando.path_foto, path_foto.c_str() );
	guardando.fecha_nacimiento = fecha_nacimiento;
	guardando.fecha_ingreso = fecha_ingreso;
	guardando.fecha_de_alta = fecha_de_alta;
	guardando.cant_prestamos = cant_prestamos;
	guardando.salario = salario;
	strcpy( guardando.curriculum, curriculum.c_str() );
	strcpy( guardando.cta_usuario, cta_usuario.c_str() );
	strcpy( guardando.cta_pass, cta_pass.c_str() );
	
	_archi.write( reinterpret_cast<char*>( &guardando ), sizeof( guardando ) );
	
	return true;
	
}

// GET'S
int bibliotecario::get_cant_prestamos ( ) const {
	
	return cant_prestamos;
	
}

string bibliotecario::get_cant_prestamos_str ( ) const {
	
	stringstream ss;
	ss<<cant_prestamos;
	return ss.str();
	
}

float bibliotecario::get_salario ( ) const {
	
	return salario;
	
}

string bibliotecario::get_salario_str ( ) const {
	
	stringstream ss;
	ss<<salario;
	return ss.str();
	
}

string bibliotecario::get_curriculum ( ) const {
	
	return curriculum;
	
}

string bibliotecario::get_cta_usuario ( ) const {
	
	return cta_usuario;
	
}

string bibliotecario::get_cta_pass ( ) const {
	
	return cta_pass;
	
}

bool bibliotecario::buscado (const string & _criterio) {
	
	int es_numero = atoi( _criterio.c_str() );
	
	switch ( es_numero ) {
		
	case 0:
		if ( nombre.find( _criterio ) != string::npos || apellido.find( _criterio ) != string::npos || cta_usuario.find( _criterio ) != string::npos || curriculum.find( _criterio ) != string::npos ) {
			
			return true;
			
		}
		
	default:
		if ( DNI == es_numero ) {
			
			return true;
			
		}
		
	}
	
	return false;
	
}

// SET's
void bibliotecario::set_salario ( const float &_salario ) {
	
	salario = _salario;
	
}

void bibliotecario::set_curriculum ( const string &_curriculum ) {
	
	curriculum = _curriculum;
	
}

void bibliotecario::set_cta_usuario ( const string &_usr ) {
	
	cta_usuario = _usr;
	
}

void bibliotecario::set_cta_pass ( const string &_pass ) {
	
	cta_pass = _pass;
	
}

// AGREGAR
int bibliotecario::sumar_prestamo ( ) {
	
	++cant_prestamos;
	
	return cant_prestamos;
	
}

// SOBRECARGA DE OPERADORES
bibliotecario & bibliotecario::operator= ( const bibliotecario &_asignando ) {
	
	DNI = _asignando.DNI;
	telefono = _asignando.telefono;
	nombre = _asignando.nombre;
	apellido = _asignando.apellido;
	domicilio = _asignando.domicilio;
	path_foto = _asignando.path_foto;
	fecha_nacimiento = _asignando.fecha_nacimiento;
	fecha_ingreso = _asignando.fecha_ingreso;
	fecha_de_alta = _asignando.fecha_de_alta;
	cant_prestamos = _asignando.cant_prestamos;
	salario = _asignando.salario;
	curriculum = _asignando.curriculum;
	cta_usuario = _asignando.cta_usuario;
	cta_pass = _asignando.cta_pass;
	
	return *this;
	
}

// FUNCIONES EXTERNAS
bool bibliotecarios_por_nombre( const bibliotecario &_comp1, const bibliotecario &_comp2 ) {
	
	if ( _comp1.apellido != _comp2.apellido ) {
		
		return _comp1.apellido < _comp2.apellido;
		
	} else if ( _comp1.nombre != _comp2.nombre ) {
		
		return _comp1.nombre < _comp2.nombre;
		
	}
	
	return _comp1.DNI < _comp2.DNI;
	
}

bool bibliotecarios_por_prestamos( const bibliotecario &_comp1, const bibliotecario &_comp2 ) {
	
	if ( _comp1.get_cant_prestamos() != _comp2.get_cant_prestamos() ) {
		
		return _comp1.get_cant_prestamos() > _comp2.get_cant_prestamos();
		
	}
	
	return bibliotecarios_por_nombre( _comp1, _comp2 );
	
}

bool bibliotecarios_por_antiguedad( const bibliotecario &_comp1, const bibliotecario &_comp2 ) {
	
	if ( _comp1.get_antiguedad() != _comp2.get_antiguedad() ) {
		
		return _comp1.get_antiguedad() > _comp2.get_antiguedad();
		
	}
	
	return bibliotecarios_por_nombre( _comp1, _comp2 );
	
}

bool bibliotecarios_por_fecha_alta( const bibliotecario &_comp1, const bibliotecario &_comp2 ) {
	
	if ( _comp1.fecha_de_alta != _comp2.fecha_de_alta ) {
		
		return _comp1.fecha_de_alta < _comp2.fecha_de_alta;
		
	}
	
	return bibliotecarios_por_nombre( _comp1, _comp2 );
	
}

bool bibliotecarios_por_salario( const bibliotecario &_comp1, const bibliotecario &_comp2 ) {
	
	if ( _comp1.get_salario() != _comp2.get_salario() ) {
		
		return _comp1.get_salario() > _comp2.get_salario();
		
	}
	
	return bibliotecarios_por_nombre( _comp1, _comp2 );
	
}
//
///////////////////////////////////////////////////////////////////////////////
/// CLASE "bibliotecarios_database"
///////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORES - DESTRUCTOR
bibliotecarios_database::bibliotecarios_database ( const string &_path_binario ) {
	
	nombre_archivo = _path_binario;
	
}

bibliotecarios_database::~bibliotecarios_database ( ) {
	
}

// CARGAR - GUARDAR
bool bibliotecarios_database::cargar ( ) {
	
	ifstream i_archi( nombre_archivo.c_str(), ios::binary );
	if ( !i_archi.is_open() ) {
		
		return false;
		
	}
	
	bibliotecario carga_bib;
	
	while ( carga_bib.cargar( i_archi ) ) {
		
		bibliotecarios.push_back( carga_bib );
		
	}
	
	i_archi.close();
	
	return true;
	
}

bool bibliotecarios_database::guardar ( ) const {
	
	ofstream o_archi( nombre_archivo.c_str(), ios::binary );
	if ( !o_archi.is_open() ) {
		
		return false;
		
	}
	
	const int tamanyo = bibliotecarios.size();
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( !bibliotecarios[i].guardar( o_archi ) ) {
			
			return false;
			
		}
		
	}
	
	return true;
	
}

// GET´s
string bibliotecarios_database::get_nombre_archivo ( ) const {
	
	return nombre_archivo;
	
}

int bibliotecarios_database::size ( ) const {
	
	return bibliotecarios.size();
	
}

bibliotecario & bibliotecarios_database::get_bibliotecario ( const string &_cta_usuario ) {
	
	const int tamanyo = bibliotecarios.size();
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( bibliotecarios[i].get_cta_usuario() == _cta_usuario ) {
			
			return bibliotecarios[i];
			
		}
		
	}
	
	return nbib;	
	
}

bibliotecario & bibliotecarios_database::get_bibliotecario ( const int &_DNI ) {
	
	const int tamanyo = bibliotecarios.size();
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( bibliotecarios[i].get_dni() == _DNI ) {
			
			return bibliotecarios[i];
			
		}
		
	}
	
	return nbib;
	
}

bibliotecario & bibliotecarios_database::get_bibliotecario_pos ( const int &_pos ) {
	
	if ( _pos < bibliotecarios.size() && _pos >= 0 ) {
		
		return bibliotecarios[_pos];
		
	}
	
	return nbib;
	
}

int bibliotecarios_database::get_pos_bibliotecario ( const string &_cta_usuario ) const {
	
	const int tamanyo = bibliotecarios.size();
	
	int i;	
	for ( i=0;i<tamanyo;i++ ) { 
		
		if ( bibliotecarios[i].get_cta_usuario() == _cta_usuario ) {
			
			return i;
			
		}
		
	}
	
	return -1;
	
}

// SET's
void bibliotecarios_database::set_nombre_archivo ( const string &_path ) {
	
	nombre_archivo = _path;
	
}

// AGREGAR - BORRAR
void bibliotecarios_database::push ( const bibliotecario &_nuevo ) {
	
	bibliotecarios.push_back( _nuevo );
	
}

void bibliotecarios_database::push ( const int &_DNI, const string &_nombre, const string &_apellido, const fecha &_nacimiento, const string &_domicilio, const string &_tel, const string &_path_foto, const fecha &_fecha_ingreso, const int &_cant_prestamos, const float &_salario, const string &_curriculum, const string &_cta_usuario, const string &_cta_pass ) {
	
	bibliotecarios.push_back( bibliotecario( _DNI, _nombre, _apellido, _nacimiento, _domicilio, _tel, _path_foto, _fecha_ingreso, _cant_prestamos, _salario, _curriculum, _cta_usuario, _cta_pass ) );
	
}

bool bibliotecarios_database::pop ( const int &_DNI ) {
	
	const int tamanyo = bibliotecarios.size();
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( bibliotecarios[i].get_dni() == _DNI ) {
			
			bibliotecarios.erase( bibliotecarios.begin() + i );
			return true;
			
		}
		
	}
	
	return false;
	
}

bool bibliotecarios_database::pop_pos ( const int &_pos ) {
	
	if ( _pos < bibliotecarios.size() && _pos >= 0 ) {
		
		bibliotecarios.erase( bibliotecarios.begin() + _pos );
		return true;
		
	}
	
	return false;
	
}

// COMPROBAR
int bibliotecarios_database::comprobar_cta_bibliotecario ( const string &_cta_bib ) const {
	
	return get_pos_bibliotecario( _cta_bib );
	
}

bool bibliotecarios_database::comprobar_pass_bibliotecario ( const int &_pos, const string &_pass_bib ) const {
	
	if ( _pos < bibliotecarios.size() ) {
		
		return bibliotecarios[_pos].get_cta_pass() == _pass_bib;
		
	}
	
	return false;
	
}

// ORDENAR
void bibliotecarios_database::sort ( const int &_criterio ) {
	
	switch ( _criterio ) {
		
	case BibPorNombre:
		std::sort( bibliotecarios.begin(), bibliotecarios.end(), bibliotecarios_por_nombre );
		break;
		
	case BibPorPrestamos:
		std::sort( bibliotecarios.begin(), bibliotecarios.end(), bibliotecarios_por_prestamos );
		break;
		
	case BibPorAlta:
		std::sort( bibliotecarios.begin(), bibliotecarios.end(), bibliotecarios_por_fecha_alta );
		break;
		
	case BibPorAntig:
		std::sort( bibliotecarios.begin(), bibliotecarios.end(), bibliotecarios_por_antiguedad );
		break;
		
	default:
		std::sort( bibliotecarios.begin(), bibliotecarios.end(), bibliotecarios_por_salario );
		
	}
	
}

// ATRIBUTOS STATIC
bibliotecario bibliotecarios_database::nbib = bibliotecario();

