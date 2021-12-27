///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/Core/utilidades.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en utilidades.h
///////////////////////////////////////////////////////////////////////////////

#include "utilidades.h"

#include <sstream>
#include <windows.h>
#include <fstream>

#include <wx/image.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
/// CLASE "fecha"
///////////////////////////////////////////////////////////////////////////////

// CONSTRUCTORES - DESTRUCTOR
fecha::fecha ( const int &_anyo, const int &_mes, const int &_dia, const int &_hora, const int &_min, const int &_sec ) {
	
	anyo = _anyo;
	mes = _mes;
	dia = _dia;
	hora = _hora;
	minutos = _min;
	segundos = _sec;
	
}

fecha::fecha ( const time_t &_t1 ) {
	
	tm *ptr_tm = localtime( &_t1 );
	dia = ptr_tm->tm_mday;
	mes = ptr_tm->tm_mon + 1;
	anyo = ptr_tm->tm_year + 1900;
	hora =  ptr_tm->tm_hour;
	minutos = ptr_tm->tm_min;
	segundos = ptr_tm->tm_sec;
	
}

fecha::fecha ( const tm *const _ptr_tm ) {
	
	dia = _ptr_tm->tm_mday;
	mes = _ptr_tm->tm_mon + 1;
	anyo = _ptr_tm->tm_year + 1900;
	hora =  _ptr_tm->tm_hour;
	minutos = _ptr_tm->tm_min;
	segundos = _ptr_tm->tm_sec;
	
}

fecha::~fecha ( ) {
	
}

// GET's
int fecha::get_anyo ( ) const {
	
	return anyo;
	
}

int fecha::get_mes ( ) const {
	
	return mes;
	
}

int fecha::get_dia ( ) const {
	
	return dia;
	
}

int fecha::get_hora ( ) const {
	
	return hora;
	
}

int fecha::get_minutos ( ) const {
	
	return minutos;
	
}

int fecha::get_segundos ( ) const {
	
	return segundos;
	
}

string fecha::get_anyo_str ( ) const {
	
	stringstream ss;
	ss<<anyo;
	return ss.str();
	
}

string fecha::get_mes_str ( ) const {
	
	stringstream ss;
	ss<<mes;
	return ss.str();
	
}

string fecha::get_dia_str ( ) const {
	
	stringstream ss;
	ss<<dia;
	return ss.str();
	
}

string fecha::get_hora_str ( ) const {
	
	stringstream ss;
	ss<<hora;
	return ss.str();
	
}

string fecha::get_minutos_str ( ) const {
	
	stringstream ss;
	ss<<minutos;
	return ss.str();
	
}

string fecha::get_segundos_str ( ) const {
	
	stringstream ss;
	ss<<segundos;
	return ss.str();
	
}

string fecha::str ( ) const {
	
	stringstream ss;
	ss<<anyo;
	ss<<mes;
	ss<<dia;
	return ss.str();
	
}

string fecha::str_completo ( ) const {
	
	stringstream ss;
	ss<<anyo;
	ss<<mes;
	ss<<dia;
	ss<<hora;
	ss<<minutos;
	ss<<segundos;
	return ss.str();
	
}

string fecha::str_ddmmaaaa ( ) const {
	
	stringstream ss;
	ss<<dia;
	ss<<"/";
	ss<<mes;
	ss<<"/";
	ss<<anyo;
	return ss.str();
	
}

time_t fecha::tt ( ) const {
	
	tm conver;
	conver.tm_year = anyo - 1900;
	conver.tm_mon = mes;
	conver.tm_mday = dia;
	conver.tm_hour = hora;
	conver.tm_min = minutos;
	conver.tm_sec = segundos;
	
	time_t retorno = mktime( &conver );
	
	return retorno;
	
}

// SET's
void fecha::set_anyo ( const int &_valor ) {
	
	anyo = _valor;
	
}

void fecha::set_anyo ( const time_t &_t1 ) {
	
	tm *ptr_tm = localtime( &_t1 );
	anyo = ptr_tm->tm_year + 1900;
	
}

void fecha::set_anyo ( const tm *const _ptr_tm ) {
	
	anyo = _ptr_tm->tm_year + 1900;
	
}

void fecha::set_mes ( const int &_valor ) {
	
	mes = _valor;
	
}

void fecha::set_mes ( const time_t &_t1 ) {
	
	tm *ptr_tm = localtime( &_t1 );
	mes = ptr_tm->tm_mon + 1;
	
}

void fecha::set_mes ( const tm *const _ptr_tm ) {
	
	mes = _ptr_tm->tm_mon + 1;
	
}

void fecha::set_dia ( const int &_valor ) {
	
	dia = _valor;
	
}

void fecha::set_dia ( const time_t &_t1 ) {
	
	tm *ptr_tm = localtime( &_t1 );
	dia = ptr_tm->tm_mday;
	
}

void fecha::set_dia ( const tm *const _ptr_tm ) {
	
	dia = _ptr_tm->tm_mday;
	
}

void fecha::set_hora ( const int &_valor ) {
	
	hora = _valor;
	
}

void fecha::set_hora ( const time_t &_t1 ) {
	
	tm *ptr_tm = localtime( &_t1 );
	hora =  ptr_tm->tm_hour;
	
}

void fecha::set_hora ( const tm *const _ptr_tm ) {
	
	hora =  _ptr_tm->tm_hour;
	
}

void fecha::set_minutos ( const int &_valor ) {
	
	minutos = _valor;
	
}

void fecha::set_minutos ( const time_t &_t1 ) {
	
	tm *ptr_tm = localtime( &_t1 );
	minutos = ptr_tm->tm_min;
	
}

void fecha::set_minutos ( const tm *const _ptr_tm ) {
	
	minutos = _ptr_tm->tm_min;
	
}

void fecha::set_segundos ( const int &_valor ) {
	
	segundos = _valor;
	
}

void fecha::set_segundos ( const time_t &_t1 ) {
	
	tm *ptr_tm = localtime( &_t1 );
	segundos = ptr_tm->tm_sec;
	
}

void fecha::set_segundos ( const tm *const _ptr_tm ) {
	
	segundos = _ptr_tm->tm_sec;
	
}

void fecha::set_actual ( ) {
	
	time_t tt = time( 0 );
	tm *ptr_tm = localtime( &tt );
	dia = ptr_tm->tm_mday;
	mes = ptr_tm->tm_mon + 1;
	anyo = ptr_tm->tm_year + 1900;
	hora =  ptr_tm->tm_hour;
	minutos = ptr_tm->tm_min;
	segundos = ptr_tm->tm_sec;
	
}

void fecha::set_from_tt ( const time_t &_t1 ) {
	
	tm *ptr_tm = localtime( &_t1 );
	dia = ptr_tm->tm_mday;
	mes = ptr_tm->tm_mon + 1;
	anyo = ptr_tm->tm_year + 1900;
	hora =  ptr_tm->tm_hour;
	minutos = ptr_tm->tm_min;
	segundos = ptr_tm->tm_sec;
	
}

// SOBRECARGA DE OPERADORES
fecha & fecha::operator= ( const fecha &_asignando ) {
	
	anyo = _asignando.anyo;
	mes = _asignando.mes;
	dia = _asignando.dia;
	hora = _asignando.hora;
	minutos = _asignando.minutos;
	segundos = _asignando.segundos;
	return *this;
	
}

fecha & fecha::operator= ( const time_t &_t1 ) {
	
	tm *ptr_tm = localtime( &_t1 );
	dia = ptr_tm->tm_mday;
	mes = ptr_tm->tm_mon + 1;
	anyo = ptr_tm->tm_year + 1900;
	hora =  ptr_tm->tm_hour;
	minutos = ptr_tm->tm_min;
	segundos = ptr_tm->tm_sec;
	return *this;
	
}

fecha fecha::operator- ( const fecha &_sustraendo ) {
	
	time_t minuendo = this->tt();
	time_t sustraendo = _sustraendo.tt();
	int diferencia_dias = difftime( minuendo, sustraendo ); // Diferencia en segundos.
	diferencia_dias /= 86400; // Diferencia en días. 86400 es la cantidad de segundos en el día (60 * 60 * 24).
	
	int ret_anyo = diferencia_dias / 365;
	int ret_mes = ( diferencia_dias % 365 ) / 30;
	int ret_dia = ( diferencia_dias % 365 ) % 30;
	
	return fecha( ret_anyo, ret_mes, ret_dia );
	
}

fecha fecha::operator+ ( const fecha &_sumando ) {
	
	fecha nuevo;
	nuevo.set_anyo( this->get_anyo() + _sumando.get_anyo() );
	nuevo.set_mes( this->get_mes() + _sumando.get_mes() );
	nuevo.set_dia( this->get_dia() + _sumando.get_dia() );
	nuevo.set_hora( this->get_hora() + _sumando.get_hora() );
	nuevo.set_minutos( this->get_minutos() + _sumando.get_minutos() );
	nuevo.set_segundos( this->get_segundos() + _sumando.get_segundos() );
	
	return nuevo;
	
}

bool fecha::operator< ( const fecha &_comp ) const {
	
	if ( anyo != _comp.anyo ) {
		
		return anyo < _comp.anyo;
		
	} else if ( mes != _comp.mes ) {
		
		return mes < _comp.mes;
		
	} else if ( dia != _comp.dia ) {
		
		return dia < _comp.dia;
		
	} else if ( hora != _comp.hora ) {
		
		return hora < _comp.hora;
		
	} else if ( minutos != _comp.minutos ) {
		
		return minutos < _comp.minutos;
		
	}
	
	return segundos < _comp.segundos;
	
}

bool fecha::operator!= ( const fecha &_comp ) const {
	
	bool b1 = anyo != _comp.anyo;
	bool b2 = mes != _comp.mes;
	bool b3 = dia != _comp.dia;
	bool b4 = hora != _comp.hora;
	bool b5 = minutos != _comp.minutos;
	bool b6 = segundos != _comp.segundos;
	
	return ( b1 || b2 || b3 || b4 || b5 || b6 );
	
}

// MIEMBROS STATIC
fecha fecha::npos = fecha();

fecha fecha::get_actual ( ) {
	
	fecha actual;
	actual.set_actual();
	return actual;
	
}
//
///////////////////////////////////////////////////////////////////////////////
/// CLASE "hexArchivos"
///////////////////////////////////////////////////////////////////////////////
//
hexArchivos::hexArchivos ( ) {
	
}

hexArchivos::~hexArchivos ( ) {
	
}

void hexArchivos::comprobar_carpetas ( ) {
	
	char buf[MAX_PATH];
	GetCurrentDirectory( MAX_PATH, buf );
	string directory = buf;
	directory += "\\Data";
	CreateDirectory(directory.c_str(),NULL);
	
	GetCurrentDirectory( MAX_PATH, buf );
	directory = buf;
	directory += "\\Img";
	CreateDirectory( directory.c_str(),NULL );
	
	GetCurrentDirectory( MAX_PATH, buf );
	directory = buf;
	directory += "\\Img\\Resources";
	CreateDirectory( directory.c_str(),NULL );
	
	GetCurrentDirectory( MAX_PATH, buf );
	directory = buf;
	directory += "\\Img\\Local";
	CreateDirectory( directory.c_str(),NULL );
	
	GetCurrentDirectory( MAX_PATH, buf );
	directory = buf;
	directory += "\\Img\\Local\\Bibliotecarios";
	CreateDirectory( directory.c_str(),NULL );
	
	GetCurrentDirectory( MAX_PATH, buf );
	directory = buf;
	directory += "\\Img\\Local\\Socios";
	CreateDirectory( directory.c_str(),NULL );
	
}

bool hexArchivos::comprobar_socios ( ) {
	
	ifstream archi( "Data\\Socios.dat", ios::binary );
	ofstream crear;
	if ( !archi ) {
		
		if ( !crear ) {
			
			archi.close();
			crear.close();
			return false;
			
		}
		
		archi.close();
		crear.open( "Data\\Socios.dat", ios::binary );
		crear.close();
		
	}
	
	return true;
	
}

bool hexArchivos::comprobar_bibliotecarios ( ) {
	
	ifstream archi( "Data\\Bibliotecarios.dat", ios::binary );
	ofstream crear;
	if ( !archi ) {
		
		if ( !crear ) {
			
			archi.close();
			crear.close();
			return false;
			
		}
		
		archi.close();
		crear.open( "Data\\Bibliotecarios.dat", ios::binary );
		crear.close();
		
	}
	
	return true;
	
}

bool hexArchivos::comprobar_libros ( ) {
	
	ifstream archi( "Data\\Libros.dat", ios::binary );
	ofstream crear;
	if ( !archi ) {
		
		if ( !crear ) {
			
			archi.close();
			crear.close();
			return false;
			
		}
		
		archi.close();
		crear.open( "Data\\Libros.dat", ios::binary );
		crear.close();
		
	}
	
	return true;
	
}

bool hexArchivos::comprobar_autores ( ) {
	
	ifstream archi( "Data\\Autores.dat", ios::binary );
	ofstream crear;
	if ( !archi ) {
		
		if ( !crear ) {
			
			archi.close();
			crear.close();
			return false;
			
		}
		
		archi.close();
		crear.open( "Data\\Autores.dat", ios::binary );
		crear.close();
		
	}
	
	return true;
	
}

bool hexArchivos::comprobar_prestamos ( ) {
	
	ifstream archi( "Data\\Prestamos.dat", ios::binary );
	ofstream crear;
	if ( !archi ) {
		
		if ( !crear ) {
			
			archi.close();
			crear.close();
			return false;
			
		}
		
		archi.close();
		crear.open( "Data\\Prestamos.dat", ios::binary );
		crear.close();
		
	}
	
	return true;
	
}
//
///////////////////////////////////////////////////////////////////////////////
/// CLASE "EditarImagen"
///////////////////////////////////////////////////////////////////////////////
//
wxBitmap EditarImagen::ajustar_tamanyo ( const wxBitmap &_origen, const int &_ancho_maximo, const int &_altura_maxima ) {
	
	// Se guardan las dimensiones originales en memoria. Van a ser usados para determinar la escala.
	int ancho_original, altura_original;
	ancho_original = _origen.GetWidth();
	altura_original = _origen.GetHeight();
	
	// Este es el valor de retorno.
	wxBitmap resultado;
	
	// Si el ancho es mayor que el alto, se determina la escala para la altura.
	if ( ancho_original >= altura_original && ancho_original > _ancho_maximo ) {
		
		float escala_altura = (float)_ancho_maximo / (float)ancho_original; // Determina la escala.
		wxImage img = _origen.ConvertToImage(); // Se crea una imagen del Bitmap.
		// Ahora se usa Rescale con las dimensiones de escala.
		resultado = wxBitmap( img.Rescale( _ancho_maximo, (int)( altura_original * escala_altura ) ) );
		
	} else if (altura_original >= ancho_original && altura_original > _altura_maxima) {
		
		// En este caso se hace un proceso similar, pero para el ancho en lugar de la altura.
		float escala_ancho = (float)_altura_maxima / (float)altura_original;
		wxImage img = _origen.ConvertToImage();
		resultado = wxBitmap( img.Rescale( (int)( ancho_original * escala_ancho ), _altura_maxima ) );
		
	} else { // No se hace nada, se devuelve el original.
		
		return _origen;
		
	}
	
	/* Ahora se recorta la imagen para adoptar la escala original, de otra forma,
	el gráfico mismo sería del tamaño correcto, pero el objeto Bitmap seguiría
	teniendo las medidas originales (que son demasiado grandes). */
	resultado.SetWidth( _ancho_maximo );
	resultado.SetHeight( _altura_maxima );
	
	return resultado;
	
}

