///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_bibliotecario.h
// Propósito:   Agregar un nuevo bibliotecario a la base de datos del programa.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// que provee una interfaz para agregar un nuevo bibliotecario.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_AGREGAR_BIBLIOTECARIO_H
#define VENTANA_AGREGAR_BIBLIOTECARIO_H

#include "Ventanas.h"
#include "ventana_agregar_curriculum.h"
#include "ventana_agregar_usuario.h"

#include "Core\personas.h"
#include "Core\programa.h"

///////////////////////////////////////////////////////////////////////////////

class ventana_agregar_bibliotecario : public vAgregarBibliotecario {

protected:
	void fecha_ingreso_actual( wxCommandEvent &_event );
	void fecha_ingreso_manual( wxCommandEvent &_event );
	void click_boton_explorar( wxCommandEvent &_event );
	void click_boton_cargar_cur( wxCommandEvent &_event );
	void click_boton_generar_cuenta( wxCommandEvent &_event );
	void click_aceptar( wxCommandEvent &_event );
	void click_cancelar( wxCommandEvent &_event );
	void redibujar_ventana();
	bool copiar_imagen( const string &_fuente );
	
protected:
	int pos;
	Programa *programa;
	bibliotecario nuevo;
	
public:
	ventana_agregar_bibliotecario( wxWindow *_parent, const int &_pos = -1 );
	~ventana_agregar_bibliotecario();
	friend class ventana_agregar_curriculum;
	friend class ventana_agregar_usuario;
	
};

#endif

