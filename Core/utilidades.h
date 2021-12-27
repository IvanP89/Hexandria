///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/Core/utilidades.h
// Propósito:   Conjunto de funciones y clases generales del proyecto.
// Autor:       Iván Pizarro.
//
// En este archivo se declaran las clases y funciones para diversos propósitos
// no específicos que van a ser usados por las clases principales del programa.
///////////////////////////////////////////////////////////////////////////////

#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <ctime>
#include <string>

#include <wx/bitmap.h>
using namespace std;


// ----------------------------------------------------------------------------
// fecha: Clase para trabajar con fechas.
//
// Contiene los atributos y métodos necesarios para realizar todas las operacio-
// nes necesarias con fechas, generando un marco para trabajar con las mismas
// de manera más simple que con la biblioteca ctime en el resto del proyecto.
// ----------------------------------------------------------------------------

class fecha {
	
protected:
	int anyo;
	int mes;
	int dia;
	int hora;
	int minutos;
	int segundos;
	
public:
	fecha( const int &_anyo = 0,
		   const int &_mes = 0,
	       const int &_dia = 0,
		   const int &_hora = 0,
		   const int &_min = 0,
		   const int &_sec = 0 );
	fecha( const time_t &_t1 );
	fecha( const tm *const _ptr_tm );
	~fecha();
	// GET's
	int get_anyo() const;
	int get_mes() const;
	int get_dia() const;
	int get_hora() const;
	int get_minutos() const;
	int get_segundos() const;
	string get_anyo_str() const;
	string get_mes_str() const;
	string get_dia_str() const;
	string get_hora_str() const;
	string get_minutos_str() const;
	string get_segundos_str() const;
	string str() const;
	string str_completo() const;
	string str_ddmmaaaa() const;
	time_t tt() const;
	// SET's
	void set_anyo( const int &_valor );
	void set_anyo( const time_t &_t1 );
	void set_anyo( const tm *const _ptr_tm );
	void set_mes( const int &_valor );
	void set_mes( const time_t &_t1 );
	void set_mes( const tm *const _ptr_tm );
	void set_dia( const int &_valor );
	void set_dia( const time_t &_t1 );
	void set_dia( const tm *const _ptr_tm );
	void set_hora( const int &_valor );
	void set_hora( const time_t &_t1 );
	void set_hora( const tm *const _ptr_tm );
	void set_minutos( const int &_valor );
	void set_minutos( const time_t &_t1 );
	void set_minutos( const tm *const _ptr_tm );
	void set_segundos( const int &_valor );
	void set_segundos( const time_t &_t1 );
	void set_segundos( const tm *const _ptr_tm );
	void set_actual();
	void set_from_tt( const time_t &_t1 );
	// SOBRECARGA DE OPERADORES
	fecha & operator=( const fecha &_asignando );
	fecha & operator=( const time_t &_t1 );
	fecha operator-( const fecha &_sustraendo );
	fecha operator+( const fecha &_sumando );
	bool operator<( const fecha &_comp ) const;
	bool operator!=( const fecha &_comp ) const;
	// MIEMBROS STATIC
	static fecha npos;
	static fecha get_actual();
	
};


// ----------------------------------------------------------------------------
// Archivos: Clase para el manejo de errores de falta de archivos.
//
// Esta clase reune funciones que comprueban que los binarios existan y crean
// los que faltan.
// ----------------------------------------------------------------------------

class hexArchivos {
	
public:
	hexArchivos();
	~hexArchivos();
	static void comprobar_carpetas();
	static bool comprobar_socios();
	static bool comprobar_bibliotecarios();
	static bool comprobar_libros();
	static bool comprobar_autores();
	static bool comprobar_prestamos();
	
};


// ----------------------------------------------------------------------------
// EditarImagen: Clase para la edición de imágenes.
// ----------------------------------------------------------------------------

class EditarImagen {
	
public:
	static wxBitmap ajustar_tamanyo( const wxBitmap &_origen,
	                                 const int &_ancho_maximo = 150,
	                                 const int &_altura_maxima = 150 );
	
};

#endif

