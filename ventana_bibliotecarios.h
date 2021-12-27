///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_bibliotecarios.h
// Prop�sito:   Interfaz de la base de datos de los bibliotecarios.
// Autor:       Iv�n Pizarro.
//
// En este archivo se declara el dise�o de la clase que que define a la ventana
// que trabaja exclusivamente con la base de datos de los bibliotecarios.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_BIBLIOTECARIOS_H
#define VENTANA_BIBLIOTECARIOS_H

#include "Ventanas.h"
#include "ventana_ayuda.h"

#include "Core\programa.h"

///////////////////////////////////////////////////////////////////////////////

class ventana_bibliotecarios : public vBibliotecarios {

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
	void click_editar_bib( wxCommandEvent &_event );
	void click_boton_detalles( wxCommandEvent &_event );
	void click_boton_estadisticas( wxCommandEvent &_event );
	void cambio_orden( wxCommandEvent &_event );
	void click_buscar( wxCommandEvent &_event );
	void click_boton_restaurar( wxCommandEvent &_event );
	void click_boton_ayuda( wxCommandEvent &_event );
	// BOTONES VENTANA
	void click_boton_aceptar( wxCommandEvent &_event );
	void click_boton_cancelar( wxCommandEvent &_event );
	// CARGA DE IMAGEN
	void cargar_imagen( const string &_path );
	
protected:
	ProgramaSombra *programa;
	int fila;
	vector<int> pos_real;
	bool cambios;
	ventana_ayuda *Ayuda;
	
public:
	ventana_bibliotecarios( wxWindow *_parent );
	~ventana_bibliotecarios();
	
};

#endif

