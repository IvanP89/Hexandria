///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_info_libro.h
// Propósito:   Ver información detallada sobre un libro.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// mediante la cual se puede observar en detalle la información sobre un libro
// determinado.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_INFO_LIBRO_H
#define VENTANA_INFO_LIBRO_H

#include "Ventanas.h"

#include "Core\programa.h"
#include "Core\bibliografia.h"

///////////////////////////////////////////////////////////////////////////////

class ventana_info_libro : public vInfoLibro {

protected:
	void click_boton_historial( wxCommandEvent &_event ) ;
	void click_boton_ir( wxCommandEvent &_event );
	void click_boton_cerrar( wxCommandEvent &_event );
	
protected:
	bool carga_desde_historial;
	
public:
	ventana_info_libro( wxWindow *_parent, const unsigned int &_pos, bool parent_es_infosocio = false );
	ventana_info_libro( wxWindow *_parent, const libro &_lib );
	~ventana_info_libro();
	
};

#endif

