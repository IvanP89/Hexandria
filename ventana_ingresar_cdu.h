///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_ingresar_cdu.h
// Propósito:   Añadir el código CDU al agregar un nuevo libro al sistema.
// Autor:       Iván Pizarro.
//
// Esta clase es llamada por "ventana_agregar_libro" para establecer el código
// de clasificación para un nuevo libro cargado al sistema.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_INGRESAR_CDU_H
#define VENTANA_INGRESAR_CDU_H
#include "Ventanas.h"
#include "ventana_agregar_libro.h"

///////////////////////////////////////////////////////////////////////////////

class ventana_agregar_libro;

class ventana_ingresar_cdu : public vIngresarCDU {

protected:
	void principal_elegido( wxCommandEvent &_event );
	void sub_1_elegido( wxCommandEvent &_event );
	void sub_2_elegido( wxCommandEvent &_event );
	void click_boton_aceptar( wxCommandEvent &_event );
	void click_boton_cancelar( wxCommandEvent &_event );
	
protected:
	ventana_agregar_libro *anterior;
	bool elec_1_hecha;
	bool elec_2_hecha;
	bool elec_3_hecha;
	
public:
	ventana_ingresar_cdu( wxWindow *_parent, ventana_agregar_libro *_anterior );
	~ventana_ingresar_cdu();
};

#endif

