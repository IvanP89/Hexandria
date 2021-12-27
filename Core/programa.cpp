///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/Core/programa.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en programa.h
///////////////////////////////////////////////////////////////////////////////

#include "programa.h"
#include "utilidades.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// CLASE "Programa"
///////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORES - DESTRUCTORES
Programa::Programa ( ) {
	
	cambios = false;
	cuenta_activa = NULL;
	
	cuenta_admin = "hxAdmin";
	pass_admin = "poo2012";
	
}

Programa::~Programa ( ) {
	
}

void Programa::inicializar ( ) {
	
	estan_todos_los_binarios = this->comprobar_archivos();
	
	if ( estan_todos_los_binarios == true ) {
		
		carga_exitosa = this->cargar();
		
	} else {
		
		carga_exitosa = false;
		
	}	
	
}

// CARGAR - GUARDAR
bool Programa::comprobar_archivos ( ) const {
	
	hexArchivos::comprobar_carpetas();
	
	bool b1 = hexArchivos::comprobar_autores();
	bool b2 = hexArchivos::comprobar_libros();
	bool b3 = hexArchivos::comprobar_socios();
	bool b4 = hexArchivos::comprobar_bibliotecarios();
	bool b5 = hexArchivos::comprobar_prestamos();
	
	return ( b1 && b2 && b3 && b4 && b5 );
	
}

bool Programa::cargar ( ) {
	
	bool b1 = autores.cargar();
	bool b2 = libros.cargar();
	bool b3 = socios.cargar();
	bool b4 = bibliotecarios.cargar();
	
	cambios = false;
	
	return ( b1 && b2 && b3 && b4 );
	
}

bool Programa::guardar ( ) {
	
	bool b1 = autores.guardar();
	bool b2 = libros.guardar();
	bool b3 = socios.guardar();
	bool b4 = bibliotecarios.guardar();
	
	cambios = false;
	
	return ( b1 && b2 && b3 && b4 );
	
}

bool Programa::get_carga_exitosa ( ) const {
	
	return carga_exitosa;
	
}

// LOGIN
void Programa::set_cuenta_activa ( bibliotecario *_activa ) {
	
	cuenta_activa = _activa;
	
}

bibliotecario * Programa::get_cuenta_activa ( ) const {
	
	return cuenta_activa;
	
}

// ADMINISTRACIÓN DE CONTRASEÑAS
bool Programa::comprobar_cta_admin ( const string &_cta_admin ) const {
	
	return cuenta_admin == _cta_admin;
	
}

bool Programa::comprobar_pass_admin ( const string &_pass_admin ) const {
	
	return pass_admin == _pass_admin;
	
}

// REGISTRAR CAMBIOS
bool Programa::get_cambios ( ) const {
	
	return cambios;
	
}

bool Programa::set_cambios ( const bool &_cambios ) {
	
	cambios = _cambios;
	return cambios;
	
}

void Programa::set_cambios_sombra ( const Programa* const _programa ) {
	
	if ( _programa->get_cuenta_activa() != NULL ) {
		
		string usuario = _programa->get_cuenta_activa()->get_cta_usuario();
		cuenta_activa = &( bibliotecarios.get_bibliotecario( usuario ) );
		
	} else {
		
		cuenta_activa = NULL;
		
	}
	
	autores = _programa->autores;
	libros = _programa->libros;
	socios = _programa->socios;
	bibliotecarios = _programa->bibliotecarios;
	
	
	cambios = true;
	
}

// REGISTRAR PRÉSTAMOS Y DEVOLUCIONES
bool Programa::prestamo_dni ( const int &_DNI_socio, const int &_codigo_libro ) {
	
	socio *ptr_socio = &socios.get_socio( _DNI_socio );
	libro *ptr_libro = &libros.get_libro( _codigo_libro );
	
	if ( *ptr_socio != socios_database::nsocio ) {
		
		if ( ptr_socio->push_prestamo( _codigo_libro ) == true ) {
			
			ptr_libro->set_prestado( true );
			if ( cuenta_activa ) {
				
				cuenta_activa->sumar_prestamo();
				
			}
			return true;
			
		}
		
	}
	
	return false;
	
}

bool Programa::prestamo_nro ( const int &_nro_socio, const int &_codigo_libro ) {
	
	socio *ptr_socio = &socios.get_socio_cod( _nro_socio );
	libro *ptr_libro = &libros.get_libro( _codigo_libro );
	
	if ( *ptr_socio != socios_database::nsocio ) {
		
		if ( ptr_socio->push_prestamo( _codigo_libro ) == true ) {
			
			ptr_libro->set_prestado( true );
			if ( cuenta_activa ) {
				
				cuenta_activa->sumar_prestamo();
				
			}
			return true;
			
		}
		
	}
	
	return false;
	
}

bool Programa::devolucion_dni ( const int &_DNI_socio, const int &_codigo_libro ) {
	
	socio *ptr_socio = &socios.get_socio( _DNI_socio );
	libro *ptr_libro = &libros.get_libro( _codigo_libro );
	
	if (  *ptr_socio != socios_database::nsocio ) {
		
		if ( ptr_socio->libro_devuelto( _codigo_libro ) ) {
			
			ptr_libro->sumar_prestamo();
			ptr_libro->set_prestado( false );
			return true;
			
		}
		
	}
	
	return false;
	
}

bool Programa::devolucion_nro ( const int &_nro_socio, const int &_codigo_libro ) {
	
	socio *ptr_socio = &socios.get_socio_cod( _nro_socio );
	libro *ptr_libro = &libros.get_libro( _codigo_libro );
	
	if (  *ptr_socio != socios_database::nsocio ) {
		
		if ( ptr_socio->libro_devuelto( _codigo_libro ) ) {
			
			ptr_libro->sumar_prestamo();
			ptr_libro->set_prestado( false );
			return true;
			
		}
		
	}
	
	return false;
	
}

// OTROS
bool Programa::es_sombra ( ) const {
	
	return false;
	
}
//
//
///////////////////////////////////////////////////////////////////////////////
/// CLASE "Singleton"
///////////////////////////////////////////////////////////////////////////////

Singleton* Singleton::instancia = NULL;
Programa* Singleton::base_activa = NULL;

Singleton * Singleton::obtener_instancia ( ) {
	
	if ( !instancia ) {
		
		instancia = new Singleton;
		
	}
	
	return instancia;
	
}

Programa * Singleton::get_base_activa ( ) {
	
	return base_activa;
	
}

Programa * Singleton::set_base_activa ( Programa *_activa ) {
	
	base_activa = _activa;
	
}
//
//
///////////////////////////////////////////////////////////////////////////////
/// CLASE "ProgramaSombra"
///////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORES - DESTRUCTORES
ProgramaSombra::ProgramaSombra ( const Programa* const _programa ) {
	
	autores = _programa->autores;
	libros = _programa->libros;
	socios = _programa->socios;
	bibliotecarios = _programa->bibliotecarios;
	
	bibliotecario *cuenta = _programa->get_cuenta_activa();
	if ( cuenta != NULL ) {
		
		cuenta_activa = &( bibliotecarios.get_bibliotecario( cuenta->get_cta_usuario() ) );
		
	} else {
		
		cuenta_activa = NULL;
		
	}
	
	cambios = false;
	
}

ProgramaSombra::~ProgramaSombra ( ) {
	
}

void Programa::no_instanciar ( ) {
	
}

