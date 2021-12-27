///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_libro.h
// Propósito:   Interfaz de la base de datos de los socios.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// mediante la cual se agregar nuevos libros a la base de datos y se editan los
// existentes.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_AGREGAR_LIBRO_H
#define VENTANA_AGREGAR_LIBRO_H

#include "Ventanas.h"
#include "Core\programa.h"
#include "Core\bibliografia.h"
#include <vector>
#include "ventana_autores.h"
#include "ventana_ingresar_cdu.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////

class ventana_agregar_libro : public vAgregarLibro {

protected:
	void click_boton_agregar_autores( wxCommandEvent &_event ) ;
	void click_boton_borrar_autores( wxCommandEvent &_event ) ;
	void click_boton_ir( wxCommandEvent &_event ) ;
	void click_boton_cdu( wxCommandEvent &_event ) ;
	void click_boton_aceptar( wxCommandEvent &_event ) ;
	void click_boton_cancelar( wxCommandEvent &_event ) ;
	
protected:
	Programa *anterior;
	autores_database *se_agrego_autor;
	int pos;
	libro nuevo;
	
public:
	ventana_agregar_libro( wxWindow *_parent,
	                       const int &_pos = -1 );
	~ventana_agregar_libro();
	void guardar_datos_libro( libro *_lib = NULL );
	friend class ventana_autores;
	friend class ventana_ingresar_cdu;
	
};

#endif

