///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_socio.h
// Propósito:   Agregar un nuevo socio a la base de datos del programa.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// que provee una interfaz para agregar un nuevo socio a la base del programa.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_AGREGAR_SOCIO_H
#define VENTANA_AGREGAR_SOCIO_H

#include "Ventanas.h"
#include "Core\programa.h"
#include "Core\personas.h"
#include <string>
using namespace std;

///////////////////////////////////////////////////////////////////////////////

class ventana_agregar_socio : public vAgregarSocio {

protected:
	void fecha_ingreso_actual( wxCommandEvent &_event ) ;
	void fecha_ingreso_manual( wxCommandEvent &_event ) ;
	void click_boton_explorar( wxCommandEvent &_event ) ;
	void click_aceptar( wxCommandEvent &_event ) ;
	void click_cancelar( wxCommandEvent &_event ) ;
	void redibujar_ventana();
	bool copiar_imagen( const string &_fuente );
	
protected:
	int pos;
	Programa *anterior;
	socio nuevo;
	
public:
	ventana_agregar_socio( wxWindow *_parent,
	                       const int &_pos = -1 );
	~ventana_agregar_socio();
	
};

#endif

