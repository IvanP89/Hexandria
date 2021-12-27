///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_socios.h
// Propósito:   Interfaz de la base de datos de los socios.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// que trabaja exclusivamente con la base de datos de los socios.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_SOCIOS_H
#define VENTANA_SOCIOS_H

#include "Ventanas.h"
#include "ventana_ayuda.h"

#include "Core\programa.h"

#include <vector>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////

class ventana_socios : public vSocios {

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
	void click_editar_socio( wxCommandEvent &_event ) ;
	void click_boton_prestar( wxCommandEvent &_event );
	void click_boton_devolver( wxCommandEvent &_event );
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
	Programa *programa;
	Programa *anterior;
	int fila;
	vector<int> pos_real;
	bool cambios;
	ventana_ayuda *Ayuda;
	
public:
	ventana_socios( wxWindow *_parent, Programa *_programa = NULL );
	~ventana_socios();	
	// CLASES AMIGAS
	friend class ventana_libros_pendientes_socio;
	
};

#endif

