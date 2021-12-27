///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_libros.h
// Propósito:   Interfaz de la base de datos de los libros.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// que trabaja exclusivamente con la base de datos de los libros.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_LIBROS_H
#define VENTANA_LIBROS_H

#include "Ventanas.h"
#include "ventana_agregar_libro.h"
#include "ventana_ayuda.h"

#include "Core\programa.h"

#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////////

class ventana_libros : public vLibros {

protected:
	// SELECCION
	void seleccion( const bool &_seleccionado = true );
	// EVENTOS GRILLA
	void refresh( const bool &_conservar_seleccion = false );
	void click_izq_grilla( wxGridEvent &_event );
	void Dclick_grilla( wxGridEvent &_event );
	void click_der_grilla( wxGridEvent &_event );
	// BARRA DE HERRAMIENTAS
	void click_boton_borrar( wxCommandEvent &_event );
	void click_boton_agregar( wxCommandEvent &_event );
	void click_editar_libro( wxCommandEvent& event ) ;
	void click_boton_prestar( wxCommandEvent &_event );
	void click_boton_devolver( wxCommandEvent &_event );
	void click_boton_detalles( wxCommandEvent &_event );
	void click_boton_estadisticas( wxCommandEvent &_event );
	void cambio_orden( wxCommandEvent &_event );
	void click_buscar( wxCommandEvent &_event );
	void click_boton_restaurar( wxCommandEvent &_event );
	void click_boton_CDU( wxCommandEvent &_event );
	void click_boton_ayuda( wxCommandEvent &_event );
	// EVENTOS CDU
	void principal_elegido( wxCommandEvent &_event );
	void sub_1_elegido( wxCommandEvent &_event );
	void sub_2_elegido( wxCommandEvent &_event );
	// BOTONES VENTANA
	void click_boton_aceptar( wxCommandEvent &_event );
	void click_boton_cancelar( wxCommandEvent &_event );
	
protected:
	Programa *programa;
	Programa *anterior;
	int fila;
	vector<int> pos_real;
	bool cambios;
	ventana_ayuda *Ayuda;

public:
	ventana_libros( wxWindow *_parent, Programa *_programa = NULL );
	~ventana_libros();
	
	// CLASES AMIGAS
	friend class ventana_agregar_libro;

};

#endif

